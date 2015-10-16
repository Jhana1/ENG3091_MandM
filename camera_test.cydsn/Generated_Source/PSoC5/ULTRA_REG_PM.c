/*******************************************************************************
* File Name: ULTRA_REG_PM.c
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

#include "ULTRA_REG.h"

/* Check for removal by optimization */
#if !defined(ULTRA_REG_Sync_ctrl_reg__REMOVED)

static ULTRA_REG_BACKUP_STRUCT  ULTRA_REG_backup = {0u};

    
/*******************************************************************************
* Function Name: ULTRA_REG_SaveConfig
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
void ULTRA_REG_SaveConfig(void) 
{
    ULTRA_REG_backup.controlState = ULTRA_REG_Control;
}


/*******************************************************************************
* Function Name: ULTRA_REG_RestoreConfig
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
void ULTRA_REG_RestoreConfig(void) 
{
     ULTRA_REG_Control = ULTRA_REG_backup.controlState;
}


/*******************************************************************************
* Function Name: ULTRA_REG_Sleep
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
void ULTRA_REG_Sleep(void) 
{
    ULTRA_REG_SaveConfig();
}


/*******************************************************************************
* Function Name: ULTRA_REG_Wakeup
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
void ULTRA_REG_Wakeup(void)  
{
    ULTRA_REG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
