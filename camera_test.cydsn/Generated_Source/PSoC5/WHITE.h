/*******************************************************************************
* File Name: WHITE.h  
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

#if !defined(CY_PINS_WHITE_H) /* Pins WHITE_H */
#define CY_PINS_WHITE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WHITE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WHITE__PORT == 15 && ((WHITE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    WHITE_Write(uint8 value) ;
void    WHITE_SetDriveMode(uint8 mode) ;
uint8   WHITE_ReadDataReg(void) ;
uint8   WHITE_Read(void) ;
uint8   WHITE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WHITE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define WHITE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define WHITE_DM_RES_UP          PIN_DM_RES_UP
#define WHITE_DM_RES_DWN         PIN_DM_RES_DWN
#define WHITE_DM_OD_LO           PIN_DM_OD_LO
#define WHITE_DM_OD_HI           PIN_DM_OD_HI
#define WHITE_DM_STRONG          PIN_DM_STRONG
#define WHITE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define WHITE_MASK               WHITE__MASK
#define WHITE_SHIFT              WHITE__SHIFT
#define WHITE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WHITE_PS                     (* (reg8 *) WHITE__PS)
/* Data Register */
#define WHITE_DR                     (* (reg8 *) WHITE__DR)
/* Port Number */
#define WHITE_PRT_NUM                (* (reg8 *) WHITE__PRT) 
/* Connect to Analog Globals */                                                  
#define WHITE_AG                     (* (reg8 *) WHITE__AG)                       
/* Analog MUX bux enable */
#define WHITE_AMUX                   (* (reg8 *) WHITE__AMUX) 
/* Bidirectional Enable */                                                        
#define WHITE_BIE                    (* (reg8 *) WHITE__BIE)
/* Bit-mask for Aliased Register Access */
#define WHITE_BIT_MASK               (* (reg8 *) WHITE__BIT_MASK)
/* Bypass Enable */
#define WHITE_BYP                    (* (reg8 *) WHITE__BYP)
/* Port wide control signals */                                                   
#define WHITE_CTL                    (* (reg8 *) WHITE__CTL)
/* Drive Modes */
#define WHITE_DM0                    (* (reg8 *) WHITE__DM0) 
#define WHITE_DM1                    (* (reg8 *) WHITE__DM1)
#define WHITE_DM2                    (* (reg8 *) WHITE__DM2) 
/* Input Buffer Disable Override */
#define WHITE_INP_DIS                (* (reg8 *) WHITE__INP_DIS)
/* LCD Common or Segment Drive */
#define WHITE_LCD_COM_SEG            (* (reg8 *) WHITE__LCD_COM_SEG)
/* Enable Segment LCD */
#define WHITE_LCD_EN                 (* (reg8 *) WHITE__LCD_EN)
/* Slew Rate Control */
#define WHITE_SLW                    (* (reg8 *) WHITE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WHITE_PRTDSI__CAPS_SEL       (* (reg8 *) WHITE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WHITE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WHITE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WHITE_PRTDSI__OE_SEL0        (* (reg8 *) WHITE__PRTDSI__OE_SEL0) 
#define WHITE_PRTDSI__OE_SEL1        (* (reg8 *) WHITE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WHITE_PRTDSI__OUT_SEL0       (* (reg8 *) WHITE__PRTDSI__OUT_SEL0) 
#define WHITE_PRTDSI__OUT_SEL1       (* (reg8 *) WHITE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WHITE_PRTDSI__SYNC_OUT       (* (reg8 *) WHITE__PRTDSI__SYNC_OUT) 


#if defined(WHITE__INTSTAT)  /* Interrupt Registers */

    #define WHITE_INTSTAT                (* (reg8 *) WHITE__INTSTAT)
    #define WHITE_SNAP                   (* (reg8 *) WHITE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WHITE_H */


/* [] END OF FILE */
