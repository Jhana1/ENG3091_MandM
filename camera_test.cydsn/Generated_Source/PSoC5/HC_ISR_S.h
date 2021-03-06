/*******************************************************************************
* File Name: HC_ISR_S.h
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
#if !defined(CY_ISR_HC_ISR_S_H)
#define CY_ISR_HC_ISR_S_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void HC_ISR_S_Start(void);
void HC_ISR_S_StartEx(cyisraddress address);
void HC_ISR_S_Stop(void);

CY_ISR_PROTO(HC_ISR_S_Interrupt);

void HC_ISR_S_SetVector(cyisraddress address);
cyisraddress HC_ISR_S_GetVector(void);

void HC_ISR_S_SetPriority(uint8 priority);
uint8 HC_ISR_S_GetPriority(void);

void HC_ISR_S_Enable(void);
uint8 HC_ISR_S_GetState(void);
void HC_ISR_S_Disable(void);

void HC_ISR_S_SetPending(void);
void HC_ISR_S_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the HC_ISR_S ISR. */
#define HC_ISR_S_INTC_VECTOR            ((reg32 *) HC_ISR_S__INTC_VECT)

/* Address of the HC_ISR_S ISR priority. */
#define HC_ISR_S_INTC_PRIOR             ((reg8 *) HC_ISR_S__INTC_PRIOR_REG)

/* Priority of the HC_ISR_S interrupt. */
#define HC_ISR_S_INTC_PRIOR_NUMBER      HC_ISR_S__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable HC_ISR_S interrupt. */
#define HC_ISR_S_INTC_SET_EN            ((reg32 *) HC_ISR_S__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the HC_ISR_S interrupt. */
#define HC_ISR_S_INTC_CLR_EN            ((reg32 *) HC_ISR_S__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the HC_ISR_S interrupt state to pending. */
#define HC_ISR_S_INTC_SET_PD            ((reg32 *) HC_ISR_S__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the HC_ISR_S interrupt. */
#define HC_ISR_S_INTC_CLR_PD            ((reg32 *) HC_ISR_S__INTC_CLR_PD_REG)


#endif /* CY_ISR_HC_ISR_S_H */


/* [] END OF FILE */
