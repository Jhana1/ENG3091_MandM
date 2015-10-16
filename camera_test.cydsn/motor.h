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
    
    #define MEND_S_STOPPED 0
    #define MEND_S_ROTATING 1
    #define MEND_S_DRIVING 2
    
    #define STALL_SPEED 150
    #define MAX_SPEED 200
    #define HEADING_ERROR_LIMIT 3 //degrees
    #define LEFT_MOTOR_SPEED_CORRECTION 0 //attempt to correct for unmatched motors
    
    void start_motors(void);
    void stop_driving();
    uint8 isRotating(); //Return true if a heading correction is taking place
    uint8 isDriving();
    int16 abs2(int16 var);
    
    //Makes the robot drive to x,y position
    void goto_position(int32 x, int32 y);
    
    int control_motors();
    void rotate_degrees(int16 angle);
    void rotate_left(int speed);
    void rotate_right(int speed);
    void go_forward(uint32 time, uint8 speed);
    void go_backward(uint32 time, uint8 speed);
    void go_backward_ultra(uint16 ultra_dist, uint8 speed);
    void set_heading(int16 new_heading);
    void setRightRotate();
    void setLeftRotate();
    void setSpeed(uint8 motor, uint8 speed);
    void setForward(uint8 motor);
    void setReverse(uint8 motor);
    void setCoast(uint8 motor);
    
    CY_ISR_PROTO(MY_SCLK_A_ISR);
#endif

/* [] END OF FILE */
