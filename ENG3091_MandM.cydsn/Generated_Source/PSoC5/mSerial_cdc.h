/*******************************************************************************
* File Name: mSerial_cdc.h
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

#if !defined(CY_USBFS_mSerial_cdc_H)
#define CY_USBFS_mSerial_cdc_H

#include "cytypes.h"


/***************************************
* Prototypes of the mSerial_cdc API.
***************************************/

#if (mSerial_ENABLE_CDC_CLASS_API != 0u)
    void mSerial_CDC_Init(void) ;
    void mSerial_PutData(const uint8* pData, uint16 length) ;
    void mSerial_PutString(const char8 string[]) ;
    void mSerial_PutChar(char8 txDataByte) ;
    void mSerial_PutCRLF(void) ;
    uint16 mSerial_GetCount(void) ;
    uint8 mSerial_CDCIsReady(void) ;
    uint8 mSerial_DataIsReady(void) ;
    uint16 mSerial_GetData(uint8* pData, uint16 length) ;
    uint16 mSerial_GetAll(uint8* pData) ;
    uint8 mSerial_GetChar(void) ;
    uint8 mSerial_IsLineChanged(void) ;
    uint32 mSerial_GetDTERate(void) ;
    uint8 mSerial_GetCharFormat(void) ;
    uint8 mSerial_GetParityType(void) ;
    uint8 mSerial_GetDataBits(void) ;
    uint16 mSerial_GetLineControl(void) ;
#endif  /*  mSerial_ENABLE_CDC_CLASS_API */


/***************************************
*  Constants for mSerial_cdc API.
***************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define mSerial_CDC_SET_LINE_CODING        (0x20u)
#define mSerial_CDC_GET_LINE_CODING        (0x21u)
#define mSerial_CDC_SET_CONTROL_LINE_STATE (0x22u)

#define mSerial_LINE_CODING_CHANGED        (0x01u)
#define mSerial_LINE_CONTROL_CHANGED       (0x02u)

#define mSerial_1_STOPBIT                  (0x00u)
#define mSerial_1_5_STOPBITS               (0x01u)
#define mSerial_2_STOPBITS                 (0x02u)

#define mSerial_PARITY_NONE                (0x00u)
#define mSerial_PARITY_ODD                 (0x01u)
#define mSerial_PARITY_EVEN                (0x02u)
#define mSerial_PARITY_MARK                (0x03u)
#define mSerial_PARITY_SPACE               (0x04u)

#define mSerial_LINE_CODING_SIZE           (0x07u)
#define mSerial_LINE_CODING_RATE           (0x00u)
#define mSerial_LINE_CODING_STOP_BITS      (0x04u)
#define mSerial_LINE_CODING_PARITY         (0x05u)
#define mSerial_LINE_CODING_DATA_BITS      (0x06u)

#define mSerial_LINE_CONTROL_DTR           (0x01u)
#define mSerial_LINE_CONTROL_RTS           (0x02u)


/***************************************
* External data references
***************************************/

extern volatile uint8 mSerial_lineCoding[mSerial_LINE_CODING_SIZE];
extern volatile uint8 mSerial_lineChanged;
extern volatile uint16 mSerial_lineControlBitmap;
extern volatile uint8 mSerial_cdc_data_in_ep;
extern volatile uint8 mSerial_cdc_data_out_ep;

#endif /*  CY_USBFS_mSerial_cdc_H */


/* [] END OF FILE */
