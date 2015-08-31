/*******************************************************************************
* File Name: M1Clock.h
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

#if !defined(CY_CLOCK_M1Clock_H)
#define CY_CLOCK_M1Clock_H

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

void M1Clock_Start(void) ;
void M1Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void M1Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void M1Clock_StandbyPower(uint8 state) ;
void M1Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 M1Clock_GetDividerRegister(void) ;
void M1Clock_SetModeRegister(uint8 modeBitMask) ;
void M1Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 M1Clock_GetModeRegister(void) ;
void M1Clock_SetSourceRegister(uint8 clkSource) ;
uint8 M1Clock_GetSourceRegister(void) ;
#if defined(M1Clock__CFG3)
void M1Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 M1Clock_GetPhaseRegister(void) ;
#endif /* defined(M1Clock__CFG3) */

#define M1Clock_Enable()                       M1Clock_Start()
#define M1Clock_Disable()                      M1Clock_Stop()
#define M1Clock_SetDivider(clkDivider)         M1Clock_SetDividerRegister(clkDivider, 1u)
#define M1Clock_SetDividerValue(clkDivider)    M1Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define M1Clock_SetMode(clkMode)               M1Clock_SetModeRegister(clkMode)
#define M1Clock_SetSource(clkSource)           M1Clock_SetSourceRegister(clkSource)
#if defined(M1Clock__CFG3)
#define M1Clock_SetPhase(clkPhase)             M1Clock_SetPhaseRegister(clkPhase)
#define M1Clock_SetPhaseValue(clkPhase)        M1Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(M1Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define M1Clock_CLKEN              (* (reg8 *) M1Clock__PM_ACT_CFG)
#define M1Clock_CLKEN_PTR          ((reg8 *) M1Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define M1Clock_CLKSTBY            (* (reg8 *) M1Clock__PM_STBY_CFG)
#define M1Clock_CLKSTBY_PTR        ((reg8 *) M1Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define M1Clock_DIV_LSB            (* (reg8 *) M1Clock__CFG0)
#define M1Clock_DIV_LSB_PTR        ((reg8 *) M1Clock__CFG0)
#define M1Clock_DIV_PTR            ((reg16 *) M1Clock__CFG0)

/* Clock MSB divider configuration register. */
#define M1Clock_DIV_MSB            (* (reg8 *) M1Clock__CFG1)
#define M1Clock_DIV_MSB_PTR        ((reg8 *) M1Clock__CFG1)

/* Mode and source configuration register */
#define M1Clock_MOD_SRC            (* (reg8 *) M1Clock__CFG2)
#define M1Clock_MOD_SRC_PTR        ((reg8 *) M1Clock__CFG2)

#if defined(M1Clock__CFG3)
/* Analog clock phase configuration register */
#define M1Clock_PHASE              (* (reg8 *) M1Clock__CFG3)
#define M1Clock_PHASE_PTR          ((reg8 *) M1Clock__CFG3)
#endif /* defined(M1Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define M1Clock_CLKEN_MASK         M1Clock__PM_ACT_MSK
#define M1Clock_CLKSTBY_MASK       M1Clock__PM_STBY_MSK

/* CFG2 field masks */
#define M1Clock_SRC_SEL_MSK        M1Clock__CFG2_SRC_SEL_MASK
#define M1Clock_MODE_MASK          (~(M1Clock_SRC_SEL_MSK))

#if defined(M1Clock__CFG3)
/* CFG3 phase mask */
#define M1Clock_PHASE_MASK         M1Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(M1Clock__CFG3) */

#endif /* CY_CLOCK_M1Clock_H */


/* [] END OF FILE */
