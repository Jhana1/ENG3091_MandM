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

volatile uint16 pulse_length_arr[3], max;
volatile int arr_i;
volatile uint16 pulse_length_front;

CY_ISR(ir_front_isr){
    pulse_length_front = (65535 - IR_FRONT_Timer_ReadCounter()) / 100;
    pulse_length_arr[arr_i] = pulse_length_front;
    arr_i = (arr_i + 1) % 3;
    
    int i;
    max = 0;
    for(i = 0; i < 3; i++)
    {
        if(pulse_length_arr[i] > max)
        {
            max = pulse_length_arr[i];
        }
    }
    
    pulse_length_front = max;
    
    IR_FRONT_DONE_ClearPending();
}

uint16 get_front_ir(){
    return pulse_length_front;
}

void start_infrared_front(){
    IR_FRONT_PWM_Start();
    IR_FRONT_Timer_Start();
    IR_FRONT_DONE_StartEx(ir_front_isr);
}
/* [] END OF FILE */
