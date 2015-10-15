/*******************************************************************************
* File Name: but1.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_but1_H)
#define CY_ISR_but1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void but1_Start(void);
void but1_StartEx(cyisraddress address);
void but1_Stop(void);

CY_ISR_PROTO(but1_Interrupt);

void but1_SetVector(cyisraddress address);
cyisraddress but1_GetVector(void);

void but1_SetPriority(uint8 priority);
uint8 but1_GetPriority(void);

void but1_Enable(void);
uint8 but1_GetState(void);
void but1_Disable(void);

void but1_SetPending(void);
void but1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the but1 ISR. */
#define but1_INTC_VECTOR            ((reg32 *) but1__INTC_VECT)

/* Address of the but1 ISR priority. */
#define but1_INTC_PRIOR             ((reg8 *) but1__INTC_PRIOR_REG)

/* Priority of the but1 interrupt. */
#define but1_INTC_PRIOR_NUMBER      but1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable but1 interrupt. */
#define but1_INTC_SET_EN            ((reg32 *) but1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the but1 interrupt. */
#define but1_INTC_CLR_EN            ((reg32 *) but1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the but1 interrupt state to pending. */
#define but1_INTC_SET_PD            ((reg32 *) but1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the but1 interrupt. */
#define but1_INTC_CLR_PD            ((reg32 *) but1__INTC_CLR_PD_REG)


#endif /* CY_ISR_but1_H */


/* [] END OF FILE */
