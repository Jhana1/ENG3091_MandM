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
        int32 x;
        int32 y;
        int16 angle;
    };
    
    void reset_navigation();
    void reset_delta_y_distance();
    void calculate_circular_functions();
    void start_navigation();
    void update_position();
    
    //CY_ISR_PROTO(REFRESH_POSITION);
#endif


/* [] END OF FILE */
