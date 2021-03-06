/*******************************************************************************
* File Name: MLIN2.h  
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

#if !defined(CY_PINS_MLIN2_H) /* Pins MLIN2_H */
#define CY_PINS_MLIN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MLIN2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MLIN2__PORT == 15 && ((MLIN2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MLIN2_Write(uint8 value) ;
void    MLIN2_SetDriveMode(uint8 mode) ;
uint8   MLIN2_ReadDataReg(void) ;
uint8   MLIN2_Read(void) ;
uint8   MLIN2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MLIN2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MLIN2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MLIN2_DM_RES_UP          PIN_DM_RES_UP
#define MLIN2_DM_RES_DWN         PIN_DM_RES_DWN
#define MLIN2_DM_OD_LO           PIN_DM_OD_LO
#define MLIN2_DM_OD_HI           PIN_DM_OD_HI
#define MLIN2_DM_STRONG          PIN_DM_STRONG
#define MLIN2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MLIN2_MASK               MLIN2__MASK
#define MLIN2_SHIFT              MLIN2__SHIFT
#define MLIN2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MLIN2_PS                     (* (reg8 *) MLIN2__PS)
/* Data Register */
#define MLIN2_DR                     (* (reg8 *) MLIN2__DR)
/* Port Number */
#define MLIN2_PRT_NUM                (* (reg8 *) MLIN2__PRT) 
/* Connect to Analog Globals */                                                  
#define MLIN2_AG                     (* (reg8 *) MLIN2__AG)                       
/* Analog MUX bux enable */
#define MLIN2_AMUX                   (* (reg8 *) MLIN2__AMUX) 
/* Bidirectional Enable */                                                        
#define MLIN2_BIE                    (* (reg8 *) MLIN2__BIE)
/* Bit-mask for Aliased Register Access */
#define MLIN2_BIT_MASK               (* (reg8 *) MLIN2__BIT_MASK)
/* Bypass Enable */
#define MLIN2_BYP                    (* (reg8 *) MLIN2__BYP)
/* Port wide control signals */                                                   
#define MLIN2_CTL                    (* (reg8 *) MLIN2__CTL)
/* Drive Modes */
#define MLIN2_DM0                    (* (reg8 *) MLIN2__DM0) 
#define MLIN2_DM1                    (* (reg8 *) MLIN2__DM1)
#define MLIN2_DM2                    (* (reg8 *) MLIN2__DM2) 
/* Input Buffer Disable Override */
#define MLIN2_INP_DIS                (* (reg8 *) MLIN2__INP_DIS)
/* LCD Common or Segment Drive */
#define MLIN2_LCD_COM_SEG            (* (reg8 *) MLIN2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MLIN2_LCD_EN                 (* (reg8 *) MLIN2__LCD_EN)
/* Slew Rate Control */
#define MLIN2_SLW                    (* (reg8 *) MLIN2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MLIN2_PRTDSI__CAPS_SEL       (* (reg8 *) MLIN2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MLIN2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MLIN2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MLIN2_PRTDSI__OE_SEL0        (* (reg8 *) MLIN2__PRTDSI__OE_SEL0) 
#define MLIN2_PRTDSI__OE_SEL1        (* (reg8 *) MLIN2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MLIN2_PRTDSI__OUT_SEL0       (* (reg8 *) MLIN2__PRTDSI__OUT_SEL0) 
#define MLIN2_PRTDSI__OUT_SEL1       (* (reg8 *) MLIN2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MLIN2_PRTDSI__SYNC_OUT       (* (reg8 *) MLIN2__PRTDSI__SYNC_OUT) 


#if defined(MLIN2__INTSTAT)  /* Interrupt Registers */

    #define MLIN2_INTSTAT                (* (reg8 *) MLIN2__INTSTAT)
    #define MLIN2_SNAP                   (* (reg8 *) MLIN2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MLIN2_H */


/* [] END OF FILE */
