/*******************************************************************************
* File Name: BEAM_BREAK_TIMER_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "BEAM_BREAK_TIMER.h"

static BEAM_BREAK_TIMER_backupStruct BEAM_BREAK_TIMER_backup;


/*******************************************************************************
* Function Name: BEAM_BREAK_TIMER_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BEAM_BREAK_TIMER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BEAM_BREAK_TIMER_SaveConfig(void) 
{
    #if (!BEAM_BREAK_TIMER_UsingFixedFunction)
        BEAM_BREAK_TIMER_backup.TimerUdb = BEAM_BREAK_TIMER_ReadCounter();
        BEAM_BREAK_TIMER_backup.InterruptMaskValue = BEAM_BREAK_TIMER_STATUS_MASK;
        #if (BEAM_BREAK_TIMER_UsingHWCaptureCounter)
            BEAM_BREAK_TIMER_backup.TimerCaptureCounter = BEAM_BREAK_TIMER_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
            BEAM_BREAK_TIMER_backup.TimerControlRegister = BEAM_BREAK_TIMER_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BEAM_BREAK_TIMER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BEAM_BREAK_TIMER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BEAM_BREAK_TIMER_RestoreConfig(void) 
{   
    #if (!BEAM_BREAK_TIMER_UsingFixedFunction)

        BEAM_BREAK_TIMER_WriteCounter(BEAM_BREAK_TIMER_backup.TimerUdb);
        BEAM_BREAK_TIMER_STATUS_MASK =BEAM_BREAK_TIMER_backup.InterruptMaskValue;
        #if (BEAM_BREAK_TIMER_UsingHWCaptureCounter)
            BEAM_BREAK_TIMER_SetCaptureCount(BEAM_BREAK_TIMER_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
            BEAM_BREAK_TIMER_WriteControlRegister(BEAM_BREAK_TIMER_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BEAM_BREAK_TIMER_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BEAM_BREAK_TIMER_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BEAM_BREAK_TIMER_Sleep(void) 
{
    #if(!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BEAM_BREAK_TIMER_CTRL_ENABLE == (BEAM_BREAK_TIMER_CONTROL & BEAM_BREAK_TIMER_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BEAM_BREAK_TIMER_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BEAM_BREAK_TIMER_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BEAM_BREAK_TIMER_Stop();
    BEAM_BREAK_TIMER_SaveConfig();
}


/*******************************************************************************
* Function Name: BEAM_BREAK_TIMER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  BEAM_BREAK_TIMER_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BEAM_BREAK_TIMER_Wakeup(void) 
{
    BEAM_BREAK_TIMER_RestoreConfig();
    #if(!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
        if(BEAM_BREAK_TIMER_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BEAM_BREAK_TIMER_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
