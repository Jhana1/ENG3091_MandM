/*******************************************************************************
* File Name: MOTOR2_PM.c
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

#include "MOTOR2.h"

static MOTOR2_backupStruct MOTOR2_backup;


/*******************************************************************************
* Function Name: MOTOR2_SaveConfig
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
*  MOTOR2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MOTOR2_SaveConfig(void) 
{

    #if(!MOTOR2_UsingFixedFunction)
        #if(!MOTOR2_PWMModeIsCenterAligned)
            MOTOR2_backup.PWMPeriod = MOTOR2_ReadPeriod();
        #endif /* (!MOTOR2_PWMModeIsCenterAligned) */
        MOTOR2_backup.PWMUdb = MOTOR2_ReadCounter();
        #if (MOTOR2_UseStatus)
            MOTOR2_backup.InterruptMaskValue = MOTOR2_STATUS_MASK;
        #endif /* (MOTOR2_UseStatus) */

        #if(MOTOR2_DeadBandMode == MOTOR2__B_PWM__DBM_256_CLOCKS || \
            MOTOR2_DeadBandMode == MOTOR2__B_PWM__DBM_2_4_CLOCKS)
            MOTOR2_backup.PWMdeadBandValue = MOTOR2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MOTOR2_KillModeMinTime)
             MOTOR2_backup.PWMKillCounterPeriod = MOTOR2_ReadKillTime();
        #endif /* (MOTOR2_KillModeMinTime) */

        #if(MOTOR2_UseControl)
            MOTOR2_backup.PWMControlRegister = MOTOR2_ReadControlRegister();
        #endif /* (MOTOR2_UseControl) */
    #endif  /* (!MOTOR2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR2_RestoreConfig
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
*  MOTOR2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR2_RestoreConfig(void) 
{
        #if(!MOTOR2_UsingFixedFunction)
            #if(!MOTOR2_PWMModeIsCenterAligned)
                MOTOR2_WritePeriod(MOTOR2_backup.PWMPeriod);
            #endif /* (!MOTOR2_PWMModeIsCenterAligned) */

            MOTOR2_WriteCounter(MOTOR2_backup.PWMUdb);

            #if (MOTOR2_UseStatus)
                MOTOR2_STATUS_MASK = MOTOR2_backup.InterruptMaskValue;
            #endif /* (MOTOR2_UseStatus) */

            #if(MOTOR2_DeadBandMode == MOTOR2__B_PWM__DBM_256_CLOCKS || \
                MOTOR2_DeadBandMode == MOTOR2__B_PWM__DBM_2_4_CLOCKS)
                MOTOR2_WriteDeadTime(MOTOR2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MOTOR2_KillModeMinTime)
                MOTOR2_WriteKillTime(MOTOR2_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR2_KillModeMinTime) */

            #if(MOTOR2_UseControl)
                MOTOR2_WriteControlRegister(MOTOR2_backup.PWMControlRegister);
            #endif /* (MOTOR2_UseControl) */
        #endif  /* (!MOTOR2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR2_Sleep
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
*  MOTOR2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR2_Sleep(void) 
{
    #if(MOTOR2_UseControl)
        if(MOTOR2_CTRL_ENABLE == (MOTOR2_CONTROL & MOTOR2_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR2_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR2_UseControl) */

    /* Stop component */
    MOTOR2_Stop();

    /* Save registers configuration */
    MOTOR2_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR2_Wakeup
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
*  MOTOR2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR2_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR2_RestoreConfig();

    if(MOTOR2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
