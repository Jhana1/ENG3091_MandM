/*******************************************************************************
* File Name: OV9650_1_I2C.h
* Version 3.50
*
* Description:
*  This file provides constants and parameter values for the I2C component.

*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_OV9650_1_I2C_H)
#define CY_I2C_OV9650_1_I2C_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check if required defines such as CY_PSOC5LP are available in cy_boot */
#if !defined (CY_PSOC5LP)
    #error Component I2C_v3_50 requires cy_boot v3.10 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define OV9650_1_I2C_IMPLEMENTATION     (1u)
#define OV9650_1_I2C_MODE               (2u)
#define OV9650_1_I2C_ENABLE_WAKEUP      (0u)
#define OV9650_1_I2C_ADDR_DECODE        (1u)
#define OV9650_1_I2C_UDB_INTRN_CLOCK    (0u)


/* I2C implementation enum */
#define OV9650_1_I2C_UDB    (0x00u)
#define OV9650_1_I2C_FF     (0x01u)

#define OV9650_1_I2C_FF_IMPLEMENTED     (OV9650_1_I2C_FF  == OV9650_1_I2C_IMPLEMENTATION)
#define OV9650_1_I2C_UDB_IMPLEMENTED    (OV9650_1_I2C_UDB == OV9650_1_I2C_IMPLEMENTATION)

#define OV9650_1_I2C_UDB_INTRN_CLOCK_ENABLED    (OV9650_1_I2C_UDB_IMPLEMENTED && \
                                                     (0u != OV9650_1_I2C_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define OV9650_1_I2C_MODE_SLAVE                 (0x01u)
#define OV9650_1_I2C_MODE_MASTER                (0x02u)
#define OV9650_1_I2C_MODE_MULTI_MASTER          (0x06u)
#define OV9650_1_I2C_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define OV9650_1_I2C_MODE_MULTI_MASTER_MASK     (0x04u)

#define OV9650_1_I2C_MODE_SLAVE_ENABLED         (0u != (OV9650_1_I2C_MODE_SLAVE  & OV9650_1_I2C_MODE))
#define OV9650_1_I2C_MODE_MASTER_ENABLED        (0u != (OV9650_1_I2C_MODE_MASTER & OV9650_1_I2C_MODE))
#define OV9650_1_I2C_MODE_MULTI_MASTER_ENABLED  (0u != (OV9650_1_I2C_MODE_MULTI_MASTER_MASK & \
                                                            OV9650_1_I2C_MODE))
#define OV9650_1_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED    (OV9650_1_I2C_MODE_MULTI_MASTER_SLAVE == \
                                                             OV9650_1_I2C_MODE)

/* Address detection enum */
#define OV9650_1_I2C_SW_DECODE      (0x00u)
#define OV9650_1_I2C_HW_DECODE      (0x01u)

#define OV9650_1_I2C_SW_ADRR_DECODE             (OV9650_1_I2C_SW_DECODE == OV9650_1_I2C_ADDR_DECODE)
#define OV9650_1_I2C_HW_ADRR_DECODE             (OV9650_1_I2C_HW_DECODE == OV9650_1_I2C_ADDR_DECODE)

/* Wakeup enabled */
#define OV9650_1_I2C_WAKEUP_ENABLED             (0u != OV9650_1_I2C_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define OV9650_1_I2C_BOOTLOADER_INTERFACE_ENABLED   (OV9650_1_I2C_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_OV9650_1_I2C) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define OV9650_1_I2C_TIMEOUT_ENABLE             (0u)
#define OV9650_1_I2C_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define OV9650_1_I2C_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define OV9650_1_I2C_TIMEOUT_PRESCALER_ENABLE   (0u)
#define OV9650_1_I2C_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define OV9650_1_I2C_TIMEOUT_ENABLED            (0u != OV9650_1_I2C_TIMEOUT_ENABLE)
#define OV9650_1_I2C_TIMEOUT_SCL_TMOUT_ENABLED  (0u != OV9650_1_I2C_TIMEOUT_SCL_TMOUT_ENABLE)
#define OV9650_1_I2C_TIMEOUT_SDA_TMOUT_ENABLED  (0u != OV9650_1_I2C_TIMEOUT_SDA_TMOUT_ENABLE)
#define OV9650_1_I2C_TIMEOUT_PRESCALER_ENABLED  (0u != OV9650_1_I2C_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define OV9650_1_I2C_TIMEOUT_UDB    (0x00u)
#define OV9650_1_I2C_TIMEOUT_FF     (0x01u)

#define OV9650_1_I2C_TIMEOUT_FF_IMPLEMENTED     (OV9650_1_I2C_TIMEOUT_FF  == \
                                                        OV9650_1_I2C_TIMEOUT_IMPLEMENTATION)
#define OV9650_1_I2C_TIMEOUT_UDB_IMPLEMENTED    (OV9650_1_I2C_TIMEOUT_UDB == \
                                                        OV9650_1_I2C_TIMEOUT_IMPLEMENTATION)

#define OV9650_1_I2C_TIMEOUT_FF_ENABLED         (OV9650_1_I2C_TIMEOUT_ENABLED && \
                                                     OV9650_1_I2C_TIMEOUT_FF_IMPLEMENTED)

#define OV9650_1_I2C_TIMEOUT_UDB_ENABLED        (OV9650_1_I2C_TIMEOUT_ENABLED && \
                                                     OV9650_1_I2C_TIMEOUT_UDB_IMPLEMENTED)

#define OV9650_1_I2C_EXTERN_I2C_INTR_HANDLER    (0u)
#define OV9650_1_I2C_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define OV9650_1_I2C_INTERN_I2C_INTR_HANDLER    (0u == OV9650_1_I2C_EXTERN_I2C_INTR_HANDLER)
#define OV9650_1_I2C_INTERN_TMOUT_INTR_HANDLER  (0u == OV9650_1_I2C_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    uint8 xcfg;
    uint8 cfg;
    uint8 addr;
    uint8 clkDiv1;
    uint8 clkDiv2;
#else
    uint8 control;
#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */

#if (OV9650_1_I2C_TIMEOUT_ENABLED)
    uint16 tmoutCfg;
    uint8  tmoutIntr;
#endif /* (OV9650_1_I2C_TIMEOUT_ENABLED) */

} OV9650_1_I2C_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void OV9650_1_I2C_Init(void)                            ;
void OV9650_1_I2C_Enable(void)                          ;

void OV9650_1_I2C_Start(void)                           ;
void OV9650_1_I2C_Stop(void)                            ;

#define OV9650_1_I2C_EnableInt()        CyIntEnable      (OV9650_1_I2C_ISR_NUMBER)
#define OV9650_1_I2C_DisableInt()       CyIntDisable     (OV9650_1_I2C_ISR_NUMBER)
#define OV9650_1_I2C_ClearPendingInt()  CyIntClearPending(OV9650_1_I2C_ISR_NUMBER)
#define OV9650_1_I2C_SetPendingInt()    CyIntSetPending  (OV9650_1_I2C_ISR_NUMBER)

void OV9650_1_I2C_SaveConfig(void)                      ;
void OV9650_1_I2C_Sleep(void)                           ;
void OV9650_1_I2C_RestoreConfig(void)                   ;
void OV9650_1_I2C_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if (OV9650_1_I2C_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 OV9650_1_I2C_MasterStatus(void)                ;
    uint8 OV9650_1_I2C_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 OV9650_1_I2C_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 OV9650_1_I2C_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 OV9650_1_I2C_MasterGetReadBufSize(void)       ;
    uint8 OV9650_1_I2C_MasterGetWriteBufSize(void)      ;
    void  OV9650_1_I2C_MasterClearReadBuf(void)         ;
    void  OV9650_1_I2C_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 OV9650_1_I2C_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 OV9650_1_I2C_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 OV9650_1_I2C_MasterSendStop(void)             ;
    uint8 OV9650_1_I2C_MasterWriteByte(uint8 theByte)   ;
    uint8 OV9650_1_I2C_MasterReadByte(uint8 acknNak)    ;

#endif /* (OV9650_1_I2C_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 OV9650_1_I2C_SlaveStatus(void)                ;
    uint8 OV9650_1_I2C_SlaveClearReadStatus(void)       ;
    uint8 OV9650_1_I2C_SlaveClearWriteStatus(void)      ;

    void  OV9650_1_I2C_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  OV9650_1_I2C_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  OV9650_1_I2C_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 OV9650_1_I2C_SlaveGetReadBufSize(void)        ;
    uint8 OV9650_1_I2C_SlaveGetWriteBufSize(void)       ;
    void  OV9650_1_I2C_SlaveClearReadBuf(void)          ;
    void  OV9650_1_I2C_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (OV9650_1_I2C_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     OV9650_1_I2C_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     OV9650_1_I2C_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     OV9650_1_I2C_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus OV9650_1_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus OV9650_1_I2C_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_OV9650_1_I2C)
            #define CyBtldrCommStart    OV9650_1_I2C_CyBtldrCommStart
            #define CyBtldrCommStop     OV9650_1_I2C_CyBtldrCommStop
            #define CyBtldrCommReset    OV9650_1_I2C_CyBtldrCommReset
            #define CyBtldrCommWrite    OV9650_1_I2C_CyBtldrCommWrite
            #define CyBtldrCommRead     OV9650_1_I2C_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_OV9650_1_I2C) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define OV9650_1_I2C_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define OV9650_1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define OV9650_1_I2C_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define OV9650_1_I2C_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (OV9650_1_I2C_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

/* Component interrupt handlers */
CY_ISR_PROTO(OV9650_1_I2C_ISR);
#if ((OV9650_1_I2C_FF_IMPLEMENTED) || (OV9650_1_I2C_WAKEUP_ENABLED))
    CY_ISR_PROTO(OV9650_1_I2C_WAKEUP_ISR);
#endif /* ((OV9650_1_I2C_FF_IMPLEMENTED) || (OV9650_1_I2C_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 OV9650_1_I2C_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define OV9650_1_I2C_DATA_RATE          (400u)
#define OV9650_1_I2C_DEFAULT_ADDR       (8u)
#define OV9650_1_I2C_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define OV9650_1_I2C_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define OV9650_1_I2C_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define OV9650_1_I2C_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define OV9650_1_I2C_I2C1_SIO_PAIR  (OV9650_1_I2C_I2C_PAIR1 == OV9650_1_I2C_I2C_PAIR_SELECTED)
#define OV9650_1_I2C_I2C0_SIO_PAIR  (OV9650_1_I2C_I2C_PAIR0 == OV9650_1_I2C_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define OV9650_1_I2C_READ_XFER_MODE     (0x01u) /* Read */
#define OV9650_1_I2C_WRITE_XFER_MODE    (0x00u) /* Write */
#define OV9650_1_I2C_ACK_DATA           (0x01u) /* Send ACK */
#define OV9650_1_I2C_NAK_DATA           (0x00u) /* Send NAK */
#define OV9650_1_I2C_OVERFLOW_RETURN    (0xFFu) /* Send on bus in case of overflow */

#if (OV9650_1_I2C_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define OV9650_1_I2C_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define OV9650_1_I2C_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define OV9650_1_I2C_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define OV9650_1_I2C_MSTAT_CLEAR            (0x00u) /* Clear (initialize) status value */

    #define OV9650_1_I2C_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define OV9650_1_I2C_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define OV9650_1_I2C_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define OV9650_1_I2C_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define OV9650_1_I2C_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define OV9650_1_I2C_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define OV9650_1_I2C_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define OV9650_1_I2C_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define OV9650_1_I2C_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define OV9650_1_I2C_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define OV9650_1_I2C_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define OV9650_1_I2C_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define OV9650_1_I2C_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define OV9650_1_I2C_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define OV9650_1_I2C_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (OV9650_1_I2C_MODE_MASTER_ENABLED) */

#if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define OV9650_1_I2C_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define OV9650_1_I2C_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define OV9650_1_I2C_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define OV9650_1_I2C_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define OV9650_1_I2C_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define OV9650_1_I2C_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define OV9650_1_I2C_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define OV9650_1_I2C_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define OV9650_1_I2C_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define OV9650_1_I2C_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define OV9650_1_I2C_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define OV9650_1_I2C_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  OV9650_1_I2C_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  OV9650_1_I2C_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  OV9650_1_I2C_SM_SLAVE          (OV9650_1_I2C_SM_IDLE) /* Any Slave state */
#define  OV9650_1_I2C_SM_SL_WR_DATA     (0x11u) /* Master writes data to slave  */
#define  OV9650_1_I2C_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  OV9650_1_I2C_SM_MASTER         (0x40u) /* Any master state */

#define  OV9650_1_I2C_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  OV9650_1_I2C_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  OV9650_1_I2C_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  OV9650_1_I2C_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  OV9650_1_I2C_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  OV9650_1_I2C_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  OV9650_1_I2C_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define OV9650_1_I2C_CHECK_SM_MASTER    (0u != (OV9650_1_I2C_SM_MASTER & OV9650_1_I2C_state))
#define OV9650_1_I2C_CHECK_SM_SLAVE     (0u != (OV9650_1_I2C_SM_SLAVE  & OV9650_1_I2C_state))


/***************************************
*              Registers
***************************************/

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define OV9650_1_I2C_XCFG_REG           (*(reg8 *) OV9650_1_I2C_I2C_FF__XCFG)
    #define OV9650_1_I2C_XCFG_PTR           ( (reg8 *) OV9650_1_I2C_I2C_FF__XCFG)

    #define OV9650_1_I2C_ADDR_REG           (*(reg8 *) OV9650_1_I2C_I2C_FF__ADR)
    #define OV9650_1_I2C_ADDR_PTR           ( (reg8 *) OV9650_1_I2C_I2C_FF__ADR)

    #define OV9650_1_I2C_CFG_REG            (*(reg8 *) OV9650_1_I2C_I2C_FF__CFG)
    #define OV9650_1_I2C_CFG_PTR            ( (reg8 *) OV9650_1_I2C_I2C_FF__CFG)

    #define OV9650_1_I2C_CSR_REG            (*(reg8 *) OV9650_1_I2C_I2C_FF__CSR)
    #define OV9650_1_I2C_CSR_PTR            ( (reg8 *) OV9650_1_I2C_I2C_FF__CSR)

    #define OV9650_1_I2C_DATA_REG           (*(reg8 *) OV9650_1_I2C_I2C_FF__D)
    #define OV9650_1_I2C_DATA_PTR           ( (reg8 *) OV9650_1_I2C_I2C_FF__D)

    #define OV9650_1_I2C_MCSR_REG           (*(reg8 *) OV9650_1_I2C_I2C_FF__MCSR)
    #define OV9650_1_I2C_MCSR_PTR           ( (reg8 *) OV9650_1_I2C_I2C_FF__MCSR)

    #define OV9650_1_I2C_ACT_PWRMGR_REG     (*(reg8 *) OV9650_1_I2C_I2C_FF__PM_ACT_CFG)
    #define OV9650_1_I2C_ACT_PWRMGR_PTR     ( (reg8 *) OV9650_1_I2C_I2C_FF__PM_ACT_CFG)
    #define OV9650_1_I2C_ACT_PWR_EN         ( (uint8)  OV9650_1_I2C_I2C_FF__PM_ACT_MSK)

    #define OV9650_1_I2C_STBY_PWRMGR_REG    (*(reg8 *) OV9650_1_I2C_I2C_FF__PM_STBY_CFG)
    #define OV9650_1_I2C_STBY_PWRMGR_PTR    ( (reg8 *) OV9650_1_I2C_I2C_FF__PM_STBY_CFG)
    #define OV9650_1_I2C_STBY_PWR_EN        ( (uint8)  OV9650_1_I2C_I2C_FF__PM_STBY_MSK)

    #define OV9650_1_I2C_PWRSYS_CR1_REG     (*(reg8 *) CYREG_PWRSYS_CR1)
    #define OV9650_1_I2C_PWRSYS_CR1_PTR     ( (reg8 *) CYREG_PWRSYS_CR1)

    #define OV9650_1_I2C_CLKDIV1_REG    (*(reg8 *) OV9650_1_I2C_I2C_FF__CLK_DIV1)
    #define OV9650_1_I2C_CLKDIV1_PTR    ( (reg8 *) OV9650_1_I2C_I2C_FF__CLK_DIV1)

    #define OV9650_1_I2C_CLKDIV2_REG    (*(reg8 *) OV9650_1_I2C_I2C_FF__CLK_DIV2)
    #define OV9650_1_I2C_CLKDIV2_PTR    ( (reg8 *) OV9650_1_I2C_I2C_FF__CLK_DIV2)

#else
    /* UDB implementation registers */
    #define OV9650_1_I2C_CFG_REG \
            (*(reg8 *) OV9650_1_I2C_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)
    #define OV9650_1_I2C_CFG_PTR \
            ( (reg8 *) OV9650_1_I2C_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)

    #define OV9650_1_I2C_CSR_REG        (*(reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__STATUS_REG)
    #define OV9650_1_I2C_CSR_PTR        ( (reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__STATUS_REG)

    #define OV9650_1_I2C_INT_MASK_REG   (*(reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__MASK_REG)
    #define OV9650_1_I2C_INT_MASK_PTR   ( (reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__MASK_REG)

    #define OV9650_1_I2C_INT_ENABLE_REG (*(reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define OV9650_1_I2C_INT_ENABLE_PTR ( (reg8 *) OV9650_1_I2C_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define OV9650_1_I2C_DATA_REG       (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__A0_REG)
    #define OV9650_1_I2C_DATA_PTR       ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__A0_REG)

    #define OV9650_1_I2C_GO_REG         (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__F1_REG)
    #define OV9650_1_I2C_GO_PTR         ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__F1_REG)

    #define OV9650_1_I2C_GO_DONE_REG    (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__A1_REG)
    #define OV9650_1_I2C_GO_DONE_PTR    ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__A1_REG)

    #define OV9650_1_I2C_MCLK_PRD_REG   (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define OV9650_1_I2C_MCLK_PRD_PTR   ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define OV9650_1_I2C_MCLK_CMP_REG   (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define OV9650_1_I2C_MCLK_CMP_PTR   ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if (OV9650_1_I2C_MODE_SLAVE_ENABLED)
        #define OV9650_1_I2C_ADDR_REG       (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__D0_REG)
        #define OV9650_1_I2C_ADDR_PTR       ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Shifter_u0__D0_REG)

        #define OV9650_1_I2C_PERIOD_REG     (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define OV9650_1_I2C_PERIOD_PTR     ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define OV9650_1_I2C_COUNTER_REG    (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define OV9650_1_I2C_COUNTER_PTR    ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define OV9650_1_I2C_COUNTER_AUX_CTL_REG \
                                    (*(reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define OV9650_1_I2C_COUNTER_AUX_CTL_PTR \
                                    ( (reg8 *) OV9650_1_I2C_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (OV9650_1_I2C_MODE_SLAVE_ENABLED) */

#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* OV9650_1_I2C_I2C_IRQ */
#define OV9650_1_I2C_ISR_NUMBER     ((uint8) OV9650_1_I2C_I2C_IRQ__INTC_NUMBER)
#define OV9650_1_I2C_ISR_PRIORITY   ((uint8) OV9650_1_I2C_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define OV9650_1_I2C_SLAVE_ADDR_MASK    (0x7Fu)
#define OV9650_1_I2C_SLAVE_ADDR_SHIFT   (0x01u)
#define OV9650_1_I2C_DATA_MASK          (0xFFu)
#define OV9650_1_I2C_READ_FLAG          (0x01u)

/* Block reset constants */
#define OV9650_1_I2C_CLEAR_REG          (0x00u)
#define OV9650_1_I2C_BLOCK_RESET_DELAY  (2u)
#define OV9650_1_I2C_FF_RESET_DELAY     (OV9650_1_I2C_BLOCK_RESET_DELAY)
#define OV9650_1_I2C_RESTORE_TIMEOUT    (255u)

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define OV9650_1_I2C_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define OV9650_1_I2C_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define OV9650_1_I2C_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define OV9650_1_I2C_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incoming transactions */
    #define OV9650_1_I2C_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define OV9650_1_I2C_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define OV9650_1_I2C_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define OV9650_1_I2C_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define OV9650_1_I2C_CFG_PSELECT        (0x40u) /* Pin Select */
    #define OV9650_1_I2C_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define OV9650_1_I2C_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define OV9650_1_I2C_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select */
    #define OV9650_1_I2C_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define OV9650_1_I2C_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define OV9650_1_I2C_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define OV9650_1_I2C_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define OV9650_1_I2C_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define OV9650_1_I2C_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define OV9650_1_I2C_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define OV9650_1_I2C_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define OV9650_1_I2C_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occurred */
    #define OV9650_1_I2C_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define OV9650_1_I2C_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define OV9650_1_I2C_CSR_ACK            (0x10u) /* ACK response */
    #define OV9650_1_I2C_CSR_NAK            (0x00u) /* NAK response */
    #define OV9650_1_I2C_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define OV9650_1_I2C_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define OV9650_1_I2C_CSR_LRB            (0x02u) /* Last received bit */
    #define OV9650_1_I2C_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define OV9650_1_I2C_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define OV9650_1_I2C_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define OV9650_1_I2C_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define OV9650_1_I2C_CSR_RDY_TO_RD      (0x00u) /* Set to receive mode */

    /* MCSR I2C Master Control and Status Register */
    #define OV9650_1_I2C_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define OV9650_1_I2C_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define OV9650_1_I2C_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define OV9650_1_I2C_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define OV9650_1_I2C_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* PWRSYS_CR1 to handle Sleep */
    #define OV9650_1_I2C_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define OV9650_1_I2C_CTRL_START_SHIFT           (7u)
    #define OV9650_1_I2C_CTRL_STOP_SHIFT            (6u)
    #define OV9650_1_I2C_CTRL_RESTART_SHIFT         (5u)
    #define OV9650_1_I2C_CTRL_NACK_SHIFT            (4u)
    #define OV9650_1_I2C_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define OV9650_1_I2C_CTRL_TRANSMIT_SHIFT        (2u)
    #define OV9650_1_I2C_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define OV9650_1_I2C_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define OV9650_1_I2C_CTRL_START_MASK            ((uint8) (0x01u << OV9650_1_I2C_CTRL_START_SHIFT))
    #define OV9650_1_I2C_CTRL_STOP_MASK             ((uint8) (0x01u << OV9650_1_I2C_CTRL_STOP_SHIFT))
    #define OV9650_1_I2C_CTRL_RESTART_MASK          ((uint8) (0x01u << OV9650_1_I2C_CTRL_RESTART_SHIFT))
    #define OV9650_1_I2C_CTRL_NACK_MASK             ((uint8) (0x01u << OV9650_1_I2C_CTRL_NACK_SHIFT))
    #define OV9650_1_I2C_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << OV9650_1_I2C_CTRL_ANY_ADDRESS_SHIFT))
    #define OV9650_1_I2C_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << OV9650_1_I2C_CTRL_TRANSMIT_SHIFT))
    #define OV9650_1_I2C_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << OV9650_1_I2C_CTRL_ENABLE_MASTER_SHIFT))
    #define OV9650_1_I2C_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << OV9650_1_I2C_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define OV9650_1_I2C_STS_LOST_ARB_SHIFT         (6u)
    #define OV9650_1_I2C_STS_STOP_SHIFT             (5u)
    #define OV9650_1_I2C_STS_BUSY_SHIFT             (4u)
    #define OV9650_1_I2C_STS_ADDR_SHIFT             (3u)
    #define OV9650_1_I2C_STS_MASTER_MODE_SHIFT      (2u)
    #define OV9650_1_I2C_STS_LRB_SHIFT              (1u)
    #define OV9650_1_I2C_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define OV9650_1_I2C_STS_LOST_ARB_MASK          ((uint8) (0x01u << OV9650_1_I2C_STS_LOST_ARB_SHIFT))
    #define OV9650_1_I2C_STS_STOP_MASK              ((uint8) (0x01u << OV9650_1_I2C_STS_STOP_SHIFT))
    #define OV9650_1_I2C_STS_BUSY_MASK              ((uint8) (0x01u << OV9650_1_I2C_STS_BUSY_SHIFT))
    #define OV9650_1_I2C_STS_ADDR_MASK              ((uint8) (0x01u << OV9650_1_I2C_STS_ADDR_SHIFT))
    #define OV9650_1_I2C_STS_MASTER_MODE_MASK       ((uint8) (0x01u << OV9650_1_I2C_STS_MASTER_MODE_SHIFT))
    #define OV9650_1_I2C_STS_LRB_MASK               ((uint8) (0x01u << OV9650_1_I2C_STS_LRB_SHIFT))
    #define OV9650_1_I2C_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << OV9650_1_I2C_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define OV9650_1_I2C_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter */
    #define OV9650_1_I2C_INT_ENABLE_MASK            (0x10u) /* Enable interrupt from status register */
    #define OV9650_1_I2C_CNT7_ENABLE                (OV9650_1_I2C_COUNTER_ENABLE_MASK)
    #define OV9650_1_I2C_INTR_ENABLE                (OV9650_1_I2C_INT_ENABLE_MASK)

#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define OV9650_1_I2C_CHECK_ADDR_ACK(csr)    ((OV9650_1_I2C_CSR_LRB_ACK | OV9650_1_I2C_CSR_ADDRESS) == \
                                                 ((OV9650_1_I2C_CSR_LRB    | OV9650_1_I2C_CSR_ADDRESS) &  \
                                                  (csr)))


#define OV9650_1_I2C_CHECK_ADDR_NAK(csr)    ((OV9650_1_I2C_CSR_LRB_NAK | OV9650_1_I2C_CSR_ADDRESS) == \
                                                 ((OV9650_1_I2C_CSR_LRB    | OV9650_1_I2C_CSR_ADDRESS) &  \
                                                  (csr)))

#define OV9650_1_I2C_CHECK_DATA_ACK(csr)    (0u == ((csr) & OV9650_1_I2C_CSR_LRB_NAK))

/* MCSR conditions check */
#define OV9650_1_I2C_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & OV9650_1_I2C_MCSR_BUS_BUSY))
#define OV9650_1_I2C_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & OV9650_1_I2C_MCSR_MSTR_MODE))

/* CSR conditions check */
#define OV9650_1_I2C_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & OV9650_1_I2C_CSR_BYTE_COMPLETE))
#define OV9650_1_I2C_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (OV9650_1_I2C_CSR_BYTE_COMPLETE | \
                                                                     OV9650_1_I2C_CSR_STOP_STATUS)))
#define OV9650_1_I2C_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & OV9650_1_I2C_CSR_BYTE_COMPLETE))
#define OV9650_1_I2C_CHECK_STOP_STS(csr)        (0u != ((csr) & OV9650_1_I2C_CSR_STOP_STATUS))
#define OV9650_1_I2C_CHECK_LOST_ARB(csr)        (0u != ((csr) & OV9650_1_I2C_CSR_LOST_ARB))
#define OV9650_1_I2C_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & OV9650_1_I2C_CSR_ADDRESS))

/* Software start and end of transaction check */
#define OV9650_1_I2C_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & OV9650_1_I2C_MODE_REPEAT_START))
#define OV9650_1_I2C_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & OV9650_1_I2C_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define OV9650_1_I2C_GET_MSTAT_CMPLT ((0u != (OV9650_1_I2C_state & OV9650_1_I2C_SM_MSTR_RD)) ? \
                                                 (OV9650_1_I2C_MSTAT_RD_CMPLT) : (OV9650_1_I2C_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address */
#define OV9650_1_I2C_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> OV9650_1_I2C_SLAVE_ADDR_SHIFT) & \
                                                                  OV9650_1_I2C_SLAVE_ADDR_MASK)

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    /* Check enable of module */
    #define OV9650_1_I2C_I2C_ENABLE_REG     (OV9650_1_I2C_ACT_PWRMGR_REG)
    #define OV9650_1_I2C_IS_I2C_ENABLE(reg) (0u != ((reg) & OV9650_1_I2C_ACT_PWR_EN))
    #define OV9650_1_I2C_IS_ENABLED         (0u != (OV9650_1_I2C_ACT_PWRMGR_REG & OV9650_1_I2C_ACT_PWR_EN))

    #define OV9650_1_I2C_CHECK_PWRSYS_I2C_BACKUP    (0u != (OV9650_1_I2C_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                OV9650_1_I2C_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define OV9650_1_I2C_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & OV9650_1_I2C_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & OV9650_1_I2C_MCSR_MSTR_MODE)))

    #define OV9650_1_I2C_CLEAR_START_GEN        do{ \
                                                        OV9650_1_I2C_MCSR_REG &=                                   \
                                                                           ((uint8) ~OV9650_1_I2C_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define OV9650_1_I2C_ENABLE_INT_ON_STOP     do{ \
                                                        OV9650_1_I2C_CFG_REG |= OV9650_1_I2C_CFG_STOP_IE; \
                                                    }while(0)

    #define OV9650_1_I2C_DISABLE_INT_ON_STOP    do{ \
                                                        OV9650_1_I2C_CFG_REG &=                                 \
                                                                           ((uint8) ~OV9650_1_I2C_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define OV9650_1_I2C_TRANSMIT_DATA          do{ \
                                                        OV9650_1_I2C_CSR_REG = OV9650_1_I2C_CSR_TRANSMIT; \
                                                    }while(0)

    #define OV9650_1_I2C_ACK_AND_TRANSMIT       do{ \
                                                        OV9650_1_I2C_CSR_REG = (OV9650_1_I2C_CSR_ACK |      \
                                                                                    OV9650_1_I2C_CSR_TRANSMIT); \
                                                    }while(0)

    #define OV9650_1_I2C_NAK_AND_TRANSMIT       do{ \
                                                        OV9650_1_I2C_CSR_REG = OV9650_1_I2C_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define OV9650_1_I2C_ACKNAK_AND_TRANSMIT    do{ \
                                                        OV9650_1_I2C_CSR_REG  = (OV9650_1_I2C_CSR_NAK |      \
                                                                                     OV9650_1_I2C_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define OV9650_1_I2C_ACK_AND_RECEIVE        do{ \
                                                        OV9650_1_I2C_CSR_REG = OV9650_1_I2C_CSR_ACK; \
                                                    }while(0)

    #define OV9650_1_I2C_NAK_AND_RECEIVE        do{ \
                                                        OV9650_1_I2C_CSR_REG = OV9650_1_I2C_CSR_NAK; \
                                                    }while(0)

    #define OV9650_1_I2C_READY_TO_READ          do{ \
                                                        OV9650_1_I2C_CSR_REG = OV9650_1_I2C_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Release bus after lost arbitration */
    #define OV9650_1_I2C_BUS_RELEASE    OV9650_1_I2C_READY_TO_READ

    /* Master Start/ReStart/Stop conditions generation */
    #define OV9650_1_I2C_GENERATE_START         do{ \
                                                        OV9650_1_I2C_MCSR_REG = OV9650_1_I2C_MCSR_START_GEN; \
                                                    }while(0)

    #define OV9650_1_I2C_GENERATE_RESTART \
                    do{                       \
                        OV9650_1_I2C_MCSR_REG = (OV9650_1_I2C_MCSR_RESTART_GEN | \
                                                     OV9650_1_I2C_MCSR_STOP_GEN);    \
                        OV9650_1_I2C_CSR_REG  = OV9650_1_I2C_CSR_TRANSMIT;       \
                    }while(0)

    #define OV9650_1_I2C_GENERATE_STOP \
                    do{                    \
                        OV9650_1_I2C_MCSR_REG = OV9650_1_I2C_MCSR_STOP_GEN; \
                        OV9650_1_I2C_CSR_REG  = OV9650_1_I2C_CSR_TRANSMIT;  \
                    }while(0)

    /* Master manual APIs compatible defines */
    #define OV9650_1_I2C_GENERATE_START_MANUAL      OV9650_1_I2C_GENERATE_START
    #define OV9650_1_I2C_GENERATE_RESTART_MANUAL    OV9650_1_I2C_GENERATE_RESTART
    #define OV9650_1_I2C_GENERATE_STOP_MANUAL       OV9650_1_I2C_GENERATE_STOP
    #define OV9650_1_I2C_TRANSMIT_DATA_MANUAL       OV9650_1_I2C_TRANSMIT_DATA
    #define OV9650_1_I2C_READY_TO_READ_MANUAL       OV9650_1_I2C_READY_TO_READ
    #define OV9650_1_I2C_ACK_AND_RECEIVE_MANUAL     OV9650_1_I2C_ACK_AND_RECEIVE
    #define OV9650_1_I2C_BUS_RELEASE_MANUAL         OV9650_1_I2C_BUS_RELEASE

#else

    /* Masks to enable interrupts from Status register */
    #define OV9650_1_I2C_STOP_IE_MASK           (OV9650_1_I2C_STS_STOP_MASK)
    #define OV9650_1_I2C_BYTE_COMPLETE_IE_MASK  (OV9650_1_I2C_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR register bit-fields */
    #define OV9650_1_I2C_CSR_LOST_ARB       (OV9650_1_I2C_STS_LOST_ARB_MASK)
    #define OV9650_1_I2C_CSR_STOP_STATUS    (OV9650_1_I2C_STS_STOP_MASK)
    #define OV9650_1_I2C_CSR_BUS_ERROR      (0x00u)
    #define OV9650_1_I2C_CSR_ADDRESS        (OV9650_1_I2C_STS_ADDR_MASK)
    #define OV9650_1_I2C_CSR_TRANSMIT       (OV9650_1_I2C_CTRL_TRANSMIT_MASK)
    #define OV9650_1_I2C_CSR_LRB            (OV9650_1_I2C_STS_LRB_MASK)
    #define OV9650_1_I2C_CSR_LRB_NAK        (OV9650_1_I2C_STS_LRB_MASK)
    #define OV9650_1_I2C_CSR_LRB_ACK        (0x00u)
    #define OV9650_1_I2C_CSR_BYTE_COMPLETE  (OV9650_1_I2C_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR registers bit-fields */
    #define OV9650_1_I2C_MCSR_REG           (OV9650_1_I2C_CSR_REG)  /* UDB incorporates master and slave regs */
    #define OV9650_1_I2C_MCSR_BUS_BUSY      (OV9650_1_I2C_STS_BUSY_MASK)      /* Is bus is busy               */
    #define OV9650_1_I2C_MCSR_START_GEN     (OV9650_1_I2C_CTRL_START_MASK)    /* Generate Start condition     */
    #define OV9650_1_I2C_MCSR_RESTART_GEN   (OV9650_1_I2C_CTRL_RESTART_MASK)  /* Generates RESTART condition  */
    #define OV9650_1_I2C_MCSR_MSTR_MODE     (OV9650_1_I2C_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define OV9650_1_I2C_PREPARE_TO_RELEASE (0xFFu)
    #define OV9650_1_I2C_RELEASE_FSM        (0x00u)

    /* Define release command done: history of byte complete status is cleared */
    #define OV9650_1_I2C_WAIT_RELEASE_CMD_DONE  (OV9650_1_I2C_RELEASE_FSM != OV9650_1_I2C_GO_DONE_REG)

    /* Check enable of module */
    #define OV9650_1_I2C_I2C_ENABLE_REG     (OV9650_1_I2C_CFG_REG)
    #define OV9650_1_I2C_IS_I2C_ENABLE(reg) ((0u != ((reg) & OV9650_1_I2C_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & OV9650_1_I2C_ENABLE_SLAVE)))

    #define OV9650_1_I2C_IS_ENABLED         (0u != (OV9650_1_I2C_CFG_REG & OV9650_1_I2C_ENABLE_MS))

    /* Check start condition generation */
    #define OV9650_1_I2C_CHECK_START_GEN(mcsr)  ((0u != (OV9650_1_I2C_CFG_REG &        \
                                                             OV9650_1_I2C_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & OV9650_1_I2C_MCSR_MSTR_MODE)))

    #define OV9650_1_I2C_CLEAR_START_GEN        do{ \
                                                        OV9650_1_I2C_CFG_REG &=                 \
                                                        ((uint8) ~OV9650_1_I2C_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define OV9650_1_I2C_ENABLE_INT_ON_STOP     do{ \
                                                       OV9650_1_I2C_INT_MASK_REG |= OV9650_1_I2C_STOP_IE_MASK; \
                                                    }while(0)

    #define OV9650_1_I2C_DISABLE_INT_ON_STOP    do{ \
                                                        OV9650_1_I2C_INT_MASK_REG &=                               \
                                                                             ((uint8) ~OV9650_1_I2C_STOP_IE_MASK); \
                                                    }while(0)

    /* Transmit data */
    #define OV9650_1_I2C_TRANSMIT_DATA \
                                    do{    \
                                        OV9650_1_I2C_CFG_REG     = (OV9650_1_I2C_CTRL_TRANSMIT_MASK | \
                                                                       OV9650_1_I2C_CTRL_DEFAULT);        \
                                        OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE;   \
                                        OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;          \
                                    }while(0)

    #define OV9650_1_I2C_ACK_AND_TRANSMIT   OV9650_1_I2C_TRANSMIT_DATA

    #define OV9650_1_I2C_NAK_AND_TRANSMIT \
                                        do{   \
                                            OV9650_1_I2C_CFG_REG     = (OV9650_1_I2C_CTRL_NACK_MASK     | \
                                                                            OV9650_1_I2C_CTRL_TRANSMIT_MASK | \
                                                                            OV9650_1_I2C_CTRL_DEFAULT);       \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE;   \
                                            OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;          \
                                        }while(0)

    /* Receive data */
    #define OV9650_1_I2C_READY_TO_READ  \
                                        do{ \
                                            OV9650_1_I2C_CFG_REG     = OV9650_1_I2C_CTRL_DEFAULT;       \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE; \
                                            OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;       \
                                        }while(0)

    #define OV9650_1_I2C_ACK_AND_RECEIVE    OV9650_1_I2C_READY_TO_READ

    /* Release bus after arbitration is lost */
    #define OV9650_1_I2C_BUS_RELEASE    OV9650_1_I2C_READY_TO_READ

    #define OV9650_1_I2C_NAK_AND_RECEIVE \
                                        do{  \
                                            OV9650_1_I2C_CFG_REG     = (OV9650_1_I2C_CTRL_NACK_MASK |   \
                                                                            OV9650_1_I2C_CTRL_DEFAULT);     \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE; \
                                            OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;       \
                                        }while(0)

    /* Master condition generation */
    #define OV9650_1_I2C_GENERATE_START \
                                        do{ \
                                            OV9650_1_I2C_CFG_REG     = (OV9650_1_I2C_CTRL_START_MASK |  \
                                                                            OV9650_1_I2C_CTRL_DEFAULT);     \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE; \
                                            OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;       \
                                        }while(0)

    #define OV9650_1_I2C_GENERATE_RESTART \
                                        do{   \
                                            OV9650_1_I2C_CFG_REG     = (OV9650_1_I2C_CTRL_RESTART_MASK | \
                                                                            OV9650_1_I2C_CTRL_NACK_MASK    | \
                                                                            OV9650_1_I2C_CTRL_DEFAULT);      \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE;  \
                                            OV9650_1_I2C_GO_REG  =     OV9650_1_I2C_RELEASE_FSM;         \
                                        }while(0)

    #define OV9650_1_I2C_GENERATE_STOP  \
                                        do{ \
                                            OV9650_1_I2C_CFG_REG    = (OV9650_1_I2C_CTRL_NACK_MASK |    \
                                                                           OV9650_1_I2C_CTRL_STOP_MASK |    \
                                                                           OV9650_1_I2C_CTRL_DEFAULT);      \
                                            OV9650_1_I2C_GO_DONE_REG = OV9650_1_I2C_PREPARE_TO_RELEASE; \
                                            OV9650_1_I2C_GO_REG      = OV9650_1_I2C_RELEASE_FSM;        \
                                        }while(0)

    /* Master manual APIs compatible macros */
    /* These macros wait until byte complete history is cleared after command issued */
    #define OV9650_1_I2C_GENERATE_START_MANUAL \
                                        do{ \
                                            OV9650_1_I2C_GENERATE_START;                  \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)
                                        
    #define OV9650_1_I2C_GENERATE_RESTART_MANUAL \
                                        do{          \
                                            OV9650_1_I2C_GENERATE_RESTART;                \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define OV9650_1_I2C_GENERATE_STOP_MANUAL \
                                        do{       \
                                            OV9650_1_I2C_GENERATE_STOP;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define OV9650_1_I2C_TRANSMIT_DATA_MANUAL \
                                        do{       \
                                            OV9650_1_I2C_TRANSMIT_DATA;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define OV9650_1_I2C_READY_TO_READ_MANUAL \
                                        do{       \
                                            OV9650_1_I2C_READY_TO_READ;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define OV9650_1_I2C_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            OV9650_1_I2C_ACK_AND_RECEIVE;                 \
                                            /* Wait until byte complete history is cleared */ \
                                            while(OV9650_1_I2C_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define OV9650_1_I2C_BUS_RELEASE_MANUAL OV9650_1_I2C_READY_TO_READ_MANUAL

#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */


/***************************************
*     Default register init constants
***************************************/

#define OV9650_1_I2C_DISABLE    (0u)
#define OV9650_1_I2C_ENABLE     (1u)

#if (OV9650_1_I2C_FF_IMPLEMENTED)
    /* OV9650_1_I2C_XCFG_REG: bits definition */
    #define OV9650_1_I2C_DEFAULT_XCFG_HW_ADDR_EN ((OV9650_1_I2C_HW_ADRR_DECODE) ? \
                                                        (OV9650_1_I2C_XCFG_HDWR_ADDR_EN) : (0u))

    #define OV9650_1_I2C_DEFAULT_XCFG_I2C_ON    ((OV9650_1_I2C_WAKEUP_ENABLED) ? \
                                                        (OV9650_1_I2C_XCFG_I2C_ON) : (0u))


    #define OV9650_1_I2C_DEFAULT_CFG_SIO_SELECT ((OV9650_1_I2C_I2C1_SIO_PAIR) ? \
                                                        (OV9650_1_I2C_CFG_SIO_SELECT) : (0u))


    /* OV9650_1_I2C_CFG_REG: bits definition */
    #define OV9650_1_I2C_DEFAULT_CFG_PSELECT    ((OV9650_1_I2C_WAKEUP_ENABLED) ? \
                                                        (OV9650_1_I2C_CFG_PSELECT) : (0u))

    #define OV9650_1_I2C_DEFAULT_CLK_RATE0  ((OV9650_1_I2C_DATA_RATE <= 50u) ?        \
                                                    (OV9650_1_I2C_CFG_CLK_RATE_050) :     \
                                                    ((OV9650_1_I2C_DATA_RATE <= 100u) ?   \
                                                        (OV9650_1_I2C_CFG_CLK_RATE_100) : \
                                                        (OV9650_1_I2C_CFG_CLK_RATE_400)))

    #define OV9650_1_I2C_DEFAULT_CLK_RATE1  ((OV9650_1_I2C_DATA_RATE <= 50u) ?           \
                                                 (OV9650_1_I2C_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (OV9650_1_I2C_CFG_CLK_RATE_GRATER_50))

    #define OV9650_1_I2C_DEFAULT_CLK_RATE   (OV9650_1_I2C_DEFAULT_CLK_RATE1)


    #define OV9650_1_I2C_ENABLE_MASTER      ((OV9650_1_I2C_MODE_MASTER_ENABLED) ? \
                                                 (OV9650_1_I2C_CFG_EN_MSTR) : (0u))

    #define OV9650_1_I2C_ENABLE_SLAVE       ((OV9650_1_I2C_MODE_SLAVE_ENABLED) ? \
                                                 (OV9650_1_I2C_CFG_EN_SLAVE) : (0u))

    #define OV9650_1_I2C_ENABLE_MS      (OV9650_1_I2C_ENABLE_MASTER | OV9650_1_I2C_ENABLE_SLAVE)


    /* OV9650_1_I2C_DEFAULT_XCFG_REG */
    #define OV9650_1_I2C_DEFAULT_XCFG   (OV9650_1_I2C_XCFG_CLK_EN         | \
                                             OV9650_1_I2C_DEFAULT_XCFG_I2C_ON | \
                                             OV9650_1_I2C_DEFAULT_XCFG_HW_ADDR_EN)

    /* OV9650_1_I2C_DEFAULT_CFG_REG */
    #define OV9650_1_I2C_DEFAULT_CFG    (OV9650_1_I2C_DEFAULT_CFG_SIO_SELECT | \
                                             OV9650_1_I2C_DEFAULT_CFG_PSELECT    | \
                                             OV9650_1_I2C_DEFAULT_CLK_RATE       | \
                                             OV9650_1_I2C_ENABLE_MASTER          | \
                                             OV9650_1_I2C_ENABLE_SLAVE)

    /*OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR_REG */
    #define OV9650_1_I2C_DEFAULT_DIVIDE_FACTOR  ((uint16) 4u)

#else
    /* OV9650_1_I2C_CFG_REG: bits definition  */
    #define OV9650_1_I2C_ENABLE_MASTER  ((OV9650_1_I2C_MODE_MASTER_ENABLED) ? \
                                             (OV9650_1_I2C_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define OV9650_1_I2C_ENABLE_SLAVE   ((OV9650_1_I2C_MODE_SLAVE_ENABLED) ? \
                                             (OV9650_1_I2C_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define OV9650_1_I2C_ENABLE_MS      (OV9650_1_I2C_ENABLE_MASTER | OV9650_1_I2C_ENABLE_SLAVE)


    #define OV9650_1_I2C_DEFAULT_CTRL_ANY_ADDR   ((OV9650_1_I2C_HW_ADRR_DECODE) ? \
                                                      (0u) : (OV9650_1_I2C_CTRL_ANY_ADDRESS_MASK))

    /* OV9650_1_I2C_DEFAULT_CFG_REG */
    #define OV9650_1_I2C_DEFAULT_CFG    (OV9650_1_I2C_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define OV9650_1_I2C_CTRL_DEFAULT   (OV9650_1_I2C_DEFAULT_CTRL_ANY_ADDR | OV9650_1_I2C_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define OV9650_1_I2C_MCLK_PERIOD_VALUE  (0x0Fu)
    #define OV9650_1_I2C_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: control period */
    #define OV9650_1_I2C_PERIOD_VALUE       (0x07u)

    /* OV9650_1_I2C_DEFAULT_INT_MASK */
    #define OV9650_1_I2C_DEFAULT_INT_MASK   (OV9650_1_I2C_BYTE_COMPLETE_IE_MASK)

    /* OV9650_1_I2C_DEFAULT_MCLK_PRD_REG */
    #define OV9650_1_I2C_DEFAULT_MCLK_PRD   (OV9650_1_I2C_MCLK_PERIOD_VALUE)

    /* OV9650_1_I2C_DEFAULT_MCLK_CMP_REG */
    #define OV9650_1_I2C_DEFAULT_MCLK_CMP   (OV9650_1_I2C_MCLK_COMPARE_VALUE)

    /* OV9650_1_I2C_DEFAULT_PERIOD_REG */
    #define OV9650_1_I2C_DEFAULT_PERIOD     (OV9650_1_I2C_PERIOD_VALUE)

#endif /* (OV9650_1_I2C_FF_IMPLEMENTED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define OV9650_1_I2C_SSTAT_RD_ERR       (0x08u)
#define OV9650_1_I2C_SSTAT_WR_ERR       (0x80u)
#define OV9650_1_I2C_MSTR_SLAVE_BUSY    (OV9650_1_I2C_MSTR_NOT_READY)
#define OV9650_1_I2C_MSTAT_ERR_BUF_OVFL (0x80u)
#define OV9650_1_I2C_SSTAT_RD_CMPT      (OV9650_1_I2C_SSTAT_RD_CMPLT)
#define OV9650_1_I2C_SSTAT_WR_CMPT      (OV9650_1_I2C_SSTAT_WR_CMPLT)
#define OV9650_1_I2C_MODE_MULTI_MASTER_ENABLE    (OV9650_1_I2C_MODE_MULTI_MASTER_MASK)
#define OV9650_1_I2C_DATA_RATE_50       (50u)
#define OV9650_1_I2C_DATA_RATE_100      (100u)
#define OV9650_1_I2C_DEV_MASK           (0xF0u)
#define OV9650_1_I2C_SM_SL_STOP         (0x14u)
#define OV9650_1_I2C_SM_MASTER_IDLE     (0x40u)
#define OV9650_1_I2C_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_OV9650_1_I2C_H */


/* [] END OF FILE */
