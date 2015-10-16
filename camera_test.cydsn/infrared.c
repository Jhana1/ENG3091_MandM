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
volatile uint16 pulse_length;

CY_ISR(ir_isr){
    pulse_length = (65535 - IR_Timer_ReadCounter()) / 100;
    pulse_length_arr[arr_i] = pulse_length;
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
    
    pulse_length = max;
    
    IR_DONE_ClearPending();
}

uint16 get_ir_val(){
    return pulse_length;
}

void select_front(){
    if (IR_REG_Read() != 0x00){
        IR_REG_Write(0x00);
    }
}
void select_right(){
    if (IR_REG_Read() == 0x00){
        IR_REG_Write(0xFF);
    }
}

void start_infrared(){
    IR_PWM_Start();
    IR_Timer_Start();
    IR_DONE_StartEx(ir_isr);
}
/* [] END OF FILE */
