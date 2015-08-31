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

#include <mouse_a.h>
#include <mouse_b.h>
#include <motor.h>
#include <navigation.h>

volatile int32 loc_x_a;
volatile int32 loc_y_a;

volatile int32 loc_x_b;
volatile int32 loc_y_b;


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
    
    loc_x_a = 0;
    loc_y_a = 0;
    
    loc_x_b = 0;
    loc_y_b = 0;
    
    CyGlobalIntDisable; /* Disable global interrupts. */
    
    mouse_a_init();
    mouse_b_init();
    
    reset_sclk_a_isr();
    reset_sclk_b_isr();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SCLK_A_ClearInterrupt();
    SCLK_B_ClearInterrupt();
    
    sclk_a_isr_StartEx(MY_SCLK_A_ISR);
    sclk_b_isr_StartEx(MY_SCLK_B_ISR);    
}

int main()
{
    char outString[16];  // String to hold the ascii result
    
    //LCD_Start();
    ORANGE_Write(0);
    
    CyDelay(200);//give mice time to boot up
    init_mice();
    reset_navigation();
    ORANGE_Write(1);
    
    CYGlobalIntEnable;
    
    init_buttons();
    init_motors();
 
    setForward(0x3);
    
    Timer_Start();
    uint32 time;

    uint8 pwm_var = 255;
    dec = 0;
    inc = 0;
    
    //Start it stopped initially...
    loc_y_a = 10000;
    loc_y_b = 10000;
    
    
    for(;;)
    {   
        time = Timer_ReadCounter();
        
        if (dec){
            dec = 0;
            //MAKE IT STOOOOP!!!
            loc_y_a = 10000;
            loc_y_b = 10000;
        } else if (inc){
            inc = 0;
            
            reset_navigation();
        }
        
        setSpeed(0x3, pwm_var);
        
        if (loc_y_a < 8000 && loc_y_b < 8000){
            setForward(0x3);
        } else {
            setCoast(0x3);
        }
        
        
        /*
        if ((time % 400) == 0){
            //LCD_ClearDisplay();
            
            sprintf(outString, "X:%ld Y:%ld", loc_x_a, loc_y_a);
            LCD_PosPrintString(0, 0, outString);
            sprintf(outString, "X:%ld Y:%ld", loc_x_b, loc_y_b);
            LCD_PosPrintString(1, 0, outString);
            //LCD_PosPrintNumber(0,0,pwm_var);
            
            setSpeed(0x3, pwm_var);
        }*/
    }
}