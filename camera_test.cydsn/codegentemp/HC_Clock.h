/*******************************************************************************
* File Name: HC_CLOCK.h
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

#if !defined(CY_CLOCK_HC_CLOCK_H)
#define CY_CLOCK_HC_CLOCK_H

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

void HC_CLOCK_Start(void) ;
void HC_CLOCK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void HC_CLOCK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void HC_CLOCK_StandbyPower(uint8 state) ;
void HC_CLOCK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 HC_CLOCK_GetDividerRegister(void) ;
void HC_CLOCK_SetModeRegister(uint8 modeBitMask) ;
void HC_CLOCK_ClearModeRegister(uint8 modeBitMask) ;
uint8 HC_CLOCK_GetModeRegister(void) ;
void HC_CLOCK_SetSourceRegister(uint8 clkSource) ;
uint8 HC_CLOCK_GetSourceRegister(void) ;
#if defined(HC_CLOCK__CFG3)
void HC_CLOCK_SetPhaseRegister(uint8 clkPhase) ;
uint8 HC_CLOCK_GetPhaseRegister(void) ;
#endif /* defined(HC_CLOCK__CFG3) */

#define HC_CLOCK_Enable()                       HC_CLOCK_Start()
#define HC_CLOCK_Disable()                      HC_CLOCK_Stop()
#define HC_CLOCK_SetDivider(clkDivider)         HC_CLOCK_SetDividerRegister(clkDivider, 1u)
#define HC_CLOCK_SetDividerValue(clkDivider)    HC_CLOCK_SetDividerRegister((clkDivider) - 1u, 1u)
#define HC_CLOCK_SetMode(clkMode)               HC_CLOCK_SetModeRegister(clkMode)
#define HC_CLOCK_SetSource(clkSource)           HC_CLOCK_SetSourceRegister(clkSource)
#if defined(HC_CLOCK__CFG3)
#define HC_CLOCK_SetPhase(clkPhase)             HC_CLOCK_SetPhaseRegister(clkPhase)
#define HC_CLOCK_SetPhaseValue(clkPhase)        HC_CLOCK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(HC_CLOCK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define HC_CLOCK_CLKEN              (* (reg8 *) HC_CLOCK__PM_ACT_CFG)
#define HC_CLOCK_CLKEN_PTR          ((reg8 *) HC_CLOCK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define HC_CLOCK_CLKSTBY            (* (reg8 *) HC_CLOCK__PM_STBY_CFG)
#define HC_CLOCK_CLKSTBY_PTR        ((reg8 *) HC_CLOCK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define HC_CLOCK_DIV_LSB            (* (reg8 *) HC_CLOCK__CFG0)
#define HC_CLOCK_DIV_LSB_PTR        ((reg8 *) HC_CLOCK__CFG0)
#define HC_CLOCK_DIV_PTR            ((reg16 *) HC_CLOCK__CFG0)

/* Clock MSB divider configuration register. */
#define HC_CLOCK_DIV_MSB            (* (reg8 *) HC_CLOCK__CFG1)
#define HC_CLOCK_DIV_MSB_PTR        ((reg8 *) HC_CLOCK__CFG1)

/* Mode and source configuration register */
#define HC_CLOCK_MOD_SRC            (* (reg8 *) HC_CLOCK__CFG2)
#define HC_CLOCK_MOD_SRC_PTR        ((reg8 *) HC_CLOCK__CFG2)

#if defined(HC_CLOCK__CFG3)
/* Analog clock phase configuration register */
#define HC_CLOCK_PHASE              (* (reg8 *) HC_CLOCK__CFG3)
#define HC_CLOCK_PHASE_PTR          ((reg8 *) HC_CLOCK__CFG3)
#endif /* defined(HC_CLOCK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define HC_CLOCK_CLKEN_MASK         HC_CLOCK__PM_ACT_MSK
#define HC_CLOCK_CLKSTBY_MASK       HC_CLOCK__PM_STBY_MSK

/* CFG2 field masks */
#define HC_CLOCK_SRC_SEL_MSK        HC_CLOCK__CFG2_SRC_SEL_MASK
#define HC_CLOCK_MODE_MASK          (~(HC_CLOCK_SRC_SEL_MSK))

#if defined(HC_CLOCK__CFG3)
/* CFG3 phase mask */
#define HC_CLOCK_PHASE_MASK         HC_CLOCK__CFG3_PHASE_DLY_MASK
#endif /* defined(HC_CLOCK__CFG3) */

#endif /* CY_CLOCK_HC_CLOCK_H */


/* [] END OF FILE */
