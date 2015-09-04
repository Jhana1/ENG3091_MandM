/*******************************************************************************
* File Name: ISR_CHECKP.h  
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

#if !defined(CY_PINS_ISR_CHECKP_H) /* Pins ISR_CHECKP_H */
#define CY_PINS_ISR_CHECKP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ISR_CHECKP_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ISR_CHECKP__PORT == 15 && ((ISR_CHECKP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ISR_CHECKP_Write(uint8 value) ;
void    ISR_CHECKP_SetDriveMode(uint8 mode) ;
uint8   ISR_CHECKP_ReadDataReg(void) ;
uint8   ISR_CHECKP_Read(void) ;
uint8   ISR_CHECKP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ISR_CHECKP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ISR_CHECKP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ISR_CHECKP_DM_RES_UP          PIN_DM_RES_UP
#define ISR_CHECKP_DM_RES_DWN         PIN_DM_RES_DWN
#define ISR_CHECKP_DM_OD_LO           PIN_DM_OD_LO
#define ISR_CHECKP_DM_OD_HI           PIN_DM_OD_HI
#define ISR_CHECKP_DM_STRONG          PIN_DM_STRONG
#define ISR_CHECKP_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ISR_CHECKP_MASK               ISR_CHECKP__MASK
#define ISR_CHECKP_SHIFT              ISR_CHECKP__SHIFT
#define ISR_CHECKP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ISR_CHECKP_PS                     (* (reg8 *) ISR_CHECKP__PS)
/* Data Register */
#define ISR_CHECKP_DR                     (* (reg8 *) ISR_CHECKP__DR)
/* Port Number */
#define ISR_CHECKP_PRT_NUM                (* (reg8 *) ISR_CHECKP__PRT) 
/* Connect to Analog Globals */                                                  
#define ISR_CHECKP_AG                     (* (reg8 *) ISR_CHECKP__AG)                       
/* Analog MUX bux enable */
#define ISR_CHECKP_AMUX                   (* (reg8 *) ISR_CHECKP__AMUX) 
/* Bidirectional Enable */                                                        
#define ISR_CHECKP_BIE                    (* (reg8 *) ISR_CHECKP__BIE)
/* Bit-mask for Aliased Register Access */
#define ISR_CHECKP_BIT_MASK               (* (reg8 *) ISR_CHECKP__BIT_MASK)
/* Bypass Enable */
#define ISR_CHECKP_BYP                    (* (reg8 *) ISR_CHECKP__BYP)
/* Port wide control signals */                                                   
#define ISR_CHECKP_CTL                    (* (reg8 *) ISR_CHECKP__CTL)
/* Drive Modes */
#define ISR_CHECKP_DM0                    (* (reg8 *) ISR_CHECKP__DM0) 
#define ISR_CHECKP_DM1                    (* (reg8 *) ISR_CHECKP__DM1)
#define ISR_CHECKP_DM2                    (* (reg8 *) ISR_CHECKP__DM2) 
/* Input Buffer Disable Override */
#define ISR_CHECKP_INP_DIS                (* (reg8 *) ISR_CHECKP__INP_DIS)
/* LCD Common or Segment Drive */
#define ISR_CHECKP_LCD_COM_SEG            (* (reg8 *) ISR_CHECKP__LCD_COM_SEG)
/* Enable Segment LCD */
#define ISR_CHECKP_LCD_EN                 (* (reg8 *) ISR_CHECKP__LCD_EN)
/* Slew Rate Control */
#define ISR_CHECKP_SLW                    (* (reg8 *) ISR_CHECKP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ISR_CHECKP_PRTDSI__CAPS_SEL       (* (reg8 *) ISR_CHECKP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ISR_CHECKP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ISR_CHECKP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ISR_CHECKP_PRTDSI__OE_SEL0        (* (reg8 *) ISR_CHECKP__PRTDSI__OE_SEL0) 
#define ISR_CHECKP_PRTDSI__OE_SEL1        (* (reg8 *) ISR_CHECKP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ISR_CHECKP_PRTDSI__OUT_SEL0       (* (reg8 *) ISR_CHECKP__PRTDSI__OUT_SEL0) 
#define ISR_CHECKP_PRTDSI__OUT_SEL1       (* (reg8 *) ISR_CHECKP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ISR_CHECKP_PRTDSI__SYNC_OUT       (* (reg8 *) ISR_CHECKP__PRTDSI__SYNC_OUT) 


#if defined(ISR_CHECKP__INTSTAT)  /* Interrupt Registers */

    #define ISR_CHECKP_INTSTAT                (* (reg8 *) ISR_CHECKP__INTSTAT)
    #define ISR_CHECKP_SNAP                   (* (reg8 *) ISR_CHECKP__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ISR_CHECKP_H */


/* [] END OF FILE */
