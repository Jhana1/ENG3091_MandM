/*******************************************************************************
* File Name: USB_audio.c
* Version 2.80
*
* Description:
*  USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB.h"

#if defined(USB_ENABLE_AUDIO_CLASS)

#include "USB_audio.h"
#include "USB_pvt.h"
#if defined(USB_ENABLE_MIDI_STREAMING)
    #include "USB_midi.h"
#endif /*  USB_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(USB_ENABLE_AUDIO_STREAMING)
    volatile uint8 USB_currentSampleFrequency[USB_MAX_EP][USB_SAMPLE_FREQ_LEN];
    volatile uint8 USB_frequencyChanged;
    volatile uint8 USB_currentMute;
    volatile uint8 USB_currentVolume[USB_VOLUME_LEN];
    volatile uint8 USB_minimumVolume[USB_VOLUME_LEN] = {USB_VOL_MIN_LSB,
                                                                                  USB_VOL_MIN_MSB};
    volatile uint8 USB_maximumVolume[USB_VOLUME_LEN] = {USB_VOL_MAX_LSB,
                                                                                  USB_VOL_MAX_MSB};
    volatile uint8 USB_resolutionVolume[USB_VOLUME_LEN] = {USB_VOL_RES_LSB,
                                                                                     USB_VOL_RES_MSB};
#endif /*  USB_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: USB_DispatchAUDIOClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches class requests
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   USB_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   USB_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((USB_frequencyChanged != 0) &&
*       (USB_transferState == USB_TRANS_STATE_IDLE))
*       {
*          USB_frequencyChanged = 0;
*       }
*       USB_transferState variable is checked to be sure that
*             transfer completes.
*   USB_currentMute: Contains mute configuration set by Host.
*   USB_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = USB_FALSE;
    uint8 bmRequestType  = CY_GET_REG8(USB_bmRequestType);

    #if defined(USB_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber = CY_GET_REG8(USB_wIndexLo) & USB_DIR_UNUSED;
    #endif /*  USB_ENABLE_AUDIO_STREAMING */


    if ((bmRequestType & USB_RQST_DIR_MASK) == USB_RQST_DIR_D2H)
    {
        /* Control Read */
        if((bmRequestType & USB_RQST_RCPT_MASK) == USB_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(USB_bRequest))
            {
                case USB_GET_CUR:
                #if defined(USB_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_wValueHi) == USB_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB_currentTD.wCount = USB_SAMPLE_FREQ_LEN;
                        USB_currentTD.pData  = USB_currentSampleFrequency[epNumber];
                        requestHandled   = USB_InitControlRead();
                    }
                #endif /*  USB_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & USB_RQST_RCPT_MASK) == USB_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB_bRequest))
            {
                case USB_GET_CUR:
                #if defined(USB_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_wValueHi) == USB_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                         /* Entity ID Control Selector is MUTE */
                        USB_currentTD.wCount = 1u;
                        USB_currentTD.pData  = &USB_currentMute;
                        requestHandled   = USB_InitControlRead();
                    }
                    else if(CY_GET_REG8(USB_wValueHi) == USB_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME, */
                        USB_currentTD.wCount = USB_VOLUME_LEN;
                        USB_currentTD.pData  = USB_currentVolume;
                        requestHandled   = USB_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                    break;
                case USB_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(USB_wValueHi) == USB_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_currentTD.wCount = USB_VOLUME_LEN;
                        USB_currentTD.pData  = &USB_minimumVolume[0];
                        requestHandled   = USB_InitControlRead();
                    }
                    break;
                case USB_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(USB_wValueHi) == USB_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_currentTD.wCount = USB_VOLUME_LEN;
                        USB_currentTD.pData  = &USB_maximumVolume[0];
                        requestHandled   = USB_InitControlRead();
                    }
                    break;
                case USB_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(USB_wValueHi) == USB_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        USB_currentTD.wCount = USB_VOLUME_LEN;
                        USB_currentTD.pData  = &USB_resolutionVolume[0];
                        requestHandled   = USB_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case USB_GET_STAT:
                        USB_currentTD.wCount = 0u;
                        requestHandled   = USB_InitControlWrite();

                #endif /*  USB_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* USB_RQST_RCPT_OTHER */
        }
    }
    else
    {
        /* Control Write */
        if((bmRequestType & USB_RQST_RCPT_MASK) == USB_RQST_RCPT_EP)
        {
            /* point */
            switch (CY_GET_REG8(USB_bRequest))
            {
                case USB_SET_CUR:
                #if defined(USB_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_wValueHi) == USB_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB_currentTD.wCount = USB_SAMPLE_FREQ_LEN;
                        USB_currentTD.pData  = USB_currentSampleFrequency[epNumber];
                        requestHandled   = USB_InitControlWrite();
                        USB_frequencyChanged = epNumber;
                    }
                #endif /*  USB_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & USB_RQST_RCPT_MASK) == USB_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB_bRequest))
            {
                case USB_SET_CUR:
                #if defined(USB_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB_wValueHi) == USB_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is MUTE */
                        USB_currentTD.wCount = 1u;
                        USB_currentTD.pData  = &USB_currentMute;
                        requestHandled   = USB_InitControlWrite();
                    }
                    else if(CY_GET_REG8(USB_wValueHi) == USB_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME */
                        USB_currentTD.wCount = USB_VOLUME_LEN;
                        USB_currentTD.pData  = USB_currentVolume;
                        requestHandled   = USB_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                #endif /*  USB_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {
            /* USB_RQST_RCPT_OTHER */
        }
    }

    return(requestHandled);
}

#endif /* USER_SUPPLIED_AUDIO_HANDLER */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  USB_ENABLE_AUDIO_CLASS */


/* [] END OF FILE */
