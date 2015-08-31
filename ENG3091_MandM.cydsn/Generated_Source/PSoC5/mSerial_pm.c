/*******************************************************************************
* File Name: mSerial_pm.c
* Version 2.80
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "project.h"
#include "mSerial.h"
#include "mSerial_pvt.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static mSerial_BACKUP_STRUCT  mSerial_backup;


#if(mSerial_DP_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: mSerial_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(mSerial_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(mSerial_DP_INTSTAT_PTR);
    }

#endif /* (mSerial_DP_ISR_REMOVE == 0u) */


/*******************************************************************************
* Function Name: mSerial_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
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
void mSerial_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: mSerial_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
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
void mSerial_RestoreConfig(void) 
{
    if(mSerial_configuration != 0u)
    {
        mSerial_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: mSerial_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power down mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  mSerial_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_Suspend(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if((CY_GET_REG8(mSerial_CR0_PTR) & mSerial_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        mSerial_backup.enableState = 1u;

        #if(mSerial_EP_MM != mSerial__EP_MANUAL)
            mSerial_Stop_DMA(mSerial_MAX_EP);     /* Stop all DMAs */
        #endif   /*  mSerial_EP_MM != mSerial__EP_MANUAL */

        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        mSerial_USBIO_CR0_REG &= (uint8)~mSerial_USBIO_CR0_TEN;
        CyDelayUs(0u);  /*~50ns delay */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        mSerial_PM_USB_CR0_REG &=
                                (uint8)~(mSerial_PM_USB_CR0_PD_N | mSerial_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE */
        mSerial_CR0_REG &= (uint8)~mSerial_CR0_ENABLE;

        CyDelayUs(0u);  /* ~50ns delay */
        /* Store mode and Disable VRegulator*/
        mSerial_backup.mode = mSerial_CR1_REG & mSerial_CR1_REG_ENABLE;
        mSerial_CR1_REG &= (uint8)~mSerial_CR1_REG_ENABLE;

        CyDelayUs(1u);  /* 0.5 us min delay */
        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        mSerial_PM_USB_CR0_REG &= (uint8)~mSerial_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
        mSerial_USBIO_CR1_REG |= mSerial_USBIO_CR1_IOMODE;

        /* Disable USB in ACT PM */
        mSerial_PM_ACT_CFG_REG &= (uint8)~mSerial_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        mSerial_PM_STBY_CFG_REG &= (uint8)~mSerial_PM_STBY_EN_FSUSB;
        CyDelayUs(1u); /* min  0.5us delay required */

    }
    else
    {
        mSerial_backup.enableState = 0u;
    }

    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if(mSerial_DP_ISR_REMOVE == 0u)
        (void) CyIntSetVector(mSerial_DP_INTC_VECT_NUM, &mSerial_DP_ISR);
        CyIntSetPriority(mSerial_DP_INTC_VECT_NUM, mSerial_DP_INTC_PRIOR);
        CyIntClearPending(mSerial_DP_INTC_VECT_NUM);
        CyIntEnable(mSerial_DP_INTC_VECT_NUM);
    #endif /* (mSerial_DP_ISR_REMOVE == 0u) */
}


/*******************************************************************************
* Function Name: mSerial_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  mSerial_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_Resume(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if(mSerial_backup.enableState != 0u)
    {
        #if(mSerial_DP_ISR_REMOVE == 0u)
            CyIntDisable(mSerial_DP_INTC_VECT_NUM);
        #endif /*  mSerial_DP_ISR_REMOVE */

        /* Enable USB block */
        mSerial_PM_ACT_CFG_REG |= mSerial_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        mSerial_PM_STBY_CFG_REG |= mSerial_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        mSerial_USB_CLK_EN_REG |= mSerial_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        mSerial_PM_USB_CR0_REG |= mSerial_PM_USB_CR0_REF_EN;
        /* The reference will be available ~40us after power restored */
        CyDelayUs(40u);
        /* Return VRegulator*/
        mSerial_CR1_REG |= mSerial_backup.mode;
        CyDelayUs(0u);  /*~50ns delay */
        /* Enable USBIO */
        mSerial_PM_USB_CR0_REG |= mSerial_PM_USB_CR0_PD_N;
        CyDelayUs(2u);
        /* Set the USBIO pull-up enable */
        mSerial_PM_USB_CR0_REG |= mSerial_PM_USB_CR0_PD_PULLUP_N;

        /* Re-init Arbiter configuration for DMA transfers */
        #if(mSerial_EP_MM != mSerial__EP_MANUAL)
            /* Usb arb interrupt enable */
            mSerial_ARB_INT_EN_REG = mSerial_ARB_INT_MASK;
            #if(mSerial_EP_MM == mSerial__EP_DMAMANUAL)
                mSerial_ARB_CFG_REG = mSerial_ARB_CFG_MANUAL_DMA;
            #endif   /*  mSerial_EP_MM == mSerial__EP_DMAMANUAL */
            #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                mSerial_ARB_CFG_REG = mSerial_ARB_CFG_AUTO_DMA | mSerial_ARB_CFG_AUTO_MEM;
            #endif   /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */
        #endif   /*  mSerial_EP_MM != mSerial__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(mSerial_EP0_CR_PTR, mSerial_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        mSerial_CR0_REG |= mSerial_CR0_ENABLE;
        CyDelayCycles(1u);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(mSerial_USBIO_CR1_PTR, mSerial_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        mSerial_RestoreConfig();
    }

    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
