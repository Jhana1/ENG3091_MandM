/*******************************************************************************
* File Name: HC_Timer_PM.c
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

#include "HC_Timer.h"

static HC_Timer_backupStruct HC_Timer_backup;


/*******************************************************************************
* Function Name: HC_Timer_SaveConfig
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
*  HC_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HC_Timer_SaveConfig(void) 
{
    #if (!HC_Timer_UsingFixedFunction)
        HC_Timer_backup.TimerUdb = HC_Timer_ReadCounter();
        HC_Timer_backup.InterruptMaskValue = HC_Timer_STATUS_MASK;
        #if (HC_Timer_UsingHWCaptureCounter)
            HC_Timer_backup.TimerCaptureCounter = HC_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HC_Timer_UDB_CONTROL_REG_REMOVED)
            HC_Timer_backup.TimerControlRegister = HC_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HC_Timer_RestoreConfig
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
*  HC_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HC_Timer_RestoreConfig(void) 
{   
    #if (!HC_Timer_UsingFixedFunction)

        HC_Timer_WriteCounter(HC_Timer_backup.TimerUdb);
        HC_Timer_STATUS_MASK =HC_Timer_backup.InterruptMaskValue;
        #if (HC_Timer_UsingHWCaptureCounter)
            HC_Timer_SetCaptureCount(HC_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HC_Timer_UDB_CONTROL_REG_REMOVED)
            HC_Timer_WriteControlRegister(HC_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HC_Timer_Sleep
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
*  HC_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HC_Timer_Sleep(void) 
{
    #if(!HC_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HC_Timer_CTRL_ENABLE == (HC_Timer_CONTROL & HC_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HC_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HC_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HC_Timer_Stop();
    HC_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: HC_Timer_Wakeup
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
*  HC_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HC_Timer_Wakeup(void) 
{
    HC_Timer_RestoreConfig();
    #if(!HC_Timer_UDB_CONTROL_REG_REMOVED)
        if(HC_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HC_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
