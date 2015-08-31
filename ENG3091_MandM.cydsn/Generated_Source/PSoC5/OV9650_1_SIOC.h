/*******************************************************************************
* File Name: OV9650_1_SIOC.h  
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

#if !defined(CY_PINS_OV9650_1_SIOC_H) /* Pins OV9650_1_SIOC_H */
#define CY_PINS_OV9650_1_SIOC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OV9650_1_SIOC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OV9650_1_SIOC__PORT == 15 && ((OV9650_1_SIOC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    OV9650_1_SIOC_Write(uint8 value) ;
void    OV9650_1_SIOC_SetDriveMode(uint8 mode) ;
uint8   OV9650_1_SIOC_ReadDataReg(void) ;
uint8   OV9650_1_SIOC_Read(void) ;
uint8   OV9650_1_SIOC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OV9650_1_SIOC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define OV9650_1_SIOC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define OV9650_1_SIOC_DM_RES_UP          PIN_DM_RES_UP
#define OV9650_1_SIOC_DM_RES_DWN         PIN_DM_RES_DWN
#define OV9650_1_SIOC_DM_OD_LO           PIN_DM_OD_LO
#define OV9650_1_SIOC_DM_OD_HI           PIN_DM_OD_HI
#define OV9650_1_SIOC_DM_STRONG          PIN_DM_STRONG
#define OV9650_1_SIOC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define OV9650_1_SIOC_MASK               OV9650_1_SIOC__MASK
#define OV9650_1_SIOC_SHIFT              OV9650_1_SIOC__SHIFT
#define OV9650_1_SIOC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OV9650_1_SIOC_PS                     (* (reg8 *) OV9650_1_SIOC__PS)
/* Data Register */
#define OV9650_1_SIOC_DR                     (* (reg8 *) OV9650_1_SIOC__DR)
/* Port Number */
#define OV9650_1_SIOC_PRT_NUM                (* (reg8 *) OV9650_1_SIOC__PRT) 
/* Connect to Analog Globals */                                                  
#define OV9650_1_SIOC_AG                     (* (reg8 *) OV9650_1_SIOC__AG)                       
/* Analog MUX bux enable */
#define OV9650_1_SIOC_AMUX                   (* (reg8 *) OV9650_1_SIOC__AMUX) 
/* Bidirectional Enable */                                                        
#define OV9650_1_SIOC_BIE                    (* (reg8 *) OV9650_1_SIOC__BIE)
/* Bit-mask for Aliased Register Access */
#define OV9650_1_SIOC_BIT_MASK               (* (reg8 *) OV9650_1_SIOC__BIT_MASK)
/* Bypass Enable */
#define OV9650_1_SIOC_BYP                    (* (reg8 *) OV9650_1_SIOC__BYP)
/* Port wide control signals */                                                   
#define OV9650_1_SIOC_CTL                    (* (reg8 *) OV9650_1_SIOC__CTL)
/* Drive Modes */
#define OV9650_1_SIOC_DM0                    (* (reg8 *) OV9650_1_SIOC__DM0) 
#define OV9650_1_SIOC_DM1                    (* (reg8 *) OV9650_1_SIOC__DM1)
#define OV9650_1_SIOC_DM2                    (* (reg8 *) OV9650_1_SIOC__DM2) 
/* Input Buffer Disable Override */
#define OV9650_1_SIOC_INP_DIS                (* (reg8 *) OV9650_1_SIOC__INP_DIS)
/* LCD Common or Segment Drive */
#define OV9650_1_SIOC_LCD_COM_SEG            (* (reg8 *) OV9650_1_SIOC__LCD_COM_SEG)
/* Enable Segment LCD */
#define OV9650_1_SIOC_LCD_EN                 (* (reg8 *) OV9650_1_SIOC__LCD_EN)
/* Slew Rate Control */
#define OV9650_1_SIOC_SLW                    (* (reg8 *) OV9650_1_SIOC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OV9650_1_SIOC_PRTDSI__CAPS_SEL       (* (reg8 *) OV9650_1_SIOC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OV9650_1_SIOC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OV9650_1_SIOC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OV9650_1_SIOC_PRTDSI__OE_SEL0        (* (reg8 *) OV9650_1_SIOC__PRTDSI__OE_SEL0) 
#define OV9650_1_SIOC_PRTDSI__OE_SEL1        (* (reg8 *) OV9650_1_SIOC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OV9650_1_SIOC_PRTDSI__OUT_SEL0       (* (reg8 *) OV9650_1_SIOC__PRTDSI__OUT_SEL0) 
#define OV9650_1_SIOC_PRTDSI__OUT_SEL1       (* (reg8 *) OV9650_1_SIOC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OV9650_1_SIOC_PRTDSI__SYNC_OUT       (* (reg8 *) OV9650_1_SIOC__PRTDSI__SYNC_OUT) 


#if defined(OV9650_1_SIOC__INTSTAT)  /* Interrupt Registers */

    #define OV9650_1_SIOC_INTSTAT                (* (reg8 *) OV9650_1_SIOC__INTSTAT)
    #define OV9650_1_SIOC_SNAP                   (* (reg8 *) OV9650_1_SIOC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OV9650_1_SIOC_H */


/* [] END OF FILE */
