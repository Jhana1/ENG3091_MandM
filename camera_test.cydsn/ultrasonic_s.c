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
#include <stdio.h>
#include <math.h>

#define MAX_COUNT 50000u
//d = vt, v=340m/s=340mm/ms=.34mm/us
//t=pulse/2, d = 1.7cm/us*pulse
#define DIST_CORRECTION 58.0

volatile uint16 ultra_s[10];
volatile int ultra_i_s = 0;
volatile uint16 ultra_distance_s;
volatile uint16 var_ultra_s = 0;

/* ** How to use this module ** 
 * 1. Start the library with start_ultrasonic();
 * 2. The module functions automatically through an ISR, so 
 *    just monitor ultra_distance which will give the distance from the
 *    device to the obstacle in cm
 */

char outString[16];

#define POS_PRINTF(R,C,X,...) \
 {sprintf(outString, X, __VA_ARGS__); LCD_Position(R, C); LCD_PrintString(outString);}

uint16 get_mean_ultra_s(void){
    return ultra_distance_s;
}

uint16 get_var_ultra_s(){
    return var_ultra_s;
}

void select_stack(){
    if (HC_REG_Read() != 0x00){
        HC_REG_Write(0x00);
    }
}
void select_left(){
    if (HC_REG_Read() == 0x00){
        HC_REG_Write(0xFF);
    }
}


int myabss(x){
    if (x < 0){
        return -x;
    } else {
        return x;
    }
}

CY_ISR(HC_TRIG_ISR_S){
    ultra_distance_s = (MAX_COUNT - HC_Timer_S_ReadCounter()) / DIST_CORRECTION;
    ultra_s[ultra_i_s] = ultra_distance_s;
    ultra_i_s = (ultra_i_s + 1) % 10;
    int i;
    for (i = 0; i < 10; i++){
        ultra_distance_s += ultra_s[i];
    } 
    ultra_distance_s /= 10;
    var_ultra_s = 0;
    for (i = 0; i < 10; i++){
        var_ultra_s += myabss(ultra_distance_s - ultra_s[i]);
    }
    HC_ISR_S_ClearPending();
}

void start_ultrasonic_s(){
    ultra_i_s = 0;
    ultra_distance_s = 0;
    HC_Timer_S_Start();
    HC_PWM_S_Start();
    HC_ISR_S_StartEx(HC_TRIG_ISR_S);
}

void stop_ultrasonic_s(){
    HC_Timer_S_Stop();
    HC_PWM_S_Stop();
    HC_ISR_S_Stop();
}

/* [] END OF FILE */
