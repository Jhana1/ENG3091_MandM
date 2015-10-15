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

#include <infrared_front.h>
#include <infrared_left.h>
#include <motor.h>
#include <buttons.h>
#include <compass.h>
#include <ultrasonic.h>
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

int main()
{
    RED_Write(1);
    CYGlobalIntEnable;
    char outString[16];
    
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
    /*
    while (1){
        if (compass_ready){
            compass_read();
        }
        print("%d %d\n", compass_x, compass_y);
    }*/
    
    start_motors();
    start_gripper();
    drop_puck();
    start_arm();
    arm_set_level(0);
    start_ultrasonic();
    start_infrared_front();
    beam_broken();
    
    /**** Declare Variables ****/
    
    uint16 ir_result;
    uint16 state;
    
    #define S_START 0
    #define S_LEAVE_BASE 1
    #define S_LEFT_BASE 2
    #define S_FIND_PUCK 3
    #define S_GO_HOME 4
    #define S_FACE_HOME 5
    #define S_GOT_HOME 6
    #define S_IN_CORNER 7
    #define S_GOOD_ULTRA 8
    
    state = S_START;
   
    
    while (1){
        switch(state){
            case S_START:
                state = S_LEAVE_BASE;
                break;
            case S_LEAVE_BASE:
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
                go_forward(2000, 255);
                CyDelay(1000);
                state = S_FACE_HOME;
                break;
            case S_FACE_HOME:
                set_heading(0);
                rotate_degrees(0);
                CyDelay(1000);
                state = S_GO_HOME;
                break;
            case S_GO_HOME:
                ir_result = get_front_ir();
                if (ir_result < 10){
                    go_forward(1200, 255);
                    CyDelay(500);
                    ir_result = get_front_ir();
                    if (ir_result < 10){
                        //PERHAPS STOP AND TAKE 3 if not accurate...
                        int var = get_var_ultra();
                        if (var > 200){
                            state = S_IN_CORNER;
                        } else {
                            state = S_GOOD_ULTRA;
                        }
                    } else {
                        if (within_range(57,ir_result,60)){
                            while (get_mean_ultra() < 70){
                                go_forward(750, 255);
                                CyDelay(500);
                            }
                            set_heading(270);
                            rotate_degrees(0);
                        }
                }
                           
                    int mean = get_mean_ultra();
                }
                LCD_ClearDisplay();
                sprintf(outString, "I%d U%d V%d", ir_result, get_mean_ultra(), get_var_ultra());
                LCD_PosPrintString(0,0,outString);
                break;
            case S_GOT_HOME:
                ;
                break;
        }
        
        //ir_result = get_front_ir();
        
        LCD_ClearDisplay();
        sprintf(outString, "u %d ic %d", ultra_distance, ir_result);
        LCD_PosPrintString(0,0,outString);
        sprintf(outString, "s%d c%d vu %d", state, compass_heading, get_var_ultra());
        LCD_PosPrintString(1,0,outString);
        CyDelay(50);
    }
}