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

/* ***** ARM IS THE BLUE CABLE ******/

/* SERVO CONSTANTS */
#define PERIOD 799
/* EXTRA CONSTANTS */
#define PAUSE 50
 
//uint8 arm_levels[6] = {22, 30, 35, 40, 45, 50};
uint8 arm_levels[6] = {50, 58, 63, 68, 73, 78};

void arm_set_level(int level){
    Arm_PWM_WriteCompare(arm_levels[level]);
}

void start_arm(){
    int i;
    /* Initialize the motor controller */
    Arm_PWM_Start();
    arm_set_level(0);
}



/* [] END OF FILE */
