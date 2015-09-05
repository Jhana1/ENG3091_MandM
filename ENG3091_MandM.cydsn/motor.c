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
#include <motor.h>
#include <navigation.h>

void init_motors(){
    /* Initialize the motor controller */
    MOTOR_L_Start();
    MLIN1_Write(0);
    MLIN2_Write(0);
    MOTOR_L_WriteCompare(0);
       
    MOTOR_R_Start();
    MRIN1_Write(0);
    MRIN2_Write(0);
    MOTOR_R_WriteCompare(0);
}

void setRightRotate(){
    setForward(MLEFT);
    setReverse(MRIGHT);
}

void setLeftRotate(){
    setForward(MRIGHT);
    setReverse(MLEFT);
}

int32 motor_time;
/* Call this every time throught the main loop */
//extern volatile Position location;
void refresh_motor(int32 delta){
    ;
}

void setSpeed(uint8 motor, uint8 speed){
    /* Set bit 1 of motor to select motor 1 
     * Set bit 2 of motor to select motor 2
     */
    if (motor & MLEFT){
        MOTOR_L_WriteCompare(speed);
    }
    
    if (motor & MRIGHT){
        MOTOR_R_WriteCompare(speed);
    }
}

void setCoast(uint8 motor){
        if (motor & MLEFT){
        MLIN1_Write(0);
        MLIN2_Write(0);
    }
    
    if (motor & MRIGHT){
        MRIN1_Write(0);
        MRIN2_Write(0);
    }
}

void setForward(uint8 motor){
    if (motor & MLEFT){
        MLIN1_Write(1);
        MLIN2_Write(0);
    }
    
    if (motor & MRIGHT){
        MRIN1_Write(1);
        MRIN2_Write(0);
    }
}

void setReverse(uint8 motor){
    if (motor & MLEFT){
        MLIN1_Write(0);
        MLIN2_Write(1);
    }
    
    if (motor & MRIGHT){
        MRIN1_Write(0);
        MRIN2_Write(1);
    }
}

/* [] END OF FILE */
