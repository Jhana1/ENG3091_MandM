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

volatile uint8 but0_b;
volatile uint8 but1_b;

CY_ISR(INC_ISR){
    but0_b = 1;
    but0_ClearPending();
}

CY_ISR(DEC_ISR){
    but1_b = 1;
    but1_ClearPending();
}

void start_buttons(){
    Button_Start();
    but0_StartEx(INC_ISR);
    but1_StartEx(DEC_ISR);
    
    but1_b = 0;
    but0_b = 0;
}

/* [] END OF FILE */
