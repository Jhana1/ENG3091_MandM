/*******************************************************************************
* File Name: mSerial_Dp.h  
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

#if !defined(CY_PINS_mSerial_Dp_H) /* Pins mSerial_Dp_H */
#define CY_PINS_mSerial_Dp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "mSerial_Dp_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 mSerial_Dp__PORT == 15 && ((mSerial_Dp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    mSerial_Dp_Write(uint8 value) ;
void    mSerial_Dp_SetDriveMode(uint8 mode) ;
uint8   mSerial_Dp_ReadDataReg(void) ;
uint8   mSerial_Dp_Read(void) ;
uint8   mSerial_Dp_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define mSerial_Dp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define mSerial_Dp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define mSerial_Dp_DM_RES_UP          PIN_DM_RES_UP
#define mSerial_Dp_DM_RES_DWN         PIN_DM_RES_DWN
#define mSerial_Dp_DM_OD_LO           PIN_DM_OD_LO
#define mSerial_Dp_DM_OD_HI           PIN_DM_OD_HI
#define mSerial_Dp_DM_STRONG          PIN_DM_STRONG
#define mSerial_Dp_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define mSerial_Dp_MASK               mSerial_Dp__MASK
#define mSerial_Dp_SHIFT              mSerial_Dp__SHIFT
#define mSerial_Dp_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define mSerial_Dp_PS                     (* (reg8 *) mSerial_Dp__PS)
/* Data Register */
#define mSerial_Dp_DR                     (* (reg8 *) mSerial_Dp__DR)
/* Port Number */
#define mSerial_Dp_PRT_NUM                (* (reg8 *) mSerial_Dp__PRT) 
/* Connect to Analog Globals */                                                  
#define mSerial_Dp_AG                     (* (reg8 *) mSerial_Dp__AG)                       
/* Analog MUX bux enable */
#define mSerial_Dp_AMUX                   (* (reg8 *) mSerial_Dp__AMUX) 
/* Bidirectional Enable */                                                        
#define mSerial_Dp_BIE                    (* (reg8 *) mSerial_Dp__BIE)
/* Bit-mask for Aliased Register Access */
#define mSerial_Dp_BIT_MASK               (* (reg8 *) mSerial_Dp__BIT_MASK)
/* Bypass Enable */
#define mSerial_Dp_BYP                    (* (reg8 *) mSerial_Dp__BYP)
/* Port wide control signals */                                                   
#define mSerial_Dp_CTL                    (* (reg8 *) mSerial_Dp__CTL)
/* Drive Modes */
#define mSerial_Dp_DM0                    (* (reg8 *) mSerial_Dp__DM0) 
#define mSerial_Dp_DM1                    (* (reg8 *) mSerial_Dp__DM1)
#define mSerial_Dp_DM2                    (* (reg8 *) mSerial_Dp__DM2) 
/* Input Buffer Disable Override */
#define mSerial_Dp_INP_DIS                (* (reg8 *) mSerial_Dp__INP_DIS)
/* LCD Common or Segment Drive */
#define mSerial_Dp_LCD_COM_SEG            (* (reg8 *) mSerial_Dp__LCD_COM_SEG)
/* Enable Segment LCD */
#define mSerial_Dp_LCD_EN                 (* (reg8 *) mSerial_Dp__LCD_EN)
/* Slew Rate Control */
#define mSerial_Dp_SLW                    (* (reg8 *) mSerial_Dp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define mSerial_Dp_PRTDSI__CAPS_SEL       (* (reg8 *) mSerial_Dp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define mSerial_Dp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) mSerial_Dp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define mSerial_Dp_PRTDSI__OE_SEL0        (* (reg8 *) mSerial_Dp__PRTDSI__OE_SEL0) 
#define mSerial_Dp_PRTDSI__OE_SEL1        (* (reg8 *) mSerial_Dp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define mSerial_Dp_PRTDSI__OUT_SEL0       (* (reg8 *) mSerial_Dp__PRTDSI__OUT_SEL0) 
#define mSerial_Dp_PRTDSI__OUT_SEL1       (* (reg8 *) mSerial_Dp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define mSerial_Dp_PRTDSI__SYNC_OUT       (* (reg8 *) mSerial_Dp__PRTDSI__SYNC_OUT) 


#if defined(mSerial_Dp__INTSTAT)  /* Interrupt Registers */

    #define mSerial_Dp_INTSTAT                (* (reg8 *) mSerial_Dp__INTSTAT)
    #define mSerial_Dp_SNAP                   (* (reg8 *) mSerial_Dp__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_mSerial_Dp_H */


/* [] END OF FILE */
