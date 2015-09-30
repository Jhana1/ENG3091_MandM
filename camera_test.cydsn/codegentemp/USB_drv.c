/*******************************************************************************
* File Name: USB_drv.c
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

#include "USB.h"
#include "USB_pvt.h"


/***************************************
* Global data allocation
***************************************/

volatile T_USB_EP_CTL_BLOCK USB_EP[USB_MAX_EP];
volatile uint8 USB_configuration;
volatile uint8 USB_interfaceNumber;
volatile uint8 USB_configurationChanged;
volatile uint8 USB_deviceAddress;
volatile uint8 USB_deviceStatus;
volatile uint8 USB_interfaceSetting[USB_MAX_INTERFACES_NUMBER];
volatile uint8 USB_interfaceSetting_last[USB_MAX_INTERFACES_NUMBER];
volatile uint8 USB_interfaceStatus[USB_MAX_INTERFACES_NUMBER];
volatile uint8 USB_device;
const uint8 CYCODE *USB_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 USB_ep0Toggle;
volatile uint8 USB_lastPacketSize;
volatile uint8 USB_transferState;
volatile T_USB_TD USB_currentTD;
volatile uint8 USB_ep0Mode;
volatile uint8 USB_ep0Count;
volatile uint16 USB_transferByteCount;


/*******************************************************************************
* Function Name: USB_ep_0_Interrupt
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
CY_ISR(USB_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;


    bRegTemp = CY_GET_REG8(USB_EP0_CR_PTR);
    if ((bRegTemp & USB_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((bRegTemp & USB_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & USB_MODE_MASK) != USB_MODE_NAK_IN_OUT)
            {
                modifyReg = 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                USB_HandleSetup();
                if((USB_ep0Mode & USB_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg = 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & USB_MODE_IN_RCVD) != 0u)
        {
            USB_HandleIN();
        }
        else if ((bRegTemp & USB_MODE_OUT_RCVD) != 0u)
        {
            USB_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp = CY_GET_REG8(USB_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & USB_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp = USB_ep0Toggle | USB_ep0Count;
                CY_SET_REG8(USB_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(USB_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg = USB_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp = CY_GET_REG8(USB_EP0_CR_PTR) & USB_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(USB_EP0_CR_PTR, USB_ep0Mode);
                            /* Writing check */
                            modifyReg = CY_GET_REG8(USB_EP0_CR_PTR) & USB_MODE_MASK;
                        }
                    }while(modifyReg != USB_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: USB_HandleSetup
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
void USB_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled = CY_GET_REG8(USB_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(USB_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled = CY_GET_REG8(USB_EP0_CR_PTR);      /* reread register */
    if((requestHandled & USB_MODE_SETUP_RCVD) != 0u)
    {
        USB_ep0Mode = requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        USB_UpdateStatusBlock(USB_XFER_PREMATURE);

        switch (CY_GET_REG8(USB_bmRequestType) & USB_RQST_TYPE_MASK)
        {
            case USB_RQST_TYPE_STD:
                requestHandled = USB_HandleStandardRqst();
                break;
            case USB_RQST_TYPE_CLS:
                requestHandled = USB_DispatchClassRqst();
                break;
            case USB_RQST_TYPE_VND:
                requestHandled = USB_HandleVendorRqst();
                break;
            default:
                requestHandled = USB_FALSE;
                break;
        }
        if (requestHandled == USB_FALSE)
        {
            USB_ep0Mode = USB_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USB_HandleIN
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
void USB_HandleIN(void) 
{
    switch (USB_transferState)
    {
        case USB_TRANS_STATE_IDLE:
            break;
        case USB_TRANS_STATE_CONTROL_READ:
            USB_ControlReadDataStage();
            break;
        case USB_TRANS_STATE_CONTROL_WRITE:
            USB_ControlWriteStatusStage();
            break;
        case USB_TRANS_STATE_NO_DATA_CONTROL:
            USB_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB_HandleOUT
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
void USB_HandleOUT(void) 
{
    switch (USB_transferState)
    {
        case USB_TRANS_STATE_IDLE:
            break;
        case USB_TRANS_STATE_CONTROL_READ:
            USB_ControlReadStatusStage();
            break;
        case USB_TRANS_STATE_CONTROL_WRITE:
            USB_ControlWriteDataStage();
            break;
        case USB_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            USB_UpdateStatusBlock(USB_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            USB_ep0Mode = USB_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB_LoadEP0
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
*  USB_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  USB_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  USB_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  USB_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  USB_ep0Toggle - inverted
*  USB_ep0Mode  - prepare for mode register content.
*  USB_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    USB_transferByteCount += USB_lastPacketSize;
    /* Now load the next transaction */
    while ((USB_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(USB_EP0_DR0_IND + ep0Count), *USB_currentTD.pData);
        USB_currentTD.pData = &USB_currentTD.pData[1u];
        ep0Count++;
        USB_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (USB_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        USB_ep0Toggle ^= USB_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        USB_ep0Mode = USB_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        USB_transferState = USB_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        USB_ep0Mode = USB_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        USB_transferState = USB_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    USB_lastPacketSize = ep0Count;
    USB_ep0Count = ep0Count;
}


/*******************************************************************************
* Function Name: USB_InitControlRead
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
*  USB_currentTD.count - counts of data to be sent.
*  USB_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_InitControlRead(void) 
{
    uint16 xferCount;
    if(USB_currentTD.count == 0u)
    {
        (void) USB_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        USB_transferState = USB_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        USB_ep0Toggle = 0u;
        /* Initialize the Status Block */
        USB_InitializeStatusBlock();
        xferCount = (((uint16)CY_GET_REG8(USB_lengthHi) << 8u) | (CY_GET_REG8(USB_lengthLo)));

        if (USB_currentTD.count > xferCount)
        {
            USB_currentTD.count = xferCount;
        }
        USB_LoadEP0();
    }

    return(USB_TRUE);
}


/*******************************************************************************
* Function Name: USB_InitZeroLengthControlTransfer
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
*  USB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_ep0Mode  - prepare for mode register content.
*  USB_transferState - set to TRANS_STATE_CONTROL_READ
*  USB_ep0Count - cleared, means the zero-length packet.
*  USB_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    USB_transferState = USB_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    USB_ep0Toggle = USB_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    USB_ep0Mode = USB_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    USB_lastPacketSize = 0u;
    USB_ep0Count = 0u;

    return(USB_TRUE);
}


/*******************************************************************************
* Function Name: USB_ControlReadDataStage
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
void USB_ControlReadDataStage(void) 

{
    USB_LoadEP0();
}


/*******************************************************************************
* Function Name: USB_ControlReadStatusStage
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
*  USB_USBFS_transferByteCount - updated with last packet size.
*  USB_transferState - set to TRANS_STATE_IDLE.
*  USB_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    USB_transferByteCount += USB_lastPacketSize;
    /* Go Idle */
    USB_transferState = USB_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UpdateStatusBlock(USB_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB_ep0Mode =  USB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_InitControlWrite
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
*  USB_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  USB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    USB_transferState = USB_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    USB_ep0Toggle = USB_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    USB_InitializeStatusBlock();

    xferCount = (((uint16)CY_GET_REG8(USB_lengthHi) << 8u) | (CY_GET_REG8(USB_lengthLo)));

    if (USB_currentTD.count > xferCount)
    {
        USB_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    USB_ep0Mode = USB_MODE_ACK_OUT_STATUS_IN;

    return(USB_TRUE);
}


/*******************************************************************************
* Function Name: USB_ControlWriteDataStage
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
*  USB_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  USB_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  USB_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  USB_ep0Toggle - inverted
*  USB_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (CY_GET_REG8(USB_EP0_CNT_PTR) & USB_EPX_CNT0_MASK) -
               USB_EPX_CNTX_CRC_COUNT;

    USB_transferByteCount += ep0Count;

    while ((USB_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *USB_currentTD.pData = CY_GET_REG8((reg8 *)(USB_EP0_DR0_IND + regIndex));
        USB_currentTD.pData = &USB_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        USB_currentTD.count--;
    }
    USB_ep0Count = ep0Count;
    /* Update the data toggle */
    USB_ep0Toggle ^= USB_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    USB_ep0Mode = USB_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: USB_ControlWriteStatusStage
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
*  USB_transferState - set to TRANS_STATE_IDLE.
*  USB_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    USB_transferState = USB_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UpdateStatusBlock(USB_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB_ep0Mode = USB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_InitNoDataControlTransfer
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
*  USB_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  USB_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  USB_ep0Count - cleared.
*  USB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_InitNoDataControlTransfer(void) 
{
    USB_transferState = USB_TRANS_STATE_NO_DATA_CONTROL;
    USB_ep0Mode = USB_MODE_STATUS_IN_ONLY;
    USB_ep0Toggle = USB_EP0_CNT_DATA_TOGGLE;
    USB_ep0Count = 0u;

    return(USB_TRUE);
}


/*******************************************************************************
* Function Name: USB_NoDataControlStatusStage
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
*  USB_transferState - set to TRANS_STATE_IDLE.
*  USB_ep0Mode  - set to MODE_STALL_IN_OUT.
*  USB_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (USB_deviceAddress != 0u)
    {
        CY_SET_REG8(USB_CR0_PTR, USB_deviceAddress | USB_CR0_ENABLE);
        USB_deviceAddress = 0u;
    }
    /* Go Idle */
    USB_transferState = USB_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB_UpdateStatusBlock(USB_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    USB_ep0Mode = USB_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the USB_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  USB_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  USB_currentTD.pStatusBlock->length - updated.
*  USB_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_UpdateStatusBlock(uint8 completionCode) 
{
    if (USB_currentTD.pStatusBlock != NULL)
    {
        USB_currentTD.pStatusBlock->status = completionCode;
        USB_currentTD.pStatusBlock->length = USB_transferByteCount;
        USB_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: USB_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes USB_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  USB_currentTD.pStatusBlock->length - cleared.
*  USB_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_InitializeStatusBlock(void) 
{
    USB_transferByteCount = 0u;
    if(USB_currentTD.pStatusBlock != NULL)
    {
        USB_currentTD.pStatusBlock->status = USB_XFER_IDLE;
        USB_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
