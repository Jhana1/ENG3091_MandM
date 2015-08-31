/*******************************************************************************
* File Name: M2EN.h  
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

#if !defined(CY_PINS_M2EN_H) /* Pins M2EN_H */
#define CY_PINS_M2EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M2EN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M2EN__PORT == 15 && ((M2EN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    M2EN_Write(uint8 value) ;
void    M2EN_SetDriveMode(uint8 mode) ;
uint8   M2EN_ReadDataReg(void) ;
uint8   M2EN_Read(void) ;
uint8   M2EN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M2EN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define M2EN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define M2EN_DM_RES_UP          PIN_DM_RES_UP
#define M2EN_DM_RES_DWN         PIN_DM_RES_DWN
#define M2EN_DM_OD_LO           PIN_DM_OD_LO
#define M2EN_DM_OD_HI           PIN_DM_OD_HI
#define M2EN_DM_STRONG          PIN_DM_STRONG
#define M2EN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define M2EN_MASK               M2EN__MASK
#define M2EN_SHIFT              M2EN__SHIFT
#define M2EN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M2EN_PS                     (* (reg8 *) M2EN__PS)
/* Data Register */
#define M2EN_DR                     (* (reg8 *) M2EN__DR)
/* Port Number */
#define M2EN_PRT_NUM                (* (reg8 *) M2EN__PRT) 
/* Connect to Analog Globals */                                                  
#define M2EN_AG                     (* (reg8 *) M2EN__AG)                       
/* Analog MUX bux enable */
#define M2EN_AMUX                   (* (reg8 *) M2EN__AMUX) 
/* Bidirectional Enable */                                                        
#define M2EN_BIE                    (* (reg8 *) M2EN__BIE)
/* Bit-mask for Aliased Register Access */
#define M2EN_BIT_MASK               (* (reg8 *) M2EN__BIT_MASK)
/* Bypass Enable */
#define M2EN_BYP                    (* (reg8 *) M2EN__BYP)
/* Port wide control signals */                                                   
#define M2EN_CTL                    (* (reg8 *) M2EN__CTL)
/* Drive Modes */
#define M2EN_DM0                    (* (reg8 *) M2EN__DM0) 
#define M2EN_DM1                    (* (reg8 *) M2EN__DM1)
#define M2EN_DM2                    (* (reg8 *) M2EN__DM2) 
/* Input Buffer Disable Override */
#define M2EN_INP_DIS                (* (reg8 *) M2EN__INP_DIS)
/* LCD Common or Segment Drive */
#define M2EN_LCD_COM_SEG            (* (reg8 *) M2EN__LCD_COM_SEG)
/* Enable Segment LCD */
#define M2EN_LCD_EN                 (* (reg8 *) M2EN__LCD_EN)
/* Slew Rate Control */
#define M2EN_SLW                    (* (reg8 *) M2EN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M2EN_PRTDSI__CAPS_SEL       (* (reg8 *) M2EN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M2EN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M2EN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M2EN_PRTDSI__OE_SEL0        (* (reg8 *) M2EN__PRTDSI__OE_SEL0) 
#define M2EN_PRTDSI__OE_SEL1        (* (reg8 *) M2EN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M2EN_PRTDSI__OUT_SEL0       (* (reg8 *) M2EN__PRTDSI__OUT_SEL0) 
#define M2EN_PRTDSI__OUT_SEL1       (* (reg8 *) M2EN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M2EN_PRTDSI__SYNC_OUT       (* (reg8 *) M2EN__PRTDSI__SYNC_OUT) 


#if defined(M2EN__INTSTAT)  /* Interrupt Registers */

    #define M2EN_INTSTAT                (* (reg8 *) M2EN__INTSTAT)
    #define M2EN_SNAP                   (* (reg8 *) M2EN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M2EN_H */


/* [] END OF FILE */
