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

volatile uint16 pulse_length_left;

CY_ISR(ir_left_isr){
    if (IR_LEFT_Timer_ReadCounter() != 65535){
        pulse_length_left = (65535 - IR_LEFT_Timer_ReadCounter()) / 100;
    }
    IR_LEFT_DONE_ClearPending();
}

uint16 get_left_ir(){
    return pulse_length_left;
}

void start_infrared_left(){
    IR_LEFT_PWM_Start();
    IR_LEFT_Timer_Start();
    IR_LEFT_DONE_StartEx(ir_left_isr);
}
/* [] END OF FILE */
