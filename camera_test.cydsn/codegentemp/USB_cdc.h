/*******************************************************************************
* File Name: USB_cdc.h
* Version 2.80
*
* Description:
*  Header File for the USBFS component.
*  Contains CDC class prototypes and constant values.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB_cdc_H)
#define CY_USBFS_USB_cdc_H

#include "cytypes.h"


/***************************************
* Prototypes of the USB_cdc API.
***************************************/

#if (USB_ENABLE_CDC_CLASS_API != 0u)
    void USB_CDC_Init(void) ;
    void USB_PutData(const uint8* pData, uint16 length) ;
    void USB_PutString(const char8 string[]) ;
    void USB_PutChar(char8 txDataByte) ;
    void USB_PutCRLF(void) ;
    uint16 USB_GetCount(void) ;
    uint8 USB_CDCIsReady(void) ;
    uint8 USB_DataIsReady(void) ;
    uint16 USB_GetData(uint8* pData, uint16 length) ;
    uint16 USB_GetAll(uint8* pData) ;
    uint8 USB_GetChar(void) ;
    uint8 USB_IsLineChanged(void) ;
    uint32 USB_GetDTERate(void) ;
    uint8 USB_GetCharFormat(void) ;
    uint8 USB_GetParityType(void) ;
    uint8 USB_GetDataBits(void) ;
    uint16 USB_GetLineControl(void) ;
#endif  /*  USB_ENABLE_CDC_CLASS_API */


/***************************************
*  Constants for USB_cdc API.
***************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define USB_CDC_SET_LINE_CODING        (0x20u)
#define USB_CDC_GET_LINE_CODING        (0x21u)
#define USB_CDC_SET_CONTROL_LINE_STATE (0x22u)

#define USB_LINE_CODING_CHANGED        (0x01u)
#define USB_LINE_CONTROL_CHANGED       (0x02u)

#define USB_1_STOPBIT                  (0x00u)
#define USB_1_5_STOPBITS               (0x01u)
#define USB_2_STOPBITS                 (0x02u)

#define USB_PARITY_NONE                (0x00u)
#define USB_PARITY_ODD                 (0x01u)
#define USB_PARITY_EVEN                (0x02u)
#define USB_PARITY_MARK                (0x03u)
#define USB_PARITY_SPACE               (0x04u)

#define USB_LINE_CODING_SIZE           (0x07u)
#define USB_LINE_CODING_RATE           (0x00u)
#define USB_LINE_CODING_STOP_BITS      (0x04u)
#define USB_LINE_CODING_PARITY         (0x05u)
#define USB_LINE_CODING_DATA_BITS      (0x06u)

#define USB_LINE_CONTROL_DTR           (0x01u)
#define USB_LINE_CONTROL_RTS           (0x02u)


/***************************************
* External data references
***************************************/

extern volatile uint8 USB_lineCoding[USB_LINE_CODING_SIZE];
extern volatile uint8 USB_lineChanged;
extern volatile uint16 USB_lineControlBitmap;
extern volatile uint8 USB_cdc_data_in_ep;
extern volatile uint8 USB_cdc_data_out_ep;

#endif /*  CY_USBFS_USB_cdc_H */


/* [] END OF FILE */
