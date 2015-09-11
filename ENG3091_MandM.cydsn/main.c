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

#include <mice.h>
#include <mouse_a.h>
#include <mouse_b.h>
#include <motor.h>
#include <navigation.h>
#include <buttons.h>
#include <compass.h>
#include <ultrasonic.h>

//this is in navigation.c
extern struct Position location;
//these are in button.c
extern volatile uint8 but0_b;
extern volatile uint8 but1_b;
//These are in compass.c
extern int16 compass_x;
extern int16 compass_y;
extern int16 compass_z;
extern double compass_heading;
extern volatile uint8 compass_ready;
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
    /* ** INITIALIZE COMPONENTS ** */
    LCD_Start();
    Timer_Start();
    USB_Start(0, USB_DWR_VDDD_OPERATION);
    //CyDelay(1000); give camera time to boot up
    
    //start_mice();
    //start_navigation();
    //start_motors();
    start_buttons();
    start_compass();
    //start_ultrasonic();
    
    /* ** DECLARE VARIABLES ** */
    char outString[16];  // String to hold the ascii result
    uint32 time;
    CyGlobalIntEnable;
    /* INFINITE LOOP */
    for(;;)
    {   
        time = Timer_ReadCounter();
        
        //Read the compass when it is ready for reading
        if (compass_ready){
            compass_ready = 0;
            compass_read();
            print("%d %d %d\n", compass_x, compass_y, compass_z);
        }
        
        if ((time % 2500) < 1250){
            BLUE_Write(0);
            RED_Write(0);
        } else {
            BLUE_Write(0);
            RED_Write(0);
        }
        
        if ((time % 1000) == 0){
            sprintf(outString, "x%d y%d", compass_x, compass_y);
            LCD_ClearDisplay();
            LCD_PosPrintString(0,0,outString);
            sprintf(outString, "z%d h%d", compass_z, (int16) (compass_heading * 180.0/M_PI));
            LCD_PosPrintString(1,0,outString);
        }
        
        if (but1_b){
            but1_b = 0;
        } else if (but0_b){
            but0_b = 0;
        }
    }
}