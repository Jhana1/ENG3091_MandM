/*******************************************************************************
* File Name: .h
* Version 2.80
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_mSerial_pvt_H)
#define CY_USBFS_mSerial_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE mSerial_DEVICE0_DESCR[18u];
extern const uint8 CYCODE mSerial_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_mSerial_EP_SETTINGS_BLOCK CYCODE mSerial_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE mSerial_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_mSerial_LUT CYCODE mSerial_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_mSerial_LUT CYCODE mSerial_DEVICE0_TABLE[2u];
extern const T_mSerial_LUT CYCODE mSerial_TABLE[1u];
extern const uint8 CYCODE mSerial_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE mSerial_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE mSerial_MSOS_DESCRIPTOR[mSerial_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE mSerial_MSOS_CONFIGURATION_DESCR[mSerial_MSOS_CONF_DESCR_LENGTH];
#if defined(mSerial_ENABLE_IDSN_STRING)
    extern uint8 mSerial_idSerialNumberStringDescriptor[mSerial_IDSN_DESCR_LENGTH];
#endif /* mSerial_ENABLE_IDSN_STRING */

extern volatile uint8 mSerial_interfaceNumber;
extern volatile uint8 mSerial_interfaceSetting[mSerial_MAX_INTERFACES_NUMBER];
extern volatile uint8 mSerial_interfaceSetting_last[mSerial_MAX_INTERFACES_NUMBER];
extern volatile uint8 mSerial_deviceAddress;
extern volatile uint8 mSerial_interfaceStatus[mSerial_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *mSerial_interfaceClass;

extern volatile T_mSerial_EP_CTL_BLOCK mSerial_EP[mSerial_MAX_EP];
extern volatile T_mSerial_TD mSerial_currentTD;

#if(mSerial_EP_MM != mSerial__EP_MANUAL)
    extern uint8 mSerial_DmaChan[mSerial_MAX_EP];
    extern uint8 mSerial_DmaTd[mSerial_MAX_EP];
#endif /*  mSerial_EP_MM */
#if((mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u))
    extern uint8 mSerial_DmaNextTd[mSerial_MAX_EP];
    extern const uint8 mSerial_epX_TD_TERMOUT_EN[mSerial_MAX_EP];
    extern volatile uint16 mSerial_inLength[mSerial_MAX_EP];
    extern const uint8 *mSerial_inDataPointer[mSerial_MAX_EP];
    extern volatile uint8 mSerial_inBufFull[mSerial_MAX_EP];
#endif /*  ((mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u)) */

extern volatile uint8 mSerial_ep0Toggle;
extern volatile uint8 mSerial_lastPacketSize;
extern volatile uint8 mSerial_ep0Mode;
extern volatile uint8 mSerial_ep0Count;
extern volatile uint16 mSerial_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  mSerial_ReInitComponent(void) ;
void  mSerial_HandleSetup(void) ;
void  mSerial_HandleIN(void) ;
void  mSerial_HandleOUT(void) ;
void  mSerial_LoadEP0(void) ;
uint8 mSerial_InitControlRead(void) ;
uint8 mSerial_InitControlWrite(void) ;
void  mSerial_ControlReadDataStage(void) ;
void  mSerial_ControlReadStatusStage(void) ;
void  mSerial_ControlReadPrematureStatus(void)
                                                ;
uint8 mSerial_InitControlWrite(void) ;
uint8 mSerial_InitZeroLengthControlTransfer(void)
                                                ;
void  mSerial_ControlWriteDataStage(void) ;
void  mSerial_ControlWriteStatusStage(void) ;
void  mSerial_ControlWritePrematureStatus(void)
                                                ;
uint8 mSerial_InitNoDataControlTransfer(void) ;
void  mSerial_NoDataControlStatusStage(void) ;
void  mSerial_InitializeStatusBlock(void) ;
void  mSerial_UpdateStatusBlock(uint8 completionCode) ;
uint8 mSerial_DispatchClassRqst(void) ;

void mSerial_Config(uint8 clearAltSetting) ;
void mSerial_ConfigAltChanged(void) ;
void mSerial_ConfigReg(void) ;

const T_mSerial_LUT CYCODE *mSerial_GetConfigTablePtr(uint8 confIndex)
                                                            ;
const T_mSerial_LUT CYCODE *mSerial_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *mSerial_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 mSerial_ClearEndpointHalt(void) ;
uint8 mSerial_SetEndpointHalt(void) ;
uint8 mSerial_ValidateAlternateSetting(void) ;

void mSerial_SaveConfig(void) ;
void mSerial_RestoreConfig(void) ;

#if ((mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u))
    void mSerial_LoadNextInEP(uint8 epNumber, uint8 mode) ;
#endif /* (mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u) */

#if defined(mSerial_ENABLE_IDSN_STRING)
    void mSerial_ReadDieID(uint8 descr[]) ;
#endif /* mSerial_ENABLE_IDSN_STRING */

#if defined(mSerial_ENABLE_HID_CLASS)
    uint8 mSerial_DispatchHIDClassRqst(void);
#endif /*  mSerial_ENABLE_HID_CLASS */
#if defined(mSerial_ENABLE_AUDIO_CLASS)
    uint8 mSerial_DispatchAUDIOClassRqst(void);
#endif /*  mSerial_ENABLE_HID_CLASS */
#if defined(mSerial_ENABLE_CDC_CLASS)
    uint8 mSerial_DispatchCDCClassRqst(void);
#endif /*  mSerial_ENABLE_CDC_CLASS */

CY_ISR_PROTO(mSerial_EP_0_ISR);
#if(mSerial_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_1_ISR);
#endif /*  mSerial_EP1_ISR_REMOVE */
#if(mSerial_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_2_ISR);
#endif /*  mSerial_EP2_ISR_REMOVE */
#if(mSerial_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_3_ISR);
#endif /*  mSerial_EP3_ISR_REMOVE */
#if(mSerial_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_4_ISR);
#endif /*  mSerial_EP4_ISR_REMOVE */
#if(mSerial_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_5_ISR);
#endif /*  mSerial_EP5_ISR_REMOVE */
#if(mSerial_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_6_ISR);
#endif /*  mSerial_EP6_ISR_REMOVE */
#if(mSerial_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_7_ISR);
#endif /*  mSerial_EP7_ISR_REMOVE */
#if(mSerial_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_EP_8_ISR);
#endif /*  mSerial_EP8_ISR_REMOVE */
CY_ISR_PROTO(mSerial_BUS_RESET_ISR);
#if(mSerial_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_SOF_ISR);
#endif /*  mSerial_SOF_ISR_REMOVE */
#if(mSerial_EP_MM != mSerial__EP_MANUAL)
    CY_ISR_PROTO(mSerial_ARB_ISR);
#endif /*  mSerial_EP_MM */
#if(mSerial_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(mSerial_DP_ISR);
#endif /*  mSerial_DP_ISR_REMOVE */
#if ((mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u))
    CY_ISR_PROTO(mSerial_EP_DMA_DONE_ISR);
#endif /* (mSerial_EP_MM == mSerial__EP_DMAAUTO) && (mSerial_EP_DMA_AUTO_OPT == 0u) */

/***************************************
* Request Handlers
***************************************/

uint8 mSerial_HandleStandardRqst(void) ;
uint8 mSerial_DispatchClassRqst(void) ;
uint8 mSerial_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/

#if defined(mSerial_ENABLE_HID_CLASS)
    void mSerial_FindReport(void) ;
    void mSerial_FindReportDescriptor(void) ;
    void mSerial_FindHidClassDecriptor(void) ;
#endif /* mSerial_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(mSerial_ENABLE_MIDI_STREAMING)
    void mSerial_MIDI_IN_EP_Service(void) ;
#endif /* mSerial_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_mSerial_pvt_H */


/* [] END OF FILE */
