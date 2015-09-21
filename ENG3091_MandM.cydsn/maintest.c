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
/*
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
#include <gripper.h>
#include <arm.h>
#include <my_camera_functions.h>
#include <blob_stats.h>

extern blob blobs[255];

//this is in mouse.c
extern volatile int32 loc_x_a;
extern volatile int32 loc_y_a;
extern volatile int32 loc_x_b;
extern volatile int32 loc_y_b;

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

int main()
{
    CyDelay(3000);
    char display[2][30];
    LCD_Start();
    LCD_PosPrintString(0,0, "LCD STARTED");
    CyDelay(1000);
    
    Timer_Start();
    LCD_PosPrintString(0,0, "TIMER STARTED");
    CyDelay(1000);
    
    //USB_Start(0, USB_DWR_VDDD_OPERATION);
    //give camera time to boot up
    start_buttons();
    LCD_PosPrintString(0,0, "BUTTONS STARTED");
    CyDelay(1000);
    
    start_motors();
    LCD_PosPrintString(0,0, "MOTORS STARTED");
    CyDelay(1000);
    
    setSpeed(MBOTH, 255);
    setForward(MLEFT);
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0, "Left Forward");
    CyDelay(1000);
    
    setCoast(MLEFT);
    setForward(MRIGHT);
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0, "RIGHT Forward");
    CyDelay(1000);
    
    setCoast(MBOTH);
    
    start_gripper();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Gripper Started");
    drop_puck();
    LCD_PosPrintString(0,0,"Dropped Puck");
    CyDelay(1000);
    pickup_puck();
    LCD_PosPrintString(0,0,"Grabbed Puck");
    CyDelay(1000);
    
    start_arm();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Arm Started");
    int i;
    for (i = 0; i < 6; i++){
        arm_set_level(i);
        LCD_PosPrintString(1,0,"Arm Position:");
        LCD_PrintNumber(i);
        CyDelay(1000);
    }
    arm_set_level(0);
    
    start_compass();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Compass Started");
    CyDelay(1000);
    CyGlobalIntEnable;
    while (!compass_ready){;}
    compass_read();
    sprintf(display[0], "x%d y%d z%d", compass_x, compass_y, compass_z);
    sprintf(display[1], "h%d", compass_heading);
    CyDelay(1000);
    
    start_ultrasonic();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0, "Ultra Started");
    LCD_PosPrintNumber(1,0, ultra_distance);
    CyDelay(1000);
    
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Starting Mice");
    start_mice();
    LCD_PosPrintString(0,0, "Mice Started");
    LCD_PosPrintString(1,0, "lx");
    LCD_PrintNumber(loc_x_a);
    LCD_PrintString("ly");
    LCD_PrintNumber(loc_y_a);
    LCD_PrintString("rx");
    LCD_PrintNumber(loc_x_b);
    LCD_PrintString("ry");
    LCD_PrintNumber(loc_y_b);
    
    
    
    init_camera();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Camera Started");
    set_gain_exposure(1);
    
    capture_thresh_image();
    char disp[2][20];
    sprintf(disp,"#:%d %d %d",blob_count(50),blobs[0].colour,blobs[1].colour);
    LCD_PosPrintString(0,0,disp);
    
}
*/