/*******************************************************************************
* File Name: OV9650_1_I2C_PM.c
* Version 3.50
*
* Description:
*  This file provides low power mode APIs for the I2C component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "OV9650_1_I2C_PVT.h"

OV9650_1_I2C_BACKUP_STRUCT OV9650_1_I2C_backup =
{
    OV9650_1_I2C_DISABLE,

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    OV9650_1_I2C_DEFAULT_XCFG,
    OV9650_1_I2C_DEFAULT_CFG,
    OV9650_1_I2C_DEFAULT_ADDR,
    LO8(OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR),
    HI8(OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR),
#else  /* (OV9650_1_I2C_UDB_IMPLEMENTED) */
    OV9650_1_I2C_DEFAULT_CFG,
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_DEFAULT_TMOUT_PERIOD,
    OV9650_1_I2C_DEFAULT_TMOUT_INTR_MASK,
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */
};

#if ((OV9650_1_I2C_FF_IMPLEMENTED) && (OV9650_1_I2C_WAKEUP_ENABLED))
    volatile uint8 OV9650_1_I2C_wakeupSource;
#endif /* ((OV9650_1_I2C_FF_IMPLEMENTED) && (OV9650_1_I2C_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: OV9650_1_I2C_SaveConfig
********************************************************************************
*
* Summary:
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Stores the component non-retention configuration registers.
*   Checked:   Disables the master, if it was enabled before, and enables
*              backup regulator of the I2C hardware. If a transaction intended
*              for component executes during this function call, it waits until
*              the current transaction is completed and I2C hardware is ready
*              to enter sleep mode. All subsequent I2C traffic is NAKed until
*              the device is put into sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  OV9650_1_I2C_backup - The global variable used to save the component
*                            configuration and non-retention registers before
*                            entering the sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void OV9650_1_I2C_SaveConfig(void) 
{
#if (OV9650_1_I2C_FF_IMPLEMENTED)
    #if (OV9650_1_I2C_WAKEUP_ENABLED)
        uint8 intState;
    #endif /* (OV9650_1_I2C_WAKEUP_ENABLED) */

    /* Store registers before enter low power mode */
    OV9650_1_I2C_backup.cfg     = OV9650_1_I2C_CFG_REG;
    OV9650_1_I2C_backup.xcfg    = OV9650_1_I2C_XCFG_REG;
    OV9650_1_I2C_backup.addr    = OV9650_1_I2C_ADDR_REG;
    OV9650_1_I2C_backup.clkDiv1 = OV9650_1_I2C_CLKDIV1_REG;
    OV9650_1_I2C_backup.clkDiv2 = OV9650_1_I2C_CLKDIV2_REG;

#if (OV9650_1_I2C_WAKEUP_ENABLED)
    /* Disable master */
    OV9650_1_I2C_CFG_REG &= (uint8) ~OV9650_1_I2C_ENABLE_MASTER;

    /* Enable backup regulator to keep block powered in low power mode */
    intState = CyEnterCriticalSection();
    OV9650_1_I2C_PWRSYS_CR1_REG |= OV9650_1_I2C_PWRSYS_CR1_I2C_REG_BACKUP;
    CyExitCriticalSection(intState);

    /* 1) Set force NACK to ignore I2C transactions;
    *  2) Wait unti I2C is ready go to Sleep; !!
    *  3) These bits are cleared on wake up.
    */
    /* Wait when block is ready for sleep */
    OV9650_1_I2C_XCFG_REG |= OV9650_1_I2C_XCFG_FORCE_NACK;
    while (0u == (OV9650_1_I2C_XCFG_REG & OV9650_1_I2C_XCFG_RDY_TO_SLEEP))
    {
    }

    /* Setup wakeup interrupt */
    OV9650_1_I2C_DisableInt();
    (void) CyIntSetVector(OV9650_1_I2C_ISR_NUMBER, &OV9650_1_I2C_WAKEUP_ISR);
    OV9650_1_I2C_wakeupSource = 0u;
    OV9650_1_I2C_EnableInt();
#endif /* (OV9650_1_I2C_WAKEUP_ENABLED) */

#else
    /* Store only address match bit */
    OV9650_1_I2C_backup.control = (OV9650_1_I2C_CFG_REG & OV9650_1_I2C_CTRL_ANY_ADDRESS_MASK);
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_TimeoutSaveConfig();
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred method to prepare the component before device enters
*  sleep mode. The Enable wakeup from Sleep Mode selection influences this
*  function implementation:
*   Unchecked: Checks current I2C component state, saves it, and disables the
*              component by calling I2C_Stop() if it is currently enabled.
*              I2C_SaveConfig() is then called to save the component
*              non-retention configuration registers.
*   Checked:   If a transaction intended for component executes during this
*              function call, it waits until the current transaction is
*              completed. All subsequent I2C traffic intended for component
*              is NAKed until the device is put to sleep mode. The address
*              match event wakes up the device.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void OV9650_1_I2C_Sleep(void) 
{
#if (OV9650_1_I2C_WAKEUP_ENABLED)
    /* Do not enable block after exit low power mode if it is wakeup source */
    OV9650_1_I2C_backup.enableState = OV9650_1_I2C_DISABLE;

    #if (OV9650_1_I2C_TIMEOUT_ENABLED)
        OV9650_1_I2C_TimeoutStop();
    #endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */

#else
    /* Store enable state */
    OV9650_1_I2C_backup.enableState = (uint8) OV9650_1_I2C_IS_ENABLED;

    if (0u != OV9650_1_I2C_backup.enableState)
    {
        OV9650_1_I2C_Stop();
    }
#endif /* (OV9650_1_I2C_WAKEUP_ENABLED) */

    OV9650_1_I2C_SaveConfig();
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_RestoreConfig
********************************************************************************
*
* Summary:
*  The Enable wakeup from Sleep Mode selection influences this function
*  implementation:
*   Unchecked: Restores the component non-retention configuration registers
*              to the state they were in before I2C_Sleep() or I2C_SaveConfig()
*              was called.
*   Checked:   Disables the backup regulator of the I2C hardware. Sets up the
*              regular component interrupt handler and generates the component
*              interrupt if it was wake up source to release the bus and
*              continue in-coming I2C transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  OV9650_1_I2C_backup - The global variable used to save the component
*                            configuration and non-retention registers before
*                            exiting the sleep mode.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Calling this function before OV9650_1_I2C_SaveConfig() or
*  OV9650_1_I2C_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void OV9650_1_I2C_RestoreConfig(void) 
{
#if (OV9650_1_I2C_FF_IMPLEMENTED)
    uint8 intState;

    if (OV9650_1_I2C_CHECK_PWRSYS_I2C_BACKUP)
    /* Low power mode was Sleep - backup regulator is enabled */
    {
        /* Enable backup regulator in active mode */
        intState = CyEnterCriticalSection();
        OV9650_1_I2C_PWRSYS_CR1_REG &= (uint8) ~OV9650_1_I2C_PWRSYS_CR1_I2C_REG_BACKUP;
        CyExitCriticalSection(intState);

        /* Restore master */
        OV9650_1_I2C_CFG_REG = OV9650_1_I2C_backup.cfg;
    }
    else
    /* Low power mode was Hibernate - backup regulator is disabled. All registers are cleared */
    {
    #if (OV9650_1_I2C_WAKEUP_ENABLED)
        /* Disable power to block before register restore */
        intState = CyEnterCriticalSection();
        OV9650_1_I2C_ACT_PWRMGR_REG  &= (uint8) ~OV9650_1_I2C_ACT_PWR_EN;
        OV9650_1_I2C_STBY_PWRMGR_REG &= (uint8) ~OV9650_1_I2C_STBY_PWR_EN;
        CyExitCriticalSection(intState);

        /* Enable component in I2C_Wakeup() after register restore */
        OV9650_1_I2C_backup.enableState = OV9650_1_I2C_ENABLE;
    #endif /* (OV9650_1_I2C_WAKEUP_ENABLED) */

        /* Restore component registers after Hibernate */
        OV9650_1_I2C_XCFG_REG    = OV9650_1_I2C_backup.xcfg;
        OV9650_1_I2C_CFG_REG     = OV9650_1_I2C_backup.cfg;
        OV9650_1_I2C_ADDR_REG    = OV9650_1_I2C_backup.addr;
        OV9650_1_I2C_CLKDIV1_REG = OV9650_1_I2C_backup.clkDiv1;
        OV9650_1_I2C_CLKDIV2_REG = OV9650_1_I2C_backup.clkDiv2;
    }

#if (OV9650_1_I2C_WAKEUP_ENABLED)
    OV9650_1_I2C_DisableInt();
    (void) CyIntSetVector(OV9650_1_I2C_ISR_NUMBER, &OV9650_1_I2C_ISR);
    if (0u != OV9650_1_I2C_wakeupSource)
    {
        /* Generate interrupt to process incoming transaction */
        OV9650_1_I2C_SetPendingInt();
    }
    OV9650_1_I2C_EnableInt();
#endif /* (OV9650_1_I2C_WAKEUP_ENABLED) */

#else
    OV9650_1_I2C_CFG_REG = OV9650_1_I2C_backup.control;
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_TimeoutRestoreConfig();
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred method to prepare the component for active mode
*  operation (when device exits sleep mode). The Enable wakeup from Sleep Mode
*  selection influences this function implementation:
*   Unchecked: Restores the component non-retention configuration registers
*              by calling I2C_RestoreConfig(). If the component was enabled
*              before the I2C_Sleep() function was called, I2C_Wakeup()
*              re-enables it.
*   Checked:   Enables  master functionality if it was enabled before sleep,
*              and disables the backup regulator of the I2C hardware.
*              The incoming transaction continues as soon as the regular
*              I2C interrupt handler is set up (global interrupts has to be
*              enabled to service I2C component interrupt).
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Calling this function before OV9650_1_I2C_SaveConfig() or
*  OV9650_1_I2C_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void OV9650_1_I2C_Wakeup(void) 
{
    OV9650_1_I2C_RestoreConfig();

    /* Restore component enable state */
    if (0u != OV9650_1_I2C_backup.enableState)
    {
        OV9650_1_I2C_Enable();
        OV9650_1_I2C_EnableInt();
    }
    else
    {
    #if (OV9650_1_I2C_TIMEOUT_ENABLED)
        OV9650_1_I2C_TimeoutEnable();
    #endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
