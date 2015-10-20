/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/* TODO ***
 * GET ALL THE COLORS
 * Work on reading instructions
 * Put the beacon at the beginning 
 * Improve search strategy
 * Make it run around faster
 * Check the compass orientations
 * Fix magnet
 * Check second ultrasonic
 * Corner handling
 * Collision handling
 * Timeouts
 * Counter for homing on puck
 */


#include <project.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

#include <infrared.h>
#include <motor.h>
#include <buttons.h>
#include <compass.h>
#include <ultrasonic.h>
#include <ultrasonic_s.h>

#include <gripper.h>
#include <arm.h>
#include <my_camera_functions.h>
#include <blob_stats.h>
#include <beam.h>

extern blob blobs[255];
//motor.c
extern uint8 HEADING_ERROR_LIMIT;
extern uint8 STALL_SPEED;
//these are in button.c
extern volatile uint8 but0_b;
extern volatile uint8 but1_b;

//These are in compass.c
extern int16 compass_x;
extern int16 compass_y;
extern int16 compass_z;
extern int16 compass_heading;
extern volatile uint8 compass_ready;
extern int16 original_compass_heading; //We set this to make the angles relative

//This is in ultrasonic.c
extern volatile uint16 ultra_distance;

char outString[25];
void calibrate_compass();

#define POS_PRINTF(R,C,X,...) \
 {sprintf(outString, X, ##__VA_ARGS__); LCD_Position(R, C); LCD_PrintString(outString);}


// print() function, works like snprintf(). See: http://www.cplusplus.com/reference/cstdio/snprintf/
void print(const char *fmt, ...)
{
   if(!USB_GetConfiguration()) return;  // Do nothing if the USB cable is not connected.
   char buffer[64];
   va_list args;
   va_start(args, fmt);
   vsnprintf(buffer, sizeof(buffer), fmt, args);
   va_end(args);
   while(!USB_CDCIsReady());
   USB_PutString(buffer);
}

int within_range(int lower, int val, int upper){
    return val >= lower && val <= upper;
}

#define NP_AHEAD 0
#define NP_TURNED_RIGHT 1
#define NP_TURNED_LEFT 2

enum State {
    S_START = 0,
    S_LEAVE_BASE,
    S_LEFT_BASE,
    S_FIND_PUCK,
    S_GO_HOME,
    S_FACE_HOME,
    S_GOT_HOME,
    S_IN_CORNER,
    S_GOING_HOME_CHECK_IR,
    S_NEAR_HOME_FIND_100,
    S_NEAR_HOME_FIND_60,
    S_CENTERED_ON_BASE,
    S_PLACE_PUCK,
    S_NEAR_HOME_SAW_30,
    S_GRAB_BEACON
};

int main()
{
    RED_Write(1);
    CYGlobalIntEnable;
    
    /**** INITIALIZE COMPONENTS ****/
    LCD_Start();
    //USB_Start(0, USB_DWR_VDDD_OPERATION);
        
    Timer_Start();
    start_buttons();
    start_compass();
    while (!compass_ready){;}
    compass_read();
    original_compass_heading = compass_heading;
    
    start_motors();
    start_gripper();
    drop_puck();
    start_arm();
    arm_set_level(0);
    start_ultrasonic();
    start_ultrasonic_s();
    start_infrared();
    beam_broken();
    
    //calibrate_compass();
    /*
    while (1){
        if (compass_ready){
            compass_read();
            print("%d %d\n", compass_x, compass_y);
            POS_PRINTF(0,0,"%d %d %d", compass_heading, compass_x, compass_y);
        }
    }*/
    

    //calibrate_compass();
    
    /*
    int arm_height = 1;
    while (1){
        LCD_ClearDisplay();
        POS_PRINTF(0,0,"R %d S %d", get_mean_ultra(), get_mean_ultra_s());
        POS_PRINTF(1,0,"B %d P %d", beam_broken(), arm_height);
        if (but0_b){
            but0_b = 0;
            if (arm_height){
                select_left();
            } else {
                select_stack();
            }
        } else if (but1_b){
            but1_b = 0;
        }
        CyDelay(50);   
    }*/
    
    
//    while (1){
//        LCD_ClearDisplay();
//        POS_PRINTF(0,0,"US %d LS %d", get_mean_ultra_s(), get_var_ultra_s());
//        POS_PRINTF(1,0," %d V %d", get_mean_ultra(), get_var_ultra());
//        CyDelay(50);
//    }

    /**** Declare Variables ****/
    
    uint16 ir_result;
    uint16 state;
    int pucks_gotten = 0;
    int near_base = 70;
    int current_color = RED;
    long start_time_find100;
    long start_time_find_puck;
    int twitching_l = 0;
    int twitching_r = 0;
    state = S_START;
    int h_left = 0; 
    int ultra;
    /*
    int abc = 0;
    while (1){
        LCD_ClearDisplay();
        POS_PRINTF(0,0,"ur%d", get_mean_ultra());
        POS_PRINTF(1,0,"ul%d", get_mean_ultra_s());
        if (but0_b){
            if (abc){
                select_left();
                stop_ultrasonic();
                abc = 0;
            } else {
                start_ultrasonic();
                select_stack();
                abc = 1;
            }
            but0_b = 0;
        }
        CyDelay(50);
    }*/
    

    
    while (1){
        if (but0_b){
            if (state > S_FIND_PUCK){
                pucks_gotten--;
            }
            state = S_LEAVE_BASE;
            POS_PRINTF(0,0,"RST TO LEAVE BASE");
            but0_b = 0;
        
            while (!but0_b){;}
            but0_b = 0;
        }
        
        switch(state){
            case S_START:
                pickup_angled_puck();
                CyDelay(1000);
                go_backward(250, 255);
                arm_set_level(6);
                CyDelay(1000);
                setForward(MBOTH);
                setSpeed(MBOTH, 200);
                CyDelay(1000);
                setCoast(MBOTH);
                pickup_puck();
                CyDelay(500);
                drop_puck();
                CyDelay(500);
                go_backward_blind(280, 180);
                POS_PRINTF(0,0,"DROPPED BEACON");
                int i;
                arm_set_level(1);
                CyDelay(500);
                LCD_PosPrintString(0,0,"STARTING CAM");
                init_camera();
                LCD_PosPrintString(0,0, "CAMERA STARTED!!!");
                //arm_inbetween_level(0,1);
                arm_set_level(0);
                CyDelay(500);
                set_gain_exposure(2);
                capture_thresh_image();
                sideways_instruction_read();
                set_gain_exposure(1);
                POS_PRINTF(0,0,"Read Instructions");
                POS_PRINTF(1,0,"%d %d %d %d", stack[3], stack[2], stack[1], stack[0]);
                CyDelay(1000);
                state = S_LEAVE_BASE;
                break;
                
            case S_LEAVE_BASE:
                arm_set_level(0);
                go_backward_ultra(60, 255);
                state = S_LEFT_BASE;
                current_color = stack[(4 - pucks_gotten) - 1];
                if (current_color == 0){
                    current_color = RED;
                } else if (current_color == 839192){
                    current_color = RED;
                }
                STALL_SPEED = ARENA_STALL_SPEED;
                break;
                
            case S_LEFT_BASE:
                set_heading(90);
                rotate_degrees(0);
                CyDelay(500);
                go_backward(1200, 255);
                CyDelay(500);
                //Give the rotation a kick in the right direction
                rotate_right(255);
                CyDelay(300);
                setCoast(MBOTH);
                set_heading(180);
                rotate_degrees(0);
                CyDelay(500);
                start_time_find_puck = Timer_ReadCounter();
                state = S_FIND_PUCK;
                twitching_l = 0;
                twitching_r =0;
                break;
                
            case S_FIND_PUCK:
                POS_PRINTF(1,0,"FIND %d of %d", current_color, pucks_gotten);
                if (start_time_find_puck - Timer_ReadCounter() > 10 * 35000){
                    set_heading(180);
                    go_backward_blind(1000, 255);
                    CyDelay(100);
                    set_heading(0);
                    while (get_mean_ultra() > 80){
                        go_forward(700, 255);
                        CyDelay(300);
                    }
                    set_heading(180);
                    rotate_degrees(0);
                    start_time_find_puck = Timer_ReadCounter();
                }
                CyDelay(300);
                capture_thresh_image();
                int pucks = to_nearest_blob(current_color, 30, 10);
                
                if (pucks == 0){
                    h_left = 0;
                    twitching_r = 0;
                    twitching_l = 0;
                    //A puck is centered, so we check our beam break and drive forward a bit.
                    go_forward(1000, 255);
                    pickup_angled_puck();
                    CyDelay(200);
                    drop_puck();
                    CyDelay(200);
                    if (beam_broken()){
                        go_forward(300, 255);
                        pickup_puck();
                        CyDelay(100);
                        
                        arm_carry_home();
                        
                        arm_set_level(0);
                        CyDelay(300);
                        set_gain_exposure(2);
                        capture_thresh_image();
                        int color = identify_colour_gripper();
                        set_gain_exposure(1);
                        POS_PRINTF(0,0,"SEE C: %d", color);
                        if (color != current_color){
                            int old_heading = compass_heading;
                            rotate_degrees(45);
                            go_forward(500, 255);
                            drop_puck();
                            go_backward(500, 255);
                            arm_set_level(0);
                            CyDelay(100);
                            set_heading(old_heading);
                            rotate_degrees(0);
                        } else {
                            arm_carry_home();
                            set_heading(180);
                            rotate_degrees(0);
                            go_backward(1500, 255);
                            pucks_gotten++;
                            start_time_find_puck = Timer_ReadCounter();
                            state = S_FACE_HOME;
                            break;
                        }
                    }                
                } else if (pucks == -1){
                    twitching_l = 0;
                    twitching_r = 0;
                    if(h_left == 0)
                    {
                        h_left = 1;
                        rotate_degrees(25);
                    }
                    else if(h_left == 1)
                    {
                        h_left = 2;
                        rotate_degrees(-50);
                    }
                    else
                    {
                        h_left = 0;
                        set_heading(180);
                        rotate_degrees(0);
                        go_forward(800,250);
                    }
                } else if (pucks < 0){
                    if (twitching_l >= 2 && twitching_r > 2){
                        twitching_r = 0;
                        twitching_l = 0;
                        go_forward(500, 255);
                    } else {
                        rotate_degrees(-4);
                        twitching_l++;
                    }
                } else if (pucks > 0){
                    if (twitching_l >= 2 && twitching_r >= 2){
                        twitching_r = 0;
                        twitching_l = 0;
                        go_forward_blind(600, 255);
                    } else {
                        rotate_degrees(4);
                        twitching_r++;
                    }
                } 
                break;
            case S_FACE_HOME:
                //Shake off any extra pucks
                set_heading(90);
                rotate_degrees(0);
                set_heading(0);
                rotate_degrees(0);
                state = S_GO_HOME;
                break;
            case S_GO_HOME:
                select_front();
                CyDelay(300);
                ir_result = get_ir_val();
                LCD_ClearDisplay();
                POS_PRINTF(0,0,"IN GO HOME I:%d U%d", ir_result, get_mean_ultra());
                //!!!!!!!!!!!
                //!!!!!!!!!!! CHECK AGAIN TO MAKE SURE IT WASNT JUST A PUCK BLOCKING the US
                //!!!!!!!!!!!
                if (get_mean_ultra() < near_base){
                    start_time_find100 = Timer_ReadCounter();
                    state = S_NEAR_HOME_FIND_100;
                    break;
                } else {
                    state = S_GOING_HOME_CHECK_IR;
                }
                break;
            case S_GOING_HOME_CHECK_IR:
                POS_PRINTF(0,0,"GOING HOME CHECK IR");
                ultra = get_mean_ultra(); 
                if (ultra <= near_base){
                    state = S_NEAR_HOME_FIND_100;
                    start_time_find100 = Timer_ReadCounter();
                }
                
                if (ultra > near_base + 20){
                    go_forward(1000,255);
                } else {
                    go_forward(400, 255);
                }
                CyDelay(300);                
                break;
            case S_NEAR_HOME_FIND_100:
                if (start_time_find100 - Timer_ReadCounter() >  10 * 25000){//We must be too far left...
                    POS_PRINTF(1,0,"TIMEOUT 100!!!");
                    set_heading(90);
                    rotate_degrees(0);
                    go_backward(4000, 255);
                    start_time_find100 = Timer_ReadCounter();
                }
                
                POS_PRINTF(0,0,"NEAR HOME FIND 100");
                POS_PRINTF(1,0,"First Turn");
                set_heading(88);
                rotate_degrees(0);
                CyDelay(300);
                
                go_forward(300, 255);
                
                select_right();
                ir_result = get_ir_val();
                POS_PRINTF(1,0,"i %d", ir_result);
                POS_PRINTF(1,5,"t %ld", Timer_ReadCounter());
                //while (!but0_b){;}but0_b = 0;
                int good_val = 0;
                if (within_range(96, ir_result, 105)){
                    int i;
                    good_val = 1;
                    for (i = 0; i < 3; i++){
                        CyDelay(300);
                        if (!within_range(96, get_ir_val(), 105)){
                            good_val = 0;
                            break;
                        }
                    }
                    if (good_val){
                        state = S_NEAR_HOME_FIND_60;
                        break;
                    }
                }
                select_left();
                POS_PRINTF(0,0,"RIGHT ULTRA");
                CyDelay(100);
                ultra = get_mean_ultra_s();
                POS_PRINTF(1,0,"%d - %d", ultra, near_base);
                if (ultra > near_base && get_var_ultra_s() < 200){
                    go_forward(300, 255);
                    POS_PRINTF(1,0,"Turn 2 Possible");
                    rotate_right(255);
                    CyDelay(200);
                    setCoast(MBOTH);
                    set_heading(0);
                    rotate_degrees(0);
                    
                    CyDelay(600);
                    ultra = get_mean_ultra();
                    
                    if (ultra > near_base){
                        go_forward(500, 255);
                    }
                    CyDelay(600);
                    ultra = get_mean_ultra();
                    while (ultra > near_base){
                        POS_PRINTF(1,0,"CU: %d", ultra);
                        go_forward(700, 255);
                        CyDelay(300);
                        ultra = get_mean_ultra();
                    } 
                    POS_PRINTF(1,0,"Turn 3 Possible");
                    rotate_left(255);
                    CyDelay(200);
                    set_heading(90);
                    rotate_degrees(0);
                    start_time_find100 = Timer_ReadCounter();   
                }
                break;
                
            case S_NEAR_HOME_SAW_30:
                POS_PRINTF(0,0,"NEAR HOME SAW 30");
                CyDelay(300);
                select_right();
                ir_result = get_ir_val();
                POS_PRINTF(1,0,"ir%d", ir_result);
                
                if (within_range(57, ir_result, 65)){
                    go_forward(500, 255);
                    set_heading(0);
                    rotate_degrees(0);
                    state = S_CENTERED_ON_BASE;
                    start_ultrasonic();
                    break;
                }
                go_forward(250, 255);
                break;
                
            case S_NEAR_HOME_FIND_60:
                POS_PRINTF(0,0,"NEAR HOME FIND 60");
                //while (!but0_b){;}but0_b = 0;
                CyDelay(500);
                select_right();
                ir_result = get_ir_val();
                POS_PRINTF(1,0,"ir%d", ir_result);
                //while (!but0_b){;}but0_b = 0;
                if (within_range(57, ir_result, 65)){
                    set_heading(0);
                    rotate_degrees(0);
                    state = S_CENTERED_ON_BASE;
                    start_ultrasonic();
                    break;
                } else if (within_range(27, ir_result, 33)){
                    CyDelay(300);
                    ir_result = get_ir_val();
                    CyDelay(300);
                    if (within_range(27, ir_result, 33) && within_range(27,get_ir_val(),33)){
                        state = S_NEAR_HOME_SAW_30;
                    }
                    break;
                }
                go_backward(250, 255);
                break;
                
            case S_CENTERED_ON_BASE:
                select_stack();
                POS_PRINTF(0,0,"CENTERED ON BASE");
                HEADING_ERROR_LIMIT = 1;
                CyDelay(200);
                arm_set_level(0);
                CyDelay(200);
                drop_puck();
                go_forward_blind(200, 220);
                pickup_puck();
                CyDelay(200);
                arm_inbetween_level(1,2);
                while (get_mean_ultra() > 24){
                    go_forward(400, 255);
                    rotate_degrees(0);
                    CyDelay(300);
                }
                ultra = get_mean_ultra();
                int stackable = 0;
                while (!within_range(15,ultra,16) && !stackable){
                    ultra = get_mean_ultra();
                    POS_PRINTF(1,0,"ULTRA: %d", ultra);
                    if (ultra > 16){
                        go_forward(200, 255);
                        rotate_degrees(0);
                        CyDelay(300);
                    } else if (ultra < 15){
                        go_backward(150,255);
                        rotate_degrees(0);
                        CyDelay(300);
                    } else if (ultra == 15){
                        stackable = 1;
                    }
                }
                
                STALL_SPEED = BASE_STALL_SPEED;
                
                rotate_left(200);
                CyDelay(400);
                
                set_heading(271);
                rotate_degrees(0);
                
                state = S_PLACE_PUCK;
                break;
                
            case S_PLACE_PUCK:
                POS_PRINTF(0,0,"PLACING PUCK");
                //FIRST PUCK EVER!
                arm_set_level(4);
                
                if (pucks_gotten == 1){
                    for (i = 0; i < 3; i++){
                        go_forward_blind(300, 210);
                        //rotate_degrees(0);
                        CyDelay(600);   
                    }
                    CyDelay(300);
                    arm_inbetween_level(0,1);
                    CyDelay(300);
                    drop_puck();
                    CyDelay(200);
                    go_backward(1200, 255);
                } else {
                    arm_set_level(pucks_gotten + 1);
                    go_forward_blind(300, 200);
                    //rotate_degrees(0);
                    int on_stack = 0;
                    while (!on_stack){
                        POS_PRINTF(0,0,"STACKING!");
                        POS_PRINTF(1, 0, "B%d SU%d", beam_broken(), get_mean_ultra_s());
                        if (beam_broken()){
                            POS_PRINTF(0,0,"BEAM BROKEN");
                            on_stack = 1;
                        } else if (get_mean_ultra_s() < 12){
                            POS_PRINTF(0,0,"Close to stack");
                            go_backward_blind(160, 170);
                            //rotate_degrees(0);
                            on_stack = 1;
                        } else if (get_mean_ultra_s() > 17) {
                            POS_PRINTF(0,0,"FAR FROM STACK");
                            go_forward_blind(160, 170);
                            //rotate_degrees(0);
                        } else {
                            POS_PRINTF(0,0,"between 12 and 17");
                            go_forward_blind(160, 170);
                            //rotate_degrees(0);
                        }
                        CyDelay(300);
                    }
                    
                    #define LEVEL_1_DIST 14
                    #define LEVEL_2_DIST 15
                    #define LEVEL_3_DIST 16
                    
                    int ultra = get_mean_ultra_s();
                    int stackable = 0;
                    switch (pucks_gotten){
                        case 2:
                            while (!within_range(LEVEL_1_DIST,ultra,LEVEL_1_DIST + 1) && !stackable){
                                ultra = get_mean_ultra_s();
                                POS_PRINTF(1,0,"ULTRA: %d", ultra);
                                if (ultra > LEVEL_1_DIST + 1){
                                    go_forward_blind(160, 160);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra < LEVEL_1_DIST){
                                    go_backward_blind(150,160);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra == LEVEL_1_DIST){
                                    stackable = 1;
                                }
                            }
                            break;   
                        case 3:
                            while (!within_range(LEVEL_2_DIST,ultra,LEVEL_2_DIST+1) && !stackable){
                                ultra = get_mean_ultra_s();
                                POS_PRINTF(1,0,"ULTRA: %d", ultra);
                                if (ultra > LEVEL_2_DIST + 1){
                                    go_forward_blind(160, 160);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra < LEVEL_2_DIST){
                                    go_backward_blind(150,160);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra == LEVEL_2_DIST){
                                    stackable = 1;
                                }
                            }
                            break;
                        case 4:
                            while (!within_range(LEVEL_3_DIST,ultra,LEVEL_3_DIST+10) && !stackable){
                                ultra = get_mean_ultra_s();
                                POS_PRINTF(1,0,"ULTRA: %d", ultra);
                                if (ultra > LEVEL_3_DIST + 1){
                                    go_forward_blind(200, 170);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra < LEVEL_3_DIST){
                                    go_backward_blind(200,170);
                                    //rotate_degrees(0);
                                    CyDelay(300);
                                } else if (ultra == LEVEL_3_DIST){
                                    stackable = 1;
                                }
                            }
                            break;
                    }
                    arm_inbetween_level(pucks_gotten - 1, pucks_gotten);
                    CyDelay(800);
                    drop_puck();
                    CyDelay(200);
                    go_backward(1200, 255);
                    arm_carry_home();
                    arm_set_level(0);
                    CyDelay(200);
                }
                
                HEADING_ERROR_LIMIT = 3;
                set_heading(0);
                rotate_degrees(0);
                go_backward(1500, 255);
                
                if (pucks_gotten == 4){
                    state = S_GRAB_BEACON;
                } else {
                    state = S_LEAVE_BASE;
                }
                break;
            case S_GRAB_BEACON:
                POS_PRINTF(0,0,"GOT HOME");
                set_heading(0);
                rotate_degrees(0);
                arm_set_level(6);
                go_forward(500, 255);
                CyDelay(500);
                pickup_angled_puck();
                go_backward(300, 255);
                break;
            case S_GOT_HOME:
                POS_PRINTF(0,0,"VICTORY!!!");
                break;
        }
    }
}

void calibrate_compass()
{
    char outString[25];
    float avx = 0,avy = 0;
    int trials = 2000;
    int32 x = 0,y = 0;
    int i;
    rotate_left(130);
    for(i = 0; i < trials; i++)
    {
        while(!compass_ready){}
        compass_read();
        x += compass_x;
        y += compass_y;
        LCD_ClearDisplay();
        //POS_PRINTF(0,0,"X:%ld Y:%ld",(int) round(avx),(int) round(avy));
        //POS_PRINTF(1,0,"C:%ld/%ld",i,(int) round(trials));
        POS_PRINTF(0,0,"X:%ld Y:%ld",x/i,y/i);
        POS_PRINTF(1,0,"T:%ld/%ld",i,trials);
    }
    setCoast(MBOTH);
    avx = x/(1.0);
    avy = y/(1.0);
    x = round(avx);
    y = round(avy);
    //EEPROM1_Write(&xHIGH,0);
    //EEPROM1_Write(&xLOW,1);
    //EEPROM1_Write(&yHIGH,2);
    //EEPROM1_Write(&yLOW,3);
    sprintf(outString,"X:%d Y:%d",x,y); 
    LCD_PosPrintString(0,0,outString);
    while(1)
    {
    }
}