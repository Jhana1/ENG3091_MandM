/*******************************************************************************
* File Name: DB5.h  
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

#if !defined(CY_PINS_DB5_H) /* Pins DB5_H */
#define CY_PINS_DB5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DB5_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DB5__PORT == 15 && ((DB5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DB5_Write(uint8 value) ;
void    DB5_SetDriveMode(uint8 mode) ;
uint8   DB5_ReadDataReg(void) ;
uint8   DB5_Read(void) ;
uint8   DB5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DB5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DB5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DB5_DM_RES_UP          PIN_DM_RES_UP
#define DB5_DM_RES_DWN         PIN_DM_RES_DWN
#define DB5_DM_OD_LO           PIN_DM_OD_LO
#define DB5_DM_OD_HI           PIN_DM_OD_HI
#define DB5_DM_STRONG          PIN_DM_STRONG
#define DB5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DB5_MASK               DB5__MASK
#define DB5_SHIFT              DB5__SHIFT
#define DB5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DB5_PS                     (* (reg8 *) DB5__PS)
/* Data Register */
#define DB5_DR                     (* (reg8 *) DB5__DR)
/* Port Number */
#define DB5_PRT_NUM                (* (reg8 *) DB5__PRT) 
/* Connect to Analog Globals */                                                  
#define DB5_AG                     (* (reg8 *) DB5__AG)                       
/* Analog MUX bux enable */
#define DB5_AMUX                   (* (reg8 *) DB5__AMUX) 
/* Bidirectional Enable */                                                        
#define DB5_BIE                    (* (reg8 *) DB5__BIE)
/* Bit-mask for Aliased Register Access */
#define DB5_BIT_MASK               (* (reg8 *) DB5__BIT_MASK)
/* Bypass Enable */
#define DB5_BYP                    (* (reg8 *) DB5__BYP)
/* Port wide control signals */                                                   
#define DB5_CTL                    (* (reg8 *) DB5__CTL)
/* Drive Modes */
#define DB5_DM0                    (* (reg8 *) DB5__DM0) 
#define DB5_DM1                    (* (reg8 *) DB5__DM1)
#define DB5_DM2                    (* (reg8 *) DB5__DM2) 
/* Input Buffer Disable Override */
#define DB5_INP_DIS                (* (reg8 *) DB5__INP_DIS)
/* LCD Common or Segment Drive */
#define DB5_LCD_COM_SEG            (* (reg8 *) DB5__LCD_COM_SEG)
/* Enable Segment LCD */
#define DB5_LCD_EN                 (* (reg8 *) DB5__LCD_EN)
/* Slew Rate Control */
#define DB5_SLW                    (* (reg8 *) DB5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DB5_PRTDSI__CAPS_SEL       (* (reg8 *) DB5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DB5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DB5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DB5_PRTDSI__OE_SEL0        (* (reg8 *) DB5__PRTDSI__OE_SEL0) 
#define DB5_PRTDSI__OE_SEL1        (* (reg8 *) DB5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DB5_PRTDSI__OUT_SEL0       (* (reg8 *) DB5__PRTDSI__OUT_SEL0) 
#define DB5_PRTDSI__OUT_SEL1       (* (reg8 *) DB5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DB5_PRTDSI__SYNC_OUT       (* (reg8 *) DB5__PRTDSI__SYNC_OUT) 


#if defined(DB5__INTSTAT)  /* Interrupt Registers */

    #define DB5_INTSTAT                (* (reg8 *) DB5__INTSTAT)
    #define DB5_SNAP                   (* (reg8 *) DB5__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DB5_H */


/* [] END OF FILE */
