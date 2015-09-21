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

//Hold the current state of the motors
uint8 motor_state;
uint8 just_arrived;
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
extern int32 delta_y_distance; 

void rotate_left(int speed);
void rotate_right(int speed);
int16 abs2(int16 val);


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
            rotate_left(clip(STALL_SPEED, abs(heading_error)*2, MAX_SPEED));
            WHITE_Write(1);
            ORANGE_Write(0);
        } else {
            rotate_right(clip(STALL_SPEED, abs(heading_error)*2, MAX_SPEED));
            WHITE_Write(0);
            ORANGE_Write(1);
        }
        return;
    }
    
    setCoast(MBOTH);
    
    int distance_error;
    
    switch (motor_state){
        case MOTOR_S_STOPPED:
            break; //Do nothing
        case MOTOR_S_FORWARD:
            distance_error = desired_distance - delta_y_distance;
            if (abs2(distance_error) > MOTOR_FORWARD_ERROR_LIMIT && distance_error > 0){
                // WHAT HAPPENS IF WE OVERSHOOT? WILL IT GET FASTER AND FASTER GOING AWAY FROM THE CORRECT POSITION?
          //if (abs2(distance_error) > MOTOR_FORWARD_ERROR_LIMIT && distance_error > 1)     
                setSpeed(MBOTH, clip(STALL_SPEED, abs(delta_y_distance - desired_distance)/2, 255));
                setForward(MBOTH);
                currently_rotating = 0;
            } else {
                setSpeed(MBOTH, 0);
                setCoast(MBOTH);
                motor_state = MOTOR_S_STOPPED;
            }
            break;
        case MOTOR_S_BACKWARD:           
            distance_error = desired_distance - delta_y_distance;
            if (abs2(distance_error) > MOTOR_FORWARD_ERROR_LIMIT && distance_error < 0){
                // WHAT HAPPENS IF OVERSHOOT?
                setSpeed(MBOTH, clip(STALL_SPEED, abs(delta_y_distance - desired_distance)/2, 255));
                setReverse(MBOTH);
                currently_rotating = 0;
            } else {
                setSpeed(MBOTH, 0);
                setCoast(MBOTH);
                motor_state = MOTOR_S_STOPPED;
            }
            break;
            break;
    }
}


/*
 * Makes the robot drive from current location to the specified x, y position
 */
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


/* 
 * Makes the robot drive forward *distance* centimeters
 */
void go_forward(int32 distance){
    reset_delta_y_distance();
    desired_distance = distance;
    motor_state = MOTOR_S_FORWARD;
}

/*
 * Makes the robot drive backward *distance* centimeters
 */
void go_backward(int32 distance){
    reset_delta_y_distance();
    desired_distance = distance;
    motor_state = MOTOR_S_BACKWARD;
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
}

/* 
 * Sets the robots heading to *new_heading*
 */
void setHeading(int16 new_heading){
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
    if (motor & MLEFT){ //Slow down the left motor because it tends to be faster
        MOTOR_L_WriteCompare(speed - LEFT_MOTOR_SPEED_CORRECTION);
    }
    
    if (motor & MRIGHT){
        MOTOR_R_WriteCompare(speed);
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

int16 abs2(int16 val)
{
    return (val > 0) ? val : -val;
}

/* [] END OF FILE */
