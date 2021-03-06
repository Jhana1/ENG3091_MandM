/*******************************************************************************
* File Name: HC_ECHO_S.h  
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

#if !defined(CY_PINS_HC_ECHO_S_H) /* Pins HC_ECHO_S_H */
#define CY_PINS_HC_ECHO_S_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HC_ECHO_S_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HC_ECHO_S__PORT == 15 && ((HC_ECHO_S__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    HC_ECHO_S_Write(uint8 value) ;
void    HC_ECHO_S_SetDriveMode(uint8 mode) ;
uint8   HC_ECHO_S_ReadDataReg(void) ;
uint8   HC_ECHO_S_Read(void) ;
uint8   HC_ECHO_S_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HC_ECHO_S_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define HC_ECHO_S_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define HC_ECHO_S_DM_RES_UP          PIN_DM_RES_UP
#define HC_ECHO_S_DM_RES_DWN         PIN_DM_RES_DWN
#define HC_ECHO_S_DM_OD_LO           PIN_DM_OD_LO
#define HC_ECHO_S_DM_OD_HI           PIN_DM_OD_HI
#define HC_ECHO_S_DM_STRONG          PIN_DM_STRONG
#define HC_ECHO_S_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define HC_ECHO_S_MASK               HC_ECHO_S__MASK
#define HC_ECHO_S_SHIFT              HC_ECHO_S__SHIFT
#define HC_ECHO_S_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HC_ECHO_S_PS                     (* (reg8 *) HC_ECHO_S__PS)
/* Data Register */
#define HC_ECHO_S_DR                     (* (reg8 *) HC_ECHO_S__DR)
/* Port Number */
#define HC_ECHO_S_PRT_NUM                (* (reg8 *) HC_ECHO_S__PRT) 
/* Connect to Analog Globals */                                                  
#define HC_ECHO_S_AG                     (* (reg8 *) HC_ECHO_S__AG)                       
/* Analog MUX bux enable */
#define HC_ECHO_S_AMUX                   (* (reg8 *) HC_ECHO_S__AMUX) 
/* Bidirectional Enable */                                                        
#define HC_ECHO_S_BIE                    (* (reg8 *) HC_ECHO_S__BIE)
/* Bit-mask for Aliased Register Access */
#define HC_ECHO_S_BIT_MASK               (* (reg8 *) HC_ECHO_S__BIT_MASK)
/* Bypass Enable */
#define HC_ECHO_S_BYP                    (* (reg8 *) HC_ECHO_S__BYP)
/* Port wide control signals */                                                   
#define HC_ECHO_S_CTL                    (* (reg8 *) HC_ECHO_S__CTL)
/* Drive Modes */
#define HC_ECHO_S_DM0                    (* (reg8 *) HC_ECHO_S__DM0) 
#define HC_ECHO_S_DM1                    (* (reg8 *) HC_ECHO_S__DM1)
#define HC_ECHO_S_DM2                    (* (reg8 *) HC_ECHO_S__DM2) 
/* Input Buffer Disable Override */
#define HC_ECHO_S_INP_DIS                (* (reg8 *) HC_ECHO_S__INP_DIS)
/* LCD Common or Segment Drive */
#define HC_ECHO_S_LCD_COM_SEG            (* (reg8 *) HC_ECHO_S__LCD_COM_SEG)
/* Enable Segment LCD */
#define HC_ECHO_S_LCD_EN                 (* (reg8 *) HC_ECHO_S__LCD_EN)
/* Slew Rate Control */
#define HC_ECHO_S_SLW                    (* (reg8 *) HC_ECHO_S__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HC_ECHO_S_PRTDSI__CAPS_SEL       (* (reg8 *) HC_ECHO_S__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HC_ECHO_S_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HC_ECHO_S__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HC_ECHO_S_PRTDSI__OE_SEL0        (* (reg8 *) HC_ECHO_S__PRTDSI__OE_SEL0) 
#define HC_ECHO_S_PRTDSI__OE_SEL1        (* (reg8 *) HC_ECHO_S__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HC_ECHO_S_PRTDSI__OUT_SEL0       (* (reg8 *) HC_ECHO_S__PRTDSI__OUT_SEL0) 
#define HC_ECHO_S_PRTDSI__OUT_SEL1       (* (reg8 *) HC_ECHO_S__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HC_ECHO_S_PRTDSI__SYNC_OUT       (* (reg8 *) HC_ECHO_S__PRTDSI__SYNC_OUT) 


#if defined(HC_ECHO_S__INTSTAT)  /* Interrupt Registers */

    #define HC_ECHO_S_INTSTAT                (* (reg8 *) HC_ECHO_S__INTSTAT)
    #define HC_ECHO_S_SNAP                   (* (reg8 *) HC_ECHO_S__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HC_ECHO_S_H */


/* [] END OF FILE */
