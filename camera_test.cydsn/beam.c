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
 
uint8 beam_broken(){
    BEAM_BREAK_TIMER_Start();
    BEAM_BREAK_TIMER_WriteCounter(65535);
    BEAM_Clock_Start();
    CyDelay(350);
    BEAM_Clock_Stop();
    uint8 broken = BEAM_BREAK_TIMER_ReadCounter() < 36000;
    BEAM_BREAK_TIMER_Stop();
    CyDelay(300);
    return broken;
}

/* [] END OF FILE */
