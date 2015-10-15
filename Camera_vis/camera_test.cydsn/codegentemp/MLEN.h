/*******************************************************************************
* File Name: MLEN.h  
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

#if !defined(CY_PINS_MLEN_H) /* Pins MLEN_H */
#define CY_PINS_MLEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MLEN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MLEN__PORT == 15 && ((MLEN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MLEN_Write(uint8 value) ;
void    MLEN_SetDriveMode(uint8 mode) ;
uint8   MLEN_ReadDataReg(void) ;
uint8   MLEN_Read(void) ;
uint8   MLEN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MLEN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MLEN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MLEN_DM_RES_UP          PIN_DM_RES_UP
#define MLEN_DM_RES_DWN         PIN_DM_RES_DWN
#define MLEN_DM_OD_LO           PIN_DM_OD_LO
#define MLEN_DM_OD_HI           PIN_DM_OD_HI
#define MLEN_DM_STRONG          PIN_DM_STRONG
#define MLEN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MLEN_MASK               MLEN__MASK
#define MLEN_SHIFT              MLEN__SHIFT
#define MLEN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MLEN_PS                     (* (reg8 *) MLEN__PS)
/* Data Register */
#define MLEN_DR                     (* (reg8 *) MLEN__DR)
/* Port Number */
#define MLEN_PRT_NUM                (* (reg8 *) MLEN__PRT) 
/* Connect to Analog Globals */                                                  
#define MLEN_AG                     (* (reg8 *) MLEN__AG)                       
/* Analog MUX bux enable */
#define MLEN_AMUX                   (* (reg8 *) MLEN__AMUX) 
/* Bidirectional Enable */                                                        
#define MLEN_BIE                    (* (reg8 *) MLEN__BIE)
/* Bit-mask for Aliased Register Access */
#define MLEN_BIT_MASK               (* (reg8 *) MLEN__BIT_MASK)
/* Bypass Enable */
#define MLEN_BYP                    (* (reg8 *) MLEN__BYP)
/* Port wide control signals */                                                   
#define MLEN_CTL                    (* (reg8 *) MLEN__CTL)
/* Drive Modes */
#define MLEN_DM0                    (* (reg8 *) MLEN__DM0) 
#define MLEN_DM1                    (* (reg8 *) MLEN__DM1)
#define MLEN_DM2                    (* (reg8 *) MLEN__DM2) 
/* Input Buffer Disable Override */
#define MLEN_INP_DIS                (* (reg8 *) MLEN__INP_DIS)
/* LCD Common or Segment Drive */
#define MLEN_LCD_COM_SEG            (* (reg8 *) MLEN__LCD_COM_SEG)
/* Enable Segment LCD */
#define MLEN_LCD_EN                 (* (reg8 *) MLEN__LCD_EN)
/* Slew Rate Control */
#define MLEN_SLW                    (* (reg8 *) MLEN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MLEN_PRTDSI__CAPS_SEL       (* (reg8 *) MLEN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MLEN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MLEN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MLEN_PRTDSI__OE_SEL0        (* (reg8 *) MLEN__PRTDSI__OE_SEL0) 
#define MLEN_PRTDSI__OE_SEL1        (* (reg8 *) MLEN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MLEN_PRTDSI__OUT_SEL0       (* (reg8 *) MLEN__PRTDSI__OUT_SEL0) 
#define MLEN_PRTDSI__OUT_SEL1       (* (reg8 *) MLEN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MLEN_PRTDSI__SYNC_OUT       (* (reg8 *) MLEN__PRTDSI__SYNC_OUT) 


#if defined(MLEN__INTSTAT)  /* Interrupt Registers */

    #define MLEN_INTSTAT                (* (reg8 *) MLEN__INTSTAT)
    #define MLEN_SNAP                   (* (reg8 *) MLEN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MLEN_H */


/* [] END OF FILE */
