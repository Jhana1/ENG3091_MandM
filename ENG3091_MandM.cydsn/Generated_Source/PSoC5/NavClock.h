/*******************************************************************************
* File Name: NavClock.h
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

#if !defined(CY_CLOCK_NavClock_H)
#define CY_CLOCK_NavClock_H

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

void NavClock_Start(void) ;
void NavClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void NavClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void NavClock_StandbyPower(uint8 state) ;
void NavClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 NavClock_GetDividerRegister(void) ;
void NavClock_SetModeRegister(uint8 modeBitMask) ;
void NavClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 NavClock_GetModeRegister(void) ;
void NavClock_SetSourceRegister(uint8 clkSource) ;
uint8 NavClock_GetSourceRegister(void) ;
#if defined(NavClock__CFG3)
void NavClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 NavClock_GetPhaseRegister(void) ;
#endif /* defined(NavClock__CFG3) */

#define NavClock_Enable()                       NavClock_Start()
#define NavClock_Disable()                      NavClock_Stop()
#define NavClock_SetDivider(clkDivider)         NavClock_SetDividerRegister(clkDivider, 1u)
#define NavClock_SetDividerValue(clkDivider)    NavClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define NavClock_SetMode(clkMode)               NavClock_SetModeRegister(clkMode)
#define NavClock_SetSource(clkSource)           NavClock_SetSourceRegister(clkSource)
#if defined(NavClock__CFG3)
#define NavClock_SetPhase(clkPhase)             NavClock_SetPhaseRegister(clkPhase)
#define NavClock_SetPhaseValue(clkPhase)        NavClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(NavClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define NavClock_CLKEN              (* (reg8 *) NavClock__PM_ACT_CFG)
#define NavClock_CLKEN_PTR          ((reg8 *) NavClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define NavClock_CLKSTBY            (* (reg8 *) NavClock__PM_STBY_CFG)
#define NavClock_CLKSTBY_PTR        ((reg8 *) NavClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define NavClock_DIV_LSB            (* (reg8 *) NavClock__CFG0)
#define NavClock_DIV_LSB_PTR        ((reg8 *) NavClock__CFG0)
#define NavClock_DIV_PTR            ((reg16 *) NavClock__CFG0)

/* Clock MSB divider configuration register. */
#define NavClock_DIV_MSB            (* (reg8 *) NavClock__CFG1)
#define NavClock_DIV_MSB_PTR        ((reg8 *) NavClock__CFG1)

/* Mode and source configuration register */
#define NavClock_MOD_SRC            (* (reg8 *) NavClock__CFG2)
#define NavClock_MOD_SRC_PTR        ((reg8 *) NavClock__CFG2)

#if defined(NavClock__CFG3)
/* Analog clock phase configuration register */
#define NavClock_PHASE              (* (reg8 *) NavClock__CFG3)
#define NavClock_PHASE_PTR          ((reg8 *) NavClock__CFG3)
#endif /* defined(NavClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define NavClock_CLKEN_MASK         NavClock__PM_ACT_MSK
#define NavClock_CLKSTBY_MASK       NavClock__PM_STBY_MSK

/* CFG2 field masks */
#define NavClock_SRC_SEL_MSK        NavClock__CFG2_SRC_SEL_MASK
#define NavClock_MODE_MASK          (~(NavClock_SRC_SEL_MSK))

#if defined(NavClock__CFG3)
/* CFG3 phase mask */
#define NavClock_PHASE_MASK         NavClock__CFG3_PHASE_DLY_MASK
#endif /* defined(NavClock__CFG3) */

#endif /* CY_CLOCK_NavClock_H */


/* [] END OF FILE */
