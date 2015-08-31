/*******************************************************************************
* File Name: D5.h  
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

#if !defined(CY_PINS_D5_H) /* Pins D5_H */
#define CY_PINS_D5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D5_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D5__PORT == 15 && ((D5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    D5_Write(uint8 value) ;
void    D5_SetDriveMode(uint8 mode) ;
uint8   D5_ReadDataReg(void) ;
uint8   D5_Read(void) ;
uint8   D5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define D5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define D5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define D5_DM_RES_UP          PIN_DM_RES_UP
#define D5_DM_RES_DWN         PIN_DM_RES_DWN
#define D5_DM_OD_LO           PIN_DM_OD_LO
#define D5_DM_OD_HI           PIN_DM_OD_HI
#define D5_DM_STRONG          PIN_DM_STRONG
#define D5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define D5_MASK               D5__MASK
#define D5_SHIFT              D5__SHIFT
#define D5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D5_PS                     (* (reg8 *) D5__PS)
/* Data Register */
#define D5_DR                     (* (reg8 *) D5__DR)
/* Port Number */
#define D5_PRT_NUM                (* (reg8 *) D5__PRT) 
/* Connect to Analog Globals */                                                  
#define D5_AG                     (* (reg8 *) D5__AG)                       
/* Analog MUX bux enable */
#define D5_AMUX                   (* (reg8 *) D5__AMUX) 
/* Bidirectional Enable */                                                        
#define D5_BIE                    (* (reg8 *) D5__BIE)
/* Bit-mask for Aliased Register Access */
#define D5_BIT_MASK               (* (reg8 *) D5__BIT_MASK)
/* Bypass Enable */
#define D5_BYP                    (* (reg8 *) D5__BYP)
/* Port wide control signals */                                                   
#define D5_CTL                    (* (reg8 *) D5__CTL)
/* Drive Modes */
#define D5_DM0                    (* (reg8 *) D5__DM0) 
#define D5_DM1                    (* (reg8 *) D5__DM1)
#define D5_DM2                    (* (reg8 *) D5__DM2) 
/* Input Buffer Disable Override */
#define D5_INP_DIS                (* (reg8 *) D5__INP_DIS)
/* LCD Common or Segment Drive */
#define D5_LCD_COM_SEG            (* (reg8 *) D5__LCD_COM_SEG)
/* Enable Segment LCD */
#define D5_LCD_EN                 (* (reg8 *) D5__LCD_EN)
/* Slew Rate Control */
#define D5_SLW                    (* (reg8 *) D5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D5_PRTDSI__CAPS_SEL       (* (reg8 *) D5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D5_PRTDSI__OE_SEL0        (* (reg8 *) D5__PRTDSI__OE_SEL0) 
#define D5_PRTDSI__OE_SEL1        (* (reg8 *) D5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D5_PRTDSI__OUT_SEL0       (* (reg8 *) D5__PRTDSI__OUT_SEL0) 
#define D5_PRTDSI__OUT_SEL1       (* (reg8 *) D5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D5_PRTDSI__SYNC_OUT       (* (reg8 *) D5__PRTDSI__SYNC_OUT) 


#if defined(D5__INTSTAT)  /* Interrupt Registers */

    #define D5_INTSTAT                (* (reg8 *) D5__INTSTAT)
    #define D5_SNAP                   (* (reg8 *) D5__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D5_H */


/* [] END OF FILE */
