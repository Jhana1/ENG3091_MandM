/*******************************************************************************
* File Name: Arm_PM.c
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

#include "Arm.h"

static Arm_backupStruct Arm_backup;


/*******************************************************************************
* Function Name: Arm_SaveConfig
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
*  Arm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Arm_SaveConfig(void) 
{

    #if(!Arm_UsingFixedFunction)
        #if(!Arm_PWMModeIsCenterAligned)
            Arm_backup.PWMPeriod = Arm_ReadPeriod();
        #endif /* (!Arm_PWMModeIsCenterAligned) */
        Arm_backup.PWMUdb = Arm_ReadCounter();
        #if (Arm_UseStatus)
            Arm_backup.InterruptMaskValue = Arm_STATUS_MASK;
        #endif /* (Arm_UseStatus) */

        #if(Arm_DeadBandMode == Arm__B_PWM__DBM_256_CLOCKS || \
            Arm_DeadBandMode == Arm__B_PWM__DBM_2_4_CLOCKS)
            Arm_backup.PWMdeadBandValue = Arm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Arm_KillModeMinTime)
             Arm_backup.PWMKillCounterPeriod = Arm_ReadKillTime();
        #endif /* (Arm_KillModeMinTime) */

        #if(Arm_UseControl)
            Arm_backup.PWMControlRegister = Arm_ReadControlRegister();
        #endif /* (Arm_UseControl) */
    #endif  /* (!Arm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Arm_RestoreConfig
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
*  Arm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Arm_RestoreConfig(void) 
{
        #if(!Arm_UsingFixedFunction)
            #if(!Arm_PWMModeIsCenterAligned)
                Arm_WritePeriod(Arm_backup.PWMPeriod);
            #endif /* (!Arm_PWMModeIsCenterAligned) */

            Arm_WriteCounter(Arm_backup.PWMUdb);

            #if (Arm_UseStatus)
                Arm_STATUS_MASK = Arm_backup.InterruptMaskValue;
            #endif /* (Arm_UseStatus) */

            #if(Arm_DeadBandMode == Arm__B_PWM__DBM_256_CLOCKS || \
                Arm_DeadBandMode == Arm__B_PWM__DBM_2_4_CLOCKS)
                Arm_WriteDeadTime(Arm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Arm_KillModeMinTime)
                Arm_WriteKillTime(Arm_backup.PWMKillCounterPeriod);
            #endif /* (Arm_KillModeMinTime) */

            #if(Arm_UseControl)
                Arm_WriteControlRegister(Arm_backup.PWMControlRegister);
            #endif /* (Arm_UseControl) */
        #endif  /* (!Arm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Arm_Sleep
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
*  Arm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Arm_Sleep(void) 
{
    #if(Arm_UseControl)
        if(Arm_CTRL_ENABLE == (Arm_CONTROL & Arm_CTRL_ENABLE))
        {
            /*Component is enabled */
            Arm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Arm_backup.PWMEnableState = 0u;
        }
    #endif /* (Arm_UseControl) */

    /* Stop component */
    Arm_Stop();

    /* Save registers configuration */
    Arm_SaveConfig();
}


/*******************************************************************************
* Function Name: Arm_Wakeup
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
*  Arm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Arm_Wakeup(void) 
{
     /* Restore registers values */
    Arm_RestoreConfig();

    if(Arm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Arm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
