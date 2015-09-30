/*******************************************************************************
* File Name: D6.h  
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

#if !defined(CY_PINS_D6_H) /* Pins D6_H */
#define CY_PINS_D6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D6_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D6__PORT == 15 && ((D6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    D6_Write(uint8 value) ;
void    D6_SetDriveMode(uint8 mode) ;
uint8   D6_ReadDataReg(void) ;
uint8   D6_Read(void) ;
uint8   D6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define D6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define D6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define D6_DM_RES_UP          PIN_DM_RES_UP
#define D6_DM_RES_DWN         PIN_DM_RES_DWN
#define D6_DM_OD_LO           PIN_DM_OD_LO
#define D6_DM_OD_HI           PIN_DM_OD_HI
#define D6_DM_STRONG          PIN_DM_STRONG
#define D6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define D6_MASK               D6__MASK
#define D6_SHIFT              D6__SHIFT
#define D6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D6_PS                     (* (reg8 *) D6__PS)
/* Data Register */
#define D6_DR                     (* (reg8 *) D6__DR)
/* Port Number */
#define D6_PRT_NUM                (* (reg8 *) D6__PRT) 
/* Connect to Analog Globals */                                                  
#define D6_AG                     (* (reg8 *) D6__AG)                       
/* Analog MUX bux enable */
#define D6_AMUX                   (* (reg8 *) D6__AMUX) 
/* Bidirectional Enable */                                                        
#define D6_BIE                    (* (reg8 *) D6__BIE)
/* Bit-mask for Aliased Register Access */
#define D6_BIT_MASK               (* (reg8 *) D6__BIT_MASK)
/* Bypass Enable */
#define D6_BYP                    (* (reg8 *) D6__BYP)
/* Port wide control signals */                                                   
#define D6_CTL                    (* (reg8 *) D6__CTL)
/* Drive Modes */
#define D6_DM0                    (* (reg8 *) D6__DM0) 
#define D6_DM1                    (* (reg8 *) D6__DM1)
#define D6_DM2                    (* (reg8 *) D6__DM2) 
/* Input Buffer Disable Override */
#define D6_INP_DIS                (* (reg8 *) D6__INP_DIS)
/* LCD Common or Segment Drive */
#define D6_LCD_COM_SEG            (* (reg8 *) D6__LCD_COM_SEG)
/* Enable Segment LCD */
#define D6_LCD_EN                 (* (reg8 *) D6__LCD_EN)
/* Slew Rate Control */
#define D6_SLW                    (* (reg8 *) D6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D6_PRTDSI__CAPS_SEL       (* (reg8 *) D6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D6_PRTDSI__OE_SEL0        (* (reg8 *) D6__PRTDSI__OE_SEL0) 
#define D6_PRTDSI__OE_SEL1        (* (reg8 *) D6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D6_PRTDSI__OUT_SEL0       (* (reg8 *) D6__PRTDSI__OUT_SEL0) 
#define D6_PRTDSI__OUT_SEL1       (* (reg8 *) D6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D6_PRTDSI__SYNC_OUT       (* (reg8 *) D6__PRTDSI__SYNC_OUT) 


#if defined(D6__INTSTAT)  /* Interrupt Registers */

    #define D6_INTSTAT                (* (reg8 *) D6__INTSTAT)
    #define D6_SNAP                   (* (reg8 *) D6__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D6_H */


/* [] END OF FILE */
