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
#include <mouse_a.h>
#include <mouse_b.h>

void start_mice(){
    sclk_a_isr_Stop();
    sclk_b_isr_Stop();
    LCD_PosPrintString(0,0,"INIT MOUSE A");
    mouse_a_init();
    LCD_PosPrintString(0,0,"INIT MOUSE B");
    mouse_b_init();
    
    reset_sclk_a_isr();
    reset_sclk_b_isr();
    
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

/* [] END OF FILE */
