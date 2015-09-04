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

#ifndef MY_NAVIGATION
    #include <project.h>
    struct Position {
        double x;
        double y;
        double angle;
    };
    
    void reset_navigation();
    void init_navigation();
    void refresh_position();
    
    CY_ISR_PROTO(REFRESH_POSITION);
#endif


/* [] END OF FILE */
