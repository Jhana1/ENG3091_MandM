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

/* Global mouse configuration info in here, e.g. sample rate, resolution, etc. */
#ifndef MY_MOUSE_CONF
    #include <project.h>
    
    #define M_RES_1 0x00
    #define M_RES_2 0x01
    #define M_RES_4 0x02
    #define M_RES_8 0x03
    
    #define M_RES M_RES_4
    /* Valid sample rates are
     * 10,20,40,60,80,100,200
     */
    #define M_SAMPLE ((uint8) 80)
    
    void start_mice(void);
    void stop_mice(void);
#endif


/* [] END OF FILE */
