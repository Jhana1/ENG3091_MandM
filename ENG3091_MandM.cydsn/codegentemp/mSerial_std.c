/*******************************************************************************
* File Name: mSerial_std.c
* Version 2.80
*
* Description:
*  USB Standard request handler.
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
#include "mSerial_cdc.h"
#include "mSerial_pvt.h"
#if defined(mSerial_ENABLE_MIDI_STREAMING)
    #include "mSerial_midi.h"
#endif /*  mSerial_ENABLE_MIDI_STREAMING*/


/***************************************
*   Static data allocation
***************************************/

#if defined(mSerial_ENABLE_FWSN_STRING)
    static volatile uint8 *mSerial_fwSerialNumberStringDescriptor;
    static volatile uint8 mSerial_snStringConfirm = mSerial_FALSE;
#endif  /* mSerial_ENABLE_FWSN_STRING */

#if defined(mSerial_ENABLE_FWSN_STRING)

    /*******************************************************************************
    * Function Name: mSerial_SerialNumString
    ********************************************************************************
    *
    * Summary:
    *  Application firmware may supply the source of the USB device descriptors
    *  serial number string during runtime.
    *
    * Parameters:
    *  snString:  pointer to string.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void  mSerial_SerialNumString(uint8 snString[]) 
    {
        mSerial_snStringConfirm = mSerial_FALSE;
        if(snString != NULL)
        {
            /* Check descriptor validation */
            if( (snString[0u] > 1u ) && (snString[1u] == mSerial_DESCR_STRING) )
            {
                mSerial_fwSerialNumberStringDescriptor = snString;
                mSerial_snStringConfirm = mSerial_TRUE;
            }
        }
    }

#endif  /* mSerial_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: mSerial_HandleStandardRqst
********************************************************************************
*
* Summary:
*  This Routine dispatches standard requests
*
* Parameters:
*  None.
*
* Return:
*  TRUE if request handled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_HandleStandardRqst(void) 
{
    uint8 requestHandled = mSerial_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    #if defined(mSerial_ENABLE_STRINGS)
        volatile uint8 *pStr = 0u;
        #if defined(mSerial_ENABLE_DESCRIPTOR_STRINGS)
            uint8 nStr;
            uint8 descrLength;
        #endif /* mSerial_ENABLE_DESCRIPTOR_STRINGS */
    #endif /* mSerial_ENABLE_STRINGS */
    static volatile uint8 mSerial_tBuffer[mSerial_STATUS_LENGTH_MAX];
    const T_mSerial_LUT CYCODE *pTmp;
    mSerial_currentTD.count = 0u;

    if ((CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_DIR_MASK) == mSerial_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(mSerial_bRequest))
        {
            case mSerial_GET_DESCRIPTOR:
                if (CY_GET_REG8(mSerial_wValueHi) == mSerial_DESCR_DEVICE)
                {
                    pTmp = mSerial_GetDeviceTablePtr();
                    mSerial_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    mSerial_currentTD.count = mSerial_DEVICE_DESCR_LENGTH;
                    requestHandled  = mSerial_InitControlRead();
                }
                else if (CY_GET_REG8(mSerial_wValueHi) == mSerial_DESCR_CONFIG)
                {
                    pTmp = mSerial_GetConfigTablePtr(CY_GET_REG8(mSerial_wValueLo));
                    if( pTmp != NULL )  /* Verify that requested descriptor exists */
                    {
                        mSerial_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        mSerial_currentTD.count = ((uint16)(mSerial_currentTD.pData)[ \
                                          mSerial_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                         (mSerial_currentTD.pData)[mSerial_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = mSerial_InitControlRead();
                    }
                }
                #if defined(mSerial_ENABLE_STRINGS)
                else if (CY_GET_REG8(mSerial_wValueHi) == mSerial_DESCR_STRING)
                {
                    /* Descriptor Strings*/
                    #if defined(mSerial_ENABLE_DESCRIPTOR_STRINGS)
                        nStr = 0u;
                        pStr = (volatile uint8 *)&mSerial_STRING_DESCRIPTORS[0u];
                        while ( (CY_GET_REG8(mSerial_wValueLo) > nStr) && (*pStr != 0u) )
                        {
                            /* Read descriptor length from 1st byte */
                            descrLength = *pStr;
                            /* Move to next string descriptor */
                            pStr = &pStr[descrLength];
                            nStr++;
                        }
                    #endif /*  mSerial_ENABLE_DESCRIPTOR_STRINGS */
                    /* Microsoft OS String*/
                    #if defined(mSerial_ENABLE_MSOS_STRING)
                        if( CY_GET_REG8(mSerial_wValueLo) == mSerial_STRING_MSOS )
                        {
                            pStr = (volatile uint8 *)&mSerial_MSOS_DESCRIPTOR[0u];
                        }
                    #endif /*  mSerial_ENABLE_MSOS_STRING*/
                    /* SN string */
                    #if defined(mSerial_ENABLE_SN_STRING)
                        if( (CY_GET_REG8(mSerial_wValueLo) != 0u) &&
                            (CY_GET_REG8(mSerial_wValueLo) ==
                            mSerial_DEVICE0_DESCR[mSerial_DEVICE_DESCR_SN_SHIFT]) )
                        {

                            #if defined(mSerial_ENABLE_IDSN_STRING)
                                /* Read DIE ID and generate string descriptor in RAM */
                                mSerial_ReadDieID(mSerial_idSerialNumberStringDescriptor);
                                pStr = mSerial_idSerialNumberStringDescriptor;
                            #elif defined(mSerial_ENABLE_FWSN_STRING)
                                if(mSerial_snStringConfirm != mSerial_FALSE)
                                {
                                    pStr = mSerial_fwSerialNumberStringDescriptor;
                                }
                                else
                                {
                                    pStr = (volatile uint8 *)&mSerial_SN_STRING_DESCRIPTOR[0u];
                                }
                            #else
                                pStr = (volatile uint8 *)&mSerial_SN_STRING_DESCRIPTOR[0u];
                            #endif  /* defined(mSerial_ENABLE_IDSN_STRING) */
                        }
                    #endif    /*  mSerial_ENABLE_SN_STRING */
                    if (*pStr != 0u)
                    {
                        mSerial_currentTD.count = *pStr;
                        mSerial_currentTD.pData = pStr;
                        requestHandled  = mSerial_InitControlRead();
                    }
                }
                #endif /*  mSerial_ENABLE_STRINGS */
                else
                {
                    requestHandled = mSerial_DispatchClassRqst();
                }
                break;
            case mSerial_GET_STATUS:
                switch ((CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_RCPT_MASK))
                {
                    case mSerial_RQST_RCPT_EP:
                        mSerial_currentTD.count = mSerial_EP_STATUS_LENGTH;
                        mSerial_tBuffer[0u] = mSerial_EP[ \
                                        CY_GET_REG8(mSerial_wIndexLo) & mSerial_DIR_UNUSED].hwEpState;
                        mSerial_tBuffer[1u] = 0u;
                        mSerial_currentTD.pData = &mSerial_tBuffer[0u];
                        requestHandled  = mSerial_InitControlRead();
                        break;
                    case mSerial_RQST_RCPT_DEV:
                        mSerial_currentTD.count = mSerial_DEVICE_STATUS_LENGTH;
                        mSerial_tBuffer[0u] = mSerial_deviceStatus;
                        mSerial_tBuffer[1u] = 0u;
                        mSerial_currentTD.pData = &mSerial_tBuffer[0u];
                        requestHandled  = mSerial_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            case mSerial_GET_CONFIGURATION:
                mSerial_currentTD.count = 1u;
                mSerial_currentTD.pData = (volatile uint8 *)&mSerial_configuration;
                requestHandled  = mSerial_InitControlRead();
                break;
            case mSerial_GET_INTERFACE:
                mSerial_currentTD.count = 1u;
                mSerial_currentTD.pData = (volatile uint8 *)&mSerial_interfaceSetting[ \
                                                                            CY_GET_REG8(mSerial_wIndexLo)];
                requestHandled  = mSerial_InitControlRead();
                break;
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else {
        /* Control Write */
        switch (CY_GET_REG8(mSerial_bRequest))
        {
            case mSerial_SET_ADDRESS:
                mSerial_deviceAddress = CY_GET_REG8(mSerial_wValueLo);
                requestHandled = mSerial_InitNoDataControlTransfer();
                break;
            case mSerial_SET_CONFIGURATION:
                configurationN = CY_GET_REG8(mSerial_wValueLo);
                if(configurationN > 0u)
                {   /* Verify that configuration descriptor exists */
                    pTmp = mSerial_GetConfigTablePtr(configurationN - 1u);
                }
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != mSerial_configuration)
                    {
                        mSerial_configuration = configurationN;
                        mSerial_configurationChanged = mSerial_TRUE;
                        mSerial_Config(mSerial_TRUE);
                    }
                    requestHandled = mSerial_InitNoDataControlTransfer();
                }
                break;
            case mSerial_SET_INTERFACE:
                if (mSerial_ValidateAlternateSetting() != 0u)
                {
                    interfaceNumber = CY_GET_REG8(mSerial_wIndexLo);
                    mSerial_interfaceNumber = interfaceNumber;
                    mSerial_configurationChanged = mSerial_TRUE;
                    #if ((mSerial_EP_MA == mSerial__MA_DYNAMIC) && \
                         (mSerial_EP_MM == mSerial__EP_MANUAL) )
                        mSerial_Config(mSerial_FALSE);
                    #else
                        mSerial_ConfigAltChanged();
                    #endif /*  (mSerial_EP_MA == mSerial__MA_DYNAMIC) */
                    /* Update handled Alt setting changes status */
                    mSerial_interfaceSetting_last[interfaceNumber] =
                         mSerial_interfaceSetting[interfaceNumber];
                    requestHandled = mSerial_InitNoDataControlTransfer();
                }
                break;
            case mSerial_CLEAR_FEATURE:
                switch (CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_RCPT_MASK)
                {
                    case mSerial_RQST_RCPT_EP:
                        if (CY_GET_REG8(mSerial_wValueLo) == mSerial_ENDPOINT_HALT)
                        {
                            requestHandled = mSerial_ClearEndpointHalt();
                        }
                        break;
                    case mSerial_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (CY_GET_REG8(mSerial_wValueLo) == mSerial_DEVICE_REMOTE_WAKEUP)
                        {
                            mSerial_deviceStatus &= (uint8)~mSerial_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = mSerial_InitNoDataControlTransfer();
                        }
                        break;
                    case mSerial_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(mSerial_wIndexLo) < mSerial_MAX_INTERFACES_NUMBER)
                        {
                            mSerial_interfaceStatus[CY_GET_REG8(mSerial_wIndexLo)] &=
                                                                (uint8)~(CY_GET_REG8(mSerial_wValueLo));
                            requestHandled = mSerial_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            case mSerial_SET_FEATURE:
                switch (CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_RCPT_MASK)
                {
                    case mSerial_RQST_RCPT_EP:
                        if (CY_GET_REG8(mSerial_wValueLo) == mSerial_ENDPOINT_HALT)
                        {
                            requestHandled = mSerial_SetEndpointHalt();
                        }
                        break;
                    case mSerial_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (CY_GET_REG8(mSerial_wValueLo) == mSerial_DEVICE_REMOTE_WAKEUP)
                        {
                            mSerial_deviceStatus |= mSerial_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = mSerial_InitNoDataControlTransfer();
                        }
                        break;
                    case mSerial_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(mSerial_wIndexLo) < mSerial_MAX_INTERFACES_NUMBER)
                        {
                            mSerial_interfaceStatus[CY_GET_REG8(mSerial_wIndexLo)] &=
                                                                (uint8)~(CY_GET_REG8(mSerial_wValueLo));
                            requestHandled = mSerial_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    return(requestHandled);
}


#if defined(mSerial_ENABLE_IDSN_STRING)

    /***************************************************************************
    * Function Name: mSerial_ReadDieID
    ****************************************************************************
    *
    * Summary:
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    * Parameters:
    *  descr:  pointer on string descriptor.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    void mSerial_ReadDieID(uint8 descr[]) 
    {
        uint8 i;
        uint8 j = 0u;
        uint8 value;
        const char8 CYCODE hex[16u] = "0123456789ABCDEF";

        /* Check descriptor validation */
        if( descr != NULL)
        {
            descr[0u] = mSerial_IDSN_DESCR_LENGTH;
            descr[1u] = mSerial_DESCR_STRING;

            /* fill descriptor */
            for(i = 2u; i < mSerial_IDSN_DESCR_LENGTH; i += 4u)
            {
                value = CY_GET_XTND_REG8((void CYFAR *)(mSerial_DIE_ID + j));
                j++;
                descr[i] = (uint8)hex[value >> 4u];
                descr[i + 2u] = (uint8)hex[value & 0x0Fu];
            }
        }
    }

#endif /*  mSerial_ENABLE_IDSN_STRING */


/*******************************************************************************
* Function Name: mSerial_ConfigReg
********************************************************************************
*
* Summary:
*  This routine configures hardware registers from the variables.
*  It is called from mSerial_Config() function and from RestoreConfig
*  after Wakeup.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void mSerial_ConfigReg(void) 
{
    uint8 ep;
    uint8 i;
    #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
        uint8 epType = 0u;
    #endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */

    /* Set the endpoint buffer addresses */
    ep = mSerial_EP1;
    for (i = 0u; i < 0x80u; i+= 0x10u)
    {
        CY_SET_REG8((reg8 *)(mSerial_ARB_EP1_CFG_IND + i), mSerial_ARB_EPX_CFG_DEFAULT);
        #if(mSerial_EP_MM != mSerial__EP_MANUAL)
            /* Enable all Arbiter EP Interrupts : err, buf under, buf over, dma gnt(mode2 only), in buf full */
            CY_SET_REG8((reg8 *)(mSerial_ARB_EP1_INT_EN_IND + i), mSerial_ARB_EPX_INT_MASK);
        #endif   /*  mSerial_EP_MM != mSerial__EP_MANUAL */

        if(mSerial_EP[ep].epMode != mSerial_MODE_DISABLE)
        {
            if((mSerial_EP[ep].addr & mSerial_DIR_IN) != 0u )
            {
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + i), mSerial_MODE_NAK_IN);
            }
            else
            {
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + i), mSerial_MODE_NAK_OUT);
                /* Prepare EP type mask for automatic memory allocation */
                #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
                    epType |= (uint8)(0x01u << (ep - mSerial_EP1));
                #endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */
            }
        }
        else
        {
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + i), mSerial_MODE_STALL_DATA_EP);
        }

        #if(mSerial_EP_MM != mSerial__EP_DMAAUTO)
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CNT0_IND + i),   mSerial_EP[ep].bufferSize >> 8u);
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CNT1_IND + i),   mSerial_EP[ep].bufferSize & 0xFFu);

            CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_RA_IND + i),     mSerial_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_RA_MSB_IND + i), mSerial_EP[ep].buffOffset >> 8u);
            CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_WA_IND + i),     mSerial_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_WA_MSB_IND + i), mSerial_EP[ep].buffOffset >> 8u);
        #endif /*  mSerial_EP_MM != mSerial__EP_DMAAUTO */

        ep++;
    }

    #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
         /* BUF_SIZE depend on DMA_THRESS value: 55-32 bytes  44-16 bytes 33-8 bytes 22-4 bytes 11-2 bytes */
        mSerial_BUF_SIZE_REG = mSerial_DMA_BUF_SIZE;
        mSerial_DMA_THRES_REG = mSerial_DMA_BYTES_PER_BURST;   /* DMA burst threshold */
        mSerial_DMA_THRES_MSB_REG = 0u;
        mSerial_EP_ACTIVE_REG = mSerial_ARB_INT_MASK;
        mSerial_EP_TYPE_REG = epType;
        /* Cfg_cmp bit set to 1 once configuration is complete. */
        mSerial_ARB_CFG_REG = mSerial_ARB_CFG_AUTO_DMA | mSerial_ARB_CFG_AUTO_MEM |
                                       mSerial_ARB_CFG_CFG_CPM;
        /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
        mSerial_ARB_CFG_REG = mSerial_ARB_CFG_AUTO_DMA | mSerial_ARB_CFG_AUTO_MEM;
    #endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */

    CY_SET_REG8(mSerial_SIE_EP_INT_EN_PTR, 0xFFu);
}


/*******************************************************************************
* Function Name: mSerial_Config
********************************************************************************
*
* Summary:
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
* Parameters:
*  clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* Return:
*  None.
*
* mSerial_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 cur_ep;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    #if(mSerial_EP_MM != mSerial__EP_DMAAUTO)
        uint16 buffCount = 0u;
    #endif /*  mSerial_EP_MM != mSerial__EP_DMAAUTO */

    const T_mSerial_LUT CYCODE *pTmp;
    const T_mSerial_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear all of the endpoints */
    for (ep = 0u; ep < mSerial_MAX_EP; ep++)
    {
        mSerial_EP[ep].attrib = 0u;
        mSerial_EP[ep].hwEpState = 0u;
        mSerial_EP[ep].apiEpState = mSerial_NO_EVENT_PENDING;
        mSerial_EP[ep].epToggle = 0u;
        mSerial_EP[ep].epMode = mSerial_MODE_DISABLE;
        mSerial_EP[ep].bufferSize = 0u;
        mSerial_EP[ep].interface = 0u;

    }

    /* Clear Alternate settings for all interfaces */
    if(clearAltSetting != 0u)
    {
        for (i = 0u; i < mSerial_MAX_INTERFACES_NUMBER; i++)
        {
            mSerial_interfaceSetting[i] = 0x00u;
            mSerial_interfaceSetting_last[i] = 0x00u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if(mSerial_configuration > 0u)
    {
        pTmp = mSerial_GetConfigTablePtr(mSerial_configuration - 1u);
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if((pDescr[mSerial_CONFIG_DESCR_ATTRIB] & mSerial_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            mSerial_deviceStatus |=  mSerial_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            mSerial_deviceStatus &=  (uint8)~mSerial_DEVICE_STATUS_SELF_POWERED;
        }
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if ((mSerial_EP_MA == mSerial__MA_DYNAMIC) && \
             (mSerial_EP_MM == mSerial__EP_MANUAL) )
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_mSerial_EP_SETTINGS_BLOCK *) pTmp->p_list;
            for (i = 0u; i < ep; i++)
            {
                /* Compare current Alternate setting with EP Alt */
                if(mSerial_interfaceSetting[pEP->interface] == pEP->altSetting)
                {
                    cur_ep = pEP->addr & mSerial_DIR_UNUSED;
                    epType = pEP->attributes & mSerial_EP_TYPE_MASK;
                    if (pEP->addr & mSerial_DIR_IN)
                    {
                        /* IN Endpoint */
                        mSerial_EP[cur_ep].apiEpState = mSerial_EVENT_PENDING;
                        mSerial_EP[cur_ep].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                        mSerial_MODE_ISO_IN : mSerial_MODE_ACK_IN;
                        #if defined(mSerial_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == mSerial_CLASS_CDC_DATA) ||
                                (pEP->bMisc == mSerial_CLASS_CDC)) &&
                                (epType != mSerial_EP_TYPE_INT))
                            {
                                mSerial_cdc_data_in_ep = cur_ep;
                            }
                        #endif  /*  mSerial_ENABLE_CDC_CLASS*/
                        #if ( defined(mSerial_ENABLE_MIDI_STREAMING) && \
                                             (mSerial_MIDI_IN_BUFF_SIZE > 0) )
                            if((pEP->bMisc == mSerial_CLASS_AUDIO) &&
                               (epType == mSerial_EP_TYPE_BULK))
                            {
                                mSerial_midi_in_ep = cur_ep;
                            }
                        #endif  /*  mSerial_ENABLE_MIDI_STREAMING*/
                    }
                    else
                    {
                        /* OUT Endpoint */
                        mSerial_EP[cur_ep].apiEpState = mSerial_NO_EVENT_PENDING;
                        mSerial_EP[cur_ep].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                    mSerial_MODE_ISO_OUT : mSerial_MODE_ACK_OUT;
                        #if defined(mSerial_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == mSerial_CLASS_CDC_DATA) ||
                                (pEP->bMisc == mSerial_CLASS_CDC)) &&
                                (epType != mSerial_EP_TYPE_INT))
                            {
                                mSerial_cdc_data_out_ep = cur_ep;
                            }
                        #endif  /*  mSerial_ENABLE_CDC_CLASS*/
                        #if ( defined(mSerial_ENABLE_MIDI_STREAMING) && \
                                     (mSerial_MIDI_OUT_BUFF_SIZE > 0) )
                            if((pEP->bMisc == mSerial_CLASS_AUDIO) &&
                               (epType == mSerial_EP_TYPE_BULK))
                            {
                                mSerial_midi_out_ep = cur_ep;
                            }
                        #endif  /*  mSerial_ENABLE_MIDI_STREAMING*/
                    }
                    mSerial_EP[cur_ep].bufferSize = pEP->bufferSize;
                    mSerial_EP[cur_ep].addr = pEP->addr;
                    mSerial_EP[cur_ep].attrib = pEP->attributes;
                }
                pEP = &pEP[1u];
            }
        #else /* Configure for static EP memory allocation  */
            for (i = mSerial_EP1; i < mSerial_MAX_EP; i++)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_mSerial_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                for (cur_ep = 0u; cur_ep < ep; cur_ep++)
                {
                    /* EP count is equal to EP # in table and we found larger EP length than have before*/
                    if(i == (pEP->addr & mSerial_DIR_UNUSED))
                    {
                        if(mSerial_EP[i].bufferSize < pEP->bufferSize)
                        {
                            mSerial_EP[i].bufferSize = pEP->bufferSize;
                        }
                        /* Compare current Alternate setting with EP Alt*/
                        if(mSerial_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {
                            epType = pEP->attributes & mSerial_EP_TYPE_MASK;
                            if ((pEP->addr & mSerial_DIR_IN) != 0u)
                            {
                                /* IN Endpoint */
                                mSerial_EP[i].apiEpState = mSerial_EVENT_PENDING;
                                mSerial_EP[i].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                        mSerial_MODE_ISO_IN : mSerial_MODE_ACK_IN;
                                /* Find and initialize CDC IN endpoint number */
                                #if defined(mSerial_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == mSerial_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == mSerial_CLASS_CDC)) &&
                                        (epType != mSerial_EP_TYPE_INT))
                                    {
                                        mSerial_cdc_data_in_ep = i;
                                    }
                                #endif  /*  mSerial_ENABLE_CDC_CLASS*/
                                #if ( defined(mSerial_ENABLE_MIDI_STREAMING) && \
                                             (mSerial_MIDI_IN_BUFF_SIZE > 0) )
                                    if((pEP->bMisc == mSerial_CLASS_AUDIO) &&
                                       (epType == mSerial_EP_TYPE_BULK))
                                    {
                                        mSerial_midi_in_ep = i;
                                    }
                                #endif  /*  mSerial_ENABLE_MIDI_STREAMING*/
                            }
                            else
                            {
                                /* OUT Endpoint */
                                mSerial_EP[i].apiEpState = mSerial_NO_EVENT_PENDING;
                                mSerial_EP[i].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                    mSerial_MODE_ISO_OUT : mSerial_MODE_ACK_OUT;
                                /* Find and initialize CDC IN endpoint number */
                                #if defined(mSerial_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == mSerial_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == mSerial_CLASS_CDC)) &&
                                        (epType != mSerial_EP_TYPE_INT))
                                    {
                                        mSerial_cdc_data_out_ep = i;
                                    }
                                #endif  /*  mSerial_ENABLE_CDC_CLASS*/
                                #if ( defined(mSerial_ENABLE_MIDI_STREAMING) && \
                                             (mSerial_MIDI_OUT_BUFF_SIZE > 0) )
                                    if((pEP->bMisc == mSerial_CLASS_AUDIO) &&
                                       (epType == mSerial_EP_TYPE_BULK))
                                    {
                                        mSerial_midi_out_ep = i;
                                    }
                                #endif  /*  mSerial_ENABLE_MIDI_STREAMING*/
                            }
                            mSerial_EP[i].addr = pEP->addr;
                            mSerial_EP[i].attrib = pEP->attributes;

                            #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
                                break;      /* use first EP setting in Auto memory managment */
                            #endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */
                        }
                    }
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (mSerial_EP_MA == mSerial__MA_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_mSerial_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP*/
            mSerial_EP[pEP->addr & mSerial_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        /* Init pointer on interface class table*/
        mSerial_interfaceClass = mSerial_GetInterfaceClassTablePtr();
        /* Set the endpoint buffer addresses */

        #if(mSerial_EP_MM != mSerial__EP_DMAAUTO)
            for (ep = mSerial_EP1; ep < mSerial_MAX_EP; ep++)
            {
                mSerial_EP[ep].buffOffset = buffCount;
                 buffCount += mSerial_EP[ep].bufferSize;
            }
        #endif /*  mSerial_EP_MM != mSerial__EP_DMAAUTO */

        /* Configure hardware registers */
        mSerial_ConfigReg();
    } /* mSerial_configuration > 0 */
}


/*******************************************************************************
* Function Name: mSerial_ConfigAltChanged
********************************************************************************
*
* Summary:
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
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
void mSerial_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 cur_ep;
    uint8 i;
    uint8 epType;
    uint8 ri;

    const T_mSerial_LUT CYCODE *pTmp;
    const T_mSerial_EP_SETTINGS_BLOCK CYCODE *pEP;


    /* Init Endpoints and Device Status if configured */
    if(mSerial_configuration > 0u)
    {
        pTmp = mSerial_GetConfigTablePtr(mSerial_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        /* Do not touch EP which doesn't need reconfiguration */
        /* When Alt setting changed, the only required endpoints need to be reconfigured */
        /* p_list points the endpoint setting table. */
        pEP = (const T_mSerial_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /*If Alt setting changed and new is same with EP Alt */
            if((mSerial_interfaceSetting[pEP->interface] !=
                mSerial_interfaceSetting_last[pEP->interface] ) &&
               (mSerial_interfaceSetting[pEP->interface] == pEP->altSetting) &&
               (pEP->interface == CY_GET_REG8(mSerial_wIndexLo)))
            {
                cur_ep = pEP->addr & mSerial_DIR_UNUSED;
                ri = ((cur_ep - mSerial_EP1) << mSerial_EPX_CNTX_ADDR_SHIFT);
                epType = pEP->attributes & mSerial_EP_TYPE_MASK;
                if ((pEP->addr & mSerial_DIR_IN) != 0u)
                {
                    /* IN Endpoint */
                    mSerial_EP[cur_ep].apiEpState = mSerial_EVENT_PENDING;
                    mSerial_EP[cur_ep].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                mSerial_MODE_ISO_IN : mSerial_MODE_ACK_IN;
                }
                else
                {
                    /* OUT Endpoint */
                    mSerial_EP[cur_ep].apiEpState = mSerial_NO_EVENT_PENDING;
                    mSerial_EP[cur_ep].epMode = (epType == mSerial_EP_TYPE_ISOC) ?
                                                mSerial_MODE_ISO_OUT : mSerial_MODE_ACK_OUT;
                }
                 /* Change the SIE mode for the selected EP to NAK ALL */
                 CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_NAK_IN_OUT);
                mSerial_EP[cur_ep].bufferSize = pEP->bufferSize;
                mSerial_EP[cur_ep].addr = pEP->addr;
                mSerial_EP[cur_ep].attrib = pEP->attributes;

                /* Clear the data toggle */
                mSerial_EP[cur_ep].epToggle = 0u;

                /* Dynamic reconfiguration for mode 3 transfer */
            #if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
                /* In_data_rdy for selected EP should be set to 0 */
                * (reg8 *)(mSerial_ARB_EP1_CFG_IND + ri) &= (uint8)~mSerial_ARB_EPX_CFG_IN_DATA_RDY;

                /* write the EP number for which reconfiguration is required */
                mSerial_DYN_RECONFIG_REG = (cur_ep - mSerial_EP1) <<
                                                    mSerial_DYN_RECONFIG_EP_SHIFT;
                /* Set the dyn_config_en bit in dynamic reconfiguration register */
                mSerial_DYN_RECONFIG_REG |= mSerial_DYN_RECONFIG_ENABLE;
                /* wait for the dyn_config_rdy bit to set by the block,
                *  this bit will be set to 1 when block is ready for reconfiguration.
                */
                while((mSerial_DYN_RECONFIG_REG & mSerial_DYN_RECONFIG_RDY_STS) == 0u)
                {
                    ;
                }
                /* Once dyn_config_rdy bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if((pEP->addr & mSerial_DIR_IN) == 0u)
                {
                    mSerial_EP_TYPE_REG |= (uint8)(0x01u << (cur_ep - mSerial_EP1));
                }
                else
                {
                    mSerial_EP_TYPE_REG &= (uint8)~(uint8)(0x01u << (cur_ep - mSerial_EP1));
                }
                /* dynamic reconfiguration enable bit cleared, pointers and control/status
                *  signals for the selected EP is cleared/re-initialized on negative edge
                *  of dynamic reconfiguration enable bit).
                */
                mSerial_DYN_RECONFIG_REG &= (uint8)~mSerial_DYN_RECONFIG_ENABLE;
                /* The main loop has to re-enable DMA and OUT endpoint*/
            #else
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CNT0_IND + ri),
                                                                mSerial_EP[cur_ep].bufferSize >> 8u);
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CNT1_IND + ri),
                                                                mSerial_EP[cur_ep].bufferSize & 0xFFu);
                CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_RA_IND + ri),
                                                                mSerial_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_RA_MSB_IND + ri),
                                                                mSerial_EP[cur_ep].buffOffset >> 8u);
                CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_WA_IND + ri),
                                                                mSerial_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8((reg8 *)(mSerial_ARB_RW1_WA_MSB_IND + ri),
                                                                mSerial_EP[cur_ep].buffOffset >> 8u);
            #endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */
            }
            /* Get next EP element */
            pEP = &pEP[1u];
        }
    }   /* mSerial_configuration > 0 */
}


/*******************************************************************************
* Function Name: mSerial_GetConfigTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer a configuration table entry
*
* Parameters:
*  confIndex:  Configuration Index
*
* Return:
*  Device Descriptor pointer or NULL when descriptor isn't exists.
*
*******************************************************************************/
const T_mSerial_LUT CYCODE *mSerial_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_mSerial_LUT CYCODE *pTmp;

    pTmp = (const T_mSerial_LUT CYCODE *) mSerial_TABLE[mSerial_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[1u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_mSerial_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_mSerial_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return( pTmp );
}


/*******************************************************************************
* Function Name: mSerial_GetDeviceTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer to the Device table
*
* Parameters:
*  None.
*
* Return:
*  Device Table pointer
*
*******************************************************************************/
const T_mSerial_LUT CYCODE *mSerial_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_mSerial_LUT CYCODE *) mSerial_TABLE[mSerial_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
********************************************************************************
*
* Summary:
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* Parameters:
*  None.
*
* Return:
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *mSerial_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_mSerial_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = mSerial_GetConfigTablePtr(mSerial_configuration - 1u);
    if( pTmp != NULL )
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[mSerial_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return( pInterfaceClass );
}


/*******************************************************************************
* Function Name: mSerial_TerminateEP
********************************************************************************
*
* Summary:
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
* Parameters:
*  Endpoint number.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void mSerial_TerminateEP(uint8 ep) 
{
    uint8 ri;

    ep &= mSerial_DIR_UNUSED;
    ri = ((ep - mSerial_EP1) << mSerial_EPX_CNTX_ADDR_SHIFT);

    if ((ep > mSerial_EP0) && (ep < mSerial_MAX_EP))
    {
        /* Set the endpoint Halt */
        mSerial_EP[ep].hwEpState |= (mSerial_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        mSerial_EP[ep].epToggle = 0u;
        mSerial_EP[ep].apiEpState = mSerial_NO_EVENT_ALLOWED;

        if ((mSerial_EP[ep].addr & mSerial_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_NAK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_NAK_OUT);
        }
    }
}


/*******************************************************************************
* Function Name: mSerial_SetEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles set endpoint halt.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_SetEndpointHalt(void) 
{
    uint8 ep;
    uint8 ri;
    uint8 requestHandled = mSerial_FALSE;

    /* Set endpoint halt */
    ep = CY_GET_REG8(mSerial_wIndexLo) & mSerial_DIR_UNUSED;
    ri = ((ep - mSerial_EP1) << mSerial_EPX_CNTX_ADDR_SHIFT);

    if ((ep > mSerial_EP0) && (ep < mSerial_MAX_EP))
    {
        /* Set the endpoint Halt */
        mSerial_EP[ep].hwEpState |= (mSerial_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        mSerial_EP[ep].epToggle = 0u;
        mSerial_EP[ep].apiEpState |= mSerial_NO_EVENT_ALLOWED;

        if ((mSerial_EP[ep].addr & mSerial_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_STALL_DATA_EP |
                                                               mSerial_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_STALL_DATA_EP |
                                                               mSerial_MODE_ACK_OUT);
        }
        requestHandled = mSerial_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: mSerial_ClearEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles clear endpoint halt.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_ClearEndpointHalt(void) 
{
    uint8 ep;
    uint8 ri;
    uint8 requestHandled = mSerial_FALSE;

    /* Clear endpoint halt */
    ep = CY_GET_REG8(mSerial_wIndexLo) & mSerial_DIR_UNUSED;
    ri = ((ep - mSerial_EP1) << mSerial_EPX_CNTX_ADDR_SHIFT);

    if ((ep > mSerial_EP0) && (ep < mSerial_MAX_EP))
    {
        /* Clear the endpoint Halt */
        mSerial_EP[ep].hwEpState &= (uint8)~(mSerial_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        mSerial_EP[ep].epToggle = 0u;
        /* Clear toggle bit for already armed packet */
        CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CNT0_IND + ri), CY_GET_REG8(
                    (reg8 *)(mSerial_SIE_EP1_CNT0_IND + ri)) & (uint8)~mSerial_EPX_CNT_DATA_TOGGLE);
        /* Return API State as it was defined before */
        mSerial_EP[ep].apiEpState &= (uint8)~mSerial_NO_EVENT_ALLOWED;

        if ((mSerial_EP[ep].addr & mSerial_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(mSerial_EP[ep].apiEpState == mSerial_IN_BUFFER_EMPTY)
            {       /* Wait for next packet from application */
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_NAK_IN);
            }
            else    /* Continue armed transfer */
            {
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_ACK_IN);
            }
        }
        else
        {
            /* OUT Endpoint */
            if(mSerial_EP[ep].apiEpState == mSerial_OUT_BUFFER_FULL)
            {       /* Allow application to read full buffer */
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_NAK_OUT);
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                CY_SET_REG8((reg8 *)(mSerial_SIE_EP1_CR0_IND + ri), mSerial_MODE_ACK_OUT);
            }
        }
        requestHandled = mSerial_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: mSerial_ValidateAlternateSetting
********************************************************************************
*
* Summary:
*  Validates (and records) a SET INTERFACE request.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = mSerial_TRUE;
    uint8 interfaceNum;
    const T_mSerial_LUT CYCODE *pTmp;
    uint8 currentInterfacesNum;

    interfaceNum = CY_GET_REG8(mSerial_wIndexLo);
    /* Validate interface setting, stall if invalid. */
    pTmp = mSerial_GetConfigTablePtr(mSerial_configuration - 1u);
    currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[mSerial_CONFIG_DESCR_NUM_INTERFACES];

    if((interfaceNum >= currentInterfacesNum) || (interfaceNum >= mSerial_MAX_INTERFACES_NUMBER))
    {   /* Wrong interface number */
        requestHandled = mSerial_FALSE;
    }
    else
    {
        /* Save current Alt setting to find out the difference in Config() function */
        mSerial_interfaceSetting_last[interfaceNum] = mSerial_interfaceSetting[interfaceNum];
        mSerial_interfaceSetting[interfaceNum] = CY_GET_REG8(mSerial_wValueLo);
    }

    return (requestHandled);
}


/* [] END OF FILE */
