/*******************************************************************************
* File Name: COMPASS_DRDY.h  
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

#if !defined(CY_PINS_COMPASS_DRDY_H) /* Pins COMPASS_DRDY_H */
#define CY_PINS_COMPASS_DRDY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "COMPASS_DRDY_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 COMPASS_DRDY__PORT == 15 && ((COMPASS_DRDY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    COMPASS_DRDY_Write(uint8 value) ;
void    COMPASS_DRDY_SetDriveMode(uint8 mode) ;
uint8   COMPASS_DRDY_ReadDataReg(void) ;
uint8   COMPASS_DRDY_Read(void) ;
uint8   COMPASS_DRDY_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define COMPASS_DRDY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define COMPASS_DRDY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define COMPASS_DRDY_DM_RES_UP          PIN_DM_RES_UP
#define COMPASS_DRDY_DM_RES_DWN         PIN_DM_RES_DWN
#define COMPASS_DRDY_DM_OD_LO           PIN_DM_OD_LO
#define COMPASS_DRDY_DM_OD_HI           PIN_DM_OD_HI
#define COMPASS_DRDY_DM_STRONG          PIN_DM_STRONG
#define COMPASS_DRDY_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define COMPASS_DRDY_MASK               COMPASS_DRDY__MASK
#define COMPASS_DRDY_SHIFT              COMPASS_DRDY__SHIFT
#define COMPASS_DRDY_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define COMPASS_DRDY_PS                     (* (reg8 *) COMPASS_DRDY__PS)
/* Data Register */
#define COMPASS_DRDY_DR                     (* (reg8 *) COMPASS_DRDY__DR)
/* Port Number */
#define COMPASS_DRDY_PRT_NUM                (* (reg8 *) COMPASS_DRDY__PRT) 
/* Connect to Analog Globals */                                                  
#define COMPASS_DRDY_AG                     (* (reg8 *) COMPASS_DRDY__AG)                       
/* Analog MUX bux enable */
#define COMPASS_DRDY_AMUX                   (* (reg8 *) COMPASS_DRDY__AMUX) 
/* Bidirectional Enable */                                                        
#define COMPASS_DRDY_BIE                    (* (reg8 *) COMPASS_DRDY__BIE)
/* Bit-mask for Aliased Register Access */
#define COMPASS_DRDY_BIT_MASK               (* (reg8 *) COMPASS_DRDY__BIT_MASK)
/* Bypass Enable */
#define COMPASS_DRDY_BYP                    (* (reg8 *) COMPASS_DRDY__BYP)
/* Port wide control signals */                                                   
#define COMPASS_DRDY_CTL                    (* (reg8 *) COMPASS_DRDY__CTL)
/* Drive Modes */
#define COMPASS_DRDY_DM0                    (* (reg8 *) COMPASS_DRDY__DM0) 
#define COMPASS_DRDY_DM1                    (* (reg8 *) COMPASS_DRDY__DM1)
#define COMPASS_DRDY_DM2                    (* (reg8 *) COMPASS_DRDY__DM2) 
/* Input Buffer Disable Override */
#define COMPASS_DRDY_INP_DIS                (* (reg8 *) COMPASS_DRDY__INP_DIS)
/* LCD Common or Segment Drive */
#define COMPASS_DRDY_LCD_COM_SEG            (* (reg8 *) COMPASS_DRDY__LCD_COM_SEG)
/* Enable Segment LCD */
#define COMPASS_DRDY_LCD_EN                 (* (reg8 *) COMPASS_DRDY__LCD_EN)
/* Slew Rate Control */
#define COMPASS_DRDY_SLW                    (* (reg8 *) COMPASS_DRDY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define COMPASS_DRDY_PRTDSI__CAPS_SEL       (* (reg8 *) COMPASS_DRDY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define COMPASS_DRDY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) COMPASS_DRDY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define COMPASS_DRDY_PRTDSI__OE_SEL0        (* (reg8 *) COMPASS_DRDY__PRTDSI__OE_SEL0) 
#define COMPASS_DRDY_PRTDSI__OE_SEL1        (* (reg8 *) COMPASS_DRDY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define COMPASS_DRDY_PRTDSI__OUT_SEL0       (* (reg8 *) COMPASS_DRDY__PRTDSI__OUT_SEL0) 
#define COMPASS_DRDY_PRTDSI__OUT_SEL1       (* (reg8 *) COMPASS_DRDY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define COMPASS_DRDY_PRTDSI__SYNC_OUT       (* (reg8 *) COMPASS_DRDY__PRTDSI__SYNC_OUT) 


#if defined(COMPASS_DRDY__INTSTAT)  /* Interrupt Registers */

    #define COMPASS_DRDY_INTSTAT                (* (reg8 *) COMPASS_DRDY__INTSTAT)
    #define COMPASS_DRDY_SNAP                   (* (reg8 *) COMPASS_DRDY__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_COMPASS_DRDY_H */


/* [] END OF FILE */
