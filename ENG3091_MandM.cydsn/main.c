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
    uint32 time;
    uint8 pwm_var = 255;
    dec = 0;
    inc = 0;
    
    setForward(0x3);
    
    for(;;)
    {   
        time = Timer_ReadCounter();
        
        refresh_position();
        
        if (dec){
            dec = 0;
        } else if (inc){
            inc = 0;
            reset_navigation();
        } 
        
        if ((time % 400) == 0){
            LCD_ClearDisplay();
            sprintf(outString, "X%ld Y%ld", (int32) (location.x), (int32) (location.y));
            LCD_PosPrintString(0, 0, outString);
            sprintf(outString, "A%d", (int) (location.angle * (180.0/M_PI)) + 42);
            LCD_PosPrintString(1, 0, outString);
        }
    }
}