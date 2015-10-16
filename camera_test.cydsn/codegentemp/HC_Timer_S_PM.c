/*******************************************************************************
* File Name: HC_Timer_S_PM.c
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

#include "HC_Timer_S.h"

static HC_Timer_S_backupStruct HC_Timer_S_backup;


/*******************************************************************************
* Function Name: HC_Timer_S_SaveConfig
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
*  HC_Timer_S_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HC_Timer_S_SaveConfig(void) 
{
    #if (!HC_Timer_S_UsingFixedFunction)
        HC_Timer_S_backup.TimerUdb = HC_Timer_S_ReadCounter();
        HC_Timer_S_backup.InterruptMaskValue = HC_Timer_S_STATUS_MASK;
        #if (HC_Timer_S_UsingHWCaptureCounter)
            HC_Timer_S_backup.TimerCaptureCounter = HC_Timer_S_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HC_Timer_S_UDB_CONTROL_REG_REMOVED)
            HC_Timer_S_backup.TimerControlRegister = HC_Timer_S_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HC_Timer_S_RestoreConfig
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
*  HC_Timer_S_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HC_Timer_S_RestoreConfig(void) 
{   
    #if (!HC_Timer_S_UsingFixedFunction)

        HC_Timer_S_WriteCounter(HC_Timer_S_backup.TimerUdb);
        HC_Timer_S_STATUS_MASK =HC_Timer_S_backup.InterruptMaskValue;
        #if (HC_Timer_S_UsingHWCaptureCounter)
            HC_Timer_S_SetCaptureCount(HC_Timer_S_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HC_Timer_S_UDB_CONTROL_REG_REMOVED)
            HC_Timer_S_WriteControlRegister(HC_Timer_S_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HC_Timer_S_Sleep
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
*  HC_Timer_S_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HC_Timer_S_Sleep(void) 
{
    #if(!HC_Timer_S_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HC_Timer_S_CTRL_ENABLE == (HC_Timer_S_CONTROL & HC_Timer_S_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HC_Timer_S_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HC_Timer_S_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HC_Timer_S_Stop();
    HC_Timer_S_SaveConfig();
}


/*******************************************************************************
* Function Name: HC_Timer_S_Wakeup
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
*  HC_Timer_S_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HC_Timer_S_Wakeup(void) 
{
    HC_Timer_S_RestoreConfig();
    #if(!HC_Timer_S_UDB_CONTROL_REG_REMOVED)
        if(HC_Timer_S_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HC_Timer_S_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
