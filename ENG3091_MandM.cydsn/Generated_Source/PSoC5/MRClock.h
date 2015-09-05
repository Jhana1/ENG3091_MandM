/*******************************************************************************
* File Name: MRClock.h
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

#if !defined(CY_CLOCK_MRClock_H)
#define CY_CLOCK_MRClock_H

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

void MRClock_Start(void) ;
void MRClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void MRClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void MRClock_StandbyPower(uint8 state) ;
void MRClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 MRClock_GetDividerRegister(void) ;
void MRClock_SetModeRegister(uint8 modeBitMask) ;
void MRClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 MRClock_GetModeRegister(void) ;
void MRClock_SetSourceRegister(uint8 clkSource) ;
uint8 MRClock_GetSourceRegister(void) ;
#if defined(MRClock__CFG3)
void MRClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 MRClock_GetPhaseRegister(void) ;
#endif /* defined(MRClock__CFG3) */

#define MRClock_Enable()                       MRClock_Start()
#define MRClock_Disable()                      MRClock_Stop()
#define MRClock_SetDivider(clkDivider)         MRClock_SetDividerRegister(clkDivider, 1u)
#define MRClock_SetDividerValue(clkDivider)    MRClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define MRClock_SetMode(clkMode)               MRClock_SetModeRegister(clkMode)
#define MRClock_SetSource(clkSource)           MRClock_SetSourceRegister(clkSource)
#if defined(MRClock__CFG3)
#define MRClock_SetPhase(clkPhase)             MRClock_SetPhaseRegister(clkPhase)
#define MRClock_SetPhaseValue(clkPhase)        MRClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(MRClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define MRClock_CLKEN              (* (reg8 *) MRClock__PM_ACT_CFG)
#define MRClock_CLKEN_PTR          ((reg8 *) MRClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define MRClock_CLKSTBY            (* (reg8 *) MRClock__PM_STBY_CFG)
#define MRClock_CLKSTBY_PTR        ((reg8 *) MRClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define MRClock_DIV_LSB            (* (reg8 *) MRClock__CFG0)
#define MRClock_DIV_LSB_PTR        ((reg8 *) MRClock__CFG0)
#define MRClock_DIV_PTR            ((reg16 *) MRClock__CFG0)

/* Clock MSB divider configuration register. */
#define MRClock_DIV_MSB            (* (reg8 *) MRClock__CFG1)
#define MRClock_DIV_MSB_PTR        ((reg8 *) MRClock__CFG1)

/* Mode and source configuration register */
#define MRClock_MOD_SRC            (* (reg8 *) MRClock__CFG2)
#define MRClock_MOD_SRC_PTR        ((reg8 *) MRClock__CFG2)

#if defined(MRClock__CFG3)
/* Analog clock phase configuration register */
#define MRClock_PHASE              (* (reg8 *) MRClock__CFG3)
#define MRClock_PHASE_PTR          ((reg8 *) MRClock__CFG3)
#endif /* defined(MRClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define MRClock_CLKEN_MASK         MRClock__PM_ACT_MSK
#define MRClock_CLKSTBY_MASK       MRClock__PM_STBY_MSK

/* CFG2 field masks */
#define MRClock_SRC_SEL_MSK        MRClock__CFG2_SRC_SEL_MASK
#define MRClock_MODE_MASK          (~(MRClock_SRC_SEL_MSK))

#if defined(MRClock__CFG3)
/* CFG3 phase mask */
#define MRClock_PHASE_MASK         MRClock__CFG3_PHASE_DLY_MASK
#endif /* defined(MRClock__CFG3) */

#endif /* CY_CLOCK_MRClock_H */


/* [] END OF FILE */
