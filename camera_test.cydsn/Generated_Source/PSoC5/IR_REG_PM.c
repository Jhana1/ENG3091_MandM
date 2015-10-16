/*******************************************************************************
* File Name: IR_REG_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "IR_REG.h"

/* Check for removal by optimization */
#if !defined(IR_REG_Sync_ctrl_reg__REMOVED)

static IR_REG_BACKUP_STRUCT  IR_REG_backup = {0u};

    
/*******************************************************************************
* Function Name: IR_REG_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void IR_REG_SaveConfig(void) 
{
    IR_REG_backup.controlState = IR_REG_Control;
}


/*******************************************************************************
* Function Name: IR_REG_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void IR_REG_RestoreConfig(void) 
{
     IR_REG_Control = IR_REG_backup.controlState;
}


/*******************************************************************************
* Function Name: IR_REG_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void IR_REG_Sleep(void) 
{
    IR_REG_SaveConfig();
}


/*******************************************************************************
* Function Name: IR_REG_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void IR_REG_Wakeup(void)  
{
    IR_REG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
