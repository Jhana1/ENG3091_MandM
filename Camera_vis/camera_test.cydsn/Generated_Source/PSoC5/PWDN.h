/*******************************************************************************
* File Name: PWDN.h  
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

#if !defined(CY_PINS_PWDN_H) /* Pins PWDN_H */
#define CY_PINS_PWDN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWDN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWDN__PORT == 15 && ((PWDN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWDN_Write(uint8 value) ;
void    PWDN_SetDriveMode(uint8 mode) ;
uint8   PWDN_ReadDataReg(void) ;
uint8   PWDN_Read(void) ;
uint8   PWDN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWDN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWDN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWDN_DM_RES_UP          PIN_DM_RES_UP
#define PWDN_DM_RES_DWN         PIN_DM_RES_DWN
#define PWDN_DM_OD_LO           PIN_DM_OD_LO
#define PWDN_DM_OD_HI           PIN_DM_OD_HI
#define PWDN_DM_STRONG          PIN_DM_STRONG
#define PWDN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWDN_MASK               PWDN__MASK
#define PWDN_SHIFT              PWDN__SHIFT
#define PWDN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWDN_PS                     (* (reg8 *) PWDN__PS)
/* Data Register */
#define PWDN_DR                     (* (reg8 *) PWDN__DR)
/* Port Number */
#define PWDN_PRT_NUM                (* (reg8 *) PWDN__PRT) 
/* Connect to Analog Globals */                                                  
#define PWDN_AG                     (* (reg8 *) PWDN__AG)                       
/* Analog MUX bux enable */
#define PWDN_AMUX                   (* (reg8 *) PWDN__AMUX) 
/* Bidirectional Enable */                                                        
#define PWDN_BIE                    (* (reg8 *) PWDN__BIE)
/* Bit-mask for Aliased Register Access */
#define PWDN_BIT_MASK               (* (reg8 *) PWDN__BIT_MASK)
/* Bypass Enable */
#define PWDN_BYP                    (* (reg8 *) PWDN__BYP)
/* Port wide control signals */                                                   
#define PWDN_CTL                    (* (reg8 *) PWDN__CTL)
/* Drive Modes */
#define PWDN_DM0                    (* (reg8 *) PWDN__DM0) 
#define PWDN_DM1                    (* (reg8 *) PWDN__DM1)
#define PWDN_DM2                    (* (reg8 *) PWDN__DM2) 
/* Input Buffer Disable Override */
#define PWDN_INP_DIS                (* (reg8 *) PWDN__INP_DIS)
/* LCD Common or Segment Drive */
#define PWDN_LCD_COM_SEG            (* (reg8 *) PWDN__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWDN_LCD_EN                 (* (reg8 *) PWDN__LCD_EN)
/* Slew Rate Control */
#define PWDN_SLW                    (* (reg8 *) PWDN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWDN_PRTDSI__CAPS_SEL       (* (reg8 *) PWDN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWDN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWDN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWDN_PRTDSI__OE_SEL0        (* (reg8 *) PWDN__PRTDSI__OE_SEL0) 
#define PWDN_PRTDSI__OE_SEL1        (* (reg8 *) PWDN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWDN_PRTDSI__OUT_SEL0       (* (reg8 *) PWDN__PRTDSI__OUT_SEL0) 
#define PWDN_PRTDSI__OUT_SEL1       (* (reg8 *) PWDN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWDN_PRTDSI__SYNC_OUT       (* (reg8 *) PWDN__PRTDSI__SYNC_OUT) 


#if defined(PWDN__INTSTAT)  /* Interrupt Registers */

    #define PWDN_INTSTAT                (* (reg8 *) PWDN__INTSTAT)
    #define PWDN_SNAP                   (* (reg8 *) PWDN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWDN_H */


/* [] END OF FILE */
