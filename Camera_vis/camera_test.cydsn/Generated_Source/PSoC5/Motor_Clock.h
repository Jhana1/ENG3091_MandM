/*******************************************************************************
* File Name: Motor_Clock.h
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

#if !defined(CY_CLOCK_Motor_Clock_H)
#define CY_CLOCK_Motor_Clock_H

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

void Motor_Clock_Start(void) ;
void Motor_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Motor_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Motor_Clock_StandbyPower(uint8 state) ;
void Motor_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Motor_Clock_GetDividerRegister(void) ;
void Motor_Clock_SetModeRegister(uint8 modeBitMask) ;
void Motor_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 Motor_Clock_GetModeRegister(void) ;
void Motor_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 Motor_Clock_GetSourceRegister(void) ;
#if defined(Motor_Clock__CFG3)
void Motor_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 Motor_Clock_GetPhaseRegister(void) ;
#endif /* defined(Motor_Clock__CFG3) */

#define Motor_Clock_Enable()                       Motor_Clock_Start()
#define Motor_Clock_Disable()                      Motor_Clock_Stop()
#define Motor_Clock_SetDivider(clkDivider)         Motor_Clock_SetDividerRegister(clkDivider, 1u)
#define Motor_Clock_SetDividerValue(clkDivider)    Motor_Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define Motor_Clock_SetMode(clkMode)               Motor_Clock_SetModeRegister(clkMode)
#define Motor_Clock_SetSource(clkSource)           Motor_Clock_SetSourceRegister(clkSource)
#if defined(Motor_Clock__CFG3)
#define Motor_Clock_SetPhase(clkPhase)             Motor_Clock_SetPhaseRegister(clkPhase)
#define Motor_Clock_SetPhaseValue(clkPhase)        Motor_Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Motor_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Motor_Clock_CLKEN              (* (reg8 *) Motor_Clock__PM_ACT_CFG)
#define Motor_Clock_CLKEN_PTR          ((reg8 *) Motor_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Motor_Clock_CLKSTBY            (* (reg8 *) Motor_Clock__PM_STBY_CFG)
#define Motor_Clock_CLKSTBY_PTR        ((reg8 *) Motor_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Motor_Clock_DIV_LSB            (* (reg8 *) Motor_Clock__CFG0)
#define Motor_Clock_DIV_LSB_PTR        ((reg8 *) Motor_Clock__CFG0)
#define Motor_Clock_DIV_PTR            ((reg16 *) Motor_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define Motor_Clock_DIV_MSB            (* (reg8 *) Motor_Clock__CFG1)
#define Motor_Clock_DIV_MSB_PTR        ((reg8 *) Motor_Clock__CFG1)

/* Mode and source configuration register */
#define Motor_Clock_MOD_SRC            (* (reg8 *) Motor_Clock__CFG2)
#define Motor_Clock_MOD_SRC_PTR        ((reg8 *) Motor_Clock__CFG2)

#if defined(Motor_Clock__CFG3)
/* Analog clock phase configuration register */
#define Motor_Clock_PHASE              (* (reg8 *) Motor_Clock__CFG3)
#define Motor_Clock_PHASE_PTR          ((reg8 *) Motor_Clock__CFG3)
#endif /* defined(Motor_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Motor_Clock_CLKEN_MASK         Motor_Clock__PM_ACT_MSK
#define Motor_Clock_CLKSTBY_MASK       Motor_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define Motor_Clock_SRC_SEL_MSK        Motor_Clock__CFG2_SRC_SEL_MASK
#define Motor_Clock_MODE_MASK          (~(Motor_Clock_SRC_SEL_MSK))

#if defined(Motor_Clock__CFG3)
/* CFG3 phase mask */
#define Motor_Clock_PHASE_MASK         Motor_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(Motor_Clock__CFG3) */

#endif /* CY_CLOCK_Motor_Clock_H */


/* [] END OF FILE */
