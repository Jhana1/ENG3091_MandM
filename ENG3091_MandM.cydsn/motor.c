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

void init_motors(){
    /* Initialize the motor controller */
    MOTOR1_Start();
    M1IN1_Write(0);
    M1IN2_Write(0);
    MOTOR1_WriteCompare(0);
       
    MOTOR2_Start();
    M2IN1_Write(0);
    M2IN2_Write(0);
    MOTOR2_WriteCompare(0);
}
    
void setSpeed(uint8 motor, uint8 speed){
    /* Set bit 1 of motor to select motor 1 
     * Set bit 2 of motor to select motor 2
     */
    if (motor & 0x1){
        MOTOR1_WriteCompare(speed);
    }
    
    if (motor & 0x2){
        MOTOR2_WriteCompare(speed);
    }
}

void setCoast(uint8 motor){
        if (motor & 0x1){
        M1IN1_Write(0);
        M1IN2_Write(0);
    }
    
    if (motor & 0x2){
        M2IN1_Write(0);
        M2IN2_Write(0);
    }
}

void setForward(uint8 motor){
    if (motor & 0x1){
        M1IN1_Write(1);
        M1IN2_Write(0);
    }
    
    if (motor & 0x2){
        M2IN1_Write(1);
        M2IN2_Write(0);
    }
}

void setReverse(uint8 motor){
    if (motor & 0x1){
        M1IN1_Write(0);
        M1IN2_Write(1);
    }
    
    if (motor & 0x2){
        M2IN1_Write(0);
        M2IN2_Write(1);
    }
}

/* [] END OF FILE */
