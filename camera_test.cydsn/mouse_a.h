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



#ifndef MY_SCLK_A_ISR
    #include <project.h>
    
    void mouse_a_init(void);
    void reset_sclk_a_isr(void);
    void mouse_a_write(uint8 data);
    
    CY_ISR_PROTO(MY_SCLK_A_ISR);
#endif
/* [] END OF FILE */
