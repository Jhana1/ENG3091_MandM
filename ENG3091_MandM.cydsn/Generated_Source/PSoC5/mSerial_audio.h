/*******************************************************************************
* File Name: mSerial_audio.h
* Version 2.80
*
* Description:
*  Header File for the USBFS component. Contains prototypes and constant values.
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

#if !defined(CY_USBFS_mSerial_audio_H)
#define CY_USBFS_mSerial_audio_H

#include "cytypes.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for mSerial_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define mSerial_REQUEST_CODE_UNDEFINED     (0x00u)
#define mSerial_SET_CUR                    (0x01u)
#define mSerial_GET_CUR                    (0x81u)
#define mSerial_SET_MIN                    (0x02u)
#define mSerial_GET_MIN                    (0x82u)
#define mSerial_SET_MAX                    (0x03u)
#define mSerial_GET_MAX                    (0x83u)
#define mSerial_SET_RES                    (0x04u)
#define mSerial_GET_RES                    (0x84u)
#define mSerial_SET_MEM                    (0x05u)
#define mSerial_GET_MEM                    (0x85u)
#define mSerial_GET_STAT                   (0xFFu)

/* point Control Selectors (AUDIO Table A-19) */
#define mSerial_EP_CONTROL_UNDEFINED       (0x00u)
#define mSerial_SAMPLING_FREQ_CONTROL      (0x01u)
#define mSerial_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define mSerial_FU_CONTROL_UNDEFINED       (0x00u)
#define mSerial_MUTE_CONTROL               (0x01u)
#define mSerial_VOLUME_CONTROL             (0x02u)
#define mSerial_BASS_CONTROL               (0x03u)
#define mSerial_MID_CONTROL                (0x04u)
#define mSerial_TREBLE_CONTROL             (0x05u)
#define mSerial_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define mSerial_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define mSerial_DELAY_CONTROL              (0x08u)
#define mSerial_BASS_BOOST_CONTROL         (0x09u)
#define mSerial_LOUDNESS_CONTROL           (0x0Au)

#define mSerial_SAMPLE_FREQ_LEN            (3u)
#define mSerial_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define mSerial_VOL_MIN_MSB            (0x80u)
    #define mSerial_VOL_MIN_LSB            (0x01u)
    #define mSerial_VOL_MAX_MSB            (0x7Fu)
    #define mSerial_VOL_MAX_LSB            (0xFFu)
    #define mSerial_VOL_RES_MSB            (0x00u)
    #define mSerial_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/

extern volatile uint8 mSerial_currentSampleFrequency[mSerial_MAX_EP]
                                                             [mSerial_SAMPLE_FREQ_LEN];
extern volatile uint8 mSerial_frequencyChanged;
extern volatile uint8 mSerial_currentMute;
extern volatile uint8 mSerial_currentVolume[mSerial_VOLUME_LEN];
extern volatile uint8 mSerial_minimumVolume[mSerial_VOLUME_LEN];
extern volatile uint8 mSerial_maximumVolume[mSerial_VOLUME_LEN];
extern volatile uint8 mSerial_resolutionVolume[mSerial_VOLUME_LEN];

#endif /*  CY_USBFS_mSerial_audio_H */


/* [] END OF FILE */
