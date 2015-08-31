/*******************************************************************************
* File Name: mSerial_audio.c
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

#include "mSerial.h"

#if defined(mSerial_ENABLE_AUDIO_CLASS)

#include "mSerial_audio.h"
#include "mSerial_pvt.h"
#if defined(mSerial_ENABLE_MIDI_STREAMING)
    #include "mSerial_midi.h"
#endif /*  mSerial_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(mSerial_ENABLE_AUDIO_STREAMING)
    volatile uint8 mSerial_currentSampleFrequency[mSerial_MAX_EP][mSerial_SAMPLE_FREQ_LEN];
    volatile uint8 mSerial_frequencyChanged;
    volatile uint8 mSerial_currentMute;
    volatile uint8 mSerial_currentVolume[mSerial_VOLUME_LEN];
    volatile uint8 mSerial_minimumVolume[mSerial_VOLUME_LEN] = {mSerial_VOL_MIN_LSB,
                                                                                  mSerial_VOL_MIN_MSB};
    volatile uint8 mSerial_maximumVolume[mSerial_VOLUME_LEN] = {mSerial_VOL_MAX_LSB,
                                                                                  mSerial_VOL_MAX_MSB};
    volatile uint8 mSerial_resolutionVolume[mSerial_VOLUME_LEN] = {mSerial_VOL_RES_LSB,
                                                                                     mSerial_VOL_RES_MSB};
#endif /*  mSerial_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: mSerial_DispatchAUDIOClassRqst
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
*   mSerial_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   mSerial_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((mSerial_frequencyChanged != 0) &&
*       (mSerial_transferState == mSerial_TRANS_STATE_IDLE))
*       {
*          mSerial_frequencyChanged = 0;
*       }
*       mSerial_transferState variable is checked to be sure that
*             transfer completes.
*   mSerial_currentMute: Contains mute configuration set by Host.
*   mSerial_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = mSerial_FALSE;
    uint8 bmRequestType  = CY_GET_REG8(mSerial_bmRequestType);

    #if defined(mSerial_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber = CY_GET_REG8(mSerial_wIndexLo) & mSerial_DIR_UNUSED;
    #endif /*  mSerial_ENABLE_AUDIO_STREAMING */


    if ((bmRequestType & mSerial_RQST_DIR_MASK) == mSerial_RQST_DIR_D2H)
    {
        /* Control Read */
        if((bmRequestType & mSerial_RQST_RCPT_MASK) == mSerial_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(mSerial_bRequest))
            {
                case mSerial_GET_CUR:
                #if defined(mSerial_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        mSerial_currentTD.wCount = mSerial_SAMPLE_FREQ_LEN;
                        mSerial_currentTD.pData  = mSerial_currentSampleFrequency[epNumber];
                        requestHandled   = mSerial_InitControlRead();
                    }
                #endif /*  mSerial_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & mSerial_RQST_RCPT_MASK) == mSerial_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(mSerial_bRequest))
            {
                case mSerial_GET_CUR:
                #if defined(mSerial_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                         /* Entity ID Control Selector is MUTE */
                        mSerial_currentTD.wCount = 1u;
                        mSerial_currentTD.pData  = &mSerial_currentMute;
                        requestHandled   = mSerial_InitControlRead();
                    }
                    else if(CY_GET_REG8(mSerial_wValueHi) == mSerial_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME, */
                        mSerial_currentTD.wCount = mSerial_VOLUME_LEN;
                        mSerial_currentTD.pData  = mSerial_currentVolume;
                        requestHandled   = mSerial_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                    break;
                case mSerial_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        mSerial_currentTD.wCount = mSerial_VOLUME_LEN;
                        mSerial_currentTD.pData  = &mSerial_minimumVolume[0];
                        requestHandled   = mSerial_InitControlRead();
                    }
                    break;
                case mSerial_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        mSerial_currentTD.wCount = mSerial_VOLUME_LEN;
                        mSerial_currentTD.pData  = &mSerial_maximumVolume[0];
                        requestHandled   = mSerial_InitControlRead();
                    }
                    break;
                case mSerial_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        mSerial_currentTD.wCount = mSerial_VOLUME_LEN;
                        mSerial_currentTD.pData  = &mSerial_resolutionVolume[0];
                        requestHandled   = mSerial_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case mSerial_GET_STAT:
                        mSerial_currentTD.wCount = 0u;
                        requestHandled   = mSerial_InitControlWrite();

                #endif /*  mSerial_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* mSerial_RQST_RCPT_OTHER */
        }
    }
    else
    {
        /* Control Write */
        if((bmRequestType & mSerial_RQST_RCPT_MASK) == mSerial_RQST_RCPT_EP)
        {
            /* point */
            switch (CY_GET_REG8(mSerial_bRequest))
            {
                case mSerial_SET_CUR:
                #if defined(mSerial_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        mSerial_currentTD.wCount = mSerial_SAMPLE_FREQ_LEN;
                        mSerial_currentTD.pData  = mSerial_currentSampleFrequency[epNumber];
                        requestHandled   = mSerial_InitControlWrite();
                        mSerial_frequencyChanged = epNumber;
                    }
                #endif /*  mSerial_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & mSerial_RQST_RCPT_MASK) == mSerial_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(mSerial_bRequest))
            {
                case mSerial_SET_CUR:
                #if defined(mSerial_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(mSerial_wValueHi) == mSerial_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is MUTE */
                        mSerial_currentTD.wCount = 1u;
                        mSerial_currentTD.pData  = &mSerial_currentMute;
                        requestHandled   = mSerial_InitControlWrite();
                    }
                    else if(CY_GET_REG8(mSerial_wValueHi) == mSerial_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME */
                        mSerial_currentTD.wCount = mSerial_VOLUME_LEN;
                        mSerial_currentTD.pData  = mSerial_currentVolume;
                        requestHandled   = mSerial_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                #endif /*  mSerial_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {
            /* mSerial_RQST_RCPT_OTHER */
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

#endif  /*  mSerial_ENABLE_AUDIO_CLASS */


/* [] END OF FILE */
