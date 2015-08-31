/*******************************************************************************
* File Name: mSerial_drv.c
* Version 2.80
*
* Description:
*  Endpoint 0 Driver for the USBFS Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "mSerial.h"
#include "mSerial_pvt.h"


/***************************************
* Global data allocation
***************************************/

volatile T_mSerial_EP_CTL_BLOCK mSerial_EP[mSerial_MAX_EP];
volatile uint8 mSerial_configuration;
volatile uint8 mSerial_interfaceNumber;
volatile uint8 mSerial_configurationChanged;
volatile uint8 mSerial_deviceAddress;
volatile uint8 mSerial_deviceStatus;
volatile uint8 mSerial_interfaceSetting[mSerial_MAX_INTERFACES_NUMBER];
volatile uint8 mSerial_interfaceSetting_last[mSerial_MAX_INTERFACES_NUMBER];
volatile uint8 mSerial_interfaceStatus[mSerial_MAX_INTERFACES_NUMBER];
volatile uint8 mSerial_device;
const uint8 CYCODE *mSerial_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 mSerial_ep0Toggle;
volatile uint8 mSerial_lastPacketSize;
volatile uint8 mSerial_transferState;
volatile T_mSerial_TD mSerial_currentTD;
volatile uint8 mSerial_ep0Mode;
volatile uint8 mSerial_ep0Count;
volatile uint16 mSerial_transferByteCount;


/*******************************************************************************
* Function Name: mSerial_ep_0_Interrupt
********************************************************************************
*
* Summary:
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(mSerial_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;


    bRegTemp = CY_GET_REG8(mSerial_EP0_CR_PTR);
    if ((bRegTemp & mSerial_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((bRegTemp & mSerial_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & mSerial_MODE_MASK) != mSerial_MODE_NAK_IN_OUT)
            {
                modifyReg = 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                mSerial_HandleSetup();
                if((mSerial_ep0Mode & mSerial_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg = 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & mSerial_MODE_IN_RCVD) != 0u)
        {
            mSerial_HandleIN();
        }
        else if ((bRegTemp & mSerial_MODE_OUT_RCVD) != 0u)
        {
            mSerial_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp = CY_GET_REG8(mSerial_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & mSerial_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp = mSerial_ep0Toggle | mSerial_ep0Count;
                CY_SET_REG8(mSerial_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(mSerial_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg = mSerial_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp = CY_GET_REG8(mSerial_EP0_CR_PTR) & mSerial_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(mSerial_EP0_CR_PTR, mSerial_ep0Mode);
                            /* Writing check */
                            modifyReg = CY_GET_REG8(mSerial_EP0_CR_PTR) & mSerial_MODE_MASK;
                        }
                    }while(modifyReg != mSerial_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: mSerial_HandleSetup
********************************************************************************
*
* Summary:
*  This Routine dispatches requests for the four USB request types
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
void mSerial_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled = CY_GET_REG8(mSerial_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(mSerial_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled = CY_GET_REG8(mSerial_EP0_CR_PTR);      /* reread register */
    if((requestHandled & mSerial_MODE_SETUP_RCVD) != 0u)
    {
        mSerial_ep0Mode = requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        mSerial_UpdateStatusBlock(mSerial_XFER_PREMATURE);

        switch (CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_TYPE_MASK)
        {
            case mSerial_RQST_TYPE_STD:
                requestHandled = mSerial_HandleStandardRqst();
                break;
            case mSerial_RQST_TYPE_CLS:
                requestHandled = mSerial_DispatchClassRqst();
                break;
            case mSerial_RQST_TYPE_VND:
                requestHandled = mSerial_HandleVendorRqst();
                break;
            default:
                requestHandled = mSerial_FALSE;
                break;
        }
        if (requestHandled == mSerial_FALSE)
        {
            mSerial_ep0Mode = mSerial_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: mSerial_HandleIN
********************************************************************************
*
* Summary:
*  This routine handles EP0 IN transfers.
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
void mSerial_HandleIN(void) 
{
    switch (mSerial_transferState)
    {
        case mSerial_TRANS_STATE_IDLE:
            break;
        case mSerial_TRANS_STATE_CONTROL_READ:
            mSerial_ControlReadDataStage();
            break;
        case mSerial_TRANS_STATE_CONTROL_WRITE:
            mSerial_ControlWriteStatusStage();
            break;
        case mSerial_TRANS_STATE_NO_DATA_CONTROL:
            mSerial_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: mSerial_HandleOUT
********************************************************************************
*
* Summary:
*  This routine handles EP0 OUT transfers.
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
void mSerial_HandleOUT(void) 
{
    switch (mSerial_transferState)
    {
        case mSerial_TRANS_STATE_IDLE:
            break;
        case mSerial_TRANS_STATE_CONTROL_READ:
            mSerial_ControlReadStatusStage();
            break;
        case mSerial_TRANS_STATE_CONTROL_WRITE:
            mSerial_ControlWriteDataStage();
            break;
        case mSerial_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            mSerial_UpdateStatusBlock(mSerial_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            mSerial_ep0Mode = mSerial_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: mSerial_LoadEP0
********************************************************************************
*
* Summary:
*  This routine loads the EP0 data registers for OUT transfers.  It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  mSerial_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  mSerial_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  mSerial_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  mSerial_ep0Toggle - inverted
*  mSerial_ep0Mode  - prepare for mode register content.
*  mSerial_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    mSerial_transferByteCount += mSerial_lastPacketSize;
    /* Now load the next transaction */
    while ((mSerial_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(mSerial_EP0_DR0_IND + ep0Count), *mSerial_currentTD.pData);
        mSerial_currentTD.pData = &mSerial_currentTD.pData[1u];
        ep0Count++;
        mSerial_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (mSerial_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        mSerial_ep0Toggle ^= mSerial_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        mSerial_ep0Mode = mSerial_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        mSerial_transferState = mSerial_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        mSerial_ep0Mode = mSerial_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        mSerial_transferState = mSerial_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    mSerial_lastPacketSize = ep0Count;
    mSerial_ep0Count = ep0Count;
}


/*******************************************************************************
* Function Name: mSerial_InitControlRead
********************************************************************************
*
* Summary:
*  Initialize a control read transaction, usable to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  mSerial_currentTD.count - counts of data to be sent.
*  mSerial_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_InitControlRead(void) 
{
    uint16 xferCount;
    if(mSerial_currentTD.count == 0u)
    {
        (void) mSerial_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        mSerial_transferState = mSerial_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        mSerial_ep0Toggle = 0u;
        /* Initialize the Status Block */
        mSerial_InitializeStatusBlock();
        xferCount = (((uint16)CY_GET_REG8(mSerial_lengthHi) << 8u) | (CY_GET_REG8(mSerial_lengthLo)));

        if (mSerial_currentTD.count > xferCount)
        {
            mSerial_currentTD.count = xferCount;
        }
        mSerial_LoadEP0();
    }

    return(mSerial_TRUE);
}


/*******************************************************************************
* Function Name: mSerial_InitZeroLengthControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a zero length data IN transfer.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  mSerial_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  mSerial_ep0Mode  - prepare for mode register content.
*  mSerial_transferState - set to TRANS_STATE_CONTROL_READ
*  mSerial_ep0Count - cleared, means the zero-length packet.
*  mSerial_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    mSerial_transferState = mSerial_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    mSerial_ep0Toggle = mSerial_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    mSerial_ep0Mode = mSerial_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    mSerial_lastPacketSize = 0u;
    mSerial_ep0Count = 0u;

    return(mSerial_TRUE);
}


/*******************************************************************************
* Function Name: mSerial_ControlReadDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control read transfer.
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
void mSerial_ControlReadDataStage(void) 

{
    mSerial_LoadEP0();
}


/*******************************************************************************
* Function Name: mSerial_ControlReadStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_USBFS_transferByteCount - updated with last packet size.
*  mSerial_transferState - set to TRANS_STATE_IDLE.
*  mSerial_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    mSerial_transferByteCount += mSerial_lastPacketSize;
    /* Go Idle */
    mSerial_transferState = mSerial_TRANS_STATE_IDLE;
    /* Update the completion block */
    mSerial_UpdateStatusBlock(mSerial_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    mSerial_ep0Mode =  mSerial_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: mSerial_InitControlWrite
********************************************************************************
*
* Summary:
*  Initialize a control write transaction
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  mSerial_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  mSerial_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  mSerial_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    mSerial_transferState = mSerial_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    mSerial_ep0Toggle = mSerial_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    mSerial_InitializeStatusBlock();

    xferCount = (((uint16)CY_GET_REG8(mSerial_lengthHi) << 8u) | (CY_GET_REG8(mSerial_lengthLo)));

    if (mSerial_currentTD.count > xferCount)
    {
        mSerial_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    mSerial_ep0Mode = mSerial_MODE_ACK_OUT_STATUS_IN;

    return(mSerial_TRUE);
}


/*******************************************************************************
* Function Name: mSerial_ControlWriteDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  mSerial_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  mSerial_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  mSerial_ep0Toggle - inverted
*  mSerial_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (CY_GET_REG8(mSerial_EP0_CNT_PTR) & mSerial_EPX_CNT0_MASK) -
               mSerial_EPX_CNTX_CRC_COUNT;

    mSerial_transferByteCount += ep0Count;

    while ((mSerial_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *mSerial_currentTD.pData = CY_GET_REG8((reg8 *)(mSerial_EP0_DR0_IND + regIndex));
        mSerial_currentTD.pData = &mSerial_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        mSerial_currentTD.count--;
    }
    mSerial_ep0Count = ep0Count;
    /* Update the data toggle */
    mSerial_ep0Toggle ^= mSerial_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    mSerial_ep0Mode = mSerial_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: mSerial_ControlWriteStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control write transfer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_transferState - set to TRANS_STATE_IDLE.
*  mSerial_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    mSerial_transferState = mSerial_TRANS_STATE_IDLE;
    /* Update the completion block */
    mSerial_UpdateStatusBlock(mSerial_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    mSerial_ep0Mode = mSerial_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: mSerial_InitNoDataControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a no data control transfer
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  mSerial_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  mSerial_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  mSerial_ep0Count - cleared.
*  mSerial_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_InitNoDataControlTransfer(void) 
{
    mSerial_transferState = mSerial_TRANS_STATE_NO_DATA_CONTROL;
    mSerial_ep0Mode = mSerial_MODE_STATUS_IN_ONLY;
    mSerial_ep0Toggle = mSerial_EP0_CNT_DATA_TOGGLE;
    mSerial_ep0Count = 0u;

    return(mSerial_TRUE);
}


/*******************************************************************************
* Function Name: mSerial_NoDataControlStatusStage
********************************************************************************
* Summary:
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_transferState - set to TRANS_STATE_IDLE.
*  mSerial_ep0Mode  - set to MODE_STALL_IN_OUT.
*  mSerial_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  mSerial_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (mSerial_deviceAddress != 0u)
    {
        CY_SET_REG8(mSerial_CR0_PTR, mSerial_deviceAddress | mSerial_CR0_ENABLE);
        mSerial_deviceAddress = 0u;
    }
    /* Go Idle */
    mSerial_transferState = mSerial_TRANS_STATE_IDLE;
    /* Update the completion block */
    mSerial_UpdateStatusBlock(mSerial_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    mSerial_ep0Mode = mSerial_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: mSerial_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the mSerial_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  mSerial_currentTD.pStatusBlock->length - updated.
*  mSerial_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_UpdateStatusBlock(uint8 completionCode) 
{
    if (mSerial_currentTD.pStatusBlock != NULL)
    {
        mSerial_currentTD.pStatusBlock->status = completionCode;
        mSerial_currentTD.pStatusBlock->length = mSerial_transferByteCount;
        mSerial_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: mSerial_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes mSerial_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  mSerial_currentTD.pStatusBlock->length - cleared.
*  mSerial_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_InitializeStatusBlock(void) 
{
    mSerial_transferByteCount = 0u;
    if(mSerial_currentTD.pStatusBlock != NULL)
    {
        mSerial_currentTD.pStatusBlock->status = mSerial_XFER_IDLE;
        mSerial_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
