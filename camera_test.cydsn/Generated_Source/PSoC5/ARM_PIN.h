/*******************************************************************************
* File Name: ARM_PIN.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ARM_PIN_H) /* Pins ARM_PIN_H */
#define CY_PINS_ARM_PIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ARM_PIN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ARM_PIN__PORT == 15 && ((ARM_PIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ARM_PIN_Write(uint8 value) ;
void    ARM_PIN_SetDriveMode(uint8 mode) ;
uint8   ARM_PIN_ReadDataReg(void) ;
uint8   ARM_PIN_Read(void) ;
uint8   ARM_PIN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ARM_PIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ARM_PIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ARM_PIN_DM_RES_UP          PIN_DM_RES_UP
#define ARM_PIN_DM_RES_DWN         PIN_DM_RES_DWN
#define ARM_PIN_DM_OD_LO           PIN_DM_OD_LO
#define ARM_PIN_DM_OD_HI           PIN_DM_OD_HI
#define ARM_PIN_DM_STRONG          PIN_DM_STRONG
#define ARM_PIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ARM_PIN_MASK               ARM_PIN__MASK
#define ARM_PIN_SHIFT              ARM_PIN__SHIFT
#define ARM_PIN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ARM_PIN_PS                     (* (reg8 *) ARM_PIN__PS)
/* Data Register */
#define ARM_PIN_DR                     (* (reg8 *) ARM_PIN__DR)
/* Port Number */
#define ARM_PIN_PRT_NUM                (* (reg8 *) ARM_PIN__PRT) 
/* Connect to Analog Globals */                                                  
#define ARM_PIN_AG                     (* (reg8 *) ARM_PIN__AG)                       
/* Analog MUX bux enable */
#define ARM_PIN_AMUX                   (* (reg8 *) ARM_PIN__AMUX) 
/* Bidirectional Enable */                                                        
#define ARM_PIN_BIE                    (* (reg8 *) ARM_PIN__BIE)
/* Bit-mask for Aliased Register Access */
#define ARM_PIN_BIT_MASK               (* (reg8 *) ARM_PIN__BIT_MASK)
/* Bypass Enable */
#define ARM_PIN_BYP                    (* (reg8 *) ARM_PIN__BYP)
/* Port wide control signals */                                                   
#define ARM_PIN_CTL                    (* (reg8 *) ARM_PIN__CTL)
/* Drive Modes */
#define ARM_PIN_DM0                    (* (reg8 *) ARM_PIN__DM0) 
#define ARM_PIN_DM1                    (* (reg8 *) ARM_PIN__DM1)
#define ARM_PIN_DM2                    (* (reg8 *) ARM_PIN__DM2) 
/* Input Buffer Disable Override */
#define ARM_PIN_INP_DIS                (* (reg8 *) ARM_PIN__INP_DIS)
/* LCD Common or Segment Drive */
#define ARM_PIN_LCD_COM_SEG            (* (reg8 *) ARM_PIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define ARM_PIN_LCD_EN                 (* (reg8 *) ARM_PIN__LCD_EN)
/* Slew Rate Control */
#define ARM_PIN_SLW                    (* (reg8 *) ARM_PIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ARM_PIN_PRTDSI__CAPS_SEL       (* (reg8 *) ARM_PIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ARM_PIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ARM_PIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ARM_PIN_PRTDSI__OE_SEL0        (* (reg8 *) ARM_PIN__PRTDSI__OE_SEL0) 
#define ARM_PIN_PRTDSI__OE_SEL1        (* (reg8 *) ARM_PIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ARM_PIN_PRTDSI__OUT_SEL0       (* (reg8 *) ARM_PIN__PRTDSI__OUT_SEL0) 
#define ARM_PIN_PRTDSI__OUT_SEL1       (* (reg8 *) ARM_PIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ARM_PIN_PRTDSI__SYNC_OUT       (* (reg8 *) ARM_PIN__PRTDSI__SYNC_OUT) 


#if defined(ARM_PIN__INTSTAT)  /* Interrupt Registers */

    #define ARM_PIN_INTSTAT                (* (reg8 *) ARM_PIN__INTSTAT)
    #define ARM_PIN_SNAP                   (* (reg8 *) ARM_PIN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ARM_PIN_H */


/* [] END OF FILE */
