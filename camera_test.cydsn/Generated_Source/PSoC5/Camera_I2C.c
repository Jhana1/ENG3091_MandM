/*******************************************************************************
* File Name: Camera_I2C.c
* Version 3.50
*
* Description:
*  This file provides the source code of APIs for the I2C component.
*  The actual protocol and operation code resides in the interrupt service
*  routine file.
*
*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Camera_I2C_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 Camera_I2C_initVar = 0u; /* Defines if component was initialized */

volatile uint8 Camera_I2C_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: Camera_I2C_Init
********************************************************************************
*
* Summary:
*  Initializes I2C registers with initial values provided from customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Camera_I2C_Init(void) 
{
#if (Camera_I2C_FF_IMPLEMENTED)
    /* Configure fixed function block */
    Camera_I2C_CFG_REG  = Camera_I2C_DEFAULT_CFG;
    Camera_I2C_XCFG_REG = Camera_I2C_DEFAULT_XCFG;
    Camera_I2C_ADDR_REG = Camera_I2C_DEFAULT_ADDR;
    Camera_I2C_CLKDIV1_REG = LO8(Camera_I2C_DEFAULT_DIVIDE_FACTOR);
    Camera_I2C_CLKDIV2_REG = HI8(Camera_I2C_DEFAULT_DIVIDE_FACTOR);

#else
    uint8 intState;

    /* Configure control and interrupt sources */
    Camera_I2C_CFG_REG      = Camera_I2C_DEFAULT_CFG;
    Camera_I2C_INT_MASK_REG = Camera_I2C_DEFAULT_INT_MASK;

    /* Enable interrupt generation in status */
    intState = CyEnterCriticalSection();
    Camera_I2C_INT_ENABLE_REG |= Camera_I2C_INTR_ENABLE;
    CyExitCriticalSection(intState);

    /* Configure bit counter */
    #if (Camera_I2C_MODE_SLAVE_ENABLED)
        Camera_I2C_PERIOD_REG = Camera_I2C_DEFAULT_PERIOD;
    #endif  /* (Camera_I2C_MODE_SLAVE_ENABLED) */

    /* Configure clock generator */
    #if (Camera_I2C_MODE_MASTER_ENABLED)
        Camera_I2C_MCLK_PRD_REG = Camera_I2C_DEFAULT_MCLK_PRD;
        Camera_I2C_MCLK_CMP_REG = Camera_I2C_DEFAULT_MCLK_CMP;
    #endif /* (Camera_I2C_MODE_MASTER_ENABLED) */
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_TimeoutInit();
#endif /* (Camera_I2C_TIMEOUT_ENABLED) */

    /* Configure internal interrupt */
    CyIntDisable    (Camera_I2C_ISR_NUMBER);
    CyIntSetPriority(Camera_I2C_ISR_NUMBER, Camera_I2C_ISR_PRIORITY);
    #if (Camera_I2C_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(Camera_I2C_ISR_NUMBER, &Camera_I2C_ISR);
    #endif /* (Camera_I2C_INTERN_I2C_INTR_HANDLER) */

    /* Set FSM to default state */
    Camera_I2C_state = Camera_I2C_SM_IDLE;

#if (Camera_I2C_MODE_SLAVE_ENABLED)
    /* Clear status and buffers index */
    Camera_I2C_slStatus = 0u;
    Camera_I2C_slRdBufIndex = 0u;
    Camera_I2C_slWrBufIndex = 0u;

    /* Configure matched address */
    Camera_I2C_SlaveSetAddress(Camera_I2C_DEFAULT_ADDR);
#endif /* (Camera_I2C_MODE_SLAVE_ENABLED) */

#if (Camera_I2C_MODE_MASTER_ENABLED)
    /* Clear status and buffers index */
    Camera_I2C_mstrStatus = 0u;
    Camera_I2C_mstrRdBufIndex = 0u;
    Camera_I2C_mstrWrBufIndex = 0u;
#endif /* (Camera_I2C_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: Camera_I2C_Enable
********************************************************************************
*
* Summary:
*  Enables I2C operations.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  None.
*
*******************************************************************************/
void Camera_I2C_Enable(void) 
{
#if (Camera_I2C_FF_IMPLEMENTED)
    uint8 intState;

    /* Enable power to block */
    intState = CyEnterCriticalSection();
    Camera_I2C_ACT_PWRMGR_REG  |= Camera_I2C_ACT_PWR_EN;
    Camera_I2C_STBY_PWRMGR_REG |= Camera_I2C_STBY_PWR_EN;
    CyExitCriticalSection(intState);
#else
    #if (Camera_I2C_MODE_SLAVE_ENABLED)
        /* Enable bit counter */
        uint8 intState = CyEnterCriticalSection();
        Camera_I2C_COUNTER_AUX_CTL_REG |= Camera_I2C_CNT7_ENABLE;
        CyExitCriticalSection(intState);
    #endif /* (Camera_I2C_MODE_SLAVE_ENABLED) */

    /* Enable slave or master bits */
    Camera_I2C_CFG_REG |= Camera_I2C_ENABLE_MS;
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_TimeoutEnable();
#endif /* (Camera_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: Camera_I2C_Start
********************************************************************************
*
* Summary:
*  Starts the I2C hardware. Enables Active mode power template bits or clock
*  gating as appropriate. It is required to be executed before I2C bus
*  operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This component automatically enables its interrupt.  If I2C is enabled !
*  without the interrupt enabled, it can lock up the I2C bus.
*
* Global variables:
*  Camera_I2C_initVar - This variable is used to check the initial
*                             configuration, modified on the first
*                             function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Camera_I2C_Start(void) 
{
    if (0u == Camera_I2C_initVar)
    {
        Camera_I2C_Init();
        Camera_I2C_initVar = 1u; /* Component initialized */
    }

    Camera_I2C_Enable();
    Camera_I2C_EnableInt();
}


/*******************************************************************************
* Function Name: Camera_I2C_Stop
********************************************************************************
*
* Summary:
*  Disables I2C hardware and disables I2C interrupt. Disables Active mode power
*  template bits or clock gating as appropriate.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Camera_I2C_Stop(void) 
{
    Camera_I2C_DisableInt();

#if (Camera_I2C_TIMEOUT_ENABLED)
    Camera_I2C_TimeoutStop();
#endif  /* End (Camera_I2C_TIMEOUT_ENABLED) */

#if (Camera_I2C_FF_IMPLEMENTED)
    {
        uint8 intState;
        uint16 blockResetCycles;

        /* Store registers effected by block disable */
        Camera_I2C_backup.addr    = Camera_I2C_ADDR_REG;
        Camera_I2C_backup.clkDiv1 = Camera_I2C_CLKDIV1_REG;
        Camera_I2C_backup.clkDiv2 = Camera_I2C_CLKDIV2_REG;

        /* Calculate number of cycles to reset block */
        blockResetCycles = ((uint16) ((uint16) Camera_I2C_CLKDIV2_REG << 8u) | Camera_I2C_CLKDIV1_REG) + 1u;

        /* Disable block */
        Camera_I2C_CFG_REG &= (uint8) ~Camera_I2C_CFG_EN_SLAVE;
        /* Wait for block reset before disable power */
        CyDelayCycles((uint32) blockResetCycles);

        /* Disable power to block */
        intState = CyEnterCriticalSection();
        Camera_I2C_ACT_PWRMGR_REG  &= (uint8) ~Camera_I2C_ACT_PWR_EN;
        Camera_I2C_STBY_PWRMGR_REG &= (uint8) ~Camera_I2C_STBY_PWR_EN;
        CyExitCriticalSection(intState);

        /* Enable block */
        Camera_I2C_CFG_REG |= (uint8) Camera_I2C_ENABLE_MS;

        /* Restore registers effected by block disable. Ticket ID#198004 */
        Camera_I2C_ADDR_REG    = Camera_I2C_backup.addr;
        Camera_I2C_ADDR_REG    = Camera_I2C_backup.addr;
        Camera_I2C_CLKDIV1_REG = Camera_I2C_backup.clkDiv1;
        Camera_I2C_CLKDIV2_REG = Camera_I2C_backup.clkDiv2;
    }
#else

    /* Disable slave or master bits */
    Camera_I2C_CFG_REG &= (uint8) ~Camera_I2C_ENABLE_MS;

#if (Camera_I2C_MODE_SLAVE_ENABLED)
    {
        /* Disable bit counter */
        uint8 intState = CyEnterCriticalSection();
        Camera_I2C_COUNTER_AUX_CTL_REG &= (uint8) ~Camera_I2C_CNT7_ENABLE;
        CyExitCriticalSection(intState);
    }
#endif /* (Camera_I2C_MODE_SLAVE_ENABLED) */

    /* Clear interrupt source register */
    (void) Camera_I2C_CSR_REG;
#endif /* (Camera_I2C_FF_IMPLEMENTED) */

    /* Disable interrupt on stop (enabled by write transaction) */
    Camera_I2C_DISABLE_INT_ON_STOP;
    Camera_I2C_ClearPendingInt();

    /* Reset FSM to default state */
    Camera_I2C_state = Camera_I2C_SM_IDLE;

    /* Clear busy statuses */
#if (Camera_I2C_MODE_SLAVE_ENABLED)
    Camera_I2C_slStatus &= (uint8) ~(Camera_I2C_SSTAT_RD_BUSY | Camera_I2C_SSTAT_WR_BUSY);
#endif /* (Camera_I2C_MODE_SLAVE_ENABLED) */
}


/* [] END OF FILE */
