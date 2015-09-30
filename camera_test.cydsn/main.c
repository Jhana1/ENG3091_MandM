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

#include <mice.h>
#include <mouse_a.h>
#include <mouse_b.h>
#include <motor.h>
#include <navigation.h>
#include <buttons.h>
#include <compass.h>
#include <ultrasonic.h>
#include <ultrasonic2.h>
#include <gripper.h>
#include <arm.h>
#include <my_camera_functions.h>
#include <blob_stats.h>

//this is in navigation.c
extern struct Position location;

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

//This is in motor.c
extern int16 desired_heading;
extern int32 desired_distance;
extern int32 delta_y_distance;

//This is in ultrasonic.c
extern volatile uint16 ultra_distance;
//This is in ultrasonic_2.c
extern volatile uint16 ultra_distance_2;

#define S_READ_INSTRUCTIONS 0
#define S_LEAVE_BASE 1
#define S_FACE_CORRECT_DIR 2
#define S_GET_PUCK 3
#define S_GOT_PUCK 4
#define S_FACE_HOME 5
#define S_GO_HOME 6
#define S_GOT_HOME 7
#define S_DROP_OFF_IN_WORKSPACE 8
#define S_HOLDING_PATTERN 9
#define S_GO_HOME_WITHOUT_PUCK_ROTATE 10
#define S_GO_HOME_WITHOUT_PUCK 11

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

int main()
{
    CyDelay(3000);
    char display[2][30];
    /* ** INITIALIZE COMPONENTS ** */
    LCD_Start();
    Timer_Start();
    //USB_Start(0, USB_DWR_VDDD_OPERATION);
    //give camera time to boot up
    
    start_buttons();
    start_motors();
    calculate_circular_functions();
    start_mice();
    start_navigation();
    start_ultrasonic();
    start_ultrasonic_2();
    start_compass();
    start_gripper();
    start_arm();
    
    LCD_PosPrintString(0,0,"Arm Started");
    
    init_camera();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Camera Started");
    
    BLUE_Write(1); //For some bizarre reason the blue led is inverted.??
    
    /* ** DECLARE VARIABLES ** */
    char outString[16];  // String to hold the ascii result
    uint32 time;
    uint32 got_home_time;
    uint32 start_finding_time;
    uint32 rotate_begin_time;
    extern volatile int32 loc_y_a;
    extern volatile int32 loc_y_b;
    int stack[3];
    char RGB[] = {'K','R','G','B'};
    int i;
    CyGlobalIntEnable;
    
    
    /* INFINITE LOOP */
    //Wait for compass to be ready for reading
    
    CyDelay(1000);
    compass_read();
    original_compass_heading = compass_heading;
    setHeading(0);
    
    LCD_PosPrintString(0,0,"STRATING!!!");
    
    int state = S_READ_INSTRUCTIONS;
    int puck_heading = 0;
    int puck_plan[3] = {RED, GREEN, BLUE};
    int color_looking_for = RED;
    int count = 0;
    int num_pucks = 0;
    int cant_see_puck_forward = 0;
    int cant_see_puck_left = 0;
    int cant_see_puck_right = 0;
    for(;;)
    {   
        
        
        RED_Write(1);
        
        //Update current time
        time = Timer_ReadCounter();
        //Read the compass when it is ready for reading
        if (compass_ready){
            compass_read();
            compass_ready = 0;
            //print("%d %d %d\n", compass_x, compass_y, compass_z);
        }
        
        //Update the current position
        update_position();
        
        //Execute any motor control
        control_motors();
        
        if (!isRotating() && !isDriving()){
            switch( state) {
                case S_READ_INSTRUCTIONS:
                    RED_Write(1);
                    BLUE_Write(0);
                    set_gain_exposure(1);
                    //capture_thresh_image();
                    //CyDelay(500);
                    //capture_thresh_image();
                    ///color_looking_for = nth_blob_colour(0);
                    color_looking_for = puck_plan[num_pucks];
                    if (color_looking_for == RED){
                        LCD_PosPrintString(0,0,"RED!!!");
                    } else if (color_looking_for == BLUE){
                        LCD_PosPrintString(0,0,"BLUE!!!");
                    } else if (color_looking_for == GREEN){
                        LCD_PosPrintString(0,0,"GREEN!!!");
                    }  else {
                        LCD_PosPrintString(0,0,"NOTHING");
                    }
                    CyDelay(500);
                    state = S_LEAVE_BASE;
                    break;
                case S_LEAVE_BASE:
                    setReverse(MBOTH);
                    setSpeed(MBOTH, 255);
                    CyDelay(600);
                    setCoast(MBOTH);
                    state = S_FACE_CORRECT_DIR;
                    break;
                case S_FACE_CORRECT_DIR:
                    setHeading(180);
                    state = S_GET_PUCK;
                    start_finding_time = time;
                    break;
                case S_GET_PUCK:
                    if (start_finding_time - time > 400000){
                        //sprintf(outString, "%lu", time);
                        //LCD_PosPrintString(0,0,outString);
                        //sprintf(outString, "%lu", start_finding_time - time);
                        //LCD_PosPrintString(1,0,outString);
                        //CyDelay(5000);
                        state = S_GO_HOME_WITHOUT_PUCK_ROTATE;
                        break;
                    }
                    CyDelay(500);
                    capture_thresh_image();
                    puck_heading = to_nearest_blob(color_looking_for, 30, 12);
                    if (puck_heading < -3){
                        rotate_left(100);
                        CyDelay(200);
                        setCoast(MBOTH);
                        CyDelay(100);
                        compass_read();
                        loc_y_a = 0;
                        loc_y_b = 0; //Cancel out the extra motion caused by rotation
                        setHeading(compass_heading);
                    } else if (puck_heading > 3){
                        rotate_right(100);
                        CyDelay(200);
                        setCoast(MBOTH);
                        CyDelay(100);
                        compass_read();
                        loc_y_a = 0;
                        loc_y_b = 0; //Cancel out the extra motion caused by rotation
                        setHeading(compass_heading);
                    } else if (puck_heading == -1) {
                        if (cant_see_puck_forward++ < 3){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 150);
                            CyDelay(500);
                            update_position();
                            setCoast(MBOTH);
                        } else if (cant_see_puck_left != 1){
                            rotate_left(100);
                            CyDelay(200);
                            setCoast(MBOTH);
                            CyDelay(100);
                            compass_read();
                            loc_y_a = 0;
                            loc_y_b = 0; //Cancel out the extra motion caused by rotation
                            setHeading(compass_heading);
                            cant_see_puck_left = 1;
                        } else if (cant_see_puck_right != 1){
                            rotate_right(100);
                            CyDelay(300);
                            setCoast(MBOTH);
                            CyDelay(100);
                            compass_read();
                            loc_y_a = 0;
                            loc_y_b = 0; //Cancel out the extra motion caused by rotation
                            setHeading(compass_heading);
                            cant_see_puck_right = 1;
                        } else if (cant_see_puck_right == 1){
                            cant_see_puck_forward = 0;
                            cant_see_puck_left = 0;
                            cant_see_puck_right = 0;
                        }
                    } else {
                        setForward(MBOTH);
                        setSpeed(MBOTH, 150);
                        CyDelay(500);
                        setCoast(MBOTH);
                        CyDelay(500);
                        if (ultra_distance < 18){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 150);
                            CyDelay(800);
                            setCoast(MBOTH);
                            CyDelay(300);
                            pickup_puck();
                            CyDelay(500);
                            state = S_FACE_HOME;
                            arm_set_level(1);
                            CyDelay(500);
                        }
                    }
                     break;
                case S_GO_HOME_WITHOUT_PUCK_ROTATE:
                    setReverse(MBOTH);
                    setSpeed(MBOTH, 150);
                    CyDelay(1500);
                    setHeading(0);
                    state = S_GO_HOME_WITHOUT_PUCK;
                    rotate_begin_time = time;
                    break;
                case S_GO_HOME_WITHOUT_PUCK:
                    if (time - rotate_begin_time > 20000){
                        while (ultra_distance_2 > 20){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 100);
                            CyDelay(1000);
                            //setReverse(MBOTH);
                            //CyDelay(50);
                            setCoast(MBOTH);
                            CyDelay(200);
                            int k;
                            for (k = 0; k < 10; k++){
                                compass_read();
                                update_position();
                                control_motors();
                                CyDelay(100);
                            }
                        }
                        state = S_LEAVE_BASE; 
                    }
                    break;
                case S_FACE_HOME:
                    setHeading(0);
                    state = S_GO_HOME;
                    rotate_begin_time = time;
                    break;
                case S_GO_HOME:
                    if (time - rotate_begin_time > 50000){
                        while (ultra_distance_2 > 24){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 100);
                            CyDelay(1000);
                            //setReverse(MBOTH);
                            //CyDelay(50);
                            setCoast(MBOTH);
                            CyDelay(200);
                            int k;
                            for (k = 0; k < 10; k++){
                                compass_read();
                                update_position();
                                control_motors();
                                CyDelay(100);
                            }
                        }
                        state = S_GOT_HOME;    
                    } else if (time - rotate_begin_time > 30000){
                        setForward(MBOTH);
                        setSpeed(MBOTH, 100);
                        CyDelay(1000);
                        int k;
                        for (k = 0; k < 10; k++){
                                compass_read();
                                update_position();
                                control_motors();
                                CyDelay(100);
                            }
                    } else if ((time - rotate_begin_time) >= 25000){
                        capture_thresh_image();
                        puck_heading = to_nearest_blob(color_looking_for, 400, 12);
                        if (puck_heading != 0){
                            setForward(MBOTH);
                            setSpeed(MBOTH, 100);
                            CyDelay(1000);
                            state = S_FACE_CORRECT_DIR;
                            drop_puck();
                        }
                    }
                    break;
                case S_GOT_HOME:
                    arm_set_level(0);
                    setHeading(90);
                    got_home_time = time;
                    state = S_DROP_OFF_IN_WORKSPACE;
                    break;
                case S_DROP_OFF_IN_WORKSPACE:
                    if (time - got_home_time > 10000){
                        setForward(MBOTH);
                        setSpeed(MBOTH, 100);
                        CyDelay(1500);
                        drop_puck();
                        num_pucks += 1;
                        if (num_pucks < 2){
                            setReverse(MBOTH);
                            setSpeed(MBOTH, 100);
                            setHeading(0);                       
                            int k;
                            for (k = 0; k < 10; k++){
                                compass_read();
                                update_position();
                                control_motors();
                                CyDelay(100);
                            }
                            CyDelay(600);
                            state = S_LEAVE_BASE;
                        } else {
                            state = S_HOLDING_PATTERN;
                        }
                    }
                    break;
                case S_HOLDING_PATTERN:
                    setHeading(90);
                    setReverse(MBOTH);
                    setSpeed(MBOTH, 80);
                    CyDelay(3000);
                    setCoast(MBOTH);
                    CyDelay(15000);
                    while (1){
                        setReverse(MBOTH);
                        setSpeed(MBOTH, 80);
                        CyDelay(3000);
                        setCoast(MBOTH);
                        int k;
                        for (k = 0; k < 10; k++){
                            compass_read();
                            update_position();
                            control_motors();
                            CyDelay(100);
                        }
                        CyDelay(10000);
                        setForward(MBOTH);
                        setSpeed(MBOTH, 80);
                        CyDelay(3000);
                        setCoast(MBOTH);
                        for (k = 0; k < 10; k++){
                            compass_read();
                            update_position();
                            control_motors();
                            CyDelay(100);
                        }
                        CyDelay(10000);
                    }
                    break;
            }
        }
        
        //Handle buttons
        if (but1_b){
            but1_b = 0;
            state = S_READ_INSTRUCTIONS;
            drop_puck();
            
        } else if (but0_b){
            but0_b = 0;
            goto_position(0,0);
            
        }
        
        //image_stuff4();
        sprintf(outString, "P%d c%d hu%d", puck_heading, color_looking_for, ultra_distance_2);
        LCD_ClearDisplay();
        LCD_PosPrintString(0,0, outString);
        sprintf(outString, "u%d S%d l%ld r%ld", ultra_distance, state, loc_y_a, loc_y_b);
        LCD_PosPrintString(1,0, outString);
//        //Print some info to the screen
        if ((time % 10000) == 0){
        
            LCD_ClearDisplay();
            sprintf(outString, "%lu", time/10000);
        
            //sprintf(outString, "c%d d%ld y%ld", compass_heading, desired_distance, delta_y_distance);
            //LCD_PosPrintString(1,0,outString);
        }
    }
}