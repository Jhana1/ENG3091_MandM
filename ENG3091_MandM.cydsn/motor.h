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
    
    void init_motors(void);
    void setSpeed(uint8 motor, uint8 speed);
    void setForward(uint8 motor);
    void setReverse(uint8 motor);
    void setCoast(uint8 motor);
    
    CY_ISR_PROTO(MY_SCLK_A_ISR);
#endif

/* [] END OF FILE */
