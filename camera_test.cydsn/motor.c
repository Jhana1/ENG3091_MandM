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

#include <math.h>
#include <stdio.h>

#include <project.h>
#include <motor.h>
#include <compass.h>
#include <ultrasonic.h>

int32 desired_distance;
int16 desired_heading;
extern volatile uint8 compass_ready;
//The position before executing a move to order
int32 start_x;
int32 start_y;
//The position we wish to go to
int32 end_x;
int32 end_y;

//Hold the current state of the motors
uint8 motor_state;
uint8 just_arrived;
uint8 currently_rotating;
uint8 isRotating(){
    return currently_rotating;
}
uint8 currently_driving;
uint8 isDriving(){
    return currently_driving;
}

// From compass.c
extern int16 compass_heading;
// From navigation.c
extern volatile struct Position location;

void rotate_left(int speed);
void rotate_right(int speed);
int16 abs2(int16 val);


int my6abs(x){
    if (x < 0){
        return -x;
    } else {
        return x;
    }
}

uint8 clip(int lower, int var, int upper){
    if (var > upper){
        return upper;
    } else if (var < lower) {
        return lower;
    } else {
        return var;
    }
}

/** This function is to be called every time through the main loop 
 * It will 
 */

int control_heading(){
    /* 
     * Step 1. Correct the heading 
     */
    while (!compass_ready){;}
    compass_read();
    int motor_end_state = 0;
    int heading_error = desired_heading - compass_heading;
    // If the error is greater than 180, there is a shorter way around the unit 
    // circle, this corrects that
    if (my6abs(heading_error) > 180){
        heading_error = -(desired_heading - (360 - compass_heading));
    }
    // We need to correct the heading if the error is greater than 
    if (my6abs(heading_error) > HEADING_ERROR_LIMIT){ 
        currently_rotating = 1;
        // the actual heading is greater than the desired heading
        if (heading_error < 0){ 
            rotate_right(clip(STALL_SPEED, my6abs(heading_error)*2, MAX_SPEED));
        } else {
            rotate_left(clip(STALL_SPEED, my6abs(heading_error)*2, MAX_SPEED));
        }
        
        return MEND_S_ROTATING;
    }
    setCoast(MBOTH);
    
    return MEND_S_STOPPED;
}

/* 
 * Makes the robot drive forward *time* seconds BLOCKING
 */
void go_forward(uint32 time, uint8 speed){
    time = time * 10;
    uint32 start_time = Timer_ReadCounter(); // each tick is 100us
    while (start_time - Timer_ReadCounter() < time){
        setForward(MBOTH);
        setSpeed(MBOTH, speed);
        control_heading();
        CyDelay(25);
    }
    setCoast(MBOTH);
}

/*
 * Makes the robot drive backward *distance* centimeters
 */
void go_backward(uint32 time, uint8 speed){
    time = time * 10;
    uint32 start_time = Timer_ReadCounter(); // each tick is 100us
    while (start_time - Timer_ReadCounter() < time){
        setReverse(MBOTH);
        setSpeed(MBOTH, speed);
        control_heading();
        CyDelay(25);
    }
    setCoast(MBOTH);
}


void go_backward_ultra(uint16 ultra_dist, uint8 speed){
    while (get_mean_ultra() < ultra_dist){
        setReverse(MBOTH);
        setSpeed(MBOTH, speed);
        control_heading();
        CyDelay(25);
    }
    setCoast(MBOTH);
}

/*
 * Makes the robot rotate *angle* degrees.
 * angle > 0 rotates right, angle < 0 rotates left
 */
void rotate_degrees(int16 angle){
    desired_heading += angle;
    if (desired_heading > 360){
        desired_heading -= 360;
    } else if (desired_heading < 0){
        desired_heading += 360;
    }
    while (control_heading() != MEND_S_STOPPED){;}
}

/* 
 * Sets the robots heading to *new_heading*
 */
void set_heading(int16 new_heading){
    desired_heading = new_heading;
}

/* 
 * Sets the motors to rotate the robot left
 */
void rotate_left(int speed){
    setForward(MRIGHT);
    setReverse(MLEFT);
    setSpeed(MBOTH, speed);
}

/*
 * Sets the motors to rotate the robot right at *speed*
 */
void rotate_right(int speed){
    setForward(MLEFT);
    setReverse(MRIGHT);
    setSpeed(MBOTH, speed);
}


/*
 * Initializes the motor PWM modules and sets the motors to stopped
 */
void start_motors(){
    MOTOR_L_Start();
    MLIN1_Write(0);
    MLIN2_Write(0);
    MOTOR_L_WriteCompare(0);
       
    MOTOR_R_Start();
    MRIN1_Write(0);
    MRIN2_Write(0);
    MOTOR_R_WriteCompare(0);
}


/*
 * Set *motor* speed to *speed*
 * Speed between 0 and 255. Note that the motors won't start to actually push
 * the robot forward til around 100
 */ 
void setSpeed(uint8 motor, uint8 speed){
    /* Set bit 1 of motor to select motor 1 
     * Set bit 2 of motor to select motor 2
     */
    if (motor & MRIGHT){
        MOTOR_R_WriteCompare(speed);
    }
    if (motor & MLEFT){ //Slow down the left motor because it tends to be faster
        MOTOR_L_WriteCompare(speed - LEFT_MOTOR_SPEED_CORRECTION);
    }
}


/*
 * Set *motor* to coast
 */ 
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


/*
 * Set *motor* to forward drive
 */ 
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

/*
 * Set *motor* to reverse drive
 */ 
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
