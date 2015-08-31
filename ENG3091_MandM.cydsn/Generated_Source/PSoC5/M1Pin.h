/*******************************************************************************
* File Name: M1Pin.h  
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

#if !defined(CY_PINS_M1Pin_H) /* Pins M1Pin_H */
#define CY_PINS_M1Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M1Pin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M1Pin__PORT == 15 && ((M1Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    M1Pin_Write(uint8 value) ;
void    M1Pin_SetDriveMode(uint8 mode) ;
uint8   M1Pin_ReadDataReg(void) ;
uint8   M1Pin_Read(void) ;
uint8   M1Pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M1Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define M1Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define M1Pin_DM_RES_UP          PIN_DM_RES_UP
#define M1Pin_DM_RES_DWN         PIN_DM_RES_DWN
#define M1Pin_DM_OD_LO           PIN_DM_OD_LO
#define M1Pin_DM_OD_HI           PIN_DM_OD_HI
#define M1Pin_DM_STRONG          PIN_DM_STRONG
#define M1Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define M1Pin_MASK               M1Pin__MASK
#define M1Pin_SHIFT              M1Pin__SHIFT
#define M1Pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M1Pin_PS                     (* (reg8 *) M1Pin__PS)
/* Data Register */
#define M1Pin_DR                     (* (reg8 *) M1Pin__DR)
/* Port Number */
#define M1Pin_PRT_NUM                (* (reg8 *) M1Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define M1Pin_AG                     (* (reg8 *) M1Pin__AG)                       
/* Analog MUX bux enable */
#define M1Pin_AMUX                   (* (reg8 *) M1Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define M1Pin_BIE                    (* (reg8 *) M1Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define M1Pin_BIT_MASK               (* (reg8 *) M1Pin__BIT_MASK)
/* Bypass Enable */
#define M1Pin_BYP                    (* (reg8 *) M1Pin__BYP)
/* Port wide control signals */                                                   
#define M1Pin_CTL                    (* (reg8 *) M1Pin__CTL)
/* Drive Modes */
#define M1Pin_DM0                    (* (reg8 *) M1Pin__DM0) 
#define M1Pin_DM1                    (* (reg8 *) M1Pin__DM1)
#define M1Pin_DM2                    (* (reg8 *) M1Pin__DM2) 
/* Input Buffer Disable Override */
#define M1Pin_INP_DIS                (* (reg8 *) M1Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define M1Pin_LCD_COM_SEG            (* (reg8 *) M1Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define M1Pin_LCD_EN                 (* (reg8 *) M1Pin__LCD_EN)
/* Slew Rate Control */
#define M1Pin_SLW                    (* (reg8 *) M1Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M1Pin_PRTDSI__CAPS_SEL       (* (reg8 *) M1Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M1Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M1Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M1Pin_PRTDSI__OE_SEL0        (* (reg8 *) M1Pin__PRTDSI__OE_SEL0) 
#define M1Pin_PRTDSI__OE_SEL1        (* (reg8 *) M1Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M1Pin_PRTDSI__OUT_SEL0       (* (reg8 *) M1Pin__PRTDSI__OUT_SEL0) 
#define M1Pin_PRTDSI__OUT_SEL1       (* (reg8 *) M1Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M1Pin_PRTDSI__SYNC_OUT       (* (reg8 *) M1Pin__PRTDSI__SYNC_OUT) 


#if defined(M1Pin__INTSTAT)  /* Interrupt Registers */

    #define M1Pin_INTSTAT                (* (reg8 *) M1Pin__INTSTAT)
    #define M1Pin_SNAP                   (* (reg8 *) M1Pin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M1Pin_H */


/* [] END OF FILE */
