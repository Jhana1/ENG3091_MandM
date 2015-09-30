/*******************************************************************************
* File Name: BUT_CLOCK.h
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

#if !defined(CY_CLOCK_BUT_CLOCK_H)
#define CY_CLOCK_BUT_CLOCK_H

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

void BUT_CLOCK_Start(void) ;
void BUT_CLOCK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void BUT_CLOCK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void BUT_CLOCK_StandbyPower(uint8 state) ;
void BUT_CLOCK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 BUT_CLOCK_GetDividerRegister(void) ;
void BUT_CLOCK_SetModeRegister(uint8 modeBitMask) ;
void BUT_CLOCK_ClearModeRegister(uint8 modeBitMask) ;
uint8 BUT_CLOCK_GetModeRegister(void) ;
void BUT_CLOCK_SetSourceRegister(uint8 clkSource) ;
uint8 BUT_CLOCK_GetSourceRegister(void) ;
#if defined(BUT_CLOCK__CFG3)
void BUT_CLOCK_SetPhaseRegister(uint8 clkPhase) ;
uint8 BUT_CLOCK_GetPhaseRegister(void) ;
#endif /* defined(BUT_CLOCK__CFG3) */

#define BUT_CLOCK_Enable()                       BUT_CLOCK_Start()
#define BUT_CLOCK_Disable()                      BUT_CLOCK_Stop()
#define BUT_CLOCK_SetDivider(clkDivider)         BUT_CLOCK_SetDividerRegister(clkDivider, 1u)
#define BUT_CLOCK_SetDividerValue(clkDivider)    BUT_CLOCK_SetDividerRegister((clkDivider) - 1u, 1u)
#define BUT_CLOCK_SetMode(clkMode)               BUT_CLOCK_SetModeRegister(clkMode)
#define BUT_CLOCK_SetSource(clkSource)           BUT_CLOCK_SetSourceRegister(clkSource)
#if defined(BUT_CLOCK__CFG3)
#define BUT_CLOCK_SetPhase(clkPhase)             BUT_CLOCK_SetPhaseRegister(clkPhase)
#define BUT_CLOCK_SetPhaseValue(clkPhase)        BUT_CLOCK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(BUT_CLOCK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define BUT_CLOCK_CLKEN              (* (reg8 *) BUT_CLOCK__PM_ACT_CFG)
#define BUT_CLOCK_CLKEN_PTR          ((reg8 *) BUT_CLOCK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define BUT_CLOCK_CLKSTBY            (* (reg8 *) BUT_CLOCK__PM_STBY_CFG)
#define BUT_CLOCK_CLKSTBY_PTR        ((reg8 *) BUT_CLOCK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define BUT_CLOCK_DIV_LSB            (* (reg8 *) BUT_CLOCK__CFG0)
#define BUT_CLOCK_DIV_LSB_PTR        ((reg8 *) BUT_CLOCK__CFG0)
#define BUT_CLOCK_DIV_PTR            ((reg16 *) BUT_CLOCK__CFG0)

/* Clock MSB divider configuration register. */
#define BUT_CLOCK_DIV_MSB            (* (reg8 *) BUT_CLOCK__CFG1)
#define BUT_CLOCK_DIV_MSB_PTR        ((reg8 *) BUT_CLOCK__CFG1)

/* Mode and source configuration register */
#define BUT_CLOCK_MOD_SRC            (* (reg8 *) BUT_CLOCK__CFG2)
#define BUT_CLOCK_MOD_SRC_PTR        ((reg8 *) BUT_CLOCK__CFG2)

#if defined(BUT_CLOCK__CFG3)
/* Analog clock phase configuration register */
#define BUT_CLOCK_PHASE              (* (reg8 *) BUT_CLOCK__CFG3)
#define BUT_CLOCK_PHASE_PTR          ((reg8 *) BUT_CLOCK__CFG3)
#endif /* defined(BUT_CLOCK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define BUT_CLOCK_CLKEN_MASK         BUT_CLOCK__PM_ACT_MSK
#define BUT_CLOCK_CLKSTBY_MASK       BUT_CLOCK__PM_STBY_MSK

/* CFG2 field masks */
#define BUT_CLOCK_SRC_SEL_MSK        BUT_CLOCK__CFG2_SRC_SEL_MASK
#define BUT_CLOCK_MODE_MASK          (~(BUT_CLOCK_SRC_SEL_MSK))

#if defined(BUT_CLOCK__CFG3)
/* CFG3 phase mask */
#define BUT_CLOCK_PHASE_MASK         BUT_CLOCK__CFG3_PHASE_DLY_MASK
#endif /* defined(BUT_CLOCK__CFG3) */

#endif /* CY_CLOCK_BUT_CLOCK_H */


/* [] END OF FILE */
