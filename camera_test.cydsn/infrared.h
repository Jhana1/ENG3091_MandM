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

#ifndef MY_INFRARED
    #include <project.h>
    CY_ISR_PROTO(ir_isr);
    void start_infrared();
    uint16 get_ir_val();
    void select_front();
    void select_right();
#endif

/* [] END OF FILE */
