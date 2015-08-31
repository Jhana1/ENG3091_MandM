/*******************************************************************************
* File Name: OV9650_1_I2C_MASTER.c
* Version 3.50
*
* Description:
*  This file provides the source code of APIs for the I2C component master mode.
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "OV9650_1_I2C_PVT.h"

#if(OV9650_1_I2C_MODE_MASTER_ENABLED)

/**********************************
*      System variables
**********************************/

volatile uint8 OV9650_1_I2C_mstrStatus;     /* Master Status byte  */
volatile uint8 OV9650_1_I2C_mstrControl;    /* Master Control byte */

/* Transmit buffer variables */
volatile uint8 * OV9650_1_I2C_mstrRdBufPtr;     /* Pointer to Master Read buffer */
volatile uint8   OV9650_1_I2C_mstrRdBufSize;    /* Master Read buffer size       */
volatile uint8   OV9650_1_I2C_mstrRdBufIndex;   /* Master Read buffer Index      */

/* Receive buffer variables */
volatile uint8 * OV9650_1_I2C_mstrWrBufPtr;     /* Pointer to Master Write buffer */
volatile uint8   OV9650_1_I2C_mstrWrBufSize;    /* Master Write buffer size       */
volatile uint8   OV9650_1_I2C_mstrWrBufIndex;   /* Master Write buffer Index      */


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterWriteBuf
********************************************************************************
*
* Summary:
*  Automatically writes an entire buffer of data to a slave device. Once the
*  data transfer is initiated by this function, further data transfer is handled
*  by the included ISR in byte by byte mode.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer of data to be sent.
*  cnt:       Size of buffer to send.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  The included ISR will start a transfer after a start or restart condition is
*  generated.
*
* Global variables:
*  OV9650_1_I2C_mstrStatus  - The global variable used to store a current
*                                 status of the I2C Master.
*  OV9650_1_I2C_state       - The global variable used to store a current
*                                 state of the software FSM.
*  OV9650_1_I2C_mstrControl - The global variable used to control the master
*                                 end of a transaction with or without Stop
*                                 generation.
*  OV9650_1_I2C_mstrWrBufPtr - The global variable used to store a pointer
*                                  to the master write buffer.
*  OV9650_1_I2C_mstrWrBufIndex - The global variable used to store current
*                                    index within the master write buffer.
*  OV9650_1_I2C_mstrWrBufSize - The global variable used to store a master
*                                   write buffer size.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode)
      
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    if(NULL != wrData)
    {
        /* Check I2C state to allow transfer: valid states are IDLE or HALT */
        if(OV9650_1_I2C_SM_IDLE == OV9650_1_I2C_state)
        {
            /* Master is ready for transaction: check if bus is free */
            if(OV9650_1_I2C_CHECK_BUS_FREE(OV9650_1_I2C_MCSR_REG))
            {
                errStatus = OV9650_1_I2C_MSTR_NO_ERROR;
            }
            else
            {
                errStatus = OV9650_1_I2C_MSTR_BUS_BUSY;
            }
        }
        else if(OV9650_1_I2C_SM_MSTR_HALT == OV9650_1_I2C_state)
        {
            /* Master is ready and waiting for ReStart */
            errStatus = OV9650_1_I2C_MSTR_NO_ERROR;

            OV9650_1_I2C_ClearPendingInt();
            OV9650_1_I2C_mstrStatus &= (uint8) ~OV9650_1_I2C_MSTAT_XFER_HALT;
        }
        else
        {
            /* errStatus = OV9650_1_I2C_MSTR_NOT_READY was send before */
        }

        if(OV9650_1_I2C_MSTR_NO_ERROR == errStatus)
        {
            /* Set state to start write transaction */
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_WR_ADDR;

            /* Prepare write buffer */
            OV9650_1_I2C_mstrWrBufIndex = 0u;
            OV9650_1_I2C_mstrWrBufSize  = cnt;
            OV9650_1_I2C_mstrWrBufPtr   = (volatile uint8 *) wrData;

            /* Set end of transaction flag: Stop or Halt (following ReStart) */
            OV9650_1_I2C_mstrControl = mode;

            /* Clear write status history */
            OV9650_1_I2C_mstrStatus &= (uint8) ~OV9650_1_I2C_MSTAT_WR_CMPLT;

            /* Hardware actions: write address and generate Start or ReStart */
            OV9650_1_I2C_DATA_REG = (uint8) (slaveAddress << OV9650_1_I2C_SLAVE_ADDR_SHIFT);

            if(OV9650_1_I2C_CHECK_RESTART(mode))
            {
                OV9650_1_I2C_GENERATE_RESTART;
            }
            else
            {
                OV9650_1_I2C_GENERATE_START;
            }

            /* Enable interrupt to complete transfer */
            OV9650_1_I2C_EnableInt();
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterReadBuf
********************************************************************************
*
* Summary:
*  Automatically writes an entire buffer of data to a slave device. Once the
*  data transfer is initiated by this function, further data transfer is handled
*  by the included ISR in byte by byte mode.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer where to put data from slave.
*  cnt:       Size of buffer to read.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  The included ISR will start a transfer after start or restart condition is
*  generated.
*
* Global variables:
*  OV9650_1_I2C_mstrStatus  - The global variable used to store a current
*                                 status of the I2C Master.
*  OV9650_1_I2C_state       - The global variable used to store a current
*                                 state of the software FSM.
*  OV9650_1_I2C_mstrControl - The global variable used to control the master
*                                 end of a transaction with or without
*                                 Stop generation.
*  OV9650_1_I2C_mstrRdBufPtr - The global variable used to store a pointer
*                                  to the master write buffer.
*  OV9650_1_I2C_mstrRdBufIndex - The global variable  used to store a
*                                    current index within the master
*                                    write buffer.
*  OV9650_1_I2C_mstrRdBufSize - The global variable used to store a master
*                                   write buffer size.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode)
      
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check I2C state to allow transfer: valid states are IDLE or HALT */
        if(OV9650_1_I2C_SM_IDLE == OV9650_1_I2C_state)
        {
            /* Master is ready to transaction: check if bus is free */
            if(OV9650_1_I2C_CHECK_BUS_FREE(OV9650_1_I2C_MCSR_REG))
            {
                errStatus = OV9650_1_I2C_MSTR_NO_ERROR;
            }
            else
            {
                errStatus = OV9650_1_I2C_MSTR_BUS_BUSY;
            }
        }
        else if(OV9650_1_I2C_SM_MSTR_HALT == OV9650_1_I2C_state)
        {
            /* Master is ready and waiting for ReStart */
            errStatus = OV9650_1_I2C_MSTR_NO_ERROR;

            OV9650_1_I2C_ClearPendingInt();
            OV9650_1_I2C_mstrStatus &= (uint8) ~OV9650_1_I2C_MSTAT_XFER_HALT;
        }
        else
        {
            /* errStatus = OV9650_1_I2C_MSTR_NOT_READY was set before */
        }

        if(OV9650_1_I2C_MSTR_NO_ERROR == errStatus)
        {
            /* Set state to start write transaction */
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_RD_ADDR;

            /* Prepare read buffer */
            OV9650_1_I2C_mstrRdBufIndex  = 0u;
            OV9650_1_I2C_mstrRdBufSize   = cnt;
            OV9650_1_I2C_mstrRdBufPtr    = (volatile uint8 *) rdData;

            /* Set end of transaction flag: Stop or Halt (following ReStart) */
            OV9650_1_I2C_mstrControl = mode;

            /* Clear read status history */
            OV9650_1_I2C_mstrStatus &= (uint8) ~OV9650_1_I2C_MSTAT_RD_CMPLT;

            /* Hardware actions: write address and generate Start or ReStart */
            OV9650_1_I2C_DATA_REG = ((uint8) (slaveAddress << OV9650_1_I2C_SLAVE_ADDR_SHIFT) |
                                                  OV9650_1_I2C_READ_FLAG);

            if(OV9650_1_I2C_CHECK_RESTART(mode))
            {
                OV9650_1_I2C_GENERATE_RESTART;
            }
            else
            {
                OV9650_1_I2C_GENERATE_START;
            }

            /* Enable interrupt to complete transfer */
            OV9650_1_I2C_EnableInt();
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterSendStart
********************************************************************************
*
* Summary:
*  Generates Start condition and sends slave address with read/write bit.
*
* Parameters:
*  slaveAddress:  7-bit slave address.
*  R_nW:          Zero, send write command, non-zero send read command.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  This function is entered without a "byte complete" bit set in the I2C_CSR
*  register. It does not exit until it is set.
*
* Global variables:
*  OV9650_1_I2C_state - The global variable used to store a current state of
*                           the software FSM.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterSendStart(uint8 slaveAddress, uint8 R_nW)
      
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    /* If IDLE, check if bus is free */
    if(OV9650_1_I2C_SM_IDLE == OV9650_1_I2C_state)
    {
        /* If bus is free, generate Start condition */
        if(OV9650_1_I2C_CHECK_BUS_FREE(OV9650_1_I2C_MCSR_REG))
        {
            /* Disable interrupt for manual master operation */
            OV9650_1_I2C_DisableInt();

            /* Set address and read/write flag */
            slaveAddress = (uint8) (slaveAddress << OV9650_1_I2C_SLAVE_ADDR_SHIFT);
            if(0u != R_nW)
            {
                slaveAddress |= OV9650_1_I2C_READ_FLAG;
                OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_RD_ADDR;
            }
            else
            {
                OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_WR_ADDR;
            }

            /* Hardware actions: write address and generate Start */
            OV9650_1_I2C_DATA_REG = slaveAddress;
            OV9650_1_I2C_GENERATE_START_MANUAL;

            /* Wait until address is transferred */
            while(OV9650_1_I2C_WAIT_BYTE_COMPLETE(OV9650_1_I2C_CSR_REG))
            {
            }

        #if(OV9650_1_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED)
            if(OV9650_1_I2C_CHECK_START_GEN(OV9650_1_I2C_MCSR_REG))
            {
                OV9650_1_I2C_CLEAR_START_GEN;

                /* Start condition was not generated: reset FSM to IDLE */
                OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
                errStatus = OV9650_1_I2C_MSTR_ERR_ABORT_START_GEN;
            }
            else
        #endif /* (OV9650_1_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED) */

        #if(OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED)
            if(OV9650_1_I2C_CHECK_LOST_ARB(OV9650_1_I2C_CSR_REG))
            {
                OV9650_1_I2C_BUS_RELEASE_MANUAL;

                /* Master lost arbitrage: reset FSM to IDLE */
                OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
                errStatus = OV9650_1_I2C_MSTR_ERR_ARB_LOST;
            }
            else
        #endif /* (OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED) */

            if(OV9650_1_I2C_CHECK_ADDR_NAK(OV9650_1_I2C_CSR_REG))
            {
                /* Address has been NACKed: reset FSM to IDLE */
                OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
                errStatus = OV9650_1_I2C_MSTR_ERR_LB_NAK;
            }
            else
            {
                /* Start was sent without errors */
                errStatus = OV9650_1_I2C_MSTR_NO_ERROR;
            }
        }
        else
        {
            errStatus = OV9650_1_I2C_MSTR_BUS_BUSY;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterSendRestart
********************************************************************************
*
* Summary:
*  Generates ReStart condition and sends slave address with read/write bit.
*
* Parameters:
*  slaveAddress:  7-bit slave address.
*  R_nW:          Zero, send write command, non-zero send read command.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  This function is entered without a "byte complete" bit set in the I2C_CSR
*  register. It does not exit until it is set.
*
* Global variables:
*  OV9650_1_I2C_state - The global variable used to store a current state of
*                           the software FSM.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterSendRestart(uint8 slaveAddress, uint8 R_nW)
      
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    /* Check if START condition was generated */
    if(OV9650_1_I2C_CHECK_MASTER_MODE(OV9650_1_I2C_MCSR_REG))
    {
        /* Set address and read/write flag */
        slaveAddress = (uint8) (slaveAddress << OV9650_1_I2C_SLAVE_ADDR_SHIFT);
        if(0u != R_nW)
        {
            slaveAddress |= OV9650_1_I2C_READ_FLAG;
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_RD_ADDR;
        }
        else
        {
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_WR_ADDR;
        }

        /* Hardware actions: write address and generate ReStart */
        OV9650_1_I2C_DATA_REG = slaveAddress;
        OV9650_1_I2C_GENERATE_RESTART_MANUAL;

        /* Wait until address has been transferred */
        while(OV9650_1_I2C_WAIT_BYTE_COMPLETE(OV9650_1_I2C_CSR_REG))
        {
        }

    #if(OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED)
        if(OV9650_1_I2C_CHECK_LOST_ARB(OV9650_1_I2C_CSR_REG))
        {
            OV9650_1_I2C_BUS_RELEASE_MANUAL;

            /* Master lost arbitrage: reset FSM to IDLE */
            OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
            errStatus = OV9650_1_I2C_MSTR_ERR_ARB_LOST;
        }
        else
    #endif /* (OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED) */

        if(OV9650_1_I2C_CHECK_ADDR_NAK(OV9650_1_I2C_CSR_REG))
        {
            /* Address has been NACKed: reset FSM to IDLE */
            OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
            errStatus = OV9650_1_I2C_MSTR_ERR_LB_NAK;
        }
        else
        {
            /* ReStart was sent without errors */
            errStatus = OV9650_1_I2C_MSTR_NO_ERROR;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterSendStop
********************************************************************************
*
* Summary:
*  Generates I2C Stop condition on bus. Function do nothing if Start or Restart
*  condition was failed before call this function.
*
* Parameters:
*  None.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  Stop generation is required to complete the transaction.
*  This function does not wait until a Stop condition is generated.
*
* Global variables:
*  OV9650_1_I2C_state - The global variable used to store a current state of
*                           the software FSM.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterSendStop(void) 
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    /* Check if master is active on bus */
    if(OV9650_1_I2C_CHECK_MASTER_MODE(OV9650_1_I2C_MCSR_REG))
    {
        OV9650_1_I2C_GENERATE_STOP_MANUAL;
        OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;

        /* Wait until stop has been generated */
        while(OV9650_1_I2C_WAIT_STOP_COMPLETE(OV9650_1_I2C_CSR_REG))
        {
        }

        errStatus = OV9650_1_I2C_MSTR_NO_ERROR;

    #if(OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED)
        if(OV9650_1_I2C_CHECK_LOST_ARB(OV9650_1_I2C_CSR_REG))
        {
            OV9650_1_I2C_BUS_RELEASE_MANUAL;

            /* NACK was generated by instead Stop */
            errStatus = OV9650_1_I2C_MSTR_ERR_ARB_LOST;
        }
    #endif /* (OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED) */
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterWriteByte
********************************************************************************
*
* Summary:
*  Sends one byte to a slave. A valid Start or ReStart condition must be
*  generated before this call this function. Function do nothing if Start or
*  Restart condition was failed before call this function.
*
* Parameters:
*  data:  The data byte to send to the slave.
*
* Return:
*  Status error - Zero means no errors.
*
* Side Effects:
*  This function is entered without a "byte complete" bit set in the I2C_CSR
*  register. It does not exit until it is set.
*
* Global variables:
*  OV9650_1_I2C_state - The global variable used to store a current state of
*                           the software FSM.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterWriteByte(uint8 theByte) 
{
    uint8 errStatus;

    errStatus = OV9650_1_I2C_MSTR_NOT_READY;

    /* Check if START condition was generated */
    if(OV9650_1_I2C_CHECK_MASTER_MODE(OV9650_1_I2C_MCSR_REG))
    {
        OV9650_1_I2C_DATA_REG = theByte;   /* Write DATA register */
        OV9650_1_I2C_TRANSMIT_DATA_MANUAL; /* Set transmit mode   */
        OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_WR_DATA;

        /* Wait until data byte has been transmitted */
        while(OV9650_1_I2C_WAIT_BYTE_COMPLETE(OV9650_1_I2C_CSR_REG))
        {
        }

    #if(OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED)
        if(OV9650_1_I2C_CHECK_LOST_ARB(OV9650_1_I2C_CSR_REG))
        {
            OV9650_1_I2C_BUS_RELEASE_MANUAL;

            /* Master lost arbitrage: reset FSM to IDLE */
            OV9650_1_I2C_state = OV9650_1_I2C_SM_IDLE;
            errStatus = OV9650_1_I2C_MSTR_ERR_ARB_LOST;
        }
        /* Check LRB bit */
        else
    #endif /* (OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED) */

        if(OV9650_1_I2C_CHECK_DATA_ACK(OV9650_1_I2C_CSR_REG))
        {
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_HALT;
            errStatus = OV9650_1_I2C_MSTR_NO_ERROR;
        }
        else
        {
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_HALT;
            errStatus = OV9650_1_I2C_MSTR_ERR_LB_NAK;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterReadByte
********************************************************************************
*
* Summary:
*  Reads one byte from a slave and ACK or NACK the transfer. A valid Start or
*  ReStart condition must be generated before this call this function. Function
*  do nothing if Start or Restart condition was failed before call this
*  function.
*
* Parameters:
*  acknNack:  Zero, response with NACK, if non-zero response with ACK.
*
* Return:
*  Byte read from slave.
*
* Side Effects:
*  This function is entered without a "byte complete" bit set in the I2C_CSR
*  register. It does not exit until it is set.
*
* Global variables:
*  OV9650_1_I2C_state - The global variable used to store a current
*                           state of the software FSM.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterReadByte(uint8 acknNak) 
{
    uint8 theByte;

    theByte = 0u;

    /* Check if START condition was generated */
    if(OV9650_1_I2C_CHECK_MASTER_MODE(OV9650_1_I2C_MCSR_REG))
    {
        /* When address phase needs to release bus and receive byte,
        * then decide ACK or NACK
        */
        if(OV9650_1_I2C_SM_MSTR_RD_ADDR == OV9650_1_I2C_state)
        {
            OV9650_1_I2C_READY_TO_READ_MANUAL;
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_RD_DATA;
        }

        /* Wait until data byte has been received */
        while(OV9650_1_I2C_WAIT_BYTE_COMPLETE(OV9650_1_I2C_CSR_REG))
        {
        }

        theByte = OV9650_1_I2C_DATA_REG;

        /* Command ACK to receive next byte and continue transfer.
        *  Do nothing for NACK. The NACK will be generated by
        *  Stop or ReStart routine.
        */
        if(acknNak != 0u) /* Generate ACK */
        {
            OV9650_1_I2C_ACK_AND_RECEIVE_MANUAL;
        }
        else              /* Do nothing for the follwong NACK */
        {
            OV9650_1_I2C_state = OV9650_1_I2C_SM_MSTR_HALT;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterStatus
********************************************************************************
*
* Summary:
*  Returns the master's communication status.
*
* Parameters:
*  None.
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  OV9650_1_I2C_mstrStatus - The global variable used to store a current
*                                status of the I2C Master.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterStatus(void) 
{
    uint8 status;

    OV9650_1_I2C_DisableInt(); /* Lock from interrupt */

    /* Read master status */
    status = OV9650_1_I2C_mstrStatus;

    if (OV9650_1_I2C_CHECK_SM_MASTER)
    {
        /* Set transfer in progress flag in status */
        status |= OV9650_1_I2C_MSTAT_XFER_INP;
    }

    OV9650_1_I2C_EnableInt(); /* Release lock */

    return (status);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterClearStatus
********************************************************************************
*
* Summary:
*  Clears all status flags and returns the master status.
*
* Parameters:
*  None.
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  OV9650_1_I2C_mstrStatus - The global variable used to store a current
*                                status of the I2C Master.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterClearStatus(void) 
{
    uint8 status;

    OV9650_1_I2C_DisableInt(); /* Lock from interrupt */

    /* Read and clear master status */
    status = OV9650_1_I2C_mstrStatus;
    OV9650_1_I2C_mstrStatus = OV9650_1_I2C_MSTAT_CLEAR;

    OV9650_1_I2C_EnableInt(); /* Release lock */

    return (status);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the amount of bytes that has been transferred with an
*  I2C_MasterReadBuf command.
*
* Parameters:
*  None.
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it will return
*  the byte count transferred so far.
*
* Global variables:
*  OV9650_1_I2C_mstrRdBufIndex - The global variable stores current index
*                                    within the master read buffer.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterGetReadBufSize(void) 
{
    return (OV9650_1_I2C_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the amount of bytes that has been transferred with an
*  I2C_MasterWriteBuf command.
*
* Parameters:
*  None.
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it will return
*  the byte count transferred so far.
*
* Global variables:
*  OV9650_1_I2C_mstrWrBufIndex -  The global variable used to stores current
*                                     index within master write buffer.
*
*******************************************************************************/
uint8 OV9650_1_I2C_MasterGetWriteBufSize(void) 
{
    return (OV9650_1_I2C_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  OV9650_1_I2C_mstrRdBufIndex - The global variable used to stores current
*                                    index within master read buffer.
*  OV9650_1_I2C_mstrStatus - The global variable used to store a current
*                                status of the I2C Master.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void OV9650_1_I2C_MasterClearReadBuf(void) 
{
    OV9650_1_I2C_DisableInt(); /* Lock from interrupt */

    OV9650_1_I2C_mstrRdBufIndex = 0u;
    OV9650_1_I2C_mstrStatus    &= (uint8) ~OV9650_1_I2C_MSTAT_RD_CMPLT;

    OV9650_1_I2C_EnableInt(); /* Release lock */
}


/*******************************************************************************
* Function Name: OV9650_1_I2C_MasterClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  OV9650_1_I2C_mstrRdBufIndex - The global variable used to stote current
*                                    index within master read buffer.
*  OV9650_1_I2C_mstrStatus - The global variable used to store a current
*                                status of the I2C Master.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void OV9650_1_I2C_MasterClearWriteBuf(void) 
{
    OV9650_1_I2C_DisableInt(); /* Lock from interrupt */

    OV9650_1_I2C_mstrWrBufIndex = 0u;
    OV9650_1_I2C_mstrStatus    &= (uint8) ~OV9650_1_I2C_MSTAT_WR_CMPLT;

    OV9650_1_I2C_EnableInt(); /* Release lock */
}

#endif /* (OV9650_1_I2C_MODE_MASTER_ENABLED) */


/* [] END OF FILE */
