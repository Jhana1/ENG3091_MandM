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

enum State {
    S_START = 0,
    S_LEAVE_BASE,
    S_LEFT_BASE,
    S_FIND_PUCK,
    S_GO_HOME,
    S_FACE_HOME,
    S_GOT_HOME,
    S_IN_CORNER,
    S_GOING_HOME_INVALID_IR,
    S_GOING_HOME_CENTER_IR,
    S_GOING_HOME_LEFT_IR,
    S_GOING_HOME_RIGHT_IR,
    S_NEAR_HOME_FIND_100,
    S_NEAR_HOME_FIND_60,
    S_CENTERED_ON_BASE,
    S_PLACE_PUCK
};

int main()
{
    RED_Write(1);
    CYGlobalIntEnable;
    
    /**** INITIALIZE COMPONENTS ****/
    LCD_Start();
    USB_Start(0, USB_DWR_VDDD_OPERATION);
   
    //CyDelay(5000);
    //LCD_PosPrintString(0,0,"STARTING CAM");
    //init_camera();
    //LCD_PosPrintString(0,0, "CAMERA STARTED!!!");
    
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
    
    /*
    while (1){
        POS_PRINTF(0,0,"M %d R %d S %d", get_avg_mean_ultra(), get_mean_ultra(), get_mean_ultra_s());
        POS_PRINTF(1,0,"B %d", beam_broken());
        CyDelay(50);
    }*/
    
    calibrate_compass();
    /*
    while (1){
        LCD_ClearDisplay();
        POS_PRINTF(0,0,"F %d L %d", get_front_ir(), get_left_ir());
        POS_PRINTF(1,0,"U %d V %d", get_mean_ultra(), get_var_ultra());
        CyDelay(50);
    }*/
    /*
    while (1){
        if (compass_ready){
            compass_read();
        }
        print("%d %d\n", compass_x, compass_y);
    }*/

    /**** Declare Variables ****/
    
    uint16 ir_result;
    uint16 state;
    int pucks_gotten = 0;
    int near_base = 70;
    
    
    state = S_START;
   
    /*
    while (1){
        LCD_ClearDisplay();
        POS_PRINTF(0,0,"u%d i%d", get_mean_ultra(), get_front_ir());
        CyDelay(50);
    }*/
    
    pickup_puck();
    CyDelay(1000);
    while (1){
        switch(state){
            case S_START:
                arm_set_level(5);
                CyDelay(500);
                go_forward(400, 255);
                CyDelay(500);
                drop_puck();
                CyDelay(500);
                go_backward(700, 255);
                int i;
                for (i = 4; i >= 0; i--){
                    arm_set_level(i);
                    CyDelay(500);
                }
                state = S_LEAVE_BASE;
                break;
            case S_LEAVE_BASE:
                arm_set_level(0);
                go_backward_ultra(50, 255);
                state = S_LEFT_BASE;
                break;
            case S_LEFT_BASE:
                set_heading(180);
                rotate_degrees(0);
                CyDelay(1000);
                state = S_FIND_PUCK;
                break;
            case S_FIND_PUCK:
                go_forward(1000, 200);
                CyDelay(1000);
                if (beam_broken() || beam_broken()){
                    go_forward(750, 255);
                    pickup_puck();
                    CyDelay(100);
                    arm_carry_home();
                    pucks_gotten++;
                    state = S_FACE_HOME;
                }
                CyDelay(1000);
                break;
            case S_FACE_HOME:
                set_heading(0);
                rotate_degrees(0);
                CyDelay(1000);
                set_heading(45);
                rotate_degrees(0);
                go_forward(800, 255);
                CyDelay(1000);
                set_heading(300);
                rotate_degrees(0);
                go_forward(800, 255);
                set_heading(0);
                rotate_degrees(0);
                state = S_GO_HOME;
                break;
            case S_GO_HOME:
                select_front();
                CyDelay(500);
                ir_result = get_ir_val();
                LCD_ClearDisplay();
                POS_PRINTF(0,0,"IN GO HOME I:%d U%d", ir_result, get_mean_ultra());
                if (get_mean_ultra() < near_base){
                    state = S_NEAR_HOME_FIND_100;
                    break;
                }
                    
                
                if (ir_result < 10){//IR INVALID
                    POS_PRINTF(0,0,"I:%d < 10: fwd", ir_result);
                    //while (!but0_b){;}but0_b = 0;
                    //or look at variance of ir
                    state = S_GOING_HOME_INVALID_IR;
                    break;
                } else if (within_range(57, ir_result, 60)){
                    state = S_GOING_HOME_CENTER_IR;
                    break;
                } else if (within_range(80, ir_result, 100)){
                    state = S_GOING_HOME_LEFT_IR;
                    break;
                } else if (within_range(25, ir_result,30)){
                    state = S_GOING_HOME_RIGHT_IR;
                    break;
                } else {
                    POS_PRINTF(0,0,"!!! %d !!!", ir_result);
                    go_forward(500,255);
                }
                break;
            case S_GOING_HOME_CENTER_IR:
                POS_PRINTF(0,0,"CENTER IR GO HOME");
                //while (!but0_b){;}but0_b = 0;
                while (get_mean_ultra() > near_base){
                    go_forward(600, 255);
                    CyDelay(600);
                }
                state = S_NEAR_HOME_FIND_100;
                break;
            case S_GOING_HOME_INVALID_IR:
                POS_PRINTF(0,0,"INVALID IR GO HOME");
                //while (!but0_b){;}but0_b = 0;
                while (get_mean_ultra() > near_base){
                    go_forward(500, 255);
                    CyDelay(600);
                }
                state = S_NEAR_HOME_FIND_100;
                break;
            case S_GOING_HOME_LEFT_IR:
                set_heading(90);
                rotate_degrees(0);
                go_forward(1000, 255);
                set_heading(0);
                rotate_degrees(0);
                select_right();
                ir_result = get_ir_val();
                ///if (ir_result 
                while (get_mean_ultra() > near_base){
                    go_forward(500, 255);
                    CyDelay(600);
                }
                state = S_NEAR_HOME_FIND_100;
                break;
            case S_GOING_HOME_RIGHT_IR:
                set_heading(270);
                rotate_degrees(0);
                go_forward(1000, 255);
                set_heading(0);
                rotate_degrees(0);
                select_right();
                ir_result = get_ir_val();
                //DO SOMETHING WITH THAT...
                while (get_mean_ultra() > near_base){
                    go_forward(600, 255);
                    CyDelay(600);
                }
                state = S_NEAR_HOME_FIND_100;
                break;
            case S_NEAR_HOME_FIND_100:
                POS_PRINTF(0,0,"NEAR HOME FIND 100");
                //while (!but0_b){;}but0_b = 0;
                set_heading(270);
                rotate_degrees(0);
                CyDelay(1000);
                select_right();
                ir_result = get_ir_val();
                POS_PRINTF(1,0,"ir:%d", ir_result);
                //while (!but0_b){;}but0_b = 0;
                
                if (within_range(80, ir_result, 105)){
                    int i;
                    int good_val = 1;
                    for (i = 0; i < 3; i++){
                        CyDelay(500);
                        if (!within_range(80, get_ir_val(), 105)){
                            good_val = 0;
                            break;
                        }
                    }
                    if (good_val){
                        state = S_NEAR_HOME_FIND_60;
                    }
                    break;
                }
                go_forward(300, 255);
                break;
            case S_NEAR_HOME_FIND_60:
                POS_PRINTF(0,0,"NEAR HOME FIND 60");
                //while (!but0_b){;}but0_b = 0;
                CyDelay(1000);
                select_right();
                ir_result = get_ir_val();
                POS_PRINTF(1,0,"ir%d", ir_result);
                //while (!but0_b){;}but0_b = 0;
                if (within_range(57, ir_result, 65)){
                    set_heading(0);
                    rotate_degrees(0);
                    state = S_CENTERED_ON_BASE;
                    break;
                }
                go_backward(250, 255);
                break;
            case S_CENTERED_ON_BASE:
                POS_PRINTF(0,0,"CENTERED ON BASE");
                arm_set_level(4);
                while (get_avg_mean_ultra() > 15){
                    go_forward(300, 255);
                    CyDelay(500);
                }
                if (get_avg_mean_ultra() < 14){
                    go_backward(200, 255);
                }
                set_heading(90);
                rotate_degrees(0);
                
                state = S_PLACE_PUCK;
                break;
            case S_PLACE_PUCK:
                //FIRST PUCK EVER!
                if (pucks_gotten == 1){
                    go_forward(1500, 200);
                    drop_puck();
                    go_backward(2000, 255);
                } else {
                    arm_set_level(pucks_gotten + 1);
                    go_forward(500, 200);
                    int on_stack = 0;
                    while (!on_stack){
                        POS_PRINTF(0,0,"STACKING!");
                        POS_PRINTF(1, 0, "B%d SU%d", beam_broken(), get_mean_ultra_s());
                        if (beam_broken()){
                            on_stack = 1;
                        } else if (get_mean_ultra_s() < 10){
                            
                            go_backward(100, 255);
                        } else {
                            go_forward(200, 255);
                        }
                    }
                    go_backward(200, 255);
                    arm_inbetween_level(pucks_gotten - 1, pucks_gotten);
                    CyDelay(500);
                    drop_puck();
                    go_backward(2000, 255);
                    arm_carry_home();
                    arm_set_level(0);
                    CyDelay(500);
                }
                
                set_heading(0);
                rotate_degrees(0);
                go_backward(2000, 255);
                state = S_LEAVE_BASE;
                break;
                    
            case S_GOT_HOME:
                POS_PRINTF(0,0,"GOT HOME");
                while (!but0_b){;}but0_b = 0;
                break;
        }
        
        /*
        LCD_ClearDisplay();
        sprintf(outString, "u %d ic %d", ultra_distance, ir_result);
        LCD_PosPrintString(0,0,outString);
        sprintf(outString, "s%d c%d vu %d", state, compass_heading, get_var_ultra());
        LCD_PosPrintString(1,0,outString);
        CyDelay(50);*/
    }
}

void calibrate_compass()
{
    char outString[25];
    double avx = 0,avy = 0;
    int trials = 1000;
    short xHIGH, xLOW, yHIGH, yLOW;
    int i;
    rotate_left(130);
    for(i = 0; i < trials; i++)
    {
        while(!compass_ready){}
        compass_read();
        avx += compass_x/((double) trials);
        avy += compass_y/((double) trials);
        LCD_ClearDisplay();
        POS_PRINTF(0,0,"X:%d Y:%d",(int) round(avx),(int) round(avy));
        POS_PRINTF(1,0,"C:%d/%d",i,(int) round(trials));
    }
    setCoast(MBOTH);
    int x = round(avx);
    int y = round(avy);
    xHIGH = x >> 8;
    xLOW = x & 0xFF;
    yHIGH = y >> 8;
    yLOW = y & 0xFF;
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