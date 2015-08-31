/*******************************************************************************
* File Name: OV9650_1_SIOD.h  
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

#if !defined(CY_PINS_OV9650_1_SIOD_H) /* Pins OV9650_1_SIOD_H */
#define CY_PINS_OV9650_1_SIOD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OV9650_1_SIOD_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OV9650_1_SIOD__PORT == 15 && ((OV9650_1_SIOD__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    OV9650_1_SIOD_Write(uint8 value) ;
void    OV9650_1_SIOD_SetDriveMode(uint8 mode) ;
uint8   OV9650_1_SIOD_ReadDataReg(void) ;
uint8   OV9650_1_SIOD_Read(void) ;
uint8   OV9650_1_SIOD_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OV9650_1_SIOD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define OV9650_1_SIOD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define OV9650_1_SIOD_DM_RES_UP          PIN_DM_RES_UP
#define OV9650_1_SIOD_DM_RES_DWN         PIN_DM_RES_DWN
#define OV9650_1_SIOD_DM_OD_LO           PIN_DM_OD_LO
#define OV9650_1_SIOD_DM_OD_HI           PIN_DM_OD_HI
#define OV9650_1_SIOD_DM_STRONG          PIN_DM_STRONG
#define OV9650_1_SIOD_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define OV9650_1_SIOD_MASK               OV9650_1_SIOD__MASK
#define OV9650_1_SIOD_SHIFT              OV9650_1_SIOD__SHIFT
#define OV9650_1_SIOD_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OV9650_1_SIOD_PS                     (* (reg8 *) OV9650_1_SIOD__PS)
/* Data Register */
#define OV9650_1_SIOD_DR                     (* (reg8 *) OV9650_1_SIOD__DR)
/* Port Number */
#define OV9650_1_SIOD_PRT_NUM                (* (reg8 *) OV9650_1_SIOD__PRT) 
/* Connect to Analog Globals */                                                  
#define OV9650_1_SIOD_AG                     (* (reg8 *) OV9650_1_SIOD__AG)                       
/* Analog MUX bux enable */
#define OV9650_1_SIOD_AMUX                   (* (reg8 *) OV9650_1_SIOD__AMUX) 
/* Bidirectional Enable */                                                        
#define OV9650_1_SIOD_BIE                    (* (reg8 *) OV9650_1_SIOD__BIE)
/* Bit-mask for Aliased Register Access */
#define OV9650_1_SIOD_BIT_MASK               (* (reg8 *) OV9650_1_SIOD__BIT_MASK)
/* Bypass Enable */
#define OV9650_1_SIOD_BYP                    (* (reg8 *) OV9650_1_SIOD__BYP)
/* Port wide control signals */                                                   
#define OV9650_1_SIOD_CTL                    (* (reg8 *) OV9650_1_SIOD__CTL)
/* Drive Modes */
#define OV9650_1_SIOD_DM0                    (* (reg8 *) OV9650_1_SIOD__DM0) 
#define OV9650_1_SIOD_DM1                    (* (reg8 *) OV9650_1_SIOD__DM1)
#define OV9650_1_SIOD_DM2                    (* (reg8 *) OV9650_1_SIOD__DM2) 
/* Input Buffer Disable Override */
#define OV9650_1_SIOD_INP_DIS                (* (reg8 *) OV9650_1_SIOD__INP_DIS)
/* LCD Common or Segment Drive */
#define OV9650_1_SIOD_LCD_COM_SEG            (* (reg8 *) OV9650_1_SIOD__LCD_COM_SEG)
/* Enable Segment LCD */
#define OV9650_1_SIOD_LCD_EN                 (* (reg8 *) OV9650_1_SIOD__LCD_EN)
/* Slew Rate Control */
#define OV9650_1_SIOD_SLW                    (* (reg8 *) OV9650_1_SIOD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OV9650_1_SIOD_PRTDSI__CAPS_SEL       (* (reg8 *) OV9650_1_SIOD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OV9650_1_SIOD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OV9650_1_SIOD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OV9650_1_SIOD_PRTDSI__OE_SEL0        (* (reg8 *) OV9650_1_SIOD__PRTDSI__OE_SEL0) 
#define OV9650_1_SIOD_PRTDSI__OE_SEL1        (* (reg8 *) OV9650_1_SIOD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OV9650_1_SIOD_PRTDSI__OUT_SEL0       (* (reg8 *) OV9650_1_SIOD__PRTDSI__OUT_SEL0) 
#define OV9650_1_SIOD_PRTDSI__OUT_SEL1       (* (reg8 *) OV9650_1_SIOD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OV9650_1_SIOD_PRTDSI__SYNC_OUT       (* (reg8 *) OV9650_1_SIOD__PRTDSI__SYNC_OUT) 


#if defined(OV9650_1_SIOD__INTSTAT)  /* Interrupt Registers */

    #define OV9650_1_SIOD_INTSTAT                (* (reg8 *) OV9650_1_SIOD__INTSTAT)
    #define OV9650_1_SIOD_SNAP                   (* (reg8 *) OV9650_1_SIOD__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OV9650_1_SIOD_H */


/* [] END OF FILE */
