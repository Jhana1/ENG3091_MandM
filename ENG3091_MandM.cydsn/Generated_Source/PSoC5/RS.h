/*******************************************************************************
* File Name: RS.h  
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

#if !defined(CY_PINS_RS_H) /* Pins RS_H */
#define CY_PINS_RS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RS__PORT == 15 && ((RS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RS_Write(uint8 value) ;
void    RS_SetDriveMode(uint8 mode) ;
uint8   RS_ReadDataReg(void) ;
uint8   RS_Read(void) ;
uint8   RS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RS_DM_RES_UP          PIN_DM_RES_UP
#define RS_DM_RES_DWN         PIN_DM_RES_DWN
#define RS_DM_OD_LO           PIN_DM_OD_LO
#define RS_DM_OD_HI           PIN_DM_OD_HI
#define RS_DM_STRONG          PIN_DM_STRONG
#define RS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RS_MASK               RS__MASK
#define RS_SHIFT              RS__SHIFT
#define RS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RS_PS                     (* (reg8 *) RS__PS)
/* Data Register */
#define RS_DR                     (* (reg8 *) RS__DR)
/* Port Number */
#define RS_PRT_NUM                (* (reg8 *) RS__PRT) 
/* Connect to Analog Globals */                                                  
#define RS_AG                     (* (reg8 *) RS__AG)                       
/* Analog MUX bux enable */
#define RS_AMUX                   (* (reg8 *) RS__AMUX) 
/* Bidirectional Enable */                                                        
#define RS_BIE                    (* (reg8 *) RS__BIE)
/* Bit-mask for Aliased Register Access */
#define RS_BIT_MASK               (* (reg8 *) RS__BIT_MASK)
/* Bypass Enable */
#define RS_BYP                    (* (reg8 *) RS__BYP)
/* Port wide control signals */                                                   
#define RS_CTL                    (* (reg8 *) RS__CTL)
/* Drive Modes */
#define RS_DM0                    (* (reg8 *) RS__DM0) 
#define RS_DM1                    (* (reg8 *) RS__DM1)
#define RS_DM2                    (* (reg8 *) RS__DM2) 
/* Input Buffer Disable Override */
#define RS_INP_DIS                (* (reg8 *) RS__INP_DIS)
/* LCD Common or Segment Drive */
#define RS_LCD_COM_SEG            (* (reg8 *) RS__LCD_COM_SEG)
/* Enable Segment LCD */
#define RS_LCD_EN                 (* (reg8 *) RS__LCD_EN)
/* Slew Rate Control */
#define RS_SLW                    (* (reg8 *) RS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RS_PRTDSI__CAPS_SEL       (* (reg8 *) RS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RS_PRTDSI__OE_SEL0        (* (reg8 *) RS__PRTDSI__OE_SEL0) 
#define RS_PRTDSI__OE_SEL1        (* (reg8 *) RS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RS_PRTDSI__OUT_SEL0       (* (reg8 *) RS__PRTDSI__OUT_SEL0) 
#define RS_PRTDSI__OUT_SEL1       (* (reg8 *) RS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RS_PRTDSI__SYNC_OUT       (* (reg8 *) RS__PRTDSI__SYNC_OUT) 


#if defined(RS__INTSTAT)  /* Interrupt Registers */

    #define RS_INTSTAT                (* (reg8 *) RS__INTSTAT)
    #define RS_SNAP                   (* (reg8 *) RS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RS_H */


/* [] END OF FILE */
