/*******************************************************************************
* File Name: HC_PWM_S_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "HC_PWM_S.h"

static HC_PWM_S_backupStruct HC_PWM_S_backup;


/*******************************************************************************
* Function Name: HC_PWM_S_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HC_PWM_S_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HC_PWM_S_SaveConfig(void) 
{

    #if(!HC_PWM_S_UsingFixedFunction)
        #if(!HC_PWM_S_PWMModeIsCenterAligned)
            HC_PWM_S_backup.PWMPeriod = HC_PWM_S_ReadPeriod();
        #endif /* (!HC_PWM_S_PWMModeIsCenterAligned) */
        HC_PWM_S_backup.PWMUdb = HC_PWM_S_ReadCounter();
        #if (HC_PWM_S_UseStatus)
            HC_PWM_S_backup.InterruptMaskValue = HC_PWM_S_STATUS_MASK;
        #endif /* (HC_PWM_S_UseStatus) */

        #if(HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_256_CLOCKS || \
            HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_2_4_CLOCKS)
            HC_PWM_S_backup.PWMdeadBandValue = HC_PWM_S_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(HC_PWM_S_KillModeMinTime)
             HC_PWM_S_backup.PWMKillCounterPeriod = HC_PWM_S_ReadKillTime();
        #endif /* (HC_PWM_S_KillModeMinTime) */

        #if(HC_PWM_S_UseControl)
            HC_PWM_S_backup.PWMControlRegister = HC_PWM_S_ReadControlRegister();
        #endif /* (HC_PWM_S_UseControl) */
    #endif  /* (!HC_PWM_S_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HC_PWM_S_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HC_PWM_S_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HC_PWM_S_RestoreConfig(void) 
{
        #if(!HC_PWM_S_UsingFixedFunction)
            #if(!HC_PWM_S_PWMModeIsCenterAligned)
                HC_PWM_S_WritePeriod(HC_PWM_S_backup.PWMPeriod);
            #endif /* (!HC_PWM_S_PWMModeIsCenterAligned) */

            HC_PWM_S_WriteCounter(HC_PWM_S_backup.PWMUdb);

            #if (HC_PWM_S_UseStatus)
                HC_PWM_S_STATUS_MASK = HC_PWM_S_backup.InterruptMaskValue;
            #endif /* (HC_PWM_S_UseStatus) */

            #if(HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_256_CLOCKS || \
                HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_2_4_CLOCKS)
                HC_PWM_S_WriteDeadTime(HC_PWM_S_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(HC_PWM_S_KillModeMinTime)
                HC_PWM_S_WriteKillTime(HC_PWM_S_backup.PWMKillCounterPeriod);
            #endif /* (HC_PWM_S_KillModeMinTime) */

            #if(HC_PWM_S_UseControl)
                HC_PWM_S_WriteControlRegister(HC_PWM_S_backup.PWMControlRegister);
            #endif /* (HC_PWM_S_UseControl) */
        #endif  /* (!HC_PWM_S_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: HC_PWM_S_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HC_PWM_S_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HC_PWM_S_Sleep(void) 
{
    #if(HC_PWM_S_UseControl)
        if(HC_PWM_S_CTRL_ENABLE == (HC_PWM_S_CONTROL & HC_PWM_S_CTRL_ENABLE))
        {
            /*Component is enabled */
            HC_PWM_S_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            HC_PWM_S_backup.PWMEnableState = 0u;
        }
    #endif /* (HC_PWM_S_UseControl) */

    /* Stop component */
    HC_PWM_S_Stop();

    /* Save registers configuration */
    HC_PWM_S_SaveConfig();
}


/*******************************************************************************
* Function Name: HC_PWM_S_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HC_PWM_S_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HC_PWM_S_Wakeup(void) 
{
     /* Restore registers values */
    HC_PWM_S_RestoreConfig();

    if(HC_PWM_S_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        HC_PWM_S_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
