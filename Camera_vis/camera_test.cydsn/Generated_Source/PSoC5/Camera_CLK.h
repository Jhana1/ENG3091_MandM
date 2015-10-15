/*******************************************************************************
* File Name: Camera_CLK.h
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

#if !defined(CY_CLOCK_Camera_CLK_H)
#define CY_CLOCK_Camera_CLK_H

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

void Camera_CLK_Start(void) ;
void Camera_CLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Camera_CLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Camera_CLK_StandbyPower(uint8 state) ;
void Camera_CLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Camera_CLK_GetDividerRegister(void) ;
void Camera_CLK_SetModeRegister(uint8 modeBitMask) ;
void Camera_CLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 Camera_CLK_GetModeRegister(void) ;
void Camera_CLK_SetSourceRegister(uint8 clkSource) ;
uint8 Camera_CLK_GetSourceRegister(void) ;
#if defined(Camera_CLK__CFG3)
void Camera_CLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 Camera_CLK_GetPhaseRegister(void) ;
#endif /* defined(Camera_CLK__CFG3) */

#define Camera_CLK_Enable()                       Camera_CLK_Start()
#define Camera_CLK_Disable()                      Camera_CLK_Stop()
#define Camera_CLK_SetDivider(clkDivider)         Camera_CLK_SetDividerRegister(clkDivider, 1u)
#define Camera_CLK_SetDividerValue(clkDivider)    Camera_CLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define Camera_CLK_SetMode(clkMode)               Camera_CLK_SetModeRegister(clkMode)
#define Camera_CLK_SetSource(clkSource)           Camera_CLK_SetSourceRegister(clkSource)
#if defined(Camera_CLK__CFG3)
#define Camera_CLK_SetPhase(clkPhase)             Camera_CLK_SetPhaseRegister(clkPhase)
#define Camera_CLK_SetPhaseValue(clkPhase)        Camera_CLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Camera_CLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Camera_CLK_CLKEN              (* (reg8 *) Camera_CLK__PM_ACT_CFG)
#define Camera_CLK_CLKEN_PTR          ((reg8 *) Camera_CLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Camera_CLK_CLKSTBY            (* (reg8 *) Camera_CLK__PM_STBY_CFG)
#define Camera_CLK_CLKSTBY_PTR        ((reg8 *) Camera_CLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Camera_CLK_DIV_LSB            (* (reg8 *) Camera_CLK__CFG0)
#define Camera_CLK_DIV_LSB_PTR        ((reg8 *) Camera_CLK__CFG0)
#define Camera_CLK_DIV_PTR            ((reg16 *) Camera_CLK__CFG0)

/* Clock MSB divider configuration register. */
#define Camera_CLK_DIV_MSB            (* (reg8 *) Camera_CLK__CFG1)
#define Camera_CLK_DIV_MSB_PTR        ((reg8 *) Camera_CLK__CFG1)

/* Mode and source configuration register */
#define Camera_CLK_MOD_SRC            (* (reg8 *) Camera_CLK__CFG2)
#define Camera_CLK_MOD_SRC_PTR        ((reg8 *) Camera_CLK__CFG2)

#if defined(Camera_CLK__CFG3)
/* Analog clock phase configuration register */
#define Camera_CLK_PHASE              (* (reg8 *) Camera_CLK__CFG3)
#define Camera_CLK_PHASE_PTR          ((reg8 *) Camera_CLK__CFG3)
#endif /* defined(Camera_CLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Camera_CLK_CLKEN_MASK         Camera_CLK__PM_ACT_MSK
#define Camera_CLK_CLKSTBY_MASK       Camera_CLK__PM_STBY_MSK

/* CFG2 field masks */
#define Camera_CLK_SRC_SEL_MSK        Camera_CLK__CFG2_SRC_SEL_MASK
#define Camera_CLK_MODE_MASK          (~(Camera_CLK_SRC_SEL_MSK))

#if defined(Camera_CLK__CFG3)
/* CFG3 phase mask */
#define Camera_CLK_PHASE_MASK         Camera_CLK__CFG3_PHASE_DLY_MASK
#endif /* defined(Camera_CLK__CFG3) */

#endif /* CY_CLOCK_Camera_CLK_H */


/* [] END OF FILE */
