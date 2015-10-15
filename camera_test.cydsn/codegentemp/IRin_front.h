/*******************************************************************************
* File Name: IRin_front.h  
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

#if !defined(CY_PINS_IRin_front_H) /* Pins IRin_front_H */
#define CY_PINS_IRin_front_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IRin_front_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IRin_front__PORT == 15 && ((IRin_front__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    IRin_front_Write(uint8 value) ;
void    IRin_front_SetDriveMode(uint8 mode) ;
uint8   IRin_front_ReadDataReg(void) ;
uint8   IRin_front_Read(void) ;
uint8   IRin_front_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define IRin_front_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define IRin_front_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define IRin_front_DM_RES_UP          PIN_DM_RES_UP
#define IRin_front_DM_RES_DWN         PIN_DM_RES_DWN
#define IRin_front_DM_OD_LO           PIN_DM_OD_LO
#define IRin_front_DM_OD_HI           PIN_DM_OD_HI
#define IRin_front_DM_STRONG          PIN_DM_STRONG
#define IRin_front_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define IRin_front_MASK               IRin_front__MASK
#define IRin_front_SHIFT              IRin_front__SHIFT
#define IRin_front_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IRin_front_PS                     (* (reg8 *) IRin_front__PS)
/* Data Register */
#define IRin_front_DR                     (* (reg8 *) IRin_front__DR)
/* Port Number */
#define IRin_front_PRT_NUM                (* (reg8 *) IRin_front__PRT) 
/* Connect to Analog Globals */                                                  
#define IRin_front_AG                     (* (reg8 *) IRin_front__AG)                       
/* Analog MUX bux enable */
#define IRin_front_AMUX                   (* (reg8 *) IRin_front__AMUX) 
/* Bidirectional Enable */                                                        
#define IRin_front_BIE                    (* (reg8 *) IRin_front__BIE)
/* Bit-mask for Aliased Register Access */
#define IRin_front_BIT_MASK               (* (reg8 *) IRin_front__BIT_MASK)
/* Bypass Enable */
#define IRin_front_BYP                    (* (reg8 *) IRin_front__BYP)
/* Port wide control signals */                                                   
#define IRin_front_CTL                    (* (reg8 *) IRin_front__CTL)
/* Drive Modes */
#define IRin_front_DM0                    (* (reg8 *) IRin_front__DM0) 
#define IRin_front_DM1                    (* (reg8 *) IRin_front__DM1)
#define IRin_front_DM2                    (* (reg8 *) IRin_front__DM2) 
/* Input Buffer Disable Override */
#define IRin_front_INP_DIS                (* (reg8 *) IRin_front__INP_DIS)
/* LCD Common or Segment Drive */
#define IRin_front_LCD_COM_SEG            (* (reg8 *) IRin_front__LCD_COM_SEG)
/* Enable Segment LCD */
#define IRin_front_LCD_EN                 (* (reg8 *) IRin_front__LCD_EN)
/* Slew Rate Control */
#define IRin_front_SLW                    (* (reg8 *) IRin_front__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IRin_front_PRTDSI__CAPS_SEL       (* (reg8 *) IRin_front__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IRin_front_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IRin_front__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IRin_front_PRTDSI__OE_SEL0        (* (reg8 *) IRin_front__PRTDSI__OE_SEL0) 
#define IRin_front_PRTDSI__OE_SEL1        (* (reg8 *) IRin_front__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IRin_front_PRTDSI__OUT_SEL0       (* (reg8 *) IRin_front__PRTDSI__OUT_SEL0) 
#define IRin_front_PRTDSI__OUT_SEL1       (* (reg8 *) IRin_front__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IRin_front_PRTDSI__SYNC_OUT       (* (reg8 *) IRin_front__PRTDSI__SYNC_OUT) 


#if defined(IRin_front__INTSTAT)  /* Interrupt Registers */

    #define IRin_front_INTSTAT                (* (reg8 *) IRin_front__INTSTAT)
    #define IRin_front_SNAP                   (* (reg8 *) IRin_front__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IRin_front_H */


/* [] END OF FILE */
