/*******************************************************************************
* File Name: Camera_VSYNC.h  
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

#if !defined(CY_PINS_Camera_VSYNC_H) /* Pins Camera_VSYNC_H */
#define CY_PINS_Camera_VSYNC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Camera_VSYNC_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Camera_VSYNC__PORT == 15 && ((Camera_VSYNC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Camera_VSYNC_Write(uint8 value) ;
void    Camera_VSYNC_SetDriveMode(uint8 mode) ;
uint8   Camera_VSYNC_ReadDataReg(void) ;
uint8   Camera_VSYNC_Read(void) ;
uint8   Camera_VSYNC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Camera_VSYNC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Camera_VSYNC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Camera_VSYNC_DM_RES_UP          PIN_DM_RES_UP
#define Camera_VSYNC_DM_RES_DWN         PIN_DM_RES_DWN
#define Camera_VSYNC_DM_OD_LO           PIN_DM_OD_LO
#define Camera_VSYNC_DM_OD_HI           PIN_DM_OD_HI
#define Camera_VSYNC_DM_STRONG          PIN_DM_STRONG
#define Camera_VSYNC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Camera_VSYNC_MASK               Camera_VSYNC__MASK
#define Camera_VSYNC_SHIFT              Camera_VSYNC__SHIFT
#define Camera_VSYNC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Camera_VSYNC_PS                     (* (reg8 *) Camera_VSYNC__PS)
/* Data Register */
#define Camera_VSYNC_DR                     (* (reg8 *) Camera_VSYNC__DR)
/* Port Number */
#define Camera_VSYNC_PRT_NUM                (* (reg8 *) Camera_VSYNC__PRT) 
/* Connect to Analog Globals */                                                  
#define Camera_VSYNC_AG                     (* (reg8 *) Camera_VSYNC__AG)                       
/* Analog MUX bux enable */
#define Camera_VSYNC_AMUX                   (* (reg8 *) Camera_VSYNC__AMUX) 
/* Bidirectional Enable */                                                        
#define Camera_VSYNC_BIE                    (* (reg8 *) Camera_VSYNC__BIE)
/* Bit-mask for Aliased Register Access */
#define Camera_VSYNC_BIT_MASK               (* (reg8 *) Camera_VSYNC__BIT_MASK)
/* Bypass Enable */
#define Camera_VSYNC_BYP                    (* (reg8 *) Camera_VSYNC__BYP)
/* Port wide control signals */                                                   
#define Camera_VSYNC_CTL                    (* (reg8 *) Camera_VSYNC__CTL)
/* Drive Modes */
#define Camera_VSYNC_DM0                    (* (reg8 *) Camera_VSYNC__DM0) 
#define Camera_VSYNC_DM1                    (* (reg8 *) Camera_VSYNC__DM1)
#define Camera_VSYNC_DM2                    (* (reg8 *) Camera_VSYNC__DM2) 
/* Input Buffer Disable Override */
#define Camera_VSYNC_INP_DIS                (* (reg8 *) Camera_VSYNC__INP_DIS)
/* LCD Common or Segment Drive */
#define Camera_VSYNC_LCD_COM_SEG            (* (reg8 *) Camera_VSYNC__LCD_COM_SEG)
/* Enable Segment LCD */
#define Camera_VSYNC_LCD_EN                 (* (reg8 *) Camera_VSYNC__LCD_EN)
/* Slew Rate Control */
#define Camera_VSYNC_SLW                    (* (reg8 *) Camera_VSYNC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Camera_VSYNC_PRTDSI__CAPS_SEL       (* (reg8 *) Camera_VSYNC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Camera_VSYNC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Camera_VSYNC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Camera_VSYNC_PRTDSI__OE_SEL0        (* (reg8 *) Camera_VSYNC__PRTDSI__OE_SEL0) 
#define Camera_VSYNC_PRTDSI__OE_SEL1        (* (reg8 *) Camera_VSYNC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Camera_VSYNC_PRTDSI__OUT_SEL0       (* (reg8 *) Camera_VSYNC__PRTDSI__OUT_SEL0) 
#define Camera_VSYNC_PRTDSI__OUT_SEL1       (* (reg8 *) Camera_VSYNC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Camera_VSYNC_PRTDSI__SYNC_OUT       (* (reg8 *) Camera_VSYNC__PRTDSI__SYNC_OUT) 


#if defined(Camera_VSYNC__INTSTAT)  /* Interrupt Registers */

    #define Camera_VSYNC_INTSTAT                (* (reg8 *) Camera_VSYNC__INTSTAT)
    #define Camera_VSYNC_SNAP                   (* (reg8 *) Camera_VSYNC__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Camera_VSYNC_H */


/* [] END OF FILE */
