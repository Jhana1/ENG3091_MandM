/*******************************************************************************
* File Name: Arm_PWM_PM.c
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

#include "Arm_PWM.h"

static Arm_PWM_backupStruct Arm_PWM_backup;


/*******************************************************************************
* Function Name: Arm_PWM_SaveConfig
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
*  Arm_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Arm_PWM_SaveConfig(void) 
{

    #if(!Arm_PWM_UsingFixedFunction)
        #if(!Arm_PWM_PWMModeIsCenterAligned)
            Arm_PWM_backup.PWMPeriod = Arm_PWM_ReadPeriod();
        #endif /* (!Arm_PWM_PWMModeIsCenterAligned) */
        Arm_PWM_backup.PWMUdb = Arm_PWM_ReadCounter();
        #if (Arm_PWM_UseStatus)
            Arm_PWM_backup.InterruptMaskValue = Arm_PWM_STATUS_MASK;
        #endif /* (Arm_PWM_UseStatus) */

        #if(Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_256_CLOCKS || \
            Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_2_4_CLOCKS)
            Arm_PWM_backup.PWMdeadBandValue = Arm_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Arm_PWM_KillModeMinTime)
             Arm_PWM_backup.PWMKillCounterPeriod = Arm_PWM_ReadKillTime();
        #endif /* (Arm_PWM_KillModeMinTime) */

        #if(Arm_PWM_UseControl)
            Arm_PWM_backup.PWMControlRegister = Arm_PWM_ReadControlRegister();
        #endif /* (Arm_PWM_UseControl) */
    #endif  /* (!Arm_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Arm_PWM_RestoreConfig
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
*  Arm_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Arm_PWM_RestoreConfig(void) 
{
        #if(!Arm_PWM_UsingFixedFunction)
            #if(!Arm_PWM_PWMModeIsCenterAligned)
                Arm_PWM_WritePeriod(Arm_PWM_backup.PWMPeriod);
            #endif /* (!Arm_PWM_PWMModeIsCenterAligned) */

            Arm_PWM_WriteCounter(Arm_PWM_backup.PWMUdb);

            #if (Arm_PWM_UseStatus)
                Arm_PWM_STATUS_MASK = Arm_PWM_backup.InterruptMaskValue;
            #endif /* (Arm_PWM_UseStatus) */

            #if(Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_256_CLOCKS || \
                Arm_PWM_DeadBandMode == Arm_PWM__B_PWM__DBM_2_4_CLOCKS)
                Arm_PWM_WriteDeadTime(Arm_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Arm_PWM_KillModeMinTime)
                Arm_PWM_WriteKillTime(Arm_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Arm_PWM_KillModeMinTime) */

            #if(Arm_PWM_UseControl)
                Arm_PWM_WriteControlRegister(Arm_PWM_backup.PWMControlRegister);
            #endif /* (Arm_PWM_UseControl) */
        #endif  /* (!Arm_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Arm_PWM_Sleep
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
*  Arm_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Arm_PWM_Sleep(void) 
{
    #if(Arm_PWM_UseControl)
        if(Arm_PWM_CTRL_ENABLE == (Arm_PWM_CONTROL & Arm_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Arm_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Arm_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Arm_PWM_UseControl) */

    /* Stop component */
    Arm_PWM_Stop();

    /* Save registers configuration */
    Arm_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Arm_PWM_Wakeup
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
*  Arm_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Arm_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Arm_PWM_RestoreConfig();

    if(Arm_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Arm_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
