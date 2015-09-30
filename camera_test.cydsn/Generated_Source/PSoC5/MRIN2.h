/*******************************************************************************
* File Name: MRIN2.h  
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

#if !defined(CY_PINS_MRIN2_H) /* Pins MRIN2_H */
#define CY_PINS_MRIN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MRIN2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MRIN2__PORT == 15 && ((MRIN2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MRIN2_Write(uint8 value) ;
void    MRIN2_SetDriveMode(uint8 mode) ;
uint8   MRIN2_ReadDataReg(void) ;
uint8   MRIN2_Read(void) ;
uint8   MRIN2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MRIN2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MRIN2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MRIN2_DM_RES_UP          PIN_DM_RES_UP
#define MRIN2_DM_RES_DWN         PIN_DM_RES_DWN
#define MRIN2_DM_OD_LO           PIN_DM_OD_LO
#define MRIN2_DM_OD_HI           PIN_DM_OD_HI
#define MRIN2_DM_STRONG          PIN_DM_STRONG
#define MRIN2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MRIN2_MASK               MRIN2__MASK
#define MRIN2_SHIFT              MRIN2__SHIFT
#define MRIN2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MRIN2_PS                     (* (reg8 *) MRIN2__PS)
/* Data Register */
#define MRIN2_DR                     (* (reg8 *) MRIN2__DR)
/* Port Number */
#define MRIN2_PRT_NUM                (* (reg8 *) MRIN2__PRT) 
/* Connect to Analog Globals */                                                  
#define MRIN2_AG                     (* (reg8 *) MRIN2__AG)                       
/* Analog MUX bux enable */
#define MRIN2_AMUX                   (* (reg8 *) MRIN2__AMUX) 
/* Bidirectional Enable */                                                        
#define MRIN2_BIE                    (* (reg8 *) MRIN2__BIE)
/* Bit-mask for Aliased Register Access */
#define MRIN2_BIT_MASK               (* (reg8 *) MRIN2__BIT_MASK)
/* Bypass Enable */
#define MRIN2_BYP                    (* (reg8 *) MRIN2__BYP)
/* Port wide control signals */                                                   
#define MRIN2_CTL                    (* (reg8 *) MRIN2__CTL)
/* Drive Modes */
#define MRIN2_DM0                    (* (reg8 *) MRIN2__DM0) 
#define MRIN2_DM1                    (* (reg8 *) MRIN2__DM1)
#define MRIN2_DM2                    (* (reg8 *) MRIN2__DM2) 
/* Input Buffer Disable Override */
#define MRIN2_INP_DIS                (* (reg8 *) MRIN2__INP_DIS)
/* LCD Common or Segment Drive */
#define MRIN2_LCD_COM_SEG            (* (reg8 *) MRIN2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MRIN2_LCD_EN                 (* (reg8 *) MRIN2__LCD_EN)
/* Slew Rate Control */
#define MRIN2_SLW                    (* (reg8 *) MRIN2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MRIN2_PRTDSI__CAPS_SEL       (* (reg8 *) MRIN2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MRIN2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MRIN2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MRIN2_PRTDSI__OE_SEL0        (* (reg8 *) MRIN2__PRTDSI__OE_SEL0) 
#define MRIN2_PRTDSI__OE_SEL1        (* (reg8 *) MRIN2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MRIN2_PRTDSI__OUT_SEL0       (* (reg8 *) MRIN2__PRTDSI__OUT_SEL0) 
#define MRIN2_PRTDSI__OUT_SEL1       (* (reg8 *) MRIN2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MRIN2_PRTDSI__SYNC_OUT       (* (reg8 *) MRIN2__PRTDSI__SYNC_OUT) 


#if defined(MRIN2__INTSTAT)  /* Interrupt Registers */

    #define MRIN2_INTSTAT                (* (reg8 *) MRIN2__INTSTAT)
    #define MRIN2_SNAP                   (* (reg8 *) MRIN2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MRIN2_H */


/* [] END OF FILE */
