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

#if !defined(CY_USBFS_USB_pvt_H)
#define CY_USBFS_USB_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE USB_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USB_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_USB_EP_SETTINGS_BLOCK CYCODE USB_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE USB_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USB_LUT CYCODE USB_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USB_LUT CYCODE USB_DEVICE0_TABLE[2u];
extern const T_USB_LUT CYCODE USB_TABLE[1u];
extern const uint8 CYCODE USB_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USB_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE USB_MSOS_DESCRIPTOR[USB_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USB_MSOS_CONFIGURATION_DESCR[USB_MSOS_CONF_DESCR_LENGTH];
#if defined(USB_ENABLE_IDSN_STRING)
    extern uint8 USB_idSerialNumberStringDescriptor[USB_IDSN_DESCR_LENGTH];
#endif /* USB_ENABLE_IDSN_STRING */

extern volatile uint8 USB_interfaceNumber;
extern volatile uint8 USB_interfaceSetting[USB_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_interfaceSetting_last[USB_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_deviceAddress;
extern volatile uint8 USB_interfaceStatus[USB_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USB_interfaceClass;

extern volatile T_USB_EP_CTL_BLOCK USB_EP[USB_MAX_EP];
extern volatile T_USB_TD USB_currentTD;

#if(USB_EP_MM != USB__EP_MANUAL)
    extern uint8 USB_DmaChan[USB_MAX_EP];
    extern uint8 USB_DmaTd[USB_MAX_EP];
#endif /*  USB_EP_MM */
#if((USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u))
    extern uint8 USB_DmaNextTd[USB_MAX_EP];
    extern const uint8 USB_epX_TD_TERMOUT_EN[USB_MAX_EP];
    extern volatile uint16 USB_inLength[USB_MAX_EP];
    extern const uint8 *USB_inDataPointer[USB_MAX_EP];
    extern volatile uint8 USB_inBufFull[USB_MAX_EP];
#endif /*  ((USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u)) */

extern volatile uint8 USB_ep0Toggle;
extern volatile uint8 USB_lastPacketSize;
extern volatile uint8 USB_ep0Mode;
extern volatile uint8 USB_ep0Count;
extern volatile uint16 USB_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USB_ReInitComponent(void) ;
void  USB_HandleSetup(void) ;
void  USB_HandleIN(void) ;
void  USB_HandleOUT(void) ;
void  USB_LoadEP0(void) ;
uint8 USB_InitControlRead(void) ;
uint8 USB_InitControlWrite(void) ;
void  USB_ControlReadDataStage(void) ;
void  USB_ControlReadStatusStage(void) ;
void  USB_ControlReadPrematureStatus(void)
                                                ;
uint8 USB_InitControlWrite(void) ;
uint8 USB_InitZeroLengthControlTransfer(void)
                                                ;
void  USB_ControlWriteDataStage(void) ;
void  USB_ControlWriteStatusStage(void) ;
void  USB_ControlWritePrematureStatus(void)
                                                ;
uint8 USB_InitNoDataControlTransfer(void) ;
void  USB_NoDataControlStatusStage(void) ;
void  USB_InitializeStatusBlock(void) ;
void  USB_UpdateStatusBlock(uint8 completionCode) ;
uint8 USB_DispatchClassRqst(void) ;

void USB_Config(uint8 clearAltSetting) ;
void USB_ConfigAltChanged(void) ;
void USB_ConfigReg(void) ;

const T_USB_LUT CYCODE *USB_GetConfigTablePtr(uint8 confIndex)
                                                            ;
const T_USB_LUT CYCODE *USB_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *USB_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 USB_ClearEndpointHalt(void) ;
uint8 USB_SetEndpointHalt(void) ;
uint8 USB_ValidateAlternateSetting(void) ;

void USB_SaveConfig(void) ;
void USB_RestoreConfig(void) ;

#if ((USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u))
    void USB_LoadNextInEP(uint8 epNumber, uint8 mode) ;
#endif /* (USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u) */

#if defined(USB_ENABLE_IDSN_STRING)
    void USB_ReadDieID(uint8 descr[]) ;
#endif /* USB_ENABLE_IDSN_STRING */

#if defined(USB_ENABLE_HID_CLASS)
    uint8 USB_DispatchHIDClassRqst(void);
#endif /*  USB_ENABLE_HID_CLASS */
#if defined(USB_ENABLE_AUDIO_CLASS)
    uint8 USB_DispatchAUDIOClassRqst(void);
#endif /*  USB_ENABLE_HID_CLASS */
#if defined(USB_ENABLE_CDC_CLASS)
    uint8 USB_DispatchCDCClassRqst(void);
#endif /*  USB_ENABLE_CDC_CLASS */

CY_ISR_PROTO(USB_EP_0_ISR);
#if(USB_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_1_ISR);
#endif /*  USB_EP1_ISR_REMOVE */
#if(USB_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_2_ISR);
#endif /*  USB_EP2_ISR_REMOVE */
#if(USB_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_3_ISR);
#endif /*  USB_EP3_ISR_REMOVE */
#if(USB_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_4_ISR);
#endif /*  USB_EP4_ISR_REMOVE */
#if(USB_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_5_ISR);
#endif /*  USB_EP5_ISR_REMOVE */
#if(USB_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_6_ISR);
#endif /*  USB_EP6_ISR_REMOVE */
#if(USB_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_7_ISR);
#endif /*  USB_EP7_ISR_REMOVE */
#if(USB_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_8_ISR);
#endif /*  USB_EP8_ISR_REMOVE */
CY_ISR_PROTO(USB_BUS_RESET_ISR);
#if(USB_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_SOF_ISR);
#endif /*  USB_SOF_ISR_REMOVE */
#if(USB_EP_MM != USB__EP_MANUAL)
    CY_ISR_PROTO(USB_ARB_ISR);
#endif /*  USB_EP_MM */
#if(USB_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_DP_ISR);
#endif /*  USB_DP_ISR_REMOVE */
#if ((USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u))
    CY_ISR_PROTO(USB_EP_DMA_DONE_ISR);
#endif /* (USB_EP_MM == USB__EP_DMAAUTO) && (USB_EP_DMA_AUTO_OPT == 0u) */

/***************************************
* Request Handlers
***************************************/

uint8 USB_HandleStandardRqst(void) ;
uint8 USB_DispatchClassRqst(void) ;
uint8 USB_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USB_ENABLE_HID_CLASS)
    void USB_FindReport(void) ;
    void USB_FindReportDescriptor(void) ;
    void USB_FindHidClassDecriptor(void) ;
#endif /* USB_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USB_ENABLE_MIDI_STREAMING)
    void USB_MIDI_IN_EP_Service(void) ;
#endif /* USB_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_USB_pvt_H */


/* [] END OF FILE */
