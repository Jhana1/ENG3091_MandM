/*******************************************************************************
* File Name: CS_Buttons_PWM_PM.c
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

#include "CS_Buttons_PWM.h"

static CS_Buttons_PWM_backupStruct CS_Buttons_PWM_backup;


/*******************************************************************************
* Function Name: CS_Buttons_PWM_SaveConfig
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
*  CS_Buttons_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void CS_Buttons_PWM_SaveConfig(void) 
{

    #if(!CS_Buttons_PWM_UsingFixedFunction)
        #if(!CS_Buttons_PWM_PWMModeIsCenterAligned)
            CS_Buttons_PWM_backup.PWMPeriod = CS_Buttons_PWM_ReadPeriod();
        #endif /* (!CS_Buttons_PWM_PWMModeIsCenterAligned) */
        CS_Buttons_PWM_backup.PWMUdb = CS_Buttons_PWM_ReadCounter();
        #if (CS_Buttons_PWM_UseStatus)
            CS_Buttons_PWM_backup.InterruptMaskValue = CS_Buttons_PWM_STATUS_MASK;
        #endif /* (CS_Buttons_PWM_UseStatus) */

        #if(CS_Buttons_PWM_DeadBandMode == CS_Buttons_PWM__B_PWM__DBM_256_CLOCKS || \
            CS_Buttons_PWM_DeadBandMode == CS_Buttons_PWM__B_PWM__DBM_2_4_CLOCKS)
            CS_Buttons_PWM_backup.PWMdeadBandValue = CS_Buttons_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(CS_Buttons_PWM_KillModeMinTime)
             CS_Buttons_PWM_backup.PWMKillCounterPeriod = CS_Buttons_PWM_ReadKillTime();
        #endif /* (CS_Buttons_PWM_KillModeMinTime) */

        #if(CS_Buttons_PWM_UseControl)
            CS_Buttons_PWM_backup.PWMControlRegister = CS_Buttons_PWM_ReadControlRegister();
        #endif /* (CS_Buttons_PWM_UseControl) */
    #endif  /* (!CS_Buttons_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CS_Buttons_PWM_RestoreConfig
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
*  CS_Buttons_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CS_Buttons_PWM_RestoreConfig(void) 
{
        #if(!CS_Buttons_PWM_UsingFixedFunction)
            #if(!CS_Buttons_PWM_PWMModeIsCenterAligned)
                CS_Buttons_PWM_WritePeriod(CS_Buttons_PWM_backup.PWMPeriod);
            #endif /* (!CS_Buttons_PWM_PWMModeIsCenterAligned) */

            CS_Buttons_PWM_WriteCounter(CS_Buttons_PWM_backup.PWMUdb);

            #if (CS_Buttons_PWM_UseStatus)
                CS_Buttons_PWM_STATUS_MASK = CS_Buttons_PWM_backup.InterruptMaskValue;
            #endif /* (CS_Buttons_PWM_UseStatus) */

            #if(CS_Buttons_PWM_DeadBandMode == CS_Buttons_PWM__B_PWM__DBM_256_CLOCKS || \
                CS_Buttons_PWM_DeadBandMode == CS_Buttons_PWM__B_PWM__DBM_2_4_CLOCKS)
                CS_Buttons_PWM_WriteDeadTime(CS_Buttons_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(CS_Buttons_PWM_KillModeMinTime)
                CS_Buttons_PWM_WriteKillTime(CS_Buttons_PWM_backup.PWMKillCounterPeriod);
            #endif /* (CS_Buttons_PWM_KillModeMinTime) */

            #if(CS_Buttons_PWM_UseControl)
                CS_Buttons_PWM_WriteControlRegister(CS_Buttons_PWM_backup.PWMControlRegister);
            #endif /* (CS_Buttons_PWM_UseControl) */
        #endif  /* (!CS_Buttons_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: CS_Buttons_PWM_Sleep
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
*  CS_Buttons_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CS_Buttons_PWM_Sleep(void) 
{
    #if(CS_Buttons_PWM_UseControl)
        if(CS_Buttons_PWM_CTRL_ENABLE == (CS_Buttons_PWM_CONTROL & CS_Buttons_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            CS_Buttons_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            CS_Buttons_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (CS_Buttons_PWM_UseControl) */

    /* Stop component */
    CS_Buttons_PWM_Stop();

    /* Save registers configuration */
    CS_Buttons_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: CS_Buttons_PWM_Wakeup
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
*  CS_Buttons_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CS_Buttons_PWM_Wakeup(void) 
{
     /* Restore registers values */
    CS_Buttons_PWM_RestoreConfig();

    if(CS_Buttons_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        CS_Buttons_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
