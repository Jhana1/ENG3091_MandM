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

#define MAX_COUNT 50000u
//d = vt, v=340m/s=340mm/ms=.34mm/us
//t=pulse/2, d = 1.7cm/us*pulse
#define DIST_CORRECTION 58.0

volatile uint16 ultra[5];
volatile int ultra_i = 0;
volatile uint16 ultra_distance_2;

/* ** How to use this module ** 
 * 1. Start the library with start_ultrasonic();
 * 2. The module functions automatically through an ISR, so 
 *    just monitor ultra_distance which will give the distance from the
 *    device to the obstacle in cm
 */


CY_ISR(HC_TRIG_ISR_2){
    ultra_distance_2 = (MAX_COUNT - HC_Timer_2_ReadCounter()) / DIST_CORRECTION;
    ultra[ultra_i] = ultra_distance_2;
    ultra_i = (ultra_i + 1) % 5;
    int i;
    for (i = 0; i < 5; i++){
        ultra_distance_2 += ultra[ultra_i];
    } 
    ultra_distance_2 /= 5;
    HC_ISR_2_ClearPending();
}

void start_ultrasonic_2(){
    ultra_i = 0;
    ultra_distance_2 = 0;
    HC_Timer_2_Start();
    HC_PWM_2_Start();
    HC_ISR_2_StartEx(HC_TRIG_ISR_2);
}

void stop_ultrasonic_2(){
    HC_Timer_2_Stop();
    HC_PWM_2_Stop();
    HC_ISR_2_Stop();
}

/* [] END OF FILE */
