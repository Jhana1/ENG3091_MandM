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
    start_compass();
    start_gripper();
    start_arm();
    
    LCD_PosPrintString(0,0,"Arm Started");
    
    init_camera();
    LCD_ClearDisplay();
    LCD_PosPrintString(0,0,"Camera Started");
    set_gain_exposure(3);
    
    BLUE_Write(1); //For some bizarre reason the blue led is inverted.??
    
    /* ** DECLARE VARIABLES ** */
    char outString[16];  // String to hold the ascii result
    uint32 time;
    extern volatile int32 loc_y_a;
    extern volatile int32 loc_y_b;
    int stack[3];
    char RGB[] = {'K','R','G','B'};
    int i;
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
    uint8 pwmvar = 30;
    /*
    
        capture_image();
        threshold_image();
        blob_detect();
        LCD_ClearDisplay();
        LCD_PosPrintString(0,0,"Instruction Read");
        CyDelay(5000);
        LCD_PosPrintString(0,0,"Instruction Read...");
        do
        {
            if(pwmvar >= 50)
            {
                break;
            }
            capture_image();
            threshold_image();
            blob_detect();
            LCD_ClearDisplay();
            LCD_PosPrintString(0,0,"Image Captured");
            CyDelay(1000);
            
            Arm_PWM_WriteCompare(++pwmvar);
            LCD_ClearDisplay();
            sprintf(display[0],"C: %d",identify_colour_instructions(100));
            sprintf(display[1],"A: %d",pwmvar);
            LCD_PosPrintString(0,0,display[0]);
            LCD_PosPrintString(0,0,display[1]);
            CyDelay(1000);
        } while(identify_colour_instructions(100) == 0);
        for(i = 0; i < 3; i++)
        {
            stack[i] = identify_colour_instructions(100);
            pwmvar += 5;
            Arm_PWM_WriteCompare(pwmvar);
            capture_image();
            threshold_image();
            blob_detect();
        }
        LCD_ClearDisplay();
        sprintf(display[1],"1:%c 2:%c 3:%c",RGB[stack[0]+1],RGB[stack[1]+1],RGB[stack[2]+1]);
        LCD_PosPrintString(0,0,display[1]);
    
    
    setHeading(90);
    */
    
    int find_blue_puck = 0;
    int puck_heading = 0;
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

        if (find_blue_puck){
            capture_thresh_image();
            puck_heading = to_nearest_blob(BLUE, 30);
            if (puck_heading < -4){
                rotate_degrees(3);
            } else if (puck_heading > 4){
                rotate_degrees(-3);
            } else if (puck_heading == -1) {
                rotate_degrees(15);
            } else {
                go_forward(500);
            }
            CyDelay(5000);   
        }
        
        //Handle buttons
        if (but1_b){
            but1_b = 0;
            loc_y_b = 0;
            //drop_puck();
            find_blue_puck = 1;
            //rotate_degrees(90);
            //go_forward(2000);
        } else if (but0_b){
            but0_b = 0;
            loc_y_b = 0;
            find_blue_puck = 0;
            //rotate_degrees(-90);
            //go_forward(2000);
            //pickup_puck();
        }
        
        
        //Print some info to the screen
        
        if ((time % 1000) == 0){
            LCD_ClearDisplay();
            sprintf(outString, "ly%ld ry%ld", loc_y_a, loc_y_b);
            LCD_PosPrintString(0,0,outString);
            sprintf(outString, "p%d B:%d", pwmvar, find_blue_puck);
            LCD_PosPrintString(1,0,outString);
            //sprintf(outString, "c%d d%ld y%ld", compass_heading, desired_distance, delta_y_distance);
            //LCD_PosPrintString(1,0,outString);
        }
    }
}