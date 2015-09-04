/*******************************************************************************
* File Name: nav_clock.h
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
#if !defined(CY_ISR_nav_clock_H)
#define CY_ISR_nav_clock_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void nav_clock_Start(void);
void nav_clock_StartEx(cyisraddress address);
void nav_clock_Stop(void);

CY_ISR_PROTO(nav_clock_Interrupt);

void nav_clock_SetVector(cyisraddress address);
cyisraddress nav_clock_GetVector(void);

void nav_clock_SetPriority(uint8 priority);
uint8 nav_clock_GetPriority(void);

void nav_clock_Enable(void);
uint8 nav_clock_GetState(void);
void nav_clock_Disable(void);

void nav_clock_SetPending(void);
void nav_clock_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the nav_clock ISR. */
#define nav_clock_INTC_VECTOR            ((reg32 *) nav_clock__INTC_VECT)

/* Address of the nav_clock ISR priority. */
#define nav_clock_INTC_PRIOR             ((reg8 *) nav_clock__INTC_PRIOR_REG)

/* Priority of the nav_clock interrupt. */
#define nav_clock_INTC_PRIOR_NUMBER      nav_clock__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable nav_clock interrupt. */
#define nav_clock_INTC_SET_EN            ((reg32 *) nav_clock__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the nav_clock interrupt. */
#define nav_clock_INTC_CLR_EN            ((reg32 *) nav_clock__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the nav_clock interrupt state to pending. */
#define nav_clock_INTC_SET_PD            ((reg32 *) nav_clock__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the nav_clock interrupt. */
#define nav_clock_INTC_CLR_PD            ((reg32 *) nav_clock__INTC_CLR_PD_REG)


#endif /* CY_ISR_nav_clock_H */


/* [] END OF FILE */
