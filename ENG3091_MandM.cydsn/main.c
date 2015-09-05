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


#include <mouse_a.h>
#include <mouse_b.h>
#include <motor.h>
#include <navigation.h>

//this is in navigation.c
extern struct Position location;

uint8 inc;
uint8 dec;

CY_ISR(INC_ISR){
    inc = 1;
    but0_ClearPending();
}

CY_ISR(DEC_ISR){
    dec = 1;
    but1_ClearPending();
}

void init_buttons(){
    Button_Start();
    but0_StartEx(INC_ISR);
    but1_StartEx(DEC_ISR);
    
    dec = 0;
    inc = 0;
}

void init_mice(){
    sclk_a_isr_Stop();
    sclk_b_isr_Stop();
    
    CyGlobalIntDisable; /* Disable global interrupts. */
    
    mouse_a_init();
    mouse_b_init();
    
    reset_sclk_a_isr();
    reset_sclk_b_isr();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SCLK_A_ClearInterrupt();
    SCLK_B_ClearInterrupt();
    sclk_a_isr_SetPriority(0);
    sclk_b_isr_SetPriority(0);
    sclk_a_isr_StartEx(MY_SCLK_A_ISR);
    sclk_b_isr_StartEx(MY_SCLK_B_ISR);    
}

void stop_mice(){
    sclk_a_isr_Stop();
    sclk_b_isr_Stop();
}

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
    
    CyDelay(200);//give mice time to boot up
    init_mice();
    init_navigation();
    init_buttons();
    init_motors();
 
    
    /* ** Variables used in main ** */
    char outString[16];  // String to hold the ascii result
    uint32 time = Timer_ReadCounter();
    uint32 delta;
    extern volatile int32 loc_x_a;
    extern volatile int32 loc_y_a;
    extern volatile int32 loc_x_b;
    extern volatile int32 loc_y_b;
    setCoast(MBOTH);
    for(;;)
    {   
        delta = Timer_ReadCounter() - time;
        time = Timer_ReadCounter();
        
        
        if (dec){
            dec = 0;
            reset_navigation();
        } else if (inc){
            inc = 0;
            
        } 
        
        if ((time % 400) == 0){
            LCD_ClearDisplay();
            
            sprintf(outString, "x%ld y%ld - L", loc_x_a, loc_y_a);
            LCD_PosPrintString(0,0, outString);
            sprintf(outString, "x%ld y%ld - R", loc_x_b, loc_y_b);
            LCD_PosPrintString(1,0, outString);
            /*
            sprintf(outString, "X%ld Y%ld", (int32) (location.x), (int32) (location.y));
            LCD_PosPrintString(0, 0, outString);
            sprintf(outString, "A:%d ", (int) (location.angle*180.0/M_PI));
            LCD_PosPrintString(1, 0, outString);
            sprintf(outString, "l%d r%d", MOTOR_L_ReadCompare(), MOTOR_R_ReadCompare());
            LCD_PrintString(outString);
            */
        }
    }
}