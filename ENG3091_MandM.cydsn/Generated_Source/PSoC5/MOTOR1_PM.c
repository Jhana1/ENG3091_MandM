/*******************************************************************************
* File Name: MOTOR1_PM.c
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

#include "MOTOR1.h"

static MOTOR1_backupStruct MOTOR1_backup;


/*******************************************************************************
* Function Name: MOTOR1_SaveConfig
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
*  MOTOR1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MOTOR1_SaveConfig(void) 
{

    #if(!MOTOR1_UsingFixedFunction)
        #if(!MOTOR1_PWMModeIsCenterAligned)
            MOTOR1_backup.PWMPeriod = MOTOR1_ReadPeriod();
        #endif /* (!MOTOR1_PWMModeIsCenterAligned) */
        MOTOR1_backup.PWMUdb = MOTOR1_ReadCounter();
        #if (MOTOR1_UseStatus)
            MOTOR1_backup.InterruptMaskValue = MOTOR1_STATUS_MASK;
        #endif /* (MOTOR1_UseStatus) */

        #if(MOTOR1_DeadBandMode == MOTOR1__B_PWM__DBM_256_CLOCKS || \
            MOTOR1_DeadBandMode == MOTOR1__B_PWM__DBM_2_4_CLOCKS)
            MOTOR1_backup.PWMdeadBandValue = MOTOR1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MOTOR1_KillModeMinTime)
             MOTOR1_backup.PWMKillCounterPeriod = MOTOR1_ReadKillTime();
        #endif /* (MOTOR1_KillModeMinTime) */

        #if(MOTOR1_UseControl)
            MOTOR1_backup.PWMControlRegister = MOTOR1_ReadControlRegister();
        #endif /* (MOTOR1_UseControl) */
    #endif  /* (!MOTOR1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR1_RestoreConfig
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
*  MOTOR1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR1_RestoreConfig(void) 
{
        #if(!MOTOR1_UsingFixedFunction)
            #if(!MOTOR1_PWMModeIsCenterAligned)
                MOTOR1_WritePeriod(MOTOR1_backup.PWMPeriod);
            #endif /* (!MOTOR1_PWMModeIsCenterAligned) */

            MOTOR1_WriteCounter(MOTOR1_backup.PWMUdb);

            #if (MOTOR1_UseStatus)
                MOTOR1_STATUS_MASK = MOTOR1_backup.InterruptMaskValue;
            #endif /* (MOTOR1_UseStatus) */

            #if(MOTOR1_DeadBandMode == MOTOR1__B_PWM__DBM_256_CLOCKS || \
                MOTOR1_DeadBandMode == MOTOR1__B_PWM__DBM_2_4_CLOCKS)
                MOTOR1_WriteDeadTime(MOTOR1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MOTOR1_KillModeMinTime)
                MOTOR1_WriteKillTime(MOTOR1_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR1_KillModeMinTime) */

            #if(MOTOR1_UseControl)
                MOTOR1_WriteControlRegister(MOTOR1_backup.PWMControlRegister);
            #endif /* (MOTOR1_UseControl) */
        #endif  /* (!MOTOR1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR1_Sleep
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
*  MOTOR1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR1_Sleep(void) 
{
    #if(MOTOR1_UseControl)
        if(MOTOR1_CTRL_ENABLE == (MOTOR1_CONTROL & MOTOR1_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR1_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR1_UseControl) */

    /* Stop component */
    MOTOR1_Stop();

    /* Save registers configuration */
    MOTOR1_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR1_Wakeup
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
*  MOTOR1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR1_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR1_RestoreConfig();

    if(MOTOR1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
