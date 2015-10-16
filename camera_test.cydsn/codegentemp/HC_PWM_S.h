/*******************************************************************************
* File Name: HC_PWM_S.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_HC_PWM_S_H)
#define CY_PWM_HC_PWM_S_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 HC_PWM_S_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define HC_PWM_S_Resolution                     (16u)
#define HC_PWM_S_UsingFixedFunction             (0u)
#define HC_PWM_S_DeadBandMode                   (0u)
#define HC_PWM_S_KillModeMinTime                (0u)
#define HC_PWM_S_KillMode                       (0u)
#define HC_PWM_S_PWMMode                        (1u)
#define HC_PWM_S_PWMModeIsCenterAligned         (0u)
#define HC_PWM_S_DeadBandUsed                   (0u)
#define HC_PWM_S_DeadBand2_4                    (0u)

#if !defined(HC_PWM_S_PWMUDB_genblk8_stsreg__REMOVED)
    #define HC_PWM_S_UseStatus                  (1u)
#else
    #define HC_PWM_S_UseStatus                  (0u)
#endif /* !defined(HC_PWM_S_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(HC_PWM_S_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define HC_PWM_S_UseControl                 (1u)
#else
    #define HC_PWM_S_UseControl                 (0u)
#endif /* !defined(HC_PWM_S_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define HC_PWM_S_UseOneCompareMode              (0u)
#define HC_PWM_S_MinimumKillTime                (1u)
#define HC_PWM_S_EnableMode                     (0u)

#define HC_PWM_S_CompareMode1SW                 (0u)
#define HC_PWM_S_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define HC_PWM_S__B_PWM__DISABLED 0
#define HC_PWM_S__B_PWM__ASYNCHRONOUS 1
#define HC_PWM_S__B_PWM__SINGLECYCLE 2
#define HC_PWM_S__B_PWM__LATCHED 3
#define HC_PWM_S__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define HC_PWM_S__B_PWM__DBMDISABLED 0
#define HC_PWM_S__B_PWM__DBM_2_4_CLOCKS 1
#define HC_PWM_S__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define HC_PWM_S__B_PWM__ONE_OUTPUT 0
#define HC_PWM_S__B_PWM__TWO_OUTPUTS 1
#define HC_PWM_S__B_PWM__DUAL_EDGE 2
#define HC_PWM_S__B_PWM__CENTER_ALIGN 3
#define HC_PWM_S__B_PWM__DITHER 5
#define HC_PWM_S__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define HC_PWM_S__B_PWM__LESS_THAN 1
#define HC_PWM_S__B_PWM__LESS_THAN_OR_EQUAL 2
#define HC_PWM_S__B_PWM__GREATER_THAN 3
#define HC_PWM_S__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define HC_PWM_S__B_PWM__EQUAL 0
#define HC_PWM_S__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!HC_PWM_S_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!HC_PWM_S_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!HC_PWM_S_PWMModeIsCenterAligned) */
        #if (HC_PWM_S_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (HC_PWM_S_UseStatus) */

        /* Backup for Deadband parameters */
        #if(HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_256_CLOCKS || \
            HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(HC_PWM_S_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (HC_PWM_S_KillModeMinTime) */

        /* Backup control register */
        #if(HC_PWM_S_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (HC_PWM_S_UseControl) */

    #endif /* (!HC_PWM_S_UsingFixedFunction) */

}HC_PWM_S_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    HC_PWM_S_Start(void) ;
void    HC_PWM_S_Stop(void) ;

#if (HC_PWM_S_UseStatus || HC_PWM_S_UsingFixedFunction)
    void  HC_PWM_S_SetInterruptMode(uint8 interruptMode) ;
    uint8 HC_PWM_S_ReadStatusRegister(void) ;
#endif /* (HC_PWM_S_UseStatus || HC_PWM_S_UsingFixedFunction) */

#define HC_PWM_S_GetInterruptSource() HC_PWM_S_ReadStatusRegister()

#if (HC_PWM_S_UseControl)
    uint8 HC_PWM_S_ReadControlRegister(void) ;
    void  HC_PWM_S_WriteControlRegister(uint8 control)
          ;
#endif /* (HC_PWM_S_UseControl) */

#if (HC_PWM_S_UseOneCompareMode)
   #if (HC_PWM_S_CompareMode1SW)
       void    HC_PWM_S_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (HC_PWM_S_CompareMode1SW) */
#else
    #if (HC_PWM_S_CompareMode1SW)
        void    HC_PWM_S_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (HC_PWM_S_CompareMode1SW) */
    #if (HC_PWM_S_CompareMode2SW)
        void    HC_PWM_S_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (HC_PWM_S_CompareMode2SW) */
#endif /* (HC_PWM_S_UseOneCompareMode) */

#if (!HC_PWM_S_UsingFixedFunction)
    uint16   HC_PWM_S_ReadCounter(void) ;
    uint16 HC_PWM_S_ReadCapture(void) ;

    #if (HC_PWM_S_UseStatus)
            void HC_PWM_S_ClearFIFO(void) ;
    #endif /* (HC_PWM_S_UseStatus) */

    void    HC_PWM_S_WriteCounter(uint16 counter)
            ;
#endif /* (!HC_PWM_S_UsingFixedFunction) */

void    HC_PWM_S_WritePeriod(uint16 period)
        ;
uint16 HC_PWM_S_ReadPeriod(void) ;

#if (HC_PWM_S_UseOneCompareMode)
    void    HC_PWM_S_WriteCompare(uint16 compare)
            ;
    uint16 HC_PWM_S_ReadCompare(void) ;
#else
    void    HC_PWM_S_WriteCompare1(uint16 compare)
            ;
    uint16 HC_PWM_S_ReadCompare1(void) ;
    void    HC_PWM_S_WriteCompare2(uint16 compare)
            ;
    uint16 HC_PWM_S_ReadCompare2(void) ;
#endif /* (HC_PWM_S_UseOneCompareMode) */


#if (HC_PWM_S_DeadBandUsed)
    void    HC_PWM_S_WriteDeadTime(uint8 deadtime) ;
    uint8   HC_PWM_S_ReadDeadTime(void) ;
#endif /* (HC_PWM_S_DeadBandUsed) */

#if ( HC_PWM_S_KillModeMinTime)
    void HC_PWM_S_WriteKillTime(uint8 killtime) ;
    uint8 HC_PWM_S_ReadKillTime(void) ;
#endif /* ( HC_PWM_S_KillModeMinTime) */

void HC_PWM_S_Init(void) ;
void HC_PWM_S_Enable(void) ;
void HC_PWM_S_Sleep(void) ;
void HC_PWM_S_Wakeup(void) ;
void HC_PWM_S_SaveConfig(void) ;
void HC_PWM_S_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define HC_PWM_S_INIT_PERIOD_VALUE          (49999u)
#define HC_PWM_S_INIT_COMPARE_VALUE1        (44979u)
#define HC_PWM_S_INIT_COMPARE_VALUE2        (10000u)
#define HC_PWM_S_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    HC_PWM_S_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HC_PWM_S_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HC_PWM_S_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HC_PWM_S_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define HC_PWM_S_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  HC_PWM_S_CTRL_CMPMODE2_SHIFT)
#define HC_PWM_S_DEFAULT_COMPARE1_MODE      (uint8)((uint8)4u <<  HC_PWM_S_CTRL_CMPMODE1_SHIFT)
#define HC_PWM_S_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (HC_PWM_S_UsingFixedFunction)
   #define HC_PWM_S_PERIOD_LSB              (*(reg16 *) HC_PWM_S_PWMHW__PER0)
   #define HC_PWM_S_PERIOD_LSB_PTR          ( (reg16 *) HC_PWM_S_PWMHW__PER0)
   #define HC_PWM_S_COMPARE1_LSB            (*(reg16 *) HC_PWM_S_PWMHW__CNT_CMP0)
   #define HC_PWM_S_COMPARE1_LSB_PTR        ( (reg16 *) HC_PWM_S_PWMHW__CNT_CMP0)
   #define HC_PWM_S_COMPARE2_LSB            (0x00u)
   #define HC_PWM_S_COMPARE2_LSB_PTR        (0x00u)
   #define HC_PWM_S_COUNTER_LSB             (*(reg16 *) HC_PWM_S_PWMHW__CNT_CMP0)
   #define HC_PWM_S_COUNTER_LSB_PTR         ( (reg16 *) HC_PWM_S_PWMHW__CNT_CMP0)
   #define HC_PWM_S_CAPTURE_LSB             (*(reg16 *) HC_PWM_S_PWMHW__CAP0)
   #define HC_PWM_S_CAPTURE_LSB_PTR         ( (reg16 *) HC_PWM_S_PWMHW__CAP0)
   #define HC_PWM_S_RT1                     (*(reg8 *)  HC_PWM_S_PWMHW__RT1)
   #define HC_PWM_S_RT1_PTR                 ( (reg8 *)  HC_PWM_S_PWMHW__RT1)

#else
   #if (HC_PWM_S_Resolution == 8u) /* 8bit - PWM */

       #if(HC_PWM_S_PWMModeIsCenterAligned)
           #define HC_PWM_S_PERIOD_LSB      (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define HC_PWM_S_PERIOD_LSB_PTR  ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define HC_PWM_S_PERIOD_LSB      (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define HC_PWM_S_PERIOD_LSB_PTR  ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (HC_PWM_S_PWMModeIsCenterAligned) */

       #define HC_PWM_S_COMPARE1_LSB        (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HC_PWM_S_COMPARE1_LSB_PTR    ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HC_PWM_S_COMPARE2_LSB        (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HC_PWM_S_COMPARE2_LSB_PTR    ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HC_PWM_S_COUNTERCAP_LSB      (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HC_PWM_S_COUNTERCAP_LSB_PTR  ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HC_PWM_S_COUNTER_LSB         (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HC_PWM_S_COUNTER_LSB_PTR     ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HC_PWM_S_CAPTURE_LSB         (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define HC_PWM_S_CAPTURE_LSB_PTR     ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(HC_PWM_S_PWMModeIsCenterAligned)
               #define HC_PWM_S_PERIOD_LSB      (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define HC_PWM_S_PERIOD_LSB_PTR  ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define HC_PWM_S_PERIOD_LSB      (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define HC_PWM_S_PERIOD_LSB_PTR  ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (HC_PWM_S_PWMModeIsCenterAligned) */

            #define HC_PWM_S_COMPARE1_LSB       (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HC_PWM_S_COMPARE1_LSB_PTR   ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HC_PWM_S_COMPARE2_LSB       (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HC_PWM_S_COMPARE2_LSB_PTR   ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HC_PWM_S_COUNTERCAP_LSB     (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HC_PWM_S_COUNTERCAP_LSB_PTR ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HC_PWM_S_COUNTER_LSB        (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HC_PWM_S_COUNTER_LSB_PTR    ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HC_PWM_S_CAPTURE_LSB        (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define HC_PWM_S_CAPTURE_LSB_PTR    ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(HC_PWM_S_PWMModeIsCenterAligned)
               #define HC_PWM_S_PERIOD_LSB      (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define HC_PWM_S_PERIOD_LSB_PTR  ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define HC_PWM_S_PERIOD_LSB      (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define HC_PWM_S_PERIOD_LSB_PTR  ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (HC_PWM_S_PWMModeIsCenterAligned) */

            #define HC_PWM_S_COMPARE1_LSB       (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HC_PWM_S_COMPARE1_LSB_PTR   ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HC_PWM_S_COMPARE2_LSB       (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HC_PWM_S_COMPARE2_LSB_PTR   ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HC_PWM_S_COUNTERCAP_LSB     (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HC_PWM_S_COUNTERCAP_LSB_PTR ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HC_PWM_S_COUNTER_LSB        (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HC_PWM_S_COUNTER_LSB_PTR    ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HC_PWM_S_CAPTURE_LSB        (*(reg16 *) HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define HC_PWM_S_CAPTURE_LSB_PTR    ((reg16 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define HC_PWM_S_AUX_CONTROLDP1          (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define HC_PWM_S_AUX_CONTROLDP1_PTR      ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (HC_PWM_S_Resolution == 8) */

   #define HC_PWM_S_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define HC_PWM_S_AUX_CONTROLDP0          (*(reg8 *)  HC_PWM_S_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define HC_PWM_S_AUX_CONTROLDP0_PTR      ((reg8 *)   HC_PWM_S_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (HC_PWM_S_UsingFixedFunction) */

#if(HC_PWM_S_KillModeMinTime )
    #define HC_PWM_S_KILLMODEMINTIME        (*(reg8 *)  HC_PWM_S_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define HC_PWM_S_KILLMODEMINTIME_PTR    ((reg8 *)   HC_PWM_S_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (HC_PWM_S_KillModeMinTime ) */

#if(HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_256_CLOCKS)
    #define HC_PWM_S_DEADBAND_COUNT         (*(reg8 *)  HC_PWM_S_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HC_PWM_S_DEADBAND_COUNT_PTR     ((reg8 *)   HC_PWM_S_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HC_PWM_S_DEADBAND_LSB_PTR       ((reg8 *)   HC_PWM_S_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define HC_PWM_S_DEADBAND_LSB           (*(reg8 *)  HC_PWM_S_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (HC_PWM_S_UsingFixedFunction)
        #define HC_PWM_S_DEADBAND_COUNT         (*(reg8 *)  HC_PWM_S_PWMHW__CFG0)
        #define HC_PWM_S_DEADBAND_COUNT_PTR     ((reg8 *)   HC_PWM_S_PWMHW__CFG0)
        #define HC_PWM_S_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HC_PWM_S_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define HC_PWM_S_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define HC_PWM_S_DEADBAND_COUNT         (*(reg8 *)  HC_PWM_S_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HC_PWM_S_DEADBAND_COUNT_PTR     ((reg8 *)   HC_PWM_S_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HC_PWM_S_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HC_PWM_S_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define HC_PWM_S_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (HC_PWM_S_UsingFixedFunction) */
#endif /* (HC_PWM_S_DeadBandMode == HC_PWM_S__B_PWM__DBM_256_CLOCKS) */



#if (HC_PWM_S_UsingFixedFunction)
    #define HC_PWM_S_STATUS                 (*(reg8 *) HC_PWM_S_PWMHW__SR0)
    #define HC_PWM_S_STATUS_PTR             ((reg8 *) HC_PWM_S_PWMHW__SR0)
    #define HC_PWM_S_STATUS_MASK            (*(reg8 *) HC_PWM_S_PWMHW__SR0)
    #define HC_PWM_S_STATUS_MASK_PTR        ((reg8 *) HC_PWM_S_PWMHW__SR0)
    #define HC_PWM_S_CONTROL                (*(reg8 *) HC_PWM_S_PWMHW__CFG0)
    #define HC_PWM_S_CONTROL_PTR            ((reg8 *) HC_PWM_S_PWMHW__CFG0)
    #define HC_PWM_S_CONTROL2               (*(reg8 *) HC_PWM_S_PWMHW__CFG1)
    #define HC_PWM_S_CONTROL3               (*(reg8 *) HC_PWM_S_PWMHW__CFG2)
    #define HC_PWM_S_GLOBAL_ENABLE          (*(reg8 *) HC_PWM_S_PWMHW__PM_ACT_CFG)
    #define HC_PWM_S_GLOBAL_ENABLE_PTR      ( (reg8 *) HC_PWM_S_PWMHW__PM_ACT_CFG)
    #define HC_PWM_S_GLOBAL_STBY_ENABLE     (*(reg8 *) HC_PWM_S_PWMHW__PM_STBY_CFG)
    #define HC_PWM_S_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) HC_PWM_S_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define HC_PWM_S_BLOCK_EN_MASK          (HC_PWM_S_PWMHW__PM_ACT_MSK)
    #define HC_PWM_S_BLOCK_STBY_EN_MASK     (HC_PWM_S_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define HC_PWM_S_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define HC_PWM_S_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define HC_PWM_S_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define HC_PWM_S_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define HC_PWM_S_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define HC_PWM_S_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define HC_PWM_S_CTRL_ENABLE            (uint8)((uint8)0x01u << HC_PWM_S_CTRL_ENABLE_SHIFT)
    #define HC_PWM_S_CTRL_RESET             (uint8)((uint8)0x01u << HC_PWM_S_CTRL_RESET_SHIFT)
    #define HC_PWM_S_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HC_PWM_S_CTRL_CMPMODE2_SHIFT)
    #define HC_PWM_S_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HC_PWM_S_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define HC_PWM_S_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define HC_PWM_S_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << HC_PWM_S_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define HC_PWM_S_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define HC_PWM_S_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define HC_PWM_S_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define HC_PWM_S_STATUS_TC_INT_EN_MASK_SHIFT            (HC_PWM_S_STATUS_TC_SHIFT - 4u)
    #define HC_PWM_S_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define HC_PWM_S_STATUS_CMP1_INT_EN_MASK_SHIFT          (HC_PWM_S_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define HC_PWM_S_STATUS_TC              (uint8)((uint8)0x01u << HC_PWM_S_STATUS_TC_SHIFT)
    #define HC_PWM_S_STATUS_CMP1            (uint8)((uint8)0x01u << HC_PWM_S_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define HC_PWM_S_STATUS_TC_INT_EN_MASK              (uint8)((uint8)HC_PWM_S_STATUS_TC >> 4u)
    #define HC_PWM_S_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)HC_PWM_S_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define HC_PWM_S_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define HC_PWM_S_RT1_MASK              (uint8)((uint8)0x03u << HC_PWM_S_RT1_SHIFT)
    #define HC_PWM_S_SYNC                  (uint8)((uint8)0x03u << HC_PWM_S_RT1_SHIFT)
    #define HC_PWM_S_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define HC_PWM_S_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << HC_PWM_S_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define HC_PWM_S_SYNCDSI_EN            (uint8)((uint8)0x0Fu << HC_PWM_S_SYNCDSI_SHIFT)


#else
    #define HC_PWM_S_STATUS                (*(reg8 *)   HC_PWM_S_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HC_PWM_S_STATUS_PTR            ((reg8 *)    HC_PWM_S_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HC_PWM_S_STATUS_MASK           (*(reg8 *)   HC_PWM_S_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HC_PWM_S_STATUS_MASK_PTR       ((reg8 *)    HC_PWM_S_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HC_PWM_S_STATUS_AUX_CTRL       (*(reg8 *)   HC_PWM_S_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define HC_PWM_S_CONTROL               (*(reg8 *)   HC_PWM_S_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define HC_PWM_S_CONTROL_PTR           ((reg8 *)    HC_PWM_S_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define HC_PWM_S_CTRL_ENABLE_SHIFT      (0x07u)
    #define HC_PWM_S_CTRL_RESET_SHIFT       (0x06u)
    #define HC_PWM_S_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define HC_PWM_S_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define HC_PWM_S_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define HC_PWM_S_CTRL_ENABLE            (uint8)((uint8)0x01u << HC_PWM_S_CTRL_ENABLE_SHIFT)
    #define HC_PWM_S_CTRL_RESET             (uint8)((uint8)0x01u << HC_PWM_S_CTRL_RESET_SHIFT)
    #define HC_PWM_S_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HC_PWM_S_CTRL_CMPMODE2_SHIFT)
    #define HC_PWM_S_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HC_PWM_S_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define HC_PWM_S_STATUS_KILL_SHIFT          (0x05u)
    #define HC_PWM_S_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define HC_PWM_S_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define HC_PWM_S_STATUS_TC_SHIFT            (0x02u)
    #define HC_PWM_S_STATUS_CMP2_SHIFT          (0x01u)
    #define HC_PWM_S_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define HC_PWM_S_STATUS_KILL_INT_EN_MASK_SHIFT          (HC_PWM_S_STATUS_KILL_SHIFT)
    #define HC_PWM_S_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (HC_PWM_S_STATUS_FIFONEMPTY_SHIFT)
    #define HC_PWM_S_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (HC_PWM_S_STATUS_FIFOFULL_SHIFT)
    #define HC_PWM_S_STATUS_TC_INT_EN_MASK_SHIFT            (HC_PWM_S_STATUS_TC_SHIFT)
    #define HC_PWM_S_STATUS_CMP2_INT_EN_MASK_SHIFT          (HC_PWM_S_STATUS_CMP2_SHIFT)
    #define HC_PWM_S_STATUS_CMP1_INT_EN_MASK_SHIFT          (HC_PWM_S_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define HC_PWM_S_STATUS_KILL            (uint8)((uint8)0x00u << HC_PWM_S_STATUS_KILL_SHIFT )
    #define HC_PWM_S_STATUS_FIFOFULL        (uint8)((uint8)0x01u << HC_PWM_S_STATUS_FIFOFULL_SHIFT)
    #define HC_PWM_S_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << HC_PWM_S_STATUS_FIFONEMPTY_SHIFT)
    #define HC_PWM_S_STATUS_TC              (uint8)((uint8)0x01u << HC_PWM_S_STATUS_TC_SHIFT)
    #define HC_PWM_S_STATUS_CMP2            (uint8)((uint8)0x01u << HC_PWM_S_STATUS_CMP2_SHIFT)
    #define HC_PWM_S_STATUS_CMP1            (uint8)((uint8)0x01u << HC_PWM_S_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define HC_PWM_S_STATUS_KILL_INT_EN_MASK            (HC_PWM_S_STATUS_KILL)
    #define HC_PWM_S_STATUS_FIFOFULL_INT_EN_MASK        (HC_PWM_S_STATUS_FIFOFULL)
    #define HC_PWM_S_STATUS_FIFONEMPTY_INT_EN_MASK      (HC_PWM_S_STATUS_FIFONEMPTY)
    #define HC_PWM_S_STATUS_TC_INT_EN_MASK              (HC_PWM_S_STATUS_TC)
    #define HC_PWM_S_STATUS_CMP2_INT_EN_MASK            (HC_PWM_S_STATUS_CMP2)
    #define HC_PWM_S_STATUS_CMP1_INT_EN_MASK            (HC_PWM_S_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define HC_PWM_S_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define HC_PWM_S_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define HC_PWM_S_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define HC_PWM_S_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define HC_PWM_S_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* HC_PWM_S_UsingFixedFunction */

#endif  /* CY_PWM_HC_PWM_S_H */


/* [] END OF FILE */
