/*******************************************************************************
* File Name: MOTOR_R_PM.c
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

#include "MOTOR_R.h"

static MOTOR_R_backupStruct MOTOR_R_backup;


/*******************************************************************************
* Function Name: MOTOR_R_SaveConfig
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
*  MOTOR_R_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MOTOR_R_SaveConfig(void) 
{

    #if(!MOTOR_R_UsingFixedFunction)
        #if(!MOTOR_R_PWMModeIsCenterAligned)
            MOTOR_R_backup.PWMPeriod = MOTOR_R_ReadPeriod();
        #endif /* (!MOTOR_R_PWMModeIsCenterAligned) */
        MOTOR_R_backup.PWMUdb = MOTOR_R_ReadCounter();
        #if (MOTOR_R_UseStatus)
            MOTOR_R_backup.InterruptMaskValue = MOTOR_R_STATUS_MASK;
        #endif /* (MOTOR_R_UseStatus) */

        #if(MOTOR_R_DeadBandMode == MOTOR_R__B_PWM__DBM_256_CLOCKS || \
            MOTOR_R_DeadBandMode == MOTOR_R__B_PWM__DBM_2_4_CLOCKS)
            MOTOR_R_backup.PWMdeadBandValue = MOTOR_R_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MOTOR_R_KillModeMinTime)
             MOTOR_R_backup.PWMKillCounterPeriod = MOTOR_R_ReadKillTime();
        #endif /* (MOTOR_R_KillModeMinTime) */

        #if(MOTOR_R_UseControl)
            MOTOR_R_backup.PWMControlRegister = MOTOR_R_ReadControlRegister();
        #endif /* (MOTOR_R_UseControl) */
    #endif  /* (!MOTOR_R_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR_R_RestoreConfig
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
*  MOTOR_R_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_R_RestoreConfig(void) 
{
        #if(!MOTOR_R_UsingFixedFunction)
            #if(!MOTOR_R_PWMModeIsCenterAligned)
                MOTOR_R_WritePeriod(MOTOR_R_backup.PWMPeriod);
            #endif /* (!MOTOR_R_PWMModeIsCenterAligned) */

            MOTOR_R_WriteCounter(MOTOR_R_backup.PWMUdb);

            #if (MOTOR_R_UseStatus)
                MOTOR_R_STATUS_MASK = MOTOR_R_backup.InterruptMaskValue;
            #endif /* (MOTOR_R_UseStatus) */

            #if(MOTOR_R_DeadBandMode == MOTOR_R__B_PWM__DBM_256_CLOCKS || \
                MOTOR_R_DeadBandMode == MOTOR_R__B_PWM__DBM_2_4_CLOCKS)
                MOTOR_R_WriteDeadTime(MOTOR_R_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MOTOR_R_KillModeMinTime)
                MOTOR_R_WriteKillTime(MOTOR_R_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR_R_KillModeMinTime) */

            #if(MOTOR_R_UseControl)
                MOTOR_R_WriteControlRegister(MOTOR_R_backup.PWMControlRegister);
            #endif /* (MOTOR_R_UseControl) */
        #endif  /* (!MOTOR_R_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR_R_Sleep
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
*  MOTOR_R_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR_R_Sleep(void) 
{
    #if(MOTOR_R_UseControl)
        if(MOTOR_R_CTRL_ENABLE == (MOTOR_R_CONTROL & MOTOR_R_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR_R_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR_R_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR_R_UseControl) */

    /* Stop component */
    MOTOR_R_Stop();

    /* Save registers configuration */
    MOTOR_R_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR_R_Wakeup
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
*  MOTOR_R_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_R_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR_R_RestoreConfig();

    if(MOTOR_R_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR_R_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
