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


#ifndef MY_MOTOR
    #include <project.h>
    
    #define MLEFT 0x1
    #define MRIGHT 0x2
    #define MBOTH 0x3
    
    #define MOTOR_S_STOPPED 0
    #define MOTOR_S_ROTATING 1
    #define MOTOR_S_FORWARD 2
    #define MOTOR_S_BACKWARD 3
    #define MOTOR_S_ARRIVED 4
    
    #define HEADING_ERROR_LIMIT 4 //degrees
    #define LEFT_MOTOR_SPEED_CORRECTION 30 //attempt to correct for unmatched motors
    
    void start_motors(void);
    
    uint8 isRotating(); //Return true if a heading correction is taking place
    
    //Makes the robot drive to x,y position
    void goto_position(int32 x, int32 y);
    
    void control_motors();
    void setHeading(int16 new_heading);
    void setDistance(int32 distance);
    void setRightRotate();
    void setLeftRotate();
    void setSpeed(uint8 motor, uint8 speed);
    void setForward(uint8 motor);
    void setReverse(uint8 motor);
    void setCoast(uint8 motor);
    
    CY_ISR_PROTO(MY_SCLK_A_ISR);
#endif

/* [] END OF FILE */
