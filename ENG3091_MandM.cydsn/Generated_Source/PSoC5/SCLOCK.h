/*******************************************************************************
* File Name: SCLOCK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SCLOCK_H)
#define CY_CLOCK_SCLOCK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SCLOCK_Start(void) ;
void SCLOCK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SCLOCK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SCLOCK_StandbyPower(uint8 state) ;
void SCLOCK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SCLOCK_GetDividerRegister(void) ;
void SCLOCK_SetModeRegister(uint8 modeBitMask) ;
void SCLOCK_ClearModeRegister(uint8 modeBitMask) ;
uint8 SCLOCK_GetModeRegister(void) ;
void SCLOCK_SetSourceRegister(uint8 clkSource) ;
uint8 SCLOCK_GetSourceRegister(void) ;
#if defined(SCLOCK__CFG3)
void SCLOCK_SetPhaseRegister(uint8 clkPhase) ;
uint8 SCLOCK_GetPhaseRegister(void) ;
#endif /* defined(SCLOCK__CFG3) */

#define SCLOCK_Enable()                       SCLOCK_Start()
#define SCLOCK_Disable()                      SCLOCK_Stop()
#define SCLOCK_SetDivider(clkDivider)         SCLOCK_SetDividerRegister(clkDivider, 1u)
#define SCLOCK_SetDividerValue(clkDivider)    SCLOCK_SetDividerRegister((clkDivider) - 1u, 1u)
#define SCLOCK_SetMode(clkMode)               SCLOCK_SetModeRegister(clkMode)
#define SCLOCK_SetSource(clkSource)           SCLOCK_SetSourceRegister(clkSource)
#if defined(SCLOCK__CFG3)
#define SCLOCK_SetPhase(clkPhase)             SCLOCK_SetPhaseRegister(clkPhase)
#define SCLOCK_SetPhaseValue(clkPhase)        SCLOCK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SCLOCK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SCLOCK_CLKEN              (* (reg8 *) SCLOCK__PM_ACT_CFG)
#define SCLOCK_CLKEN_PTR          ((reg8 *) SCLOCK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SCLOCK_CLKSTBY            (* (reg8 *) SCLOCK__PM_STBY_CFG)
#define SCLOCK_CLKSTBY_PTR        ((reg8 *) SCLOCK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SCLOCK_DIV_LSB            (* (reg8 *) SCLOCK__CFG0)
#define SCLOCK_DIV_LSB_PTR        ((reg8 *) SCLOCK__CFG0)
#define SCLOCK_DIV_PTR            ((reg16 *) SCLOCK__CFG0)

/* Clock MSB divider configuration register. */
#define SCLOCK_DIV_MSB            (* (reg8 *) SCLOCK__CFG1)
#define SCLOCK_DIV_MSB_PTR        ((reg8 *) SCLOCK__CFG1)

/* Mode and source configuration register */
#define SCLOCK_MOD_SRC            (* (reg8 *) SCLOCK__CFG2)
#define SCLOCK_MOD_SRC_PTR        ((reg8 *) SCLOCK__CFG2)

#if defined(SCLOCK__CFG3)
/* Analog clock phase configuration register */
#define SCLOCK_PHASE              (* (reg8 *) SCLOCK__CFG3)
#define SCLOCK_PHASE_PTR          ((reg8 *) SCLOCK__CFG3)
#endif /* defined(SCLOCK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SCLOCK_CLKEN_MASK         SCLOCK__PM_ACT_MSK
#define SCLOCK_CLKSTBY_MASK       SCLOCK__PM_STBY_MSK

/* CFG2 field masks */
#define SCLOCK_SRC_SEL_MSK        SCLOCK__CFG2_SRC_SEL_MASK
#define SCLOCK_MODE_MASK          (~(SCLOCK_SRC_SEL_MSK))

#if defined(SCLOCK__CFG3)
/* CFG3 phase mask */
#define SCLOCK_PHASE_MASK         SCLOCK__CFG3_PHASE_DLY_MASK
#endif /* defined(SCLOCK__CFG3) */

#endif /* CY_CLOCK_SCLOCK_H */


/* [] END OF FILE */
