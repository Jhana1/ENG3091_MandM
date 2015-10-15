/*******************************************************************************
* File Name: BEAM_BREAK_IN.h  
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

#if !defined(CY_PINS_BEAM_BREAK_IN_H) /* Pins BEAM_BREAK_IN_H */
#define CY_PINS_BEAM_BREAK_IN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BEAM_BREAK_IN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BEAM_BREAK_IN__PORT == 15 && ((BEAM_BREAK_IN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    BEAM_BREAK_IN_Write(uint8 value) ;
void    BEAM_BREAK_IN_SetDriveMode(uint8 mode) ;
uint8   BEAM_BREAK_IN_ReadDataReg(void) ;
uint8   BEAM_BREAK_IN_Read(void) ;
uint8   BEAM_BREAK_IN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BEAM_BREAK_IN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BEAM_BREAK_IN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BEAM_BREAK_IN_DM_RES_UP          PIN_DM_RES_UP
#define BEAM_BREAK_IN_DM_RES_DWN         PIN_DM_RES_DWN
#define BEAM_BREAK_IN_DM_OD_LO           PIN_DM_OD_LO
#define BEAM_BREAK_IN_DM_OD_HI           PIN_DM_OD_HI
#define BEAM_BREAK_IN_DM_STRONG          PIN_DM_STRONG
#define BEAM_BREAK_IN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BEAM_BREAK_IN_MASK               BEAM_BREAK_IN__MASK
#define BEAM_BREAK_IN_SHIFT              BEAM_BREAK_IN__SHIFT
#define BEAM_BREAK_IN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BEAM_BREAK_IN_PS                     (* (reg8 *) BEAM_BREAK_IN__PS)
/* Data Register */
#define BEAM_BREAK_IN_DR                     (* (reg8 *) BEAM_BREAK_IN__DR)
/* Port Number */
#define BEAM_BREAK_IN_PRT_NUM                (* (reg8 *) BEAM_BREAK_IN__PRT) 
/* Connect to Analog Globals */                                                  
#define BEAM_BREAK_IN_AG                     (* (reg8 *) BEAM_BREAK_IN__AG)                       
/* Analog MUX bux enable */
#define BEAM_BREAK_IN_AMUX                   (* (reg8 *) BEAM_BREAK_IN__AMUX) 
/* Bidirectional Enable */                                                        
#define BEAM_BREAK_IN_BIE                    (* (reg8 *) BEAM_BREAK_IN__BIE)
/* Bit-mask for Aliased Register Access */
#define BEAM_BREAK_IN_BIT_MASK               (* (reg8 *) BEAM_BREAK_IN__BIT_MASK)
/* Bypass Enable */
#define BEAM_BREAK_IN_BYP                    (* (reg8 *) BEAM_BREAK_IN__BYP)
/* Port wide control signals */                                                   
#define BEAM_BREAK_IN_CTL                    (* (reg8 *) BEAM_BREAK_IN__CTL)
/* Drive Modes */
#define BEAM_BREAK_IN_DM0                    (* (reg8 *) BEAM_BREAK_IN__DM0) 
#define BEAM_BREAK_IN_DM1                    (* (reg8 *) BEAM_BREAK_IN__DM1)
#define BEAM_BREAK_IN_DM2                    (* (reg8 *) BEAM_BREAK_IN__DM2) 
/* Input Buffer Disable Override */
#define BEAM_BREAK_IN_INP_DIS                (* (reg8 *) BEAM_BREAK_IN__INP_DIS)
/* LCD Common or Segment Drive */
#define BEAM_BREAK_IN_LCD_COM_SEG            (* (reg8 *) BEAM_BREAK_IN__LCD_COM_SEG)
/* Enable Segment LCD */
#define BEAM_BREAK_IN_LCD_EN                 (* (reg8 *) BEAM_BREAK_IN__LCD_EN)
/* Slew Rate Control */
#define BEAM_BREAK_IN_SLW                    (* (reg8 *) BEAM_BREAK_IN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BEAM_BREAK_IN_PRTDSI__CAPS_SEL       (* (reg8 *) BEAM_BREAK_IN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BEAM_BREAK_IN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BEAM_BREAK_IN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BEAM_BREAK_IN_PRTDSI__OE_SEL0        (* (reg8 *) BEAM_BREAK_IN__PRTDSI__OE_SEL0) 
#define BEAM_BREAK_IN_PRTDSI__OE_SEL1        (* (reg8 *) BEAM_BREAK_IN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BEAM_BREAK_IN_PRTDSI__OUT_SEL0       (* (reg8 *) BEAM_BREAK_IN__PRTDSI__OUT_SEL0) 
#define BEAM_BREAK_IN_PRTDSI__OUT_SEL1       (* (reg8 *) BEAM_BREAK_IN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BEAM_BREAK_IN_PRTDSI__SYNC_OUT       (* (reg8 *) BEAM_BREAK_IN__PRTDSI__SYNC_OUT) 


#if defined(BEAM_BREAK_IN__INTSTAT)  /* Interrupt Registers */

    #define BEAM_BREAK_IN_INTSTAT                (* (reg8 *) BEAM_BREAK_IN__INTSTAT)
    #define BEAM_BREAK_IN_SNAP                   (* (reg8 *) BEAM_BREAK_IN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BEAM_BREAK_IN_H */


/* [] END OF FILE */
