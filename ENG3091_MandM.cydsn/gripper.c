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

/* [] END OF FILE */

#include <project.h>
#include <stdio.h>

/* SERVO CONSTANTS */
#define MINIMUM_POINT 18
#define MAXIMUM_POINT 50
#define OPTIMAL_GRIP_POINT 29
#define PICKUP_ANGLE_POINT 19
#define PERIOD 799

/* EXTRA CONSTANTS */
#define PAUSE 50
 


int PWM_VAL = 25;
char outString[40];

void init_gripper(){
    int i;
    /* Initialize the motor controller */
    Gripper_PWM_Start();
    Gripper_PWM_WriteCompare(MAXIMUM_POINT);
    while(1)
    {   
        for(i = 0; i <= 100; i += 2)
        {
            Gripper_PWM_WriteCompare(i);
            CyDelay(500);
            Gripper_PWM_WriteCompare(i-1);
            CyDelay(500);
        }
    }
}

void pickup_puck(){
    /* Set Servo to Pickup Flat Puck */
    Gripper_PWM_WriteCompare(OPTIMAL_GRIP_POINT);
    CyDelay(PAUSE);
    //TODO: Implement Potential Power Saving by Killing the PWM???
}

void drop_puck(){
    /* Set Servo to Drop Any Puck*/
    Gripper_PWM_WriteCompare(MAXIMUM_POINT);
    CyDelay(PAUSE);
    //TODO: Implement Potential Power Saving by Killing the PWM???
}

void pickup_angled_puck(){
    /* Set Servo to Pickup Angled Puck*/
    Gripper_PWM_WriteCompare(PICKUP_ANGLE_POINT);
    CyDelay(PAUSE);
}




/* LEGACY FUNCTIONS FOR TESTING */

void inc_gripper(){
    Gripper_PWM_WriteCompare(++PWM_VAL);
    LCD_ClearDisplay();
    sprintf(outString, "Servo Value: %d",PWM_VAL);
    LCD_PosPrintString(0, 0, outString);
    //for(PWM_VAL = 18; PWM_VAL <= 50; PWM_VAL++)
    //{
    //    Gripper_PWM_WriteCompare(PWM_VAL);
    //    CyDelay(10);
    //}
}

void dec_gripper(){
    Gripper_PWM_WriteCompare(--PWM_VAL);
    LCD_ClearDisplay();
    sprintf(outString, "Servo Value: %d",PWM_VAL);
    LCD_PosPrintString(0, 0, outString);
    //for(PWM_VAL = 50; PWM_VAL >= 18; PWM_VAL--)
    //{
    //    Gripper_PWM_WriteCompare(PWM_VAL);
    //    CyDelay(10);
    //}
}

/* [] END OF FILE */
