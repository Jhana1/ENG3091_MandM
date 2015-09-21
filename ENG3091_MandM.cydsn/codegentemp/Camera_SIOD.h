/*******************************************************************************
* File Name: Camera_SIOD.h  
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

#if !defined(CY_PINS_Camera_SIOD_H) /* Pins Camera_SIOD_H */
#define CY_PINS_Camera_SIOD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Camera_SIOD_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Camera_SIOD__PORT == 15 && ((Camera_SIOD__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Camera_SIOD_Write(uint8 value) ;
void    Camera_SIOD_SetDriveMode(uint8 mode) ;
uint8   Camera_SIOD_ReadDataReg(void) ;
uint8   Camera_SIOD_Read(void) ;
uint8   Camera_SIOD_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Camera_SIOD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Camera_SIOD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Camera_SIOD_DM_RES_UP          PIN_DM_RES_UP
#define Camera_SIOD_DM_RES_DWN         PIN_DM_RES_DWN
#define Camera_SIOD_DM_OD_LO           PIN_DM_OD_LO
#define Camera_SIOD_DM_OD_HI           PIN_DM_OD_HI
#define Camera_SIOD_DM_STRONG          PIN_DM_STRONG
#define Camera_SIOD_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Camera_SIOD_MASK               Camera_SIOD__MASK
#define Camera_SIOD_SHIFT              Camera_SIOD__SHIFT
#define Camera_SIOD_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Camera_SIOD_PS                     (* (reg8 *) Camera_SIOD__PS)
/* Data Register */
#define Camera_SIOD_DR                     (* (reg8 *) Camera_SIOD__DR)
/* Port Number */
#define Camera_SIOD_PRT_NUM                (* (reg8 *) Camera_SIOD__PRT) 
/* Connect to Analog Globals */                                                  
#define Camera_SIOD_AG                     (* (reg8 *) Camera_SIOD__AG)                       
/* Analog MUX bux enable */
#define Camera_SIOD_AMUX                   (* (reg8 *) Camera_SIOD__AMUX) 
/* Bidirectional Enable */                                                        
#define Camera_SIOD_BIE                    (* (reg8 *) Camera_SIOD__BIE)
/* Bit-mask for Aliased Register Access */
#define Camera_SIOD_BIT_MASK               (* (reg8 *) Camera_SIOD__BIT_MASK)
/* Bypass Enable */
#define Camera_SIOD_BYP                    (* (reg8 *) Camera_SIOD__BYP)
/* Port wide control signals */                                                   
#define Camera_SIOD_CTL                    (* (reg8 *) Camera_SIOD__CTL)
/* Drive Modes */
#define Camera_SIOD_DM0                    (* (reg8 *) Camera_SIOD__DM0) 
#define Camera_SIOD_DM1                    (* (reg8 *) Camera_SIOD__DM1)
#define Camera_SIOD_DM2                    (* (reg8 *) Camera_SIOD__DM2) 
/* Input Buffer Disable Override */
#define Camera_SIOD_INP_DIS                (* (reg8 *) Camera_SIOD__INP_DIS)
/* LCD Common or Segment Drive */
#define Camera_SIOD_LCD_COM_SEG            (* (reg8 *) Camera_SIOD__LCD_COM_SEG)
/* Enable Segment LCD */
#define Camera_SIOD_LCD_EN                 (* (reg8 *) Camera_SIOD__LCD_EN)
/* Slew Rate Control */
#define Camera_SIOD_SLW                    (* (reg8 *) Camera_SIOD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Camera_SIOD_PRTDSI__CAPS_SEL       (* (reg8 *) Camera_SIOD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Camera_SIOD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Camera_SIOD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Camera_SIOD_PRTDSI__OE_SEL0        (* (reg8 *) Camera_SIOD__PRTDSI__OE_SEL0) 
#define Camera_SIOD_PRTDSI__OE_SEL1        (* (reg8 *) Camera_SIOD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Camera_SIOD_PRTDSI__OUT_SEL0       (* (reg8 *) Camera_SIOD__PRTDSI__OUT_SEL0) 
#define Camera_SIOD_PRTDSI__OUT_SEL1       (* (reg8 *) Camera_SIOD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Camera_SIOD_PRTDSI__SYNC_OUT       (* (reg8 *) Camera_SIOD__PRTDSI__SYNC_OUT) 


#if defined(Camera_SIOD__INTSTAT)  /* Interrupt Registers */

    #define Camera_SIOD_INTSTAT                (* (reg8 *) Camera_SIOD__INTSTAT)
    #define Camera_SIOD_SNAP                   (* (reg8 *) Camera_SIOD__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Camera_SIOD_H */


/* [] END OF FILE */
