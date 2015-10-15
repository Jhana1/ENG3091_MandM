/*******************************************************************************
* File Name: IR_LEFT_DONE.h
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
#if !defined(CY_ISR_IR_LEFT_DONE_H)
#define CY_ISR_IR_LEFT_DONE_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IR_LEFT_DONE_Start(void);
void IR_LEFT_DONE_StartEx(cyisraddress address);
void IR_LEFT_DONE_Stop(void);

CY_ISR_PROTO(IR_LEFT_DONE_Interrupt);

void IR_LEFT_DONE_SetVector(cyisraddress address);
cyisraddress IR_LEFT_DONE_GetVector(void);

void IR_LEFT_DONE_SetPriority(uint8 priority);
uint8 IR_LEFT_DONE_GetPriority(void);

void IR_LEFT_DONE_Enable(void);
uint8 IR_LEFT_DONE_GetState(void);
void IR_LEFT_DONE_Disable(void);

void IR_LEFT_DONE_SetPending(void);
void IR_LEFT_DONE_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IR_LEFT_DONE ISR. */
#define IR_LEFT_DONE_INTC_VECTOR            ((reg32 *) IR_LEFT_DONE__INTC_VECT)

/* Address of the IR_LEFT_DONE ISR priority. */
#define IR_LEFT_DONE_INTC_PRIOR             ((reg8 *) IR_LEFT_DONE__INTC_PRIOR_REG)

/* Priority of the IR_LEFT_DONE interrupt. */
#define IR_LEFT_DONE_INTC_PRIOR_NUMBER      IR_LEFT_DONE__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IR_LEFT_DONE interrupt. */
#define IR_LEFT_DONE_INTC_SET_EN            ((reg32 *) IR_LEFT_DONE__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IR_LEFT_DONE interrupt. */
#define IR_LEFT_DONE_INTC_CLR_EN            ((reg32 *) IR_LEFT_DONE__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IR_LEFT_DONE interrupt state to pending. */
#define IR_LEFT_DONE_INTC_SET_PD            ((reg32 *) IR_LEFT_DONE__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IR_LEFT_DONE interrupt. */
#define IR_LEFT_DONE_INTC_CLR_PD            ((reg32 *) IR_LEFT_DONE__INTC_CLR_PD_REG)


#endif /* CY_ISR_IR_LEFT_DONE_H */


/* [] END OF FILE */
