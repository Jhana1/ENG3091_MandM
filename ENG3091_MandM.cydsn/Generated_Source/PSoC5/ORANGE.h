/*******************************************************************************
* File Name: ORANGE.h  
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

#if !defined(CY_PINS_ORANGE_H) /* Pins ORANGE_H */
#define CY_PINS_ORANGE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ORANGE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ORANGE__PORT == 15 && ((ORANGE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ORANGE_Write(uint8 value) ;
void    ORANGE_SetDriveMode(uint8 mode) ;
uint8   ORANGE_ReadDataReg(void) ;
uint8   ORANGE_Read(void) ;
uint8   ORANGE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ORANGE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ORANGE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ORANGE_DM_RES_UP          PIN_DM_RES_UP
#define ORANGE_DM_RES_DWN         PIN_DM_RES_DWN
#define ORANGE_DM_OD_LO           PIN_DM_OD_LO
#define ORANGE_DM_OD_HI           PIN_DM_OD_HI
#define ORANGE_DM_STRONG          PIN_DM_STRONG
#define ORANGE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ORANGE_MASK               ORANGE__MASK
#define ORANGE_SHIFT              ORANGE__SHIFT
#define ORANGE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ORANGE_PS                     (* (reg8 *) ORANGE__PS)
/* Data Register */
#define ORANGE_DR                     (* (reg8 *) ORANGE__DR)
/* Port Number */
#define ORANGE_PRT_NUM                (* (reg8 *) ORANGE__PRT) 
/* Connect to Analog Globals */                                                  
#define ORANGE_AG                     (* (reg8 *) ORANGE__AG)                       
/* Analog MUX bux enable */
#define ORANGE_AMUX                   (* (reg8 *) ORANGE__AMUX) 
/* Bidirectional Enable */                                                        
#define ORANGE_BIE                    (* (reg8 *) ORANGE__BIE)
/* Bit-mask for Aliased Register Access */
#define ORANGE_BIT_MASK               (* (reg8 *) ORANGE__BIT_MASK)
/* Bypass Enable */
#define ORANGE_BYP                    (* (reg8 *) ORANGE__BYP)
/* Port wide control signals */                                                   
#define ORANGE_CTL                    (* (reg8 *) ORANGE__CTL)
/* Drive Modes */
#define ORANGE_DM0                    (* (reg8 *) ORANGE__DM0) 
#define ORANGE_DM1                    (* (reg8 *) ORANGE__DM1)
#define ORANGE_DM2                    (* (reg8 *) ORANGE__DM2) 
/* Input Buffer Disable Override */
#define ORANGE_INP_DIS                (* (reg8 *) ORANGE__INP_DIS)
/* LCD Common or Segment Drive */
#define ORANGE_LCD_COM_SEG            (* (reg8 *) ORANGE__LCD_COM_SEG)
/* Enable Segment LCD */
#define ORANGE_LCD_EN                 (* (reg8 *) ORANGE__LCD_EN)
/* Slew Rate Control */
#define ORANGE_SLW                    (* (reg8 *) ORANGE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ORANGE_PRTDSI__CAPS_SEL       (* (reg8 *) ORANGE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ORANGE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ORANGE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ORANGE_PRTDSI__OE_SEL0        (* (reg8 *) ORANGE__PRTDSI__OE_SEL0) 
#define ORANGE_PRTDSI__OE_SEL1        (* (reg8 *) ORANGE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ORANGE_PRTDSI__OUT_SEL0       (* (reg8 *) ORANGE__PRTDSI__OUT_SEL0) 
#define ORANGE_PRTDSI__OUT_SEL1       (* (reg8 *) ORANGE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ORANGE_PRTDSI__SYNC_OUT       (* (reg8 *) ORANGE__PRTDSI__SYNC_OUT) 


#if defined(ORANGE__INTSTAT)  /* Interrupt Registers */

    #define ORANGE_INTSTAT                (* (reg8 *) ORANGE__INTSTAT)
    #define ORANGE_SNAP                   (* (reg8 *) ORANGE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ORANGE_H */


/* [] END OF FILE */
