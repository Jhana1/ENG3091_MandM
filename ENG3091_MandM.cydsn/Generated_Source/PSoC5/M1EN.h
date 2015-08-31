/*******************************************************************************
* File Name: M1EN.h  
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

#if !defined(CY_PINS_M1EN_H) /* Pins M1EN_H */
#define CY_PINS_M1EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M1EN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M1EN__PORT == 15 && ((M1EN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    M1EN_Write(uint8 value) ;
void    M1EN_SetDriveMode(uint8 mode) ;
uint8   M1EN_ReadDataReg(void) ;
uint8   M1EN_Read(void) ;
uint8   M1EN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M1EN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define M1EN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define M1EN_DM_RES_UP          PIN_DM_RES_UP
#define M1EN_DM_RES_DWN         PIN_DM_RES_DWN
#define M1EN_DM_OD_LO           PIN_DM_OD_LO
#define M1EN_DM_OD_HI           PIN_DM_OD_HI
#define M1EN_DM_STRONG          PIN_DM_STRONG
#define M1EN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define M1EN_MASK               M1EN__MASK
#define M1EN_SHIFT              M1EN__SHIFT
#define M1EN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M1EN_PS                     (* (reg8 *) M1EN__PS)
/* Data Register */
#define M1EN_DR                     (* (reg8 *) M1EN__DR)
/* Port Number */
#define M1EN_PRT_NUM                (* (reg8 *) M1EN__PRT) 
/* Connect to Analog Globals */                                                  
#define M1EN_AG                     (* (reg8 *) M1EN__AG)                       
/* Analog MUX bux enable */
#define M1EN_AMUX                   (* (reg8 *) M1EN__AMUX) 
/* Bidirectional Enable */                                                        
#define M1EN_BIE                    (* (reg8 *) M1EN__BIE)
/* Bit-mask for Aliased Register Access */
#define M1EN_BIT_MASK               (* (reg8 *) M1EN__BIT_MASK)
/* Bypass Enable */
#define M1EN_BYP                    (* (reg8 *) M1EN__BYP)
/* Port wide control signals */                                                   
#define M1EN_CTL                    (* (reg8 *) M1EN__CTL)
/* Drive Modes */
#define M1EN_DM0                    (* (reg8 *) M1EN__DM0) 
#define M1EN_DM1                    (* (reg8 *) M1EN__DM1)
#define M1EN_DM2                    (* (reg8 *) M1EN__DM2) 
/* Input Buffer Disable Override */
#define M1EN_INP_DIS                (* (reg8 *) M1EN__INP_DIS)
/* LCD Common or Segment Drive */
#define M1EN_LCD_COM_SEG            (* (reg8 *) M1EN__LCD_COM_SEG)
/* Enable Segment LCD */
#define M1EN_LCD_EN                 (* (reg8 *) M1EN__LCD_EN)
/* Slew Rate Control */
#define M1EN_SLW                    (* (reg8 *) M1EN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M1EN_PRTDSI__CAPS_SEL       (* (reg8 *) M1EN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M1EN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M1EN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M1EN_PRTDSI__OE_SEL0        (* (reg8 *) M1EN__PRTDSI__OE_SEL0) 
#define M1EN_PRTDSI__OE_SEL1        (* (reg8 *) M1EN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M1EN_PRTDSI__OUT_SEL0       (* (reg8 *) M1EN__PRTDSI__OUT_SEL0) 
#define M1EN_PRTDSI__OUT_SEL1       (* (reg8 *) M1EN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M1EN_PRTDSI__SYNC_OUT       (* (reg8 *) M1EN__PRTDSI__SYNC_OUT) 


#if defined(M1EN__INTSTAT)  /* Interrupt Registers */

    #define M1EN_INTSTAT                (* (reg8 *) M1EN__INTSTAT)
    #define M1EN_SNAP                   (* (reg8 *) M1EN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M1EN_H */


/* [] END OF FILE */
