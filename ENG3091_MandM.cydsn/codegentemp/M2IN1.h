/*******************************************************************************
* File Name: M2IN1.h  
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

#if !defined(CY_PINS_M2IN1_H) /* Pins M2IN1_H */
#define CY_PINS_M2IN1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M2IN1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M2IN1__PORT == 15 && ((M2IN1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    M2IN1_Write(uint8 value) ;
void    M2IN1_SetDriveMode(uint8 mode) ;
uint8   M2IN1_ReadDataReg(void) ;
uint8   M2IN1_Read(void) ;
uint8   M2IN1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M2IN1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define M2IN1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define M2IN1_DM_RES_UP          PIN_DM_RES_UP
#define M2IN1_DM_RES_DWN         PIN_DM_RES_DWN
#define M2IN1_DM_OD_LO           PIN_DM_OD_LO
#define M2IN1_DM_OD_HI           PIN_DM_OD_HI
#define M2IN1_DM_STRONG          PIN_DM_STRONG
#define M2IN1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define M2IN1_MASK               M2IN1__MASK
#define M2IN1_SHIFT              M2IN1__SHIFT
#define M2IN1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M2IN1_PS                     (* (reg8 *) M2IN1__PS)
/* Data Register */
#define M2IN1_DR                     (* (reg8 *) M2IN1__DR)
/* Port Number */
#define M2IN1_PRT_NUM                (* (reg8 *) M2IN1__PRT) 
/* Connect to Analog Globals */                                                  
#define M2IN1_AG                     (* (reg8 *) M2IN1__AG)                       
/* Analog MUX bux enable */
#define M2IN1_AMUX                   (* (reg8 *) M2IN1__AMUX) 
/* Bidirectional Enable */                                                        
#define M2IN1_BIE                    (* (reg8 *) M2IN1__BIE)
/* Bit-mask for Aliased Register Access */
#define M2IN1_BIT_MASK               (* (reg8 *) M2IN1__BIT_MASK)
/* Bypass Enable */
#define M2IN1_BYP                    (* (reg8 *) M2IN1__BYP)
/* Port wide control signals */                                                   
#define M2IN1_CTL                    (* (reg8 *) M2IN1__CTL)
/* Drive Modes */
#define M2IN1_DM0                    (* (reg8 *) M2IN1__DM0) 
#define M2IN1_DM1                    (* (reg8 *) M2IN1__DM1)
#define M2IN1_DM2                    (* (reg8 *) M2IN1__DM2) 
/* Input Buffer Disable Override */
#define M2IN1_INP_DIS                (* (reg8 *) M2IN1__INP_DIS)
/* LCD Common or Segment Drive */
#define M2IN1_LCD_COM_SEG            (* (reg8 *) M2IN1__LCD_COM_SEG)
/* Enable Segment LCD */
#define M2IN1_LCD_EN                 (* (reg8 *) M2IN1__LCD_EN)
/* Slew Rate Control */
#define M2IN1_SLW                    (* (reg8 *) M2IN1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M2IN1_PRTDSI__CAPS_SEL       (* (reg8 *) M2IN1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M2IN1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M2IN1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M2IN1_PRTDSI__OE_SEL0        (* (reg8 *) M2IN1__PRTDSI__OE_SEL0) 
#define M2IN1_PRTDSI__OE_SEL1        (* (reg8 *) M2IN1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M2IN1_PRTDSI__OUT_SEL0       (* (reg8 *) M2IN1__PRTDSI__OUT_SEL0) 
#define M2IN1_PRTDSI__OUT_SEL1       (* (reg8 *) M2IN1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M2IN1_PRTDSI__SYNC_OUT       (* (reg8 *) M2IN1__PRTDSI__SYNC_OUT) 


#if defined(M2IN1__INTSTAT)  /* Interrupt Registers */

    #define M2IN1_INTSTAT                (* (reg8 *) M2IN1__INTSTAT)
    #define M2IN1_SNAP                   (* (reg8 *) M2IN1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M2IN1_H */


/* [] END OF FILE */
