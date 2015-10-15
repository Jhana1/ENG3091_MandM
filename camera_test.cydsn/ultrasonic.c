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

volatile uint16 ultra[10];
volatile int ultra_i = 0;
volatile uint16 ultra_distance;
volatile uint16 var_ultra = 0;

/* ** How to use this module ** 
 * 1. Start the library with start_ultrasonic();
 * 2. The module functions automatically through an ISR, so 
 *    just monitor ultra_distance which will give the distance from the
 *    device to the obstacle in cm
 */

CY_ISR(HC_TRIG_ISR){
    ultra_distance = (MAX_COUNT - HC_Timer_ReadCounter()) / DIST_CORRECTION;
    ultra[ultra_i] = ultra_distance;
    ultra_i = (ultra_i + 1) % 10;
    int i;
    for (i = 0; i < 10; i++){
        ultra_distance += ultra[i];
    } 
    ultra_distance /= 10;
    var_ultra = 0;
    for (i = 0; i < 10; i++){
        var_ultra +=  (ultra_distance > ultra[i]) ? (ultra_distance - ultra[i]) : (ultra[i] - ultra_distance);
    }
    HC_ISR_ClearPending();
}

uint16 get_mean_ultra(void){
    return ultra_distance;
}

uint16 get_var_ultra(){
    return var_ultra;
}

void start_ultrasonic(){
    ultra_i = 0;
    ultra_distance = 0;
    HC_Timer_Start();
    HC_PWM_Start();
    HC_ISR_StartEx(HC_TRIG_ISR);
}

void stop_ultrasonic(){
    HC_Timer_Stop();
    HC_PWM_Stop();
    HC_ISR_Stop();
}

/* [] END OF FILE */
