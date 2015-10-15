/*******************************************************************************
* File Name: BEAM_BREAK_TIMER.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_BEAM_BREAK_TIMER_H)
#define CY_Timer_v2_60_BEAM_BREAK_TIMER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BEAM_BREAK_TIMER_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define BEAM_BREAK_TIMER_Resolution                 16u
#define BEAM_BREAK_TIMER_UsingFixedFunction         0u
#define BEAM_BREAK_TIMER_UsingHWCaptureCounter      0u
#define BEAM_BREAK_TIMER_SoftwareCaptureMode        0u
#define BEAM_BREAK_TIMER_SoftwareTriggerMode        0u
#define BEAM_BREAK_TIMER_UsingHWEnable              1u
#define BEAM_BREAK_TIMER_EnableTriggerMode          0u
#define BEAM_BREAK_TIMER_InterruptOnCaptureCount    0u
#define BEAM_BREAK_TIMER_RunModeUsed                0u
#define BEAM_BREAK_TIMER_ControlRegRemoved          1u

#if defined(BEAM_BREAK_TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (BEAM_BREAK_TIMER_UsingFixedFunction)
    #define BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End BEAM_BREAK_TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!BEAM_BREAK_TIMER_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (BEAM_BREAK_TIMER_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}BEAM_BREAK_TIMER_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    BEAM_BREAK_TIMER_Start(void) ;
void    BEAM_BREAK_TIMER_Stop(void) ;

void    BEAM_BREAK_TIMER_SetInterruptMode(uint8 interruptMode) ;
uint8   BEAM_BREAK_TIMER_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define BEAM_BREAK_TIMER_GetInterruptSource() BEAM_BREAK_TIMER_ReadStatusRegister()

#if(!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED)
    uint8   BEAM_BREAK_TIMER_ReadControlRegister(void) ;
    void    BEAM_BREAK_TIMER_WriteControlRegister(uint8 control) ;
#endif /* (!BEAM_BREAK_TIMER_UDB_CONTROL_REG_REMOVED) */

uint16  BEAM_BREAK_TIMER_ReadPeriod(void) ;
void    BEAM_BREAK_TIMER_WritePeriod(uint16 period) ;
uint16  BEAM_BREAK_TIMER_ReadCounter(void) ;
void    BEAM_BREAK_TIMER_WriteCounter(uint16 counter) ;
uint16  BEAM_BREAK_TIMER_ReadCapture(void) ;
void    BEAM_BREAK_TIMER_SoftwareCapture(void) ;

#if(!BEAM_BREAK_TIMER_UsingFixedFunction) /* UDB Prototypes */
    #if (BEAM_BREAK_TIMER_SoftwareCaptureMode)
        void    BEAM_BREAK_TIMER_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!BEAM_BREAK_TIMER_UsingFixedFunction) */

    #if (BEAM_BREAK_TIMER_SoftwareTriggerMode)
        void    BEAM_BREAK_TIMER_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (BEAM_BREAK_TIMER_SoftwareTriggerMode) */

    #if (BEAM_BREAK_TIMER_EnableTriggerMode)
        void    BEAM_BREAK_TIMER_EnableTrigger(void) ;
        void    BEAM_BREAK_TIMER_DisableTrigger(void) ;
    #endif /* (BEAM_BREAK_TIMER_EnableTriggerMode) */


    #if(BEAM_BREAK_TIMER_InterruptOnCaptureCount)
        void    BEAM_BREAK_TIMER_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (BEAM_BREAK_TIMER_InterruptOnCaptureCount) */

    #if (BEAM_BREAK_TIMER_UsingHWCaptureCounter)
        void    BEAM_BREAK_TIMER_SetCaptureCount(uint8 captureCount) ;
        uint8   BEAM_BREAK_TIMER_ReadCaptureCount(void) ;
    #endif /* (BEAM_BREAK_TIMER_UsingHWCaptureCounter) */

    void BEAM_BREAK_TIMER_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void BEAM_BREAK_TIMER_Init(void)          ;
void BEAM_BREAK_TIMER_Enable(void)        ;
void BEAM_BREAK_TIMER_SaveConfig(void)    ;
void BEAM_BREAK_TIMER_RestoreConfig(void) ;
void BEAM_BREAK_TIMER_Sleep(void)         ;
void BEAM_BREAK_TIMER_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define BEAM_BREAK_TIMER__B_TIMER__CM_NONE 0
#define BEAM_BREAK_TIMER__B_TIMER__CM_RISINGEDGE 1
#define BEAM_BREAK_TIMER__B_TIMER__CM_FALLINGEDGE 2
#define BEAM_BREAK_TIMER__B_TIMER__CM_EITHEREDGE 3
#define BEAM_BREAK_TIMER__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define BEAM_BREAK_TIMER__B_TIMER__TM_NONE 0x00u
#define BEAM_BREAK_TIMER__B_TIMER__TM_RISINGEDGE 0x04u
#define BEAM_BREAK_TIMER__B_TIMER__TM_FALLINGEDGE 0x08u
#define BEAM_BREAK_TIMER__B_TIMER__TM_EITHEREDGE 0x0Cu
#define BEAM_BREAK_TIMER__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define BEAM_BREAK_TIMER_INIT_PERIOD             65535u
#define BEAM_BREAK_TIMER_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << BEAM_BREAK_TIMER_CTRL_CAP_MODE_SHIFT))
#define BEAM_BREAK_TIMER_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << BEAM_BREAK_TIMER_CTRL_TRIG_MODE_SHIFT))
#if (BEAM_BREAK_TIMER_UsingFixedFunction)
    #define BEAM_BREAK_TIMER_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << BEAM_BREAK_TIMER_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define BEAM_BREAK_TIMER_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << BEAM_BREAK_TIMER_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BEAM_BREAK_TIMER_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (BEAM_BREAK_TIMER_UsingFixedFunction) */
#define BEAM_BREAK_TIMER_INIT_CAPTURE_COUNT      (2u)
#define BEAM_BREAK_TIMER_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << BEAM_BREAK_TIMER_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (BEAM_BREAK_TIMER_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define BEAM_BREAK_TIMER_STATUS         (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define BEAM_BREAK_TIMER_STATUS_MASK    (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__SR0 )
    #define BEAM_BREAK_TIMER_CONTROL        (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__CFG0)
    #define BEAM_BREAK_TIMER_CONTROL2       (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__CFG1)
    #define BEAM_BREAK_TIMER_CONTROL2_PTR   ( (reg8 *) BEAM_BREAK_TIMER_TimerHW__CFG1)
    #define BEAM_BREAK_TIMER_RT1            (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__RT1)
    #define BEAM_BREAK_TIMER_RT1_PTR        ( (reg8 *) BEAM_BREAK_TIMER_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define BEAM_BREAK_TIMER_CONTROL3       (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__CFG2)
        #define BEAM_BREAK_TIMER_CONTROL3_PTR   ( (reg8 *) BEAM_BREAK_TIMER_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define BEAM_BREAK_TIMER_GLOBAL_ENABLE  (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__PM_ACT_CFG)
    #define BEAM_BREAK_TIMER_GLOBAL_STBY_ENABLE  (*(reg8 *) BEAM_BREAK_TIMER_TimerHW__PM_STBY_CFG)

    #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerHW__CAP0 )
    #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerHW__CAP0 )
    #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg16 *) BEAM_BREAK_TIMER_TimerHW__PER0 )
    #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg16 *) BEAM_BREAK_TIMER_TimerHW__PER0 )
    #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerHW__CNT_CMP0 )
    #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define BEAM_BREAK_TIMER_BLOCK_EN_MASK                     BEAM_BREAK_TIMER_TimerHW__PM_ACT_MSK
    #define BEAM_BREAK_TIMER_BLOCK_STBY_EN_MASK                BEAM_BREAK_TIMER_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define BEAM_BREAK_TIMER_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define BEAM_BREAK_TIMER_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define BEAM_BREAK_TIMER_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define BEAM_BREAK_TIMER_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define BEAM_BREAK_TIMER_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define BEAM_BREAK_TIMER_CTRL_ENABLE                        ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BEAM_BREAK_TIMER_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define BEAM_BREAK_TIMER_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define BEAM_BREAK_TIMER_CTRL_MODE_SHIFT                 0x01u
        #define BEAM_BREAK_TIMER_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << BEAM_BREAK_TIMER_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define BEAM_BREAK_TIMER_CTRL_RCOD_SHIFT        0x02u
        #define BEAM_BREAK_TIMER_CTRL_ENBL_SHIFT        0x00u
        #define BEAM_BREAK_TIMER_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define BEAM_BREAK_TIMER_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define BEAM_BREAK_TIMER_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << BEAM_BREAK_TIMER_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define BEAM_BREAK_TIMER_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define BEAM_BREAK_TIMER_CTRL_RCOD       ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_RCOD_SHIFT))
        #define BEAM_BREAK_TIMER_CTRL_ENBL       ((uint8)((uint8)0x80u << BEAM_BREAK_TIMER_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define BEAM_BREAK_TIMER_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define BEAM_BREAK_TIMER_RT1_MASK                        ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_RT1_SHIFT))
    #define BEAM_BREAK_TIMER_SYNC                            ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_RT1_SHIFT))
    #define BEAM_BREAK_TIMER_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define BEAM_BREAK_TIMER_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << BEAM_BREAK_TIMER_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define BEAM_BREAK_TIMER_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << BEAM_BREAK_TIMER_SYNCDSI_SHIFT))

    #define BEAM_BREAK_TIMER_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_CTRL_MODE_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << BEAM_BREAK_TIMER_CTRL_MODE_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << BEAM_BREAK_TIMER_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BEAM_BREAK_TIMER_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BEAM_BREAK_TIMER_STATUS_TC_INT_MASK_SHIFT        (BEAM_BREAK_TIMER_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK_SHIFT   (BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define BEAM_BREAK_TIMER_STATUS_TC                       ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_TC_SHIFT))
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define BEAM_BREAK_TIMER_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define BEAM_BREAK_TIMER_STATUS              (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define BEAM_BREAK_TIMER_STATUS_MASK         (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_rstSts_stsreg__MASK_REG)
    #define BEAM_BREAK_TIMER_STATUS_AUX_CTRL     (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define BEAM_BREAK_TIMER_CONTROL             (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(BEAM_BREAK_TIMER_Resolution <= 8u) /* 8-bit Timer */
        #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(BEAM_BREAK_TIMER_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg16 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(BEAM_BREAK_TIMER_Resolution <= 24u)/* 24-bit Timer */
        #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define BEAM_BREAK_TIMER_CAPTURE_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define BEAM_BREAK_TIMER_CAPTURE_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB          (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define BEAM_BREAK_TIMER_PERIOD_LSB_PTR        ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB         (* (reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR       ((reg32 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define BEAM_BREAK_TIMER_COUNTER_LSB_PTR_8BIT       ((reg8 *) BEAM_BREAK_TIMER_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (BEAM_BREAK_TIMER_UsingHWCaptureCounter)
        #define BEAM_BREAK_TIMER_CAP_COUNT              (*(reg8 *) BEAM_BREAK_TIMER_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BEAM_BREAK_TIMER_CAP_COUNT_PTR          ( (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BEAM_BREAK_TIMER_CAPTURE_COUNT_CTRL     (*(reg8 *) BEAM_BREAK_TIMER_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define BEAM_BREAK_TIMER_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) BEAM_BREAK_TIMER_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (BEAM_BREAK_TIMER_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define BEAM_BREAK_TIMER_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define BEAM_BREAK_TIMER_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_INTCNT_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_TRIG_MODE_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_CTRL_TRIG_EN_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << BEAM_BREAK_TIMER_CTRL_CAP_MODE_SHIFT))
    #define BEAM_BREAK_TIMER_CTRL_ENABLE                    ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define BEAM_BREAK_TIMER_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define BEAM_BREAK_TIMER_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_STATUS_TC_INT_MASK_SHIFT       BEAM_BREAK_TIMER_STATUS_TC_SHIFT
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK_SHIFT  BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT
    #define BEAM_BREAK_TIMER_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define BEAM_BREAK_TIMER_STATUS_FIFOFULL_INT_MASK_SHIFT BEAM_BREAK_TIMER_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_TC                      ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BEAM_BREAK_TIMER_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << BEAM_BREAK_TIMER_STATUS_FIFOFULL_SHIFT))

    #define BEAM_BREAK_TIMER_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define BEAM_BREAK_TIMER_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define BEAM_BREAK_TIMER_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define BEAM_BREAK_TIMER_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define BEAM_BREAK_TIMER_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define BEAM_BREAK_TIMER_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_BEAM_BREAK_TIMER_H */


/* [] END OF FILE */
