/*******************************************************************************
* File Name: Camera_I2C_PM.c
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

#include "Camera_I2C_PVT.h"

Camera_I2C_BACKUP_STRUCT Camera_I2C_backup =
{
    Camera_I2C_DISABLE,

#if (Camera_I2C_FF_IMPLEMENTED)
    Camera_I2C_DEFAULT_XCFG,
    Camera_I2C_DEFAULT_CFG,
    Camera_I2C_DEFAULT_ADDR,
    LO8(Camera_I2C_DEFAULT_DIVIDE_FACTOR),
    HI8(Camera_I2C_DEFAULT_DIVIDE_FACTOR),
#else  /* (Camera_I2C_UDB_IMPLEMENTED) */
    Camera_I2C_DEFAULT_CFG,
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_DEFAULT_TMOUT_PERIOD,
    Camera_I2C_DEFAULT_TMOUT_INTR_MASK,
#endif /* (Camera_I2C_TIMEOUT_ENABLED) */
};

#if ((Camera_I2C_FF_IMPLEMENTED) && (Camera_I2C_WAKEUP_ENABLED))
    volatile uint8 Camera_I2C_wakeupSource;
#endif /* ((Camera_I2C_FF_IMPLEMENTED) && (Camera_I2C_WAKEUP_ENABLED)) */


/*******************************************************************************
* Function Name: Camera_I2C_SaveConfig
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
*  Camera_I2C_backup - The global variable used to save the component
*                            configuration and non-retention registers before
*                            entering the sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Camera_I2C_SaveConfig(void) 
{
#if (Camera_I2C_FF_IMPLEMENTED)
    #if (Camera_I2C_WAKEUP_ENABLED)
        uint8 intState;
    #endif /* (Camera_I2C_WAKEUP_ENABLED) */

    /* Store registers before enter low power mode */
    Camera_I2C_backup.cfg     = Camera_I2C_CFG_REG;
    Camera_I2C_backup.xcfg    = Camera_I2C_XCFG_REG;
    Camera_I2C_backup.addr    = Camera_I2C_ADDR_REG;
    Camera_I2C_backup.clkDiv1 = Camera_I2C_CLKDIV1_REG;
    Camera_I2C_backup.clkDiv2 = Camera_I2C_CLKDIV2_REG;

#if (Camera_I2C_WAKEUP_ENABLED)
    /* Disable master */
    Camera_I2C_CFG_REG &= (uint8) ~Camera_I2C_ENABLE_MASTER;

    /* Enable backup regulator to keep block powered in low power mode */
    intState = CyEnterCriticalSection();
    Camera_I2C_PWRSYS_CR1_REG |= Camera_I2C_PWRSYS_CR1_I2C_REG_BACKUP;
    CyExitCriticalSection(intState);

    /* 1) Set force NACK to ignore I2C transactions;
    *  2) Wait unti I2C is ready go to Sleep; !!
    *  3) These bits are cleared on wake up.
    */
    /* Wait when block is ready for sleep */
    Camera_I2C_XCFG_REG |= Camera_I2C_XCFG_FORCE_NACK;
    while (0u == (Camera_I2C_XCFG_REG & Camera_I2C_XCFG_RDY_TO_SLEEP))
    {
    }

    /* Setup wakeup interrupt */
    Camera_I2C_DisableInt();
    (void) CyIntSetVector(Camera_I2C_ISR_NUMBER, &Camera_I2C_WAKEUP_ISR);
    Camera_I2C_wakeupSource = 0u;
    Camera_I2C_EnableInt();
#endif /* (Camera_I2C_WAKEUP_ENABLED) */

#else
    /* Store only address match bit */
    Camera_I2C_backup.control = (Camera_I2C_CFG_REG & Camera_I2C_CTRL_ANY_ADDRESS_MASK);
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_TimeoutSaveConfig();
#endif /* (Camera_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Camera_I2C_Sleep
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
void Camera_I2C_Sleep(void) 
{
#if (Camera_I2C_WAKEUP_ENABLED)
    /* Do not enable block after exit low power mode if it is wakeup source */
    Camera_I2C_backup.enableState = Camera_I2C_DISABLE;

    #if (Camera_I2C_TIMEOUT_ENABLED)
        Camera_I2C_TimeoutStop();
    #endif /* (Camera_I2C_TIMEOUT_ENABLED) */

#else
    /* Store enable state */
    Camera_I2C_backup.enableState = (uint8) Camera_I2C_IS_ENABLED;

    if (0u != Camera_I2C_backup.enableState)
    {
        Camera_I2C_Stop();
    }
#endif /* (Camera_I2C_WAKEUP_ENABLED) */

    Camera_I2C_SaveConfig();
}


/*******************************************************************************
* Function Name: Camera_I2C_RestoreConfig
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
*  Camera_I2C_backup - The global variable used to save the component
*                            configuration and non-retention registers before
*                            exiting the sleep mode.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Calling this function before Camera_I2C_SaveConfig() or
*  Camera_I2C_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void Camera_I2C_RestoreConfig(void) 
{
#if (Camera_I2C_FF_IMPLEMENTED)
    uint8 intState;

    if (Camera_I2C_CHECK_PWRSYS_I2C_BACKUP)
    /* Low power mode was Sleep - backup regulator is enabled */
    {
        /* Enable backup regulator in active mode */
        intState = CyEnterCriticalSection();
        Camera_I2C_PWRSYS_CR1_REG &= (uint8) ~Camera_I2C_PWRSYS_CR1_I2C_REG_BACKUP;
        CyExitCriticalSection(intState);

        /* Restore master */
        Camera_I2C_CFG_REG = Camera_I2C_backup.cfg;
    }
    else
    /* Low power mode was Hibernate - backup regulator is disabled. All registers are cleared */
    {
    #if (Camera_I2C_WAKEUP_ENABLED)
        /* Disable power to block before register restore */
        intState = CyEnterCriticalSection();
        Camera_I2C_ACT_PWRMGR_REG  &= (uint8) ~Camera_I2C_ACT_PWR_EN;
        Camera_I2C_STBY_PWRMGR_REG &= (uint8) ~Camera_I2C_STBY_PWR_EN;
        CyExitCriticalSection(intState);

        /* Enable component in I2C_Wakeup() after register restore */
        Camera_I2C_backup.enableState = Camera_I2C_ENABLE;
    #endif /* (Camera_I2C_WAKEUP_ENABLED) */

        /* Restore component registers after Hibernate */
        Camera_I2C_XCFG_REG    = Camera_I2C_backup.xcfg;
        Camera_I2C_CFG_REG     = Camera_I2C_backup.cfg;
        Camera_I2C_ADDR_REG    = Camera_I2C_backup.addr;
        Camera_I2C_CLKDIV1_REG = Camera_I2C_backup.clkDiv1;
        Camera_I2C_CLKDIV2_REG = Camera_I2C_backup.clkDiv2;
    }

#if (Camera_I2C_WAKEUP_ENABLED)
    Camera_I2C_DisableInt();
    (void) CyIntSetVector(Camera_I2C_ISR_NUMBER, &Camera_I2C_ISR);
    if (0u != Camera_I2C_wakeupSource)
    {
        /* Generate interrupt to process incoming transaction */
        Camera_I2C_SetPendingInt();
    }
    Camera_I2C_EnableInt();
#endif /* (Camera_I2C_WAKEUP_ENABLED) */

#else
    Camera_I2C_CFG_REG = Camera_I2C_backup.control;
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_TimeoutRestoreConfig();
#endif /* (Camera_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Camera_I2C_Wakeup
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
*  Calling this function before Camera_I2C_SaveConfig() or
*  Camera_I2C_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void Camera_I2C_Wakeup(void) 
{
    Camera_I2C_RestoreConfig();

    /* Restore component enable state */
    if (0u != Camera_I2C_backup.enableState)
    {
        Camera_I2C_Enable();
        Camera_I2C_EnableInt();
    }
    else
    {
    #if (Camera_I2C_TIMEOUT_ENABLED)
        Camera_I2C_TimeoutEnable();
    #endif /* (Camera_I2C_TIMEOUT_ENABLED) */
    }
}


/* [] END OF FILE */
