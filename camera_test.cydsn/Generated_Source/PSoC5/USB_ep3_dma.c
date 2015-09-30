/***************************************************************************
* File Name: USB_ep3_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <USB_ep3_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* USB_ep3__DRQ_CTL_REG
* 
* 
* USB_ep3__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* USB_ep3__NUMBEROF_TDS
* 
* Priority of this channel.
* USB_ep3__PRIORITY
* 
* True if USB_ep3_TERMIN_SEL is used.
* USB_ep3__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* USB_ep3__TERMIN_SEL
* 
* 
* True if USB_ep3_TERMOUT0_SEL is used.
* USB_ep3__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* USB_ep3__TERMOUT0_SEL
* 
* 
* True if USB_ep3_TERMOUT1_SEL is used.
* USB_ep3__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* USB_ep3__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of USB_ep3 dma channel */
uint8 USB_ep3_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 USB_ep3_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 USB_ep3_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    USB_ep3_DmaHandle = (uint8)USB_ep3__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(USB_ep3_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)USB_ep3__TERMOUT0_SEL,
                                  (uint8)USB_ep3__TERMOUT1_SEL,
                                  (uint8)USB_ep3__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(USB_ep3_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(USB_ep3_DmaHandle, (uint8)USB_ep3__PRIORITY);
    
    return USB_ep3_DmaHandle;
}

/*********************************************************************
* Function Name: void USB_ep3_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with USB_ep3.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void USB_ep3_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(USB_ep3_DmaHandle);
}

