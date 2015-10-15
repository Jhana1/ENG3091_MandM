/*******************************************************************************
* File Name: IR_LEFT_Timer_PM.c
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

#include "IR_LEFT_Timer.h"

static IR_LEFT_Timer_backupStruct IR_LEFT_Timer_backup;


/*******************************************************************************
* Function Name: IR_LEFT_Timer_SaveConfig
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
*  IR_LEFT_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void IR_LEFT_Timer_SaveConfig(void) 
{
    #if (!IR_LEFT_Timer_UsingFixedFunction)
        IR_LEFT_Timer_backup.TimerUdb = IR_LEFT_Timer_ReadCounter();
        IR_LEFT_Timer_backup.InterruptMaskValue = IR_LEFT_Timer_STATUS_MASK;
        #if (IR_LEFT_Timer_UsingHWCaptureCounter)
            IR_LEFT_Timer_backup.TimerCaptureCounter = IR_LEFT_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!IR_LEFT_Timer_UDB_CONTROL_REG_REMOVED)
            IR_LEFT_Timer_backup.TimerControlRegister = IR_LEFT_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: IR_LEFT_Timer_RestoreConfig
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
*  IR_LEFT_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void IR_LEFT_Timer_RestoreConfig(void) 
{   
    #if (!IR_LEFT_Timer_UsingFixedFunction)

        IR_LEFT_Timer_WriteCounter(IR_LEFT_Timer_backup.TimerUdb);
        IR_LEFT_Timer_STATUS_MASK =IR_LEFT_Timer_backup.InterruptMaskValue;
        #if (IR_LEFT_Timer_UsingHWCaptureCounter)
            IR_LEFT_Timer_SetCaptureCount(IR_LEFT_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!IR_LEFT_Timer_UDB_CONTROL_REG_REMOVED)
            IR_LEFT_Timer_WriteControlRegister(IR_LEFT_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: IR_LEFT_Timer_Sleep
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
*  IR_LEFT_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void IR_LEFT_Timer_Sleep(void) 
{
    #if(!IR_LEFT_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(IR_LEFT_Timer_CTRL_ENABLE == (IR_LEFT_Timer_CONTROL & IR_LEFT_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            IR_LEFT_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            IR_LEFT_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    IR_LEFT_Timer_Stop();
    IR_LEFT_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: IR_LEFT_Timer_Wakeup
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
*  IR_LEFT_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IR_LEFT_Timer_Wakeup(void) 
{
    IR_LEFT_Timer_RestoreConfig();
    #if(!IR_LEFT_Timer_UDB_CONTROL_REG_REMOVED)
        if(IR_LEFT_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                IR_LEFT_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
