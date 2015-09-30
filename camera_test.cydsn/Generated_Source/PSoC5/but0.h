/*******************************************************************************
* File Name: but0.h
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
#if !defined(CY_ISR_but0_H)
#define CY_ISR_but0_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void but0_Start(void);
void but0_StartEx(cyisraddress address);
void but0_Stop(void);

CY_ISR_PROTO(but0_Interrupt);

void but0_SetVector(cyisraddress address);
cyisraddress but0_GetVector(void);

void but0_SetPriority(uint8 priority);
uint8 but0_GetPriority(void);

void but0_Enable(void);
uint8 but0_GetState(void);
void but0_Disable(void);

void but0_SetPending(void);
void but0_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the but0 ISR. */
#define but0_INTC_VECTOR            ((reg32 *) but0__INTC_VECT)

/* Address of the but0 ISR priority. */
#define but0_INTC_PRIOR             ((reg8 *) but0__INTC_PRIOR_REG)

/* Priority of the but0 interrupt. */
#define but0_INTC_PRIOR_NUMBER      but0__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable but0 interrupt. */
#define but0_INTC_SET_EN            ((reg32 *) but0__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the but0 interrupt. */
#define but0_INTC_CLR_EN            ((reg32 *) but0__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the but0 interrupt state to pending. */
#define but0_INTC_SET_PD            ((reg32 *) but0__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the but0 interrupt. */
#define but0_INTC_CLR_PD            ((reg32 *) but0__INTC_CLR_PD_REG)


#endif /* CY_ISR_but0_H */


/* [] END OF FILE */
