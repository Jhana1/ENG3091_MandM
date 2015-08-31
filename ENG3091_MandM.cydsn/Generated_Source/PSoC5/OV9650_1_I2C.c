/*******************************************************************************
* File Name: OV9650_1_I2C.c
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

#include "OV9650_1_I2C_PVT.h"


/**********************************
*      System variables
**********************************/

uint8 OV9650_1_I2C_initVar = 0u; /* Defines if component was initialized */

volatile uint8 OV9650_1_I2C_state;  /* Current state of I2C FSM */


/*******************************************************************************
* Function Name: OV9650_1_I2C_Init
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
void OV9650_1_I2C_Init(void) 
{
#if (OV9650_1_I2C_FF_IMPLEMENTED)
    /* Configure fixed function block */
    OV9650_1_I2C_CFG_REG  = OV9650_1_I2C_DEFAULT_CFG;
    OV9650_1_I2C_XCFG_REG = OV9650_1_I2C_DEFAULT_XCFG;
    OV9650_1_I2C_ADDR_REG = OV9650_1_I2C_DEFAULT_ADDR;
    OV9650_1_I2C_CLKDIV1_REG = LO8(OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR);
    OV9650_1_I2C_CLKDIV2_REG = HI8(OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR);

#else
    uint8 intState;

    /* Configure control and interrupt sources */
    OV9650_1_I2C_CFG_REG      = OV9650_1_I2C_DEFAULT_CFG;
    OV9650_1_I2C_INT_MASK_REG = OV9650_1_I2C_DEFAULT_INT_MASK;

    /* Enable interrupt generation in status */
    intState = CyEnterCriticalSection();
    OV9650_1_I2C_INT_ENABLE_REG |= OV9650_1_I2C_INTR_ENABLE;
    CyExitCriticalSection(intState);

    /* Configure bit counter */
    #if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
        OV9650_1_I2C_PERIOD_REG = OV9650_1_I2C_DEFAULT_PERIOD;
    #endif  /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

    /* Configure clock generator */
    #if (OV9650_1_I2C_MODE_MASTER_ENABLED)
        OV9650_1_I2C_MCLK_PRD_REG = OV9650_1_I2C_DEFAULT_MCLK_PRD;
        OV9650_1_I2C_MCLK_CMP_REG = OV9650_1_I2C_DEFAULT_MCLK_CMP;
    #endif /* (OV9650_1_I2C_MODE_MASTER_ENABLED) */
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_TimeoutInit();
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */

    /* Configure internal interrupt */
    CyIntDisable    (OV9650_1_I2C_ISR_NUMBER);
    CyIntSetPriority(OV9650_1_I2C_ISR_NUMBER, OV9650_1_I2C_ISR_PRIORITY);
    #if (OV9650_1_I2C_INTERN_I2C_INTR_HANDLER)
        (void) CyIntSetVector(OV9650_1_I2C_ISR_NUMBER, &OV9650_1_I2C_ISR);
    #endif /* (OV9650_1_I2C_INTERN_I2C_INTR_HANDLER) */

    /* Set FSM to default state */
    OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;

#if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
    /* Clear status and buffers index */
    OV9650_1_I2C_slStatus = 0u;
    OV9650_1_I2C_slRdBufIndex = 0u;
    OV9650_1_I2C_slWrBufIndex = 0u;

    /* Configure matched address */
    OV9650_1_I2C_SlaveSetAddress(OV9650_1_I2C_DEFAULT_ADDR);
#endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

#if (OV9650_1_I2C_MODE_MASTER_ENABLED)
    /* Clear status and buffers index */
    OV9650_1_I2C_mstrStatus = 0u;
    OV9650_1_I2C_mstrRdBufIndex = 0u;
    OV9650_1_I2C_mstrWrBufIndex = 0u;
#endif /* (OV9650_1_I2C_MODE_MASTER_ENABLED) */
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_Enable
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
void OV9650_1_I2C_Enable(void) 
{
#if (OV9650_1_I2C_FF_IMPLEMENTED)
    uint8 intState;

    /* Enable power to block */
    intState = CyEnterCriticalSection();
    OV9650_1_I2C_ACT_PWRMGR_REG  |= OV9650_1_I2C_ACT_PWR_EN;
    OV9650_1_I2C_STBY_PWRMGR_REG |= OV9650_1_I2C_STBY_PWR_EN;
    CyExitCriticalSection(intState);
#else
    #if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
        /* Enable bit counter */
        uint8 intState = CyEnterCriticalSection();
        OV9650_1_I2C_COUNTER_AUX_CTL_REG |= OV9650_1_I2C_CNT7_ENABLE;
        CyExitCriticalSection(intState);
    #endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

    /* Enable slave or master bits */
    OV9650_1_I2C_CFG_REG |= OV9650_1_I2C_ENABLE_MS;
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_TimeoutEnable();
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_Start
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
*  OV9650_1_I2C_initVar - This variable is used to check the initial
*                             configuration, modified on the first
*                             function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void OV9650_1_I2C_Start(void) 
{
    if (0u == OV9650_1_I2C_initVar)
    {
        OV9650_1_I2C_Init();
        OV9650_1_I2C_initVar = 1u; /* Component initialized */
    }

    OV9650_1_I2C_Enable();
    OV9650_1_I2C_EnableInt();
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_Stop
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
void OV9650_1_I2C_Stop(void) 
{
    OV9650_1_I2C_DisableInt();

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    OV9650_1_I2C_TimeoutStop();
#endif  /* End (OV9650_1_I2C_TIMEOUT_ENABLED) */

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    {
        uint8 intState;
        uint16 blockResetCycles;

        /* Store registers effected by block disable */
        OV9650_1_I2C_backup.addr    = OV9650_1_I2C_ADDR_REG;
        OV9650_1_I2C_backup.clkDiv1 = OV9650_1_I2C_CLKDIV1_REG;
        OV9650_1_I2C_backup.clkDiv2 = OV9650_1_I2C_CLKDIV2_REG;

        /* Calculate number of cycles to reset block */
        blockResetCycles = ((uint16) ((uint16) OV9650_1_I2C_CLKDIV2_REG << 8u) | OV9650_1_I2C_CLKDIV1_REG) + 1u;

        /* Disable block */
        OV9650_1_I2C_CFG_REG &= (uint8) ~OV9650_1_I2C_CFG_EN_SLAVE;
        /* Wait for block reset before disable power */
        CyDelayCycles((uint32) blockResetCycles);

        /* Disable power to block */
        intState = CyEnterCriticalSection();
        OV9650_1_I2C_ACT_PWRMGR_REG  &= (uint8) ~OV9650_1_I2C_ACT_PWR_EN;
        OV9650_1_I2C_STBY_PWRMGR_REG &= (uint8) ~OV9650_1_I2C_STBY_PWR_EN;
        CyExitCriticalSection(intState);

        /* Enable block */
        OV9650_1_I2C_CFG_REG |= (uint8) OV9650_1_I2C_ENABLE_MS;

        /* Restore registers effected by block disable. Ticket ID#198004 */
        OV9650_1_I2C_ADDR_REG    = OV9650_1_I2C_backup.addr;
        OV9650_1_I2C_ADDR_REG    = OV9650_1_I2C_backup.addr;
        OV9650_1_I2C_CLKDIV1_REG = OV9650_1_I2C_backup.clkDiv1;
        OV9650_1_I2C_CLKDIV2_REG = OV9650_1_I2C_backup.clkDiv2;
    }
#else

    /* Disable slave or master bits */
    OV9650_1_I2C_CFG_REG &= (uint8) ~OV9650_1_I2C_ENABLE_MS;

#if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
    {
        /* Disable bit counter */
        uint8 intState = CyEnterCriticalSection();
        OV9650_1_I2C_COUNTER_AUX_CTL_REG &= (uint8) ~OV9650_1_I2C_CNT7_ENABLE;
        CyExitCriticalSection(intState);
    }
#endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

    /* Clear interrupt source register */
    (void) OV9650_1_I2C_CSR_REG;
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

    /* Disable interrupt on stop (enabled by write transaction) */
    OV9650_1_I2C_DISABLE_INT_ON_STOP;
    OV9650_1_I2C_ClearPendingInt();

    /* Reset FSM to default state */
    OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;

    /* Clear busy statuses */
#if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
    OV9650_1_I2C_slStatus &= (uint8) ~(OV9650_1_I2C_SSTAT_RD_BUSY | OV9650_1_I2C_SSTAT_WR_BUSY);
#endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */
}


/* [] END OF FILE */
