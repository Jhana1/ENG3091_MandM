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
#include <gripper.h>
#include <arm.h>

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
    /* ** INITIALIZE COMPONENTS ** */
    LCD_Start();
    Timer_Start();
    //USB_Start(0, USB_DWR_VDDD_OPERATION);
    //CyDelay(1000); give camera time to boot up
    start_buttons();
    start_motors();
    calculate_circular_functions();
    start_mice();
    
    start_navigation();
    
    start_compass();
    start_gripper();
    start_arm();
    start_ultrasonic();
   
    
    BLUE_Write(1); //For some bizarre reason the blue led is inverted.??
    
    /* ** DECLARE VARIABLES ** */
    char outString[16];  // String to hold the ascii result
    uint32 time;
    extern volatile int32 loc_y_a;
    extern volatile int32 loc_y_b;
    CyGlobalIntEnable;
    /* INFINITE LOOP */
    //Wait for compass to be ready for reading
    
    //while (!compass_ready){;} //!!! NEED TIMEOUT
    //compass_read();
    //compass_ready = 0;
    //int state = 0;
    //original_compass_heading = compass_heading;
    //setHeading(0);
    
    LCD_PosPrintString(0,0,"STRATING!!!");
    uint8 alevel = 0;
    uint8 pwmvar = 18;
    for(;;)
    {   
        //Update current time
        time = Timer_ReadCounter();
        //Read the compass when it is ready for reading
        if (compass_ready){
            compass_read();
            compass_ready = 0;
        //    print("%d %d %d\n", compass_x, compass_y, compass_z);
        }
        
        //Update the current position
        update_position();
        
        //Execute any motor control
        control_motors();
        
        
        
        //Handle buttons
        if (but1_b){
            but1_b = 0;
            loc_y_b = 0;          
            //drop_puck(); 
            //alevel = (alevel + 1) % 6;
            //arm_set_level(alevel);
            goto_position(4000,4000);
        } else if (but0_b){
            but0_b = 0;
            loc_y_b = 0;
            //pickup_puck();
           
            //alevel = (alevel + 1) % 6;
            //arm_set_level(alevel);
            goto_position(0,0);
        }
        
        //Print some info to the screen
        
        if ((time % 1000) == 0){
            LCD_ClearDisplay();
            sprintf(outString, "ly%ld ry%ld", loc_y_a, loc_y_b);
            LCD_PosPrintString(0,0,outString);
            
            sprintf(outString, "a%d u%d p%d", compass_heading, ultra_distance, pwmvar);
            LCD_PosPrintString(1,0,outString);
        }
    }
}