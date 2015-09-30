/*******************************************************************************
* File Name: MOTOR_L_PM.c
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

#include "MOTOR_L.h"

static MOTOR_L_backupStruct MOTOR_L_backup;


/*******************************************************************************
* Function Name: MOTOR_L_SaveConfig
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
*  MOTOR_L_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MOTOR_L_SaveConfig(void) 
{

    #if(!MOTOR_L_UsingFixedFunction)
        #if(!MOTOR_L_PWMModeIsCenterAligned)
            MOTOR_L_backup.PWMPeriod = MOTOR_L_ReadPeriod();
        #endif /* (!MOTOR_L_PWMModeIsCenterAligned) */
        MOTOR_L_backup.PWMUdb = MOTOR_L_ReadCounter();
        #if (MOTOR_L_UseStatus)
            MOTOR_L_backup.InterruptMaskValue = MOTOR_L_STATUS_MASK;
        #endif /* (MOTOR_L_UseStatus) */

        #if(MOTOR_L_DeadBandMode == MOTOR_L__B_PWM__DBM_256_CLOCKS || \
            MOTOR_L_DeadBandMode == MOTOR_L__B_PWM__DBM_2_4_CLOCKS)
            MOTOR_L_backup.PWMdeadBandValue = MOTOR_L_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MOTOR_L_KillModeMinTime)
             MOTOR_L_backup.PWMKillCounterPeriod = MOTOR_L_ReadKillTime();
        #endif /* (MOTOR_L_KillModeMinTime) */

        #if(MOTOR_L_UseControl)
            MOTOR_L_backup.PWMControlRegister = MOTOR_L_ReadControlRegister();
        #endif /* (MOTOR_L_UseControl) */
    #endif  /* (!MOTOR_L_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MOTOR_L_RestoreConfig
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
*  MOTOR_L_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_L_RestoreConfig(void) 
{
        #if(!MOTOR_L_UsingFixedFunction)
            #if(!MOTOR_L_PWMModeIsCenterAligned)
                MOTOR_L_WritePeriod(MOTOR_L_backup.PWMPeriod);
            #endif /* (!MOTOR_L_PWMModeIsCenterAligned) */

            MOTOR_L_WriteCounter(MOTOR_L_backup.PWMUdb);

            #if (MOTOR_L_UseStatus)
                MOTOR_L_STATUS_MASK = MOTOR_L_backup.InterruptMaskValue;
            #endif /* (MOTOR_L_UseStatus) */

            #if(MOTOR_L_DeadBandMode == MOTOR_L__B_PWM__DBM_256_CLOCKS || \
                MOTOR_L_DeadBandMode == MOTOR_L__B_PWM__DBM_2_4_CLOCKS)
                MOTOR_L_WriteDeadTime(MOTOR_L_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MOTOR_L_KillModeMinTime)
                MOTOR_L_WriteKillTime(MOTOR_L_backup.PWMKillCounterPeriod);
            #endif /* (MOTOR_L_KillModeMinTime) */

            #if(MOTOR_L_UseControl)
                MOTOR_L_WriteControlRegister(MOTOR_L_backup.PWMControlRegister);
            #endif /* (MOTOR_L_UseControl) */
        #endif  /* (!MOTOR_L_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MOTOR_L_Sleep
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
*  MOTOR_L_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MOTOR_L_Sleep(void) 
{
    #if(MOTOR_L_UseControl)
        if(MOTOR_L_CTRL_ENABLE == (MOTOR_L_CONTROL & MOTOR_L_CTRL_ENABLE))
        {
            /*Component is enabled */
            MOTOR_L_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MOTOR_L_backup.PWMEnableState = 0u;
        }
    #endif /* (MOTOR_L_UseControl) */

    /* Stop component */
    MOTOR_L_Stop();

    /* Save registers configuration */
    MOTOR_L_SaveConfig();
}


/*******************************************************************************
* Function Name: MOTOR_L_Wakeup
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
*  MOTOR_L_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MOTOR_L_Wakeup(void) 
{
     /* Restore registers values */
    MOTOR_L_RestoreConfig();

    if(MOTOR_L_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MOTOR_L_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
