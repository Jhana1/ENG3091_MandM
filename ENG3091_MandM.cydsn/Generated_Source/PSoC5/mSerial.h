/*******************************************************************************
* File Name: mSerial.h
* Version 2.80
*
* Description:
*  Header File for the USBFS component. Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_mSerial_H)
#define CY_USBFS_mSerial_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component USBFS_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*  Memory Type Definitions
***************************************/

/* Renamed Type Definitions for backward compatibility.
*  Should not be used in new designs.
*/
#define mSerial_CODE CYCODE
#define mSerial_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define mSerial_DATA data
    #define mSerial_XDATA xdata
#else
    #define mSerial_DATA
    #define mSerial_XDATA
#endif /*  __C51__ */
#define mSerial_NULL       NULL


/***************************************
* Enumerated Types and Parameters
***************************************/

#define mSerial__EP_MANUAL 0
#define mSerial__EP_DMAMANUAL 1
#define mSerial__EP_DMAAUTO 2

#define mSerial__MA_STATIC 0
#define mSerial__MA_DYNAMIC 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define mSerial_NUM_DEVICES   (1u)
#define mSerial_ENABLE_CDC_CLASS   
#define mSerial_ENABLE_DESCRIPTOR_STRINGS   
#define mSerial_ENABLE_MSOS_STRING   
#define mSerial_ENABLE_SN_STRING   
#define mSerial_ENABLE_IDSN_STRING   
#define mSerial_ENABLE_STRINGS   
#define mSerial_MAX_REPORTID_NUMBER   (0u)

#define mSerial_MON_VBUS                       (0u)
#define mSerial_EXTERN_VBUS                    (0u)
#define mSerial_EXTERN_VND                     (0u)
#define mSerial_EXTERN_CLS                     (0u)
#define mSerial_MAX_INTERFACES_NUMBER          (2u)
#define mSerial_EP0_ISR_REMOVE                 (0u)
#define mSerial_EP1_ISR_REMOVE                 (0u)
#define mSerial_EP2_ISR_REMOVE                 (0u)
#define mSerial_EP3_ISR_REMOVE                 (0u)
#define mSerial_EP4_ISR_REMOVE                 (1u)
#define mSerial_EP5_ISR_REMOVE                 (1u)
#define mSerial_EP6_ISR_REMOVE                 (1u)
#define mSerial_EP7_ISR_REMOVE                 (1u)
#define mSerial_EP8_ISR_REMOVE                 (1u)
#define mSerial_EP_MM                          (0u)
#define mSerial_EP_MA                          (0u)
#define mSerial_EP_DMA_AUTO_OPT                (0u)
#define mSerial_DMA1_REMOVE                    (1u)
#define mSerial_DMA2_REMOVE                    (1u)
#define mSerial_DMA3_REMOVE                    (1u)
#define mSerial_DMA4_REMOVE                    (1u)
#define mSerial_DMA5_REMOVE                    (1u)
#define mSerial_DMA6_REMOVE                    (1u)
#define mSerial_DMA7_REMOVE                    (1u)
#define mSerial_DMA8_REMOVE                    (1u)
#define mSerial_SOF_ISR_REMOVE                 (0u)
#define mSerial_ARB_ISR_REMOVE                 (0u)
#define mSerial_DP_ISR_REMOVE                  (0u)
#define mSerial_ENABLE_CDC_CLASS_API           (1u)
#define mSerial_ENABLE_MIDI_API                (1u)
#define mSerial_MIDI_EXT_MODE                  (0u)


/***************************************
*    Data Struct Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_mSerial_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_mSerial_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_mSerial_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_mSerial_XFER_STATUS_BLOCK *pStatusBlock;
} T_mSerial_TD;


typedef struct
{
    uint8   c;
    const void *p_list;
} T_mSerial_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
} mSerial_BACKUP_STRUCT;


/* Renamed structure fields for backward compatibility.
*  Should not be used in new designs.
*/
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable for backward compatibility.
*  Should not be used in new designs.
*/
#define CurrentTD           mSerial_currentTD


/***************************************
*       Function Prototypes
***************************************/

void   mSerial_Start(uint8 device, uint8 mode) ;
void   mSerial_Init(void) ;
void   mSerial_InitComponent(uint8 device, uint8 mode) ;
void   mSerial_Stop(void) ;
uint8  mSerial_CheckActivity(void) ;
uint8  mSerial_GetConfiguration(void) ;
uint8  mSerial_IsConfigurationChanged(void) ;
uint8  mSerial_GetInterfaceSetting(uint8 interfaceNumber)
                                                        ;
uint8  mSerial_GetEPState(uint8 epNumber) ;
uint16 mSerial_GetEPCount(uint8 epNumber) ;
void   mSerial_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                    ;
uint16 mSerial_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                    ;
void   mSerial_EnableOutEP(uint8 epNumber) ;
void   mSerial_DisableOutEP(uint8 epNumber) ;
void   mSerial_Force(uint8 bState) ;
uint8  mSerial_GetEPAckState(uint8 epNumber) ;
void   mSerial_SetPowerStatus(uint8 powerStatus) ;
uint8  mSerial_RWUEnabled(void) ;
void   mSerial_TerminateEP(uint8 ep) ;

void   mSerial_Suspend(void) ;
void   mSerial_Resume(void) ;

#if defined(mSerial_ENABLE_FWSN_STRING)
    void   mSerial_SerialNumString(uint8 snString[]) ;
#endif  /* mSerial_ENABLE_FWSN_STRING */
#if (mSerial_MON_VBUS == 1u)
    uint8  mSerial_VBusPresent(void) ;
#endif /*  mSerial_MON_VBUS */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_mSerial) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

    void mSerial_CyBtldrCommStart(void) ;
    void mSerial_CyBtldrCommStop(void) ;
    void mSerial_CyBtldrCommReset(void) ;
    cystatus mSerial_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
    cystatus mSerial_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;

    #define mSerial_BTLDR_OUT_EP      (0x01u)
    #define mSerial_BTLDR_IN_EP       (0x02u)

    #define mSerial_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* EP 1 OUT */
    #define mSerial_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* EP 2 IN  */
    #define mSerial_BTLDR_MAX_PACKET_SIZE      mSerial_BTLDR_SIZEOF_WRITE_BUFFER

    #define mSerial_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* These defines active if used USBFS interface as an
    *  IO Component for bootloading. When Custom_Interface selected
    *  in Bootloder configuration as the IO Component, user must
    *  provide these functions.
    */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_mSerial)
        #define CyBtldrCommStart        mSerial_CyBtldrCommStart
        #define CyBtldrCommStop         mSerial_CyBtldrCommStop
        #define CyBtldrCommReset        mSerial_CyBtldrCommReset
        #define CyBtldrCommWrite        mSerial_CyBtldrCommWrite
        #define CyBtldrCommRead         mSerial_CyBtldrCommRead
    #endif  /*End   CYDEV_BOOTLOADER_IO_COMP == CyBtldr_mSerial */

#endif /*  CYDEV_BOOTLOADER_IO_COMP  */

#if(mSerial_EP_MM != mSerial__EP_MANUAL)
    void mSerial_InitEP_DMA(uint8 epNumber, const uint8* pData)
                                                    ;
    void mSerial_Stop_DMA(uint8 epNumber) ;
#endif /*  mSerial_EP_MM != mSerial__EP_MANUAL) */

#if defined(mSerial_ENABLE_MIDI_STREAMING) && (mSerial_ENABLE_MIDI_API != 0u)
    void mSerial_MIDI_EP_Init(void) ;

    #if (mSerial_MIDI_IN_BUFF_SIZE > 0)
        void mSerial_MIDI_IN_Service(void) ;
        uint8 mSerial_PutUsbMidiIn(uint8 ic, const uint8 midiMsg[], uint8 cable)
                                                                ;
    #endif /* mSerial_MIDI_IN_BUFF_SIZE > 0 */

    #if (mSerial_MIDI_OUT_BUFF_SIZE > 0)
        void mSerial_MIDI_OUT_EP_Service(void) ;
    #endif /* mSerial_MIDI_OUT_BUFF_SIZE > 0 */

#endif /*  mSerial_ENABLE_MIDI_API != 0u */

/* Renamed Functions for backward compatibility.
*  Should not be used in new designs.
*/

#define mSerial_bCheckActivity             mSerial_CheckActivity
#define mSerial_bGetConfiguration          mSerial_GetConfiguration
#define mSerial_bGetInterfaceSetting       mSerial_GetInterfaceSetting
#define mSerial_bGetEPState                mSerial_GetEPState
#define mSerial_wGetEPCount                mSerial_GetEPCount
#define mSerial_bGetEPAckState             mSerial_GetEPAckState
#define mSerial_bRWUEnabled                mSerial_RWUEnabled
#define mSerial_bVBusPresent               mSerial_VBusPresent

#define mSerial_bConfiguration             mSerial_configuration
#define mSerial_bInterfaceSetting          mSerial_interfaceSetting
#define mSerial_bDeviceAddress             mSerial_deviceAddress
#define mSerial_bDeviceStatus              mSerial_deviceStatus
#define mSerial_bDevice                    mSerial_device
#define mSerial_bTransferState             mSerial_transferState
#define mSerial_bLastPacketSize            mSerial_lastPacketSize

#define mSerial_LoadEP                     mSerial_LoadInEP
#define mSerial_LoadInISOCEP               mSerial_LoadInEP
#define mSerial_EnableOutISOCEP            mSerial_EnableOutEP

#define mSerial_SetVector                  CyIntSetVector
#define mSerial_SetPriority                CyIntSetPriority
#define mSerial_EnableInt                  CyIntEnable


/***************************************
*          API Constants
***************************************/

#define mSerial_EP0                        (0u)
#define mSerial_EP1                        (1u)
#define mSerial_EP2                        (2u)
#define mSerial_EP3                        (3u)
#define mSerial_EP4                        (4u)
#define mSerial_EP5                        (5u)
#define mSerial_EP6                        (6u)
#define mSerial_EP7                        (7u)
#define mSerial_EP8                        (8u)
#define mSerial_MAX_EP                     (9u)

#define mSerial_TRUE                       (1u)
#define mSerial_FALSE                      (0u)

#define mSerial_NO_EVENT_ALLOWED           (2u)
#define mSerial_EVENT_PENDING              (1u)
#define mSerial_NO_EVENT_PENDING           (0u)

#define mSerial_IN_BUFFER_FULL             mSerial_NO_EVENT_PENDING
#define mSerial_IN_BUFFER_EMPTY            mSerial_EVENT_PENDING
#define mSerial_OUT_BUFFER_FULL            mSerial_EVENT_PENDING
#define mSerial_OUT_BUFFER_EMPTY           mSerial_NO_EVENT_PENDING

#define mSerial_FORCE_J                    (0xA0u)
#define mSerial_FORCE_K                    (0x80u)
#define mSerial_FORCE_SE0                  (0xC0u)
#define mSerial_FORCE_NONE                 (0x00u)

#define mSerial_IDLE_TIMER_RUNNING         (0x02u)
#define mSerial_IDLE_TIMER_EXPIRED         (0x01u)
#define mSerial_IDLE_TIMER_INDEFINITE      (0x00u)

#define mSerial_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define mSerial_DEVICE_STATUS_SELF_POWERED (0x01u)

#define mSerial_3V_OPERATION               (0x00u)
#define mSerial_5V_OPERATION               (0x01u)
#define mSerial_DWR_VDDD_OPERATION         (0x02u)

#define mSerial_MODE_DISABLE               (0x00u)
#define mSerial_MODE_NAK_IN_OUT            (0x01u)
#define mSerial_MODE_STATUS_OUT_ONLY       (0x02u)
#define mSerial_MODE_STALL_IN_OUT          (0x03u)
#define mSerial_MODE_RESERVED_0100         (0x04u)
#define mSerial_MODE_ISO_OUT               (0x05u)
#define mSerial_MODE_STATUS_IN_ONLY        (0x06u)
#define mSerial_MODE_ISO_IN                (0x07u)
#define mSerial_MODE_NAK_OUT               (0x08u)
#define mSerial_MODE_ACK_OUT               (0x09u)
#define mSerial_MODE_RESERVED_1010         (0x0Au)
#define mSerial_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define mSerial_MODE_NAK_IN                (0x0Cu)
#define mSerial_MODE_ACK_IN                (0x0Du)
#define mSerial_MODE_RESERVED_1110         (0x0Eu)
#define mSerial_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define mSerial_MODE_MASK                  (0x0Fu)
#define mSerial_MODE_STALL_DATA_EP         (0x80u)

#define mSerial_MODE_ACKD                  (0x10u)
#define mSerial_MODE_OUT_RCVD              (0x20u)
#define mSerial_MODE_IN_RCVD               (0x40u)
#define mSerial_MODE_SETUP_RCVD            (0x80u)

#define mSerial_RQST_TYPE_MASK             (0x60u)
#define mSerial_RQST_TYPE_STD              (0x00u)
#define mSerial_RQST_TYPE_CLS              (0x20u)
#define mSerial_RQST_TYPE_VND              (0x40u)
#define mSerial_RQST_DIR_MASK              (0x80u)
#define mSerial_RQST_DIR_D2H               (0x80u)
#define mSerial_RQST_DIR_H2D               (0x00u)
#define mSerial_RQST_RCPT_MASK             (0x03u)
#define mSerial_RQST_RCPT_DEV              (0x00u)
#define mSerial_RQST_RCPT_IFC              (0x01u)
#define mSerial_RQST_RCPT_EP               (0x02u)
#define mSerial_RQST_RCPT_OTHER            (0x03u)

/* USB Class Codes */
#define mSerial_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define mSerial_CLASS_AUDIO                (0x01u)     /* Audio device */
#define mSerial_CLASS_CDC                  (0x02u)     /* Communication device class */
#define mSerial_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define mSerial_CLASS_PDC                  (0x05u)     /* Physical device class */
#define mSerial_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define mSerial_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define mSerial_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define mSerial_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define mSerial_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define mSerial_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define mSerial_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define mSerial_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define mSerial_CLASS_PHD                  (0x0Fu)     /* Personal Healthcare device */
#define mSerial_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define mSerial_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define mSerial_CLASS_APP                  (0xEFu)     /* Application Specific */
#define mSerial_CLASS_VENDOR               (0xFFu)     /* Vendor specific */


/* Standard Request Types (Table 9-4) */
#define mSerial_GET_STATUS                 (0x00u)
#define mSerial_CLEAR_FEATURE              (0x01u)
#define mSerial_SET_FEATURE                (0x03u)
#define mSerial_SET_ADDRESS                (0x05u)
#define mSerial_GET_DESCRIPTOR             (0x06u)
#define mSerial_SET_DESCRIPTOR             (0x07u)
#define mSerial_GET_CONFIGURATION          (0x08u)
#define mSerial_SET_CONFIGURATION          (0x09u)
#define mSerial_GET_INTERFACE              (0x0Au)
#define mSerial_SET_INTERFACE              (0x0Bu)
#define mSerial_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define mSerial_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define mSerial_DESCR_DEVICE                   (1u)
#define mSerial_DESCR_CONFIG                   (2u)
#define mSerial_DESCR_STRING                   (3u)
#define mSerial_DESCR_INTERFACE                (4u)
#define mSerial_DESCR_ENDPOINT                 (5u)
#define mSerial_DESCR_DEVICE_QUALIFIER         (6u)
#define mSerial_DESCR_OTHER_SPEED              (7u)
#define mSerial_DESCR_INTERFACE_POWER          (8u)

/* Device Descriptor Defines */
#define mSerial_DEVICE_DESCR_LENGTH            (18u)
#define mSerial_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define mSerial_CONFIG_DESCR_LENGTH                (0u)
#define mSerial_CONFIG_DESCR_TYPE                  (1u)
#define mSerial_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define mSerial_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define mSerial_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define mSerial_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define mSerial_CONFIG_DESCR_CONFIGURATION         (6u)
#define mSerial_CONFIG_DESCR_ATTRIB                (7u)
#define mSerial_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define mSerial_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

/* Feature Selectors (Table 9-6) */
#define mSerial_DEVICE_REMOTE_WAKEUP           (0x01u)
#define mSerial_ENDPOINT_HALT                  (0x00u)
#define mSerial_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define mSerial_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define mSerial_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define mSerial_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define mSerial_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define mSerial_DIR_IN                         (0x80u)
#define mSerial_DIR_OUT                        (0x00u)
#define mSerial_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define mSerial_EP_TYPE_CTRL                   (0x00u)
#define mSerial_EP_TYPE_ISOC                   (0x01u)
#define mSerial_EP_TYPE_BULK                   (0x02u)
#define mSerial_EP_TYPE_INT                    (0x03u)
#define mSerial_EP_TYPE_MASK                   (0x03u)

#define mSerial_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define mSerial_EP_SYNC_TYPE_ASYNC             (0x04u)
#define mSerial_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define mSerial_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define mSerial_EP_SYNC_TYPE_MASK              (0x0Cu)

#define mSerial_EP_USAGE_TYPE_DATA             (0x00u)
#define mSerial_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define mSerial_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define mSerial_EP_USAGE_TYPE_RESERVED         (0x30u)
#define mSerial_EP_USAGE_TYPE_MASK             (0x30u)

/* point Status defines */
#define mSerial_EP_STATUS_LENGTH               (0x02u)

/* point Device defines */
#define mSerial_DEVICE_STATUS_LENGTH           (0x02u)

#define mSerial_STATUS_LENGTH_MAX \
                 ( (mSerial_EP_STATUS_LENGTH > mSerial_DEVICE_STATUS_LENGTH) ? \
                    mSerial_EP_STATUS_LENGTH : mSerial_DEVICE_STATUS_LENGTH )
/* Transfer Completion Notification */
#define mSerial_XFER_IDLE                      (0x00u)
#define mSerial_XFER_STATUS_ACK                (0x01u)
#define mSerial_XFER_PREMATURE                 (0x02u)
#define mSerial_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define mSerial_TRANS_STATE_IDLE               (0x00u)
#define mSerial_TRANS_STATE_CONTROL_READ       (0x02u)
#define mSerial_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define mSerial_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define mSerial_STRING_MSOS                    (0xEEu)
#define mSerial_MSOS_DESCRIPTOR_LENGTH         (18u)
#define mSerial_MSOS_CONF_DESCR_LENGTH         (40u)

#if(mSerial_EP_MM == mSerial__EP_DMAMANUAL)
    /* DMA manual mode defines */
    #define mSerial_DMA_BYTES_PER_BURST        (0u)
    #define mSerial_DMA_REQUEST_PER_BURST      (0u)
#endif /*  mSerial_EP_MM == mSerial__EP_DMAMANUAL */
#if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
    /* DMA automatic mode defines */
    #define mSerial_DMA_BYTES_PER_BURST        (32u)
    #define mSerial_DMA_BYTES_REPEAT           (2u)
    /* BUF_SIZE-BYTES_PER_BURST examples: 55-32 bytes  44-16 bytes 33-8 bytes 22-4 bytes 11-2 bytes */
    #define mSerial_DMA_BUF_SIZE               (0x55u)
    #define mSerial_DMA_REQUEST_PER_BURST      (1u)

    #if(mSerial_DMA1_REMOVE == 0u)
        #define mSerial_ep1_TD_TERMOUT_EN      mSerial_ep1__TD_TERMOUT_EN
    #else
        #define mSerial_ep1_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA1_REMOVE == 0u */
    #if(mSerial_DMA2_REMOVE == 0u)
        #define mSerial_ep2_TD_TERMOUT_EN      mSerial_ep2__TD_TERMOUT_EN
    #else
        #define mSerial_ep2_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA2_REMOVE == 0u */
    #if(mSerial_DMA3_REMOVE == 0u)
        #define mSerial_ep3_TD_TERMOUT_EN      mSerial_ep3__TD_TERMOUT_EN
    #else
        #define mSerial_ep3_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA3_REMOVE == 0u */
    #if(mSerial_DMA4_REMOVE == 0u)
        #define mSerial_ep4_TD_TERMOUT_EN      mSerial_ep4__TD_TERMOUT_EN
    #else
        #define mSerial_ep4_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA4_REMOVE == 0u */
    #if(mSerial_DMA5_REMOVE == 0u)
        #define mSerial_ep5_TD_TERMOUT_EN      mSerial_ep5__TD_TERMOUT_EN
    #else
        #define mSerial_ep5_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA5_REMOVE == 0u */
    #if(mSerial_DMA6_REMOVE == 0u)
        #define mSerial_ep6_TD_TERMOUT_EN      mSerial_ep6__TD_TERMOUT_EN
    #else
        #define mSerial_ep6_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA6_REMOVE == 0u */
    #if(mSerial_DMA7_REMOVE == 0u)
        #define mSerial_ep7_TD_TERMOUT_EN      mSerial_ep7__TD_TERMOUT_EN
    #else
        #define mSerial_ep7_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA7_REMOVE == 0u */
    #if(mSerial_DMA8_REMOVE == 0u)
        #define mSerial_ep8_TD_TERMOUT_EN      mSerial_ep8__TD_TERMOUT_EN
    #else
        #define mSerial_ep8_TD_TERMOUT_EN      (0u)
    #endif /* mSerial_DMA8_REMOVE == 0u */

    #define     mSerial_EP17_SR_MASK           (0x7fu)
    #define     mSerial_EP8_SR_MASK            (0x03u)

#endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */

/* DIE ID string descriptor defines */
#if defined(mSerial_ENABLE_IDSN_STRING)
    #define mSerial_IDSN_DESCR_LENGTH          (0x22u)
#endif /* mSerial_ENABLE_IDSN_STRING */


/***************************************
* External data references
***************************************/

extern uint8 mSerial_initVar;
extern volatile uint8 mSerial_device;
extern volatile uint8 mSerial_transferState;
extern volatile uint8 mSerial_configuration;
extern volatile uint8 mSerial_configurationChanged;
extern volatile uint8 mSerial_deviceStatus;

/* HID Variables */
#if defined(mSerial_ENABLE_HID_CLASS)
    extern volatile uint8 mSerial_hidProtocol[mSerial_MAX_INTERFACES_NUMBER];
    extern volatile uint8 mSerial_hidIdleRate[mSerial_MAX_INTERFACES_NUMBER];
    extern volatile uint8 mSerial_hidIdleTimer[mSerial_MAX_INTERFACES_NUMBER];
#endif /* mSerial_ENABLE_HID_CLASS */


/***************************************
*              Registers
***************************************/

#define mSerial_ARB_CFG_PTR        (  (reg8 *) mSerial_USB__ARB_CFG)
#define mSerial_ARB_CFG_REG        (* (reg8 *) mSerial_USB__ARB_CFG)

#define mSerial_ARB_EP1_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP1_CFG)
#define mSerial_ARB_EP1_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP1_CFG)
#define mSerial_ARB_EP1_CFG_IND    mSerial_USB__ARB_EP1_CFG
#define mSerial_ARB_EP1_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP1_INT_EN)
#define mSerial_ARB_EP1_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP1_INT_EN)
#define mSerial_ARB_EP1_INT_EN_IND mSerial_USB__ARB_EP1_INT_EN
#define mSerial_ARB_EP1_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP1_SR)
#define mSerial_ARB_EP1_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP1_SR)
#define mSerial_ARB_EP1_SR_IND     mSerial_USB__ARB_EP1_SR

#define mSerial_ARB_EP2_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP2_CFG)
#define mSerial_ARB_EP2_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP2_CFG)
#define mSerial_ARB_EP2_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP2_INT_EN)
#define mSerial_ARB_EP2_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP2_INT_EN)
#define mSerial_ARB_EP2_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP2_SR)
#define mSerial_ARB_EP2_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP2_SR)

#define mSerial_ARB_EP3_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP3_CFG)
#define mSerial_ARB_EP3_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP3_CFG)
#define mSerial_ARB_EP3_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP3_INT_EN)
#define mSerial_ARB_EP3_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP3_INT_EN)
#define mSerial_ARB_EP3_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP3_SR)
#define mSerial_ARB_EP3_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP3_SR)

#define mSerial_ARB_EP4_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP4_CFG)
#define mSerial_ARB_EP4_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP4_CFG)
#define mSerial_ARB_EP4_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP4_INT_EN)
#define mSerial_ARB_EP4_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP4_INT_EN)
#define mSerial_ARB_EP4_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP4_SR)
#define mSerial_ARB_EP4_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP4_SR)

#define mSerial_ARB_EP5_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP5_CFG)
#define mSerial_ARB_EP5_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP5_CFG)
#define mSerial_ARB_EP5_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP5_INT_EN)
#define mSerial_ARB_EP5_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP5_INT_EN)
#define mSerial_ARB_EP5_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP5_SR)
#define mSerial_ARB_EP5_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP5_SR)

#define mSerial_ARB_EP6_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP6_CFG)
#define mSerial_ARB_EP6_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP6_CFG)
#define mSerial_ARB_EP6_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP6_INT_EN)
#define mSerial_ARB_EP6_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP6_INT_EN)
#define mSerial_ARB_EP6_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP6_SR)
#define mSerial_ARB_EP6_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP6_SR)

#define mSerial_ARB_EP7_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP7_CFG)
#define mSerial_ARB_EP7_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP7_CFG)
#define mSerial_ARB_EP7_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP7_INT_EN)
#define mSerial_ARB_EP7_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP7_INT_EN)
#define mSerial_ARB_EP7_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP7_SR)
#define mSerial_ARB_EP7_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP7_SR)

#define mSerial_ARB_EP8_CFG_PTR    (  (reg8 *) mSerial_USB__ARB_EP8_CFG)
#define mSerial_ARB_EP8_CFG_REG    (* (reg8 *) mSerial_USB__ARB_EP8_CFG)
#define mSerial_ARB_EP8_INT_EN_PTR (  (reg8 *) mSerial_USB__ARB_EP8_INT_EN)
#define mSerial_ARB_EP8_INT_EN_REG (* (reg8 *) mSerial_USB__ARB_EP8_INT_EN)
#define mSerial_ARB_EP8_SR_PTR     (  (reg8 *) mSerial_USB__ARB_EP8_SR)
#define mSerial_ARB_EP8_SR_REG     (* (reg8 *) mSerial_USB__ARB_EP8_SR)

#define mSerial_ARB_INT_EN_PTR     (  (reg8 *) mSerial_USB__ARB_INT_EN)
#define mSerial_ARB_INT_EN_REG     (* (reg8 *) mSerial_USB__ARB_INT_EN)
#define mSerial_ARB_INT_SR_PTR     (  (reg8 *) mSerial_USB__ARB_INT_SR)
#define mSerial_ARB_INT_SR_REG     (* (reg8 *) mSerial_USB__ARB_INT_SR)

#define mSerial_ARB_RW1_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW1_DR)
#define mSerial_ARB_RW1_DR_IND     mSerial_USB__ARB_RW1_DR
#define mSerial_ARB_RW1_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW1_RA)
#define mSerial_ARB_RW1_RA_IND     mSerial_USB__ARB_RW1_RA
#define mSerial_ARB_RW1_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW1_RA_MSB)
#define mSerial_ARB_RW1_RA_MSB_IND mSerial_USB__ARB_RW1_RA_MSB
#define mSerial_ARB_RW1_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW1_WA)
#define mSerial_ARB_RW1_WA_IND     mSerial_USB__ARB_RW1_WA
#define mSerial_ARB_RW1_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW1_WA_MSB)
#define mSerial_ARB_RW1_WA_MSB_IND mSerial_USB__ARB_RW1_WA_MSB

#define mSerial_ARB_RW2_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW2_DR)
#define mSerial_ARB_RW2_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW2_RA)
#define mSerial_ARB_RW2_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW2_RA_MSB)
#define mSerial_ARB_RW2_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW2_WA)
#define mSerial_ARB_RW2_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW2_WA_MSB)

#define mSerial_ARB_RW3_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW3_DR)
#define mSerial_ARB_RW3_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW3_RA)
#define mSerial_ARB_RW3_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW3_RA_MSB)
#define mSerial_ARB_RW3_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW3_WA)
#define mSerial_ARB_RW3_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW3_WA_MSB)

#define mSerial_ARB_RW4_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW4_DR)
#define mSerial_ARB_RW4_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW4_RA)
#define mSerial_ARB_RW4_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW4_RA_MSB)
#define mSerial_ARB_RW4_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW4_WA)
#define mSerial_ARB_RW4_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW4_WA_MSB)

#define mSerial_ARB_RW5_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW5_DR)
#define mSerial_ARB_RW5_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW5_RA)
#define mSerial_ARB_RW5_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW5_RA_MSB)
#define mSerial_ARB_RW5_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW5_WA)
#define mSerial_ARB_RW5_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW5_WA_MSB)

#define mSerial_ARB_RW6_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW6_DR)
#define mSerial_ARB_RW6_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW6_RA)
#define mSerial_ARB_RW6_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW6_RA_MSB)
#define mSerial_ARB_RW6_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW6_WA)
#define mSerial_ARB_RW6_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW6_WA_MSB)

#define mSerial_ARB_RW7_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW7_DR)
#define mSerial_ARB_RW7_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW7_RA)
#define mSerial_ARB_RW7_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW7_RA_MSB)
#define mSerial_ARB_RW7_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW7_WA)
#define mSerial_ARB_RW7_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW7_WA_MSB)

#define mSerial_ARB_RW8_DR_PTR     ((reg8 *) mSerial_USB__ARB_RW8_DR)
#define mSerial_ARB_RW8_RA_PTR     ((reg8 *) mSerial_USB__ARB_RW8_RA)
#define mSerial_ARB_RW8_RA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW8_RA_MSB)
#define mSerial_ARB_RW8_WA_PTR     ((reg8 *) mSerial_USB__ARB_RW8_WA)
#define mSerial_ARB_RW8_WA_MSB_PTR ((reg8 *) mSerial_USB__ARB_RW8_WA_MSB)

#define mSerial_BUF_SIZE_PTR       (  (reg8 *) mSerial_USB__BUF_SIZE)
#define mSerial_BUF_SIZE_REG       (* (reg8 *) mSerial_USB__BUF_SIZE)
#define mSerial_BUS_RST_CNT_PTR    (  (reg8 *) mSerial_USB__BUS_RST_CNT)
#define mSerial_BUS_RST_CNT_REG    (* (reg8 *) mSerial_USB__BUS_RST_CNT)
#define mSerial_CWA_PTR            (  (reg8 *) mSerial_USB__CWA)
#define mSerial_CWA_REG            (* (reg8 *) mSerial_USB__CWA)
#define mSerial_CWA_MSB_PTR        (  (reg8 *) mSerial_USB__CWA_MSB)
#define mSerial_CWA_MSB_REG        (* (reg8 *) mSerial_USB__CWA_MSB)
#define mSerial_CR0_PTR            (  (reg8 *) mSerial_USB__CR0)
#define mSerial_CR0_REG            (* (reg8 *) mSerial_USB__CR0)
#define mSerial_CR1_PTR            (  (reg8 *) mSerial_USB__CR1)
#define mSerial_CR1_REG            (* (reg8 *) mSerial_USB__CR1)

#define mSerial_DMA_THRES_PTR      (  (reg8 *) mSerial_USB__DMA_THRES)
#define mSerial_DMA_THRES_REG      (* (reg8 *) mSerial_USB__DMA_THRES)
#define mSerial_DMA_THRES_MSB_PTR  (  (reg8 *) mSerial_USB__DMA_THRES_MSB)
#define mSerial_DMA_THRES_MSB_REG  (* (reg8 *) mSerial_USB__DMA_THRES_MSB)

#define mSerial_EP_ACTIVE_PTR      (  (reg8 *) mSerial_USB__EP_ACTIVE)
#define mSerial_EP_ACTIVE_REG      (* (reg8 *) mSerial_USB__EP_ACTIVE)
#define mSerial_EP_TYPE_PTR        (  (reg8 *) mSerial_USB__EP_TYPE)
#define mSerial_EP_TYPE_REG        (* (reg8 *) mSerial_USB__EP_TYPE)

#define mSerial_EP0_CNT_PTR        (  (reg8 *) mSerial_USB__EP0_CNT)
#define mSerial_EP0_CNT_REG        (* (reg8 *) mSerial_USB__EP0_CNT)
#define mSerial_EP0_CR_PTR         (  (reg8 *) mSerial_USB__EP0_CR)
#define mSerial_EP0_CR_REG         (* (reg8 *) mSerial_USB__EP0_CR)
#define mSerial_EP0_DR0_PTR        (  (reg8 *) mSerial_USB__EP0_DR0)
#define mSerial_EP0_DR0_REG        (* (reg8 *) mSerial_USB__EP0_DR0)
#define mSerial_EP0_DR0_IND        mSerial_USB__EP0_DR0
#define mSerial_EP0_DR1_PTR        (  (reg8 *) mSerial_USB__EP0_DR1)
#define mSerial_EP0_DR1_REG        (* (reg8 *) mSerial_USB__EP0_DR1)
#define mSerial_EP0_DR2_PTR        (  (reg8 *) mSerial_USB__EP0_DR2)
#define mSerial_EP0_DR2_REG        (* (reg8 *) mSerial_USB__EP0_DR2)
#define mSerial_EP0_DR3_PTR        (  (reg8 *) mSerial_USB__EP0_DR3)
#define mSerial_EP0_DR3_REG        (* (reg8 *) mSerial_USB__EP0_DR3)
#define mSerial_EP0_DR4_PTR        (  (reg8 *) mSerial_USB__EP0_DR4)
#define mSerial_EP0_DR4_REG        (* (reg8 *) mSerial_USB__EP0_DR4)
#define mSerial_EP0_DR5_PTR        (  (reg8 *) mSerial_USB__EP0_DR5)
#define mSerial_EP0_DR5_REG        (* (reg8 *) mSerial_USB__EP0_DR5)
#define mSerial_EP0_DR6_PTR        (  (reg8 *) mSerial_USB__EP0_DR6)
#define mSerial_EP0_DR6_REG        (* (reg8 *) mSerial_USB__EP0_DR6)
#define mSerial_EP0_DR7_PTR        (  (reg8 *) mSerial_USB__EP0_DR7)
#define mSerial_EP0_DR7_REG        (* (reg8 *) mSerial_USB__EP0_DR7)

#define mSerial_OSCLK_DR0_PTR      (  (reg8 *) mSerial_USB__OSCLK_DR0)
#define mSerial_OSCLK_DR0_REG      (* (reg8 *) mSerial_USB__OSCLK_DR0)
#define mSerial_OSCLK_DR1_PTR      (  (reg8 *) mSerial_USB__OSCLK_DR1)
#define mSerial_OSCLK_DR1_REG      (* (reg8 *) mSerial_USB__OSCLK_DR1)

#define mSerial_PM_ACT_CFG_PTR     (  (reg8 *) mSerial_USB__PM_ACT_CFG)
#define mSerial_PM_ACT_CFG_REG     (* (reg8 *) mSerial_USB__PM_ACT_CFG)
#define mSerial_PM_STBY_CFG_PTR    (  (reg8 *) mSerial_USB__PM_STBY_CFG)
#define mSerial_PM_STBY_CFG_REG    (* (reg8 *) mSerial_USB__PM_STBY_CFG)

#define mSerial_SIE_EP_INT_EN_PTR  (  (reg8 *) mSerial_USB__SIE_EP_INT_EN)
#define mSerial_SIE_EP_INT_EN_REG  (* (reg8 *) mSerial_USB__SIE_EP_INT_EN)
#define mSerial_SIE_EP_INT_SR_PTR  (  (reg8 *) mSerial_USB__SIE_EP_INT_SR)
#define mSerial_SIE_EP_INT_SR_REG  (* (reg8 *) mSerial_USB__SIE_EP_INT_SR)

#define mSerial_SIE_EP1_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP1_CNT0)
#define mSerial_SIE_EP1_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP1_CNT0)
#define mSerial_SIE_EP1_CNT0_IND   mSerial_USB__SIE_EP1_CNT0
#define mSerial_SIE_EP1_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP1_CNT1)
#define mSerial_SIE_EP1_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP1_CNT1)
#define mSerial_SIE_EP1_CNT1_IND   mSerial_USB__SIE_EP1_CNT1
#define mSerial_SIE_EP1_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP1_CR0)
#define mSerial_SIE_EP1_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP1_CR0)
#define mSerial_SIE_EP1_CR0_IND    mSerial_USB__SIE_EP1_CR0

#define mSerial_SIE_EP2_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP2_CNT0)
#define mSerial_SIE_EP2_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP2_CNT0)
#define mSerial_SIE_EP2_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP2_CNT1)
#define mSerial_SIE_EP2_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP2_CNT1)
#define mSerial_SIE_EP2_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP2_CR0)
#define mSerial_SIE_EP2_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP2_CR0)

#define mSerial_SIE_EP3_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP3_CNT0)
#define mSerial_SIE_EP3_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP3_CNT0)
#define mSerial_SIE_EP3_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP3_CNT1)
#define mSerial_SIE_EP3_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP3_CNT1)
#define mSerial_SIE_EP3_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP3_CR0)
#define mSerial_SIE_EP3_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP3_CR0)

#define mSerial_SIE_EP4_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP4_CNT0)
#define mSerial_SIE_EP4_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP4_CNT0)
#define mSerial_SIE_EP4_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP4_CNT1)
#define mSerial_SIE_EP4_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP4_CNT1)
#define mSerial_SIE_EP4_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP4_CR0)
#define mSerial_SIE_EP4_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP4_CR0)

#define mSerial_SIE_EP5_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP5_CNT0)
#define mSerial_SIE_EP5_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP5_CNT0)
#define mSerial_SIE_EP5_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP5_CNT1)
#define mSerial_SIE_EP5_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP5_CNT1)
#define mSerial_SIE_EP5_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP5_CR0)
#define mSerial_SIE_EP5_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP5_CR0)

#define mSerial_SIE_EP6_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP6_CNT0)
#define mSerial_SIE_EP6_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP6_CNT0)
#define mSerial_SIE_EP6_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP6_CNT1)
#define mSerial_SIE_EP6_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP6_CNT1)
#define mSerial_SIE_EP6_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP6_CR0)
#define mSerial_SIE_EP6_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP6_CR0)

#define mSerial_SIE_EP7_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP7_CNT0)
#define mSerial_SIE_EP7_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP7_CNT0)
#define mSerial_SIE_EP7_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP7_CNT1)
#define mSerial_SIE_EP7_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP7_CNT1)
#define mSerial_SIE_EP7_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP7_CR0)
#define mSerial_SIE_EP7_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP7_CR0)

#define mSerial_SIE_EP8_CNT0_PTR   (  (reg8 *) mSerial_USB__SIE_EP8_CNT0)
#define mSerial_SIE_EP8_CNT0_REG   (* (reg8 *) mSerial_USB__SIE_EP8_CNT0)
#define mSerial_SIE_EP8_CNT1_PTR   (  (reg8 *) mSerial_USB__SIE_EP8_CNT1)
#define mSerial_SIE_EP8_CNT1_REG   (* (reg8 *) mSerial_USB__SIE_EP8_CNT1)
#define mSerial_SIE_EP8_CR0_PTR    (  (reg8 *) mSerial_USB__SIE_EP8_CR0)
#define mSerial_SIE_EP8_CR0_REG    (* (reg8 *) mSerial_USB__SIE_EP8_CR0)

#define mSerial_SOF0_PTR           (  (reg8 *) mSerial_USB__SOF0)
#define mSerial_SOF0_REG           (* (reg8 *) mSerial_USB__SOF0)
#define mSerial_SOF1_PTR           (  (reg8 *) mSerial_USB__SOF1)
#define mSerial_SOF1_REG           (* (reg8 *) mSerial_USB__SOF1)

#define mSerial_USB_CLK_EN_PTR     (  (reg8 *) mSerial_USB__USB_CLK_EN)
#define mSerial_USB_CLK_EN_REG     (* (reg8 *) mSerial_USB__USB_CLK_EN)

#define mSerial_USBIO_CR0_PTR      (  (reg8 *) mSerial_USB__USBIO_CR0)
#define mSerial_USBIO_CR0_REG      (* (reg8 *) mSerial_USB__USBIO_CR0)
#define mSerial_USBIO_CR1_PTR      (  (reg8 *) mSerial_USB__USBIO_CR1)
#define mSerial_USBIO_CR1_REG      (* (reg8 *) mSerial_USB__USBIO_CR1)
#if(!CY_PSOC5LP)
    #define mSerial_USBIO_CR2_PTR      (  (reg8 *) mSerial_USB__USBIO_CR2)
    #define mSerial_USBIO_CR2_REG      (* (reg8 *) mSerial_USB__USBIO_CR2)
#endif /*  CY_PSOC5LP */

#define mSerial_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

#define mSerial_PM_USB_CR0_PTR     (  (reg8 *) CYREG_PM_USB_CR0)
#define mSerial_PM_USB_CR0_REG     (* (reg8 *) CYREG_PM_USB_CR0)
#define mSerial_DYN_RECONFIG_PTR   (  (reg8 *) mSerial_USB__DYN_RECONFIG)
#define mSerial_DYN_RECONFIG_REG   (* (reg8 *) mSerial_USB__DYN_RECONFIG)

#define mSerial_DM_INP_DIS_PTR     (  (reg8 *) mSerial_Dm__INP_DIS)
#define mSerial_DM_INP_DIS_REG     (* (reg8 *) mSerial_Dm__INP_DIS)
#define mSerial_DP_INP_DIS_PTR     (  (reg8 *) mSerial_Dp__INP_DIS)
#define mSerial_DP_INP_DIS_REG     (* (reg8 *) mSerial_Dp__INP_DIS)
#define mSerial_DP_INTSTAT_PTR     (  (reg8 *) mSerial_Dp__INTSTAT)
#define mSerial_DP_INTSTAT_REG     (* (reg8 *) mSerial_Dp__INTSTAT)

#if (mSerial_MON_VBUS == 1u)
    #if (mSerial_EXTERN_VBUS == 0u)
        #define mSerial_VBUS_DR_PTR        (  (reg8 *) mSerial_VBUS__DR)
        #define mSerial_VBUS_DR_REG        (* (reg8 *) mSerial_VBUS__DR)
        #define mSerial_VBUS_PS_PTR        (  (reg8 *) mSerial_VBUS__PS)
        #define mSerial_VBUS_PS_REG        (* (reg8 *) mSerial_VBUS__PS)
        #define mSerial_VBUS_MASK          mSerial_VBUS__MASK
    #else
        #define mSerial_VBUS_PS_PTR        (  (reg8 *) mSerial_Vbus_ps_sts_sts_reg__STATUS_REG )
        #define mSerial_VBUS_MASK          (0x01u)
    #endif /*  mSerial_EXTERN_VBUS == 0u */
#endif /*  mSerial_MON_VBUS */

/* Renamed Registers for backward compatibility.
*  Should not be used in new designs.
*/
#define mSerial_ARB_CFG        mSerial_ARB_CFG_PTR

#define mSerial_ARB_EP1_CFG    mSerial_ARB_EP1_CFG_PTR
#define mSerial_ARB_EP1_INT_EN mSerial_ARB_EP1_INT_EN_PTR
#define mSerial_ARB_EP1_SR     mSerial_ARB_EP1_SR_PTR

#define mSerial_ARB_EP2_CFG    mSerial_ARB_EP2_CFG_PTR
#define mSerial_ARB_EP2_INT_EN mSerial_ARB_EP2_INT_EN_PTR
#define mSerial_ARB_EP2_SR     mSerial_ARB_EP2_SR_PTR

#define mSerial_ARB_EP3_CFG    mSerial_ARB_EP3_CFG_PTR
#define mSerial_ARB_EP3_INT_EN mSerial_ARB_EP3_INT_EN_PTR
#define mSerial_ARB_EP3_SR     mSerial_ARB_EP3_SR_PTR

#define mSerial_ARB_EP4_CFG    mSerial_ARB_EP4_CFG_PTR
#define mSerial_ARB_EP4_INT_EN mSerial_ARB_EP4_INT_EN_PTR
#define mSerial_ARB_EP4_SR     mSerial_ARB_EP4_SR_PTR

#define mSerial_ARB_EP5_CFG    mSerial_ARB_EP5_CFG_PTR
#define mSerial_ARB_EP5_INT_EN mSerial_ARB_EP5_INT_EN_PTR
#define mSerial_ARB_EP5_SR     mSerial_ARB_EP5_SR_PTR

#define mSerial_ARB_EP6_CFG    mSerial_ARB_EP6_CFG_PTR
#define mSerial_ARB_EP6_INT_EN mSerial_ARB_EP6_INT_EN_PTR
#define mSerial_ARB_EP6_SR     mSerial_ARB_EP6_SR_PTR

#define mSerial_ARB_EP7_CFG    mSerial_ARB_EP7_CFG_PTR
#define mSerial_ARB_EP7_INT_EN mSerial_ARB_EP7_INT_EN_PTR
#define mSerial_ARB_EP7_SR     mSerial_ARB_EP7_SR_PTR

#define mSerial_ARB_EP8_CFG    mSerial_ARB_EP8_CFG_PTR
#define mSerial_ARB_EP8_INT_EN mSerial_ARB_EP8_INT_EN_PTR
#define mSerial_ARB_EP8_SR     mSerial_ARB_EP8_SR_PTR

#define mSerial_ARB_INT_EN     mSerial_ARB_INT_EN_PTR
#define mSerial_ARB_INT_SR     mSerial_ARB_INT_SR_PTR

#define mSerial_ARB_RW1_DR     mSerial_ARB_RW1_DR_PTR
#define mSerial_ARB_RW1_RA     mSerial_ARB_RW1_RA_PTR
#define mSerial_ARB_RW1_RA_MSB mSerial_ARB_RW1_RA_MSB_PTR
#define mSerial_ARB_RW1_WA     mSerial_ARB_RW1_WA_PTR
#define mSerial_ARB_RW1_WA_MSB mSerial_ARB_RW1_WA_MSB_PTR

#define mSerial_ARB_RW2_DR     mSerial_ARB_RW2_DR_PTR
#define mSerial_ARB_RW2_RA     mSerial_ARB_RW2_RA_PTR
#define mSerial_ARB_RW2_RA_MSB mSerial_ARB_RW2_RA_MSB_PTR
#define mSerial_ARB_RW2_WA     mSerial_ARB_RW2_WA_PTR
#define mSerial_ARB_RW2_WA_MSB mSerial_ARB_RW2_WA_MSB_PTR

#define mSerial_ARB_RW3_DR     mSerial_ARB_RW3_DR_PTR
#define mSerial_ARB_RW3_RA     mSerial_ARB_RW3_RA_PTR
#define mSerial_ARB_RW3_RA_MSB mSerial_ARB_RW3_RA_MSB_PTR
#define mSerial_ARB_RW3_WA     mSerial_ARB_RW3_WA_PTR
#define mSerial_ARB_RW3_WA_MSB mSerial_ARB_RW3_WA_MSB_PTR

#define mSerial_ARB_RW4_DR     mSerial_ARB_RW4_DR_PTR
#define mSerial_ARB_RW4_RA     mSerial_ARB_RW4_RA_PTR
#define mSerial_ARB_RW4_RA_MSB mSerial_ARB_RW4_RA_MSB_PTR
#define mSerial_ARB_RW4_WA     mSerial_ARB_RW4_WA_PTR
#define mSerial_ARB_RW4_WA_MSB mSerial_ARB_RW4_WA_MSB_PTR

#define mSerial_ARB_RW5_DR     mSerial_ARB_RW5_DR_PTR
#define mSerial_ARB_RW5_RA     mSerial_ARB_RW5_RA_PTR
#define mSerial_ARB_RW5_RA_MSB mSerial_ARB_RW5_RA_MSB_PTR
#define mSerial_ARB_RW5_WA     mSerial_ARB_RW5_WA_PTR
#define mSerial_ARB_RW5_WA_MSB mSerial_ARB_RW5_WA_MSB_PTR

#define mSerial_ARB_RW6_DR     mSerial_ARB_RW6_DR_PTR
#define mSerial_ARB_RW6_RA     mSerial_ARB_RW6_RA_PTR
#define mSerial_ARB_RW6_RA_MSB mSerial_ARB_RW6_RA_MSB_PTR
#define mSerial_ARB_RW6_WA     mSerial_ARB_RW6_WA_PTR
#define mSerial_ARB_RW6_WA_MSB mSerial_ARB_RW6_WA_MSB_PTR

#define mSerial_ARB_RW7_DR     mSerial_ARB_RW7_DR_PTR
#define mSerial_ARB_RW7_RA     mSerial_ARB_RW7_RA_PTR
#define mSerial_ARB_RW7_RA_MSB mSerial_ARB_RW7_RA_MSB_PTR
#define mSerial_ARB_RW7_WA     mSerial_ARB_RW7_WA_PTR
#define mSerial_ARB_RW7_WA_MSB mSerial_ARB_RW7_WA_MSB_PTR

#define mSerial_ARB_RW8_DR     mSerial_ARB_RW8_DR_PTR
#define mSerial_ARB_RW8_RA     mSerial_ARB_RW8_RA_PTR
#define mSerial_ARB_RW8_RA_MSB mSerial_ARB_RW8_RA_MSB_PTR
#define mSerial_ARB_RW8_WA     mSerial_ARB_RW8_WA_PTR
#define mSerial_ARB_RW8_WA_MSB mSerial_ARB_RW8_WA_MSB_PTR

#define mSerial_BUF_SIZE       mSerial_BUF_SIZE_PTR
#define mSerial_BUS_RST_CNT    mSerial_BUS_RST_CNT_PTR
#define mSerial_CR0            mSerial_CR0_PTR
#define mSerial_CR1            mSerial_CR1_PTR
#define mSerial_CWA            mSerial_CWA_PTR
#define mSerial_CWA_MSB        mSerial_CWA_MSB_PTR

#define mSerial_DMA_THRES      mSerial_DMA_THRES_PTR
#define mSerial_DMA_THRES_MSB  mSerial_DMA_THRES_MSB_PTR

#define mSerial_EP_ACTIVE      mSerial_EP_ACTIVE_PTR
#define mSerial_EP_TYPE        mSerial_EP_TYPE_PTR

#define mSerial_EP0_CNT        mSerial_EP0_CNT_PTR
#define mSerial_EP0_CR         mSerial_EP0_CR_PTR
#define mSerial_EP0_DR0        mSerial_EP0_DR0_PTR
#define mSerial_EP0_DR1        mSerial_EP0_DR1_PTR
#define mSerial_EP0_DR2        mSerial_EP0_DR2_PTR
#define mSerial_EP0_DR3        mSerial_EP0_DR3_PTR
#define mSerial_EP0_DR4        mSerial_EP0_DR4_PTR
#define mSerial_EP0_DR5        mSerial_EP0_DR5_PTR
#define mSerial_EP0_DR6        mSerial_EP0_DR6_PTR
#define mSerial_EP0_DR7        mSerial_EP0_DR7_PTR

#define mSerial_OSCLK_DR0      mSerial_OSCLK_DR0_PTR
#define mSerial_OSCLK_DR1      mSerial_OSCLK_DR1_PTR

#define mSerial_PM_ACT_CFG     mSerial_PM_ACT_CFG_PTR
#define mSerial_PM_STBY_CFG    mSerial_PM_STBY_CFG_PTR

#define mSerial_SIE_EP_INT_EN  mSerial_SIE_EP_INT_EN_PTR
#define mSerial_SIE_EP_INT_SR  mSerial_SIE_EP_INT_SR_PTR

#define mSerial_SIE_EP1_CNT0   mSerial_SIE_EP1_CNT0_PTR
#define mSerial_SIE_EP1_CNT1   mSerial_SIE_EP1_CNT1_PTR
#define mSerial_SIE_EP1_CR0    mSerial_SIE_EP1_CR0_PTR

#define mSerial_SIE_EP2_CNT0   mSerial_SIE_EP2_CNT0_PTR
#define mSerial_SIE_EP2_CNT1   mSerial_SIE_EP2_CNT1_PTR
#define mSerial_SIE_EP2_CR0    mSerial_SIE_EP2_CR0_PTR

#define mSerial_SIE_EP3_CNT0   mSerial_SIE_EP3_CNT0_PTR
#define mSerial_SIE_EP3_CNT1   mSerial_SIE_EP3_CNT1_PTR
#define mSerial_SIE_EP3_CR0    mSerial_SIE_EP3_CR0_PTR

#define mSerial_SIE_EP4_CNT0   mSerial_SIE_EP4_CNT0_PTR
#define mSerial_SIE_EP4_CNT1   mSerial_SIE_EP4_CNT1_PTR
#define mSerial_SIE_EP4_CR0    mSerial_SIE_EP4_CR0_PTR

#define mSerial_SIE_EP5_CNT0   mSerial_SIE_EP5_CNT0_PTR
#define mSerial_SIE_EP5_CNT1   mSerial_SIE_EP5_CNT1_PTR
#define mSerial_SIE_EP5_CR0    mSerial_SIE_EP5_CR0_PTR

#define mSerial_SIE_EP6_CNT0   mSerial_SIE_EP6_CNT0_PTR
#define mSerial_SIE_EP6_CNT1   mSerial_SIE_EP6_CNT1_PTR
#define mSerial_SIE_EP6_CR0    mSerial_SIE_EP6_CR0_PTR

#define mSerial_SIE_EP7_CNT0   mSerial_SIE_EP7_CNT0_PTR
#define mSerial_SIE_EP7_CNT1   mSerial_SIE_EP7_CNT1_PTR
#define mSerial_SIE_EP7_CR0    mSerial_SIE_EP7_CR0_PTR

#define mSerial_SIE_EP8_CNT0   mSerial_SIE_EP8_CNT0_PTR
#define mSerial_SIE_EP8_CNT1   mSerial_SIE_EP8_CNT1_PTR
#define mSerial_SIE_EP8_CR0    mSerial_SIE_EP8_CR0_PTR

#define mSerial_SOF0           mSerial_SOF0_PTR
#define mSerial_SOF1           mSerial_SOF1_PTR

#define mSerial_USB_CLK_EN     mSerial_USB_CLK_EN_PTR

#define mSerial_USBIO_CR0      mSerial_USBIO_CR0_PTR
#define mSerial_USBIO_CR1      mSerial_USBIO_CR1_PTR
#define mSerial_USBIO_CR2      mSerial_USBIO_CR2_PTR

#define mSerial_USB_MEM        ((reg8 *) CYDEV_USB_MEM_BASE)

#if(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* PSoC3 interrupt registers*/
    #define mSerial_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define mSerial_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define mSerial_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define mSerial_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif(CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* PSoC5 interrupt registers*/
    #define mSerial_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define mSerial_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define mSerial_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define mSerial_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


/***************************************
* Interrupt vectors, masks and priorities
***************************************/

#define mSerial_BUS_RESET_PRIOR    mSerial_bus_reset__INTC_PRIOR_NUM
#define mSerial_BUS_RESET_MASK     mSerial_bus_reset__INTC_MASK
#define mSerial_BUS_RESET_VECT_NUM mSerial_bus_reset__INTC_NUMBER

#define mSerial_SOF_PRIOR          mSerial_sof_int__INTC_PRIOR_NUM
#define mSerial_SOF_MASK           mSerial_sof_int__INTC_MASK
#define mSerial_SOF_VECT_NUM       mSerial_sof_int__INTC_NUMBER

#define mSerial_EP_0_PRIOR         mSerial_ep_0__INTC_PRIOR_NUM
#define mSerial_EP_0_MASK          mSerial_ep_0__INTC_MASK
#define mSerial_EP_0_VECT_NUM      mSerial_ep_0__INTC_NUMBER

#define mSerial_EP_1_PRIOR         mSerial_ep_1__INTC_PRIOR_NUM
#define mSerial_EP_1_MASK          mSerial_ep_1__INTC_MASK
#define mSerial_EP_1_VECT_NUM      mSerial_ep_1__INTC_NUMBER

#define mSerial_EP_2_PRIOR         mSerial_ep_2__INTC_PRIOR_NUM
#define mSerial_EP_2_MASK          mSerial_ep_2__INTC_MASK
#define mSerial_EP_2_VECT_NUM      mSerial_ep_2__INTC_NUMBER

#define mSerial_EP_3_PRIOR         mSerial_ep_3__INTC_PRIOR_NUM
#define mSerial_EP_3_MASK          mSerial_ep_3__INTC_MASK
#define mSerial_EP_3_VECT_NUM      mSerial_ep_3__INTC_NUMBER

#define mSerial_EP_4_PRIOR         mSerial_ep_4__INTC_PRIOR_NUM
#define mSerial_EP_4_MASK          mSerial_ep_4__INTC_MASK
#define mSerial_EP_4_VECT_NUM      mSerial_ep_4__INTC_NUMBER

#define mSerial_EP_5_PRIOR         mSerial_ep_5__INTC_PRIOR_NUM
#define mSerial_EP_5_MASK          mSerial_ep_5__INTC_MASK
#define mSerial_EP_5_VECT_NUM      mSerial_ep_5__INTC_NUMBER

#define mSerial_EP_6_PRIOR         mSerial_ep_6__INTC_PRIOR_NUM
#define mSerial_EP_6_MASK          mSerial_ep_6__INTC_MASK
#define mSerial_EP_6_VECT_NUM      mSerial_ep_6__INTC_NUMBER

#define mSerial_EP_7_PRIOR         mSerial_ep_7__INTC_PRIOR_NUM
#define mSerial_EP_7_MASK          mSerial_ep_7__INTC_MASK
#define mSerial_EP_7_VECT_NUM      mSerial_ep_7__INTC_NUMBER

#define mSerial_EP_8_PRIOR         mSerial_ep_8__INTC_PRIOR_NUM
#define mSerial_EP_8_MASK          mSerial_ep_8__INTC_MASK
#define mSerial_EP_8_VECT_NUM      mSerial_ep_8__INTC_NUMBER

#define mSerial_DP_INTC_PRIOR      mSerial_dp_int__INTC_PRIOR_NUM
#define mSerial_DP_INTC_MASK       mSerial_dp_int__INTC_MASK
#define mSerial_DP_INTC_VECT_NUM   mSerial_dp_int__INTC_NUMBER

/* ARB ISR should have higher priority from EP_X ISR, therefore it is defined to highest (0) */
#define mSerial_ARB_PRIOR          (0u)
#define mSerial_ARB_MASK           mSerial_arb_int__INTC_MASK
#define mSerial_ARB_VECT_NUM       mSerial_arb_int__INTC_NUMBER

/***************************************
 *  Endpoint 0 offsets (Table 9-2)
 **************************************/

#define mSerial_bmRequestType      mSerial_EP0_DR0_PTR
#define mSerial_bRequest           mSerial_EP0_DR1_PTR
#define mSerial_wValue             mSerial_EP0_DR2_PTR
#define mSerial_wValueHi           mSerial_EP0_DR3_PTR
#define mSerial_wValueLo           mSerial_EP0_DR2_PTR
#define mSerial_wIndex             mSerial_EP0_DR4_PTR
#define mSerial_wIndexHi           mSerial_EP0_DR5_PTR
#define mSerial_wIndexLo           mSerial_EP0_DR4_PTR
#define mSerial_length             mSerial_EP0_DR6_PTR
#define mSerial_lengthHi           mSerial_EP0_DR7_PTR
#define mSerial_lengthLo           mSerial_EP0_DR6_PTR


/***************************************
*       Register Constants
***************************************/
#define mSerial_VDDD_MV                    CYDEV_VDDD_MV
#define mSerial_3500MV                     (3500u)

#define mSerial_CR1_REG_ENABLE             (0x01u)
#define mSerial_CR1_ENABLE_LOCK            (0x02u)
#define mSerial_CR1_BUS_ACTIVITY_SHIFT     (0x02u)
#define mSerial_CR1_BUS_ACTIVITY           ((uint8)(0x01u << mSerial_CR1_BUS_ACTIVITY_SHIFT))
#define mSerial_CR1_TRIM_MSB_EN            (0x08u)

#define mSerial_EP0_CNT_DATA_TOGGLE        (0x80u)
#define mSerial_EPX_CNT_DATA_TOGGLE        (0x80u)
#define mSerial_EPX_CNT0_MASK              (0x0Fu)
#define mSerial_EPX_CNTX_MSB_MASK          (0x07u)
#define mSerial_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define mSerial_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define mSerial_EPX_CNTX_CRC_COUNT         (0x02u)
#define mSerial_EPX_DATA_BUF_MAX           (512u)

#define mSerial_CR0_ENABLE                 (0x80u)

/* A 100 KHz clock is used for BUS reset count. Recommended is to count 10 pulses */
#define mSerial_BUS_RST_COUNT              (0x0au)

#define mSerial_USBIO_CR1_IOMODE           (0x20u)
#define mSerial_USBIO_CR1_USBPUEN          (0x04u)
#define mSerial_USBIO_CR1_DP0              (0x02u)
#define mSerial_USBIO_CR1_DM0              (0x01u)

#define mSerial_USBIO_CR0_TEN              (0x80u)
#define mSerial_USBIO_CR0_TSE0             (0x40u)
#define mSerial_USBIO_CR0_TD               (0x20u)
#define mSerial_USBIO_CR0_RD               (0x01u)

#define mSerial_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define mSerial_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define mSerial_FASTCLK_IMO_CR_FX2ON       (0x10u)

#define mSerial_ARB_EPX_CFG_RESET          (0x08u)
#define mSerial_ARB_EPX_CFG_CRC_BYPASS     (0x04u)
#define mSerial_ARB_EPX_CFG_DMA_REQ        (0x02u)
#define mSerial_ARB_EPX_CFG_IN_DATA_RDY    (0x01u)
#define mSerial_ARB_EPX_CFG_DEFAULT        (mSerial_ARB_EPX_CFG_RESET | \
                                                     mSerial_ARB_EPX_CFG_CRC_BYPASS)

#define mSerial_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define mSerial_ARB_EPX_SR_DMA_GNT         (0x02u)
#define mSerial_ARB_EPX_SR_BUF_OVER        (0x04u)
#define mSerial_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define mSerial_ARB_CFG_AUTO_MEM           (0x10u)
#define mSerial_ARB_CFG_MANUAL_DMA         (0x20u)
#define mSerial_ARB_CFG_AUTO_DMA           (0x40u)
#define mSerial_ARB_CFG_CFG_CPM            (0x80u)

#if(mSerial_EP_MM == mSerial__EP_DMAAUTO)
    #define mSerial_ARB_EPX_INT_MASK           (0x1Du)
#else
    #define mSerial_ARB_EPX_INT_MASK           (0x1Fu)
#endif /*  mSerial_EP_MM == mSerial__EP_DMAAUTO */
#define mSerial_ARB_INT_MASK       (uint8)((mSerial_DMA1_REMOVE ^ 1u) | \
                                            (uint8)((mSerial_DMA2_REMOVE ^ 1u) << 1u) | \
                                            (uint8)((mSerial_DMA3_REMOVE ^ 1u) << 2u) | \
                                            (uint8)((mSerial_DMA4_REMOVE ^ 1u) << 3u) | \
                                            (uint8)((mSerial_DMA5_REMOVE ^ 1u) << 4u) | \
                                            (uint8)((mSerial_DMA6_REMOVE ^ 1u) << 5u) | \
                                            (uint8)((mSerial_DMA7_REMOVE ^ 1u) << 6u) | \
                                            (uint8)((mSerial_DMA8_REMOVE ^ 1u) << 7u) )

#define mSerial_SIE_EP_INT_EP1_MASK        (0x01u)
#define mSerial_SIE_EP_INT_EP2_MASK        (0x02u)
#define mSerial_SIE_EP_INT_EP3_MASK        (0x04u)
#define mSerial_SIE_EP_INT_EP4_MASK        (0x08u)
#define mSerial_SIE_EP_INT_EP5_MASK        (0x10u)
#define mSerial_SIE_EP_INT_EP6_MASK        (0x20u)
#define mSerial_SIE_EP_INT_EP7_MASK        (0x40u)
#define mSerial_SIE_EP_INT_EP8_MASK        (0x80u)

#define mSerial_PM_ACT_EN_FSUSB            mSerial_USB__PM_ACT_MSK
#define mSerial_PM_STBY_EN_FSUSB           mSerial_USB__PM_STBY_MSK
#define mSerial_PM_AVAIL_EN_FSUSBIO        (0x10u)

#define mSerial_PM_USB_CR0_REF_EN          (0x01u)
#define mSerial_PM_USB_CR0_PD_N            (0x02u)
#define mSerial_PM_USB_CR0_PD_PULLUP_N     (0x04u)

#define mSerial_USB_CLK_ENABLE             (0x01u)

#define mSerial_DM_MASK                    mSerial_Dm__0__MASK
#define mSerial_DP_MASK                    mSerial_Dp__0__MASK

#define mSerial_DYN_RECONFIG_ENABLE        (0x01u)
#define mSerial_DYN_RECONFIG_EP_SHIFT      (0x01u)
#define mSerial_DYN_RECONFIG_RDY_STS       (0x10u)


#endif /*  CY_USBFS_mSerial_H */


/* [] END OF FILE */
