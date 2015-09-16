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

#include <project.h>
#include <motor.h>
#include <navigation.h>
#include <compass.h>

#include <mouse_b.h>

int32 desired_distance;
int16 desired_heading;

//The position before executing a move to order
int32 start_x;
int32 start_y;
//The position we wish to go to
int32 end_x;
int32 end_y;

uint8 currently_rotating;
uint8 isRotating(){
    return currently_rotating;
}


// From compass.c
extern int16 compass_heading;
// From mouse_b.c
extern volatile int32 loc_y_b;
// From navigation.c
extern volatile struct Position location;

void rotate_left(int speed);
void rotate_right(int speed);

uint8 clip(int var, int limit){
    if (var > limit){
        return limit;
    } else {
        return var;
    }
}

/** This function is to be called every time through the main loop 
 * It will 
 */
void control_motors(){
    /* 
     * Step 1. Correct the heading 
     */
    int heading_error = desired_heading - compass_heading;
    //If the error is greater than 180, there is a shorter way around the unit 
    //this correc tthat
    if (abs(heading_error) > 180){ 
        heading_error = -(desired_heading - (360 - compass_heading));
    }
    // We need to correct the heading if the error is greater than 
    if (abs(heading_error) > HEADING_ERROR_LIMIT){ 
        currently_rotating = 1;
        
        // the actual heading is greater than the desired heading
        if (heading_error < 0){ 
            rotate_left(clip(abs(heading_error)*15 + 50, 255));
            WHITE_Write(1);
            ORANGE_Write(0);
        } else {
            rotate_right(clip(abs(heading_error)*15 + 50, 255));
            WHITE_Write(0);
            ORANGE_Write(1);
        }
        return;
    }
    
    // We are at the correct heading, so go forward the required distance
    int32 dx = (end_x - location.x);
    int32 dy = (end_y - location.y);
    int32 dd = sqrt(dx*dx + dy*dy);
    
    if (abs(dd) > 500){
        setSpeed(MBOTH, clip(dd/2, 255));
        setForward(MBOTH);
        currently_rotating = 0;
    } else {
        setCoast(MBOTH);
        currently_rotating = 0;
    }
}

void goto_position(int32 x, int32 y){
    start_x = location.x;
    start_y = location.y;
    end_x = x;
    end_y = y;
    //Calculate the angle of the line we need to run along
    int32 dx = end_x - start_x;
    int32 dy = end_y - start_y;
    setHeading(atan2((double) dy, (double) dx) * 180.0/M_PI + 180.0);
}


void setHeading(int16 new_heading){
    desired_heading = new_heading;
}

void rotate_left(int speed){
    setForward(MRIGHT);
    setReverse(MLEFT);
    setSpeed(MBOTH, speed);
}

void rotate_right(int speed){
    setForward(MLEFT);
    setReverse(MRIGHT);
    setSpeed(MBOTH, speed);
}

void start_motors(){
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

void setSpeed(uint8 motor, uint8 speed){
    /* Set bit 1 of motor to select motor 1 
     * Set bit 2 of motor to select motor 2
     */
    if (motor & MLEFT){
        MOTOR_L_WriteCompare(speed - LEFT_MOTOR_SPEED_CORRECTION);
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
