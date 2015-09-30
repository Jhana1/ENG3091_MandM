/*******************************************************************************
* File Name: ISR_CHECKP.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "ISR_CHECKP.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ISR_CHECKP__PORT == 15 && ((ISR_CHECKP__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ISR_CHECKP_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void ISR_CHECKP_Write(uint8 value) 
{
    uint8 staticBits = (ISR_CHECKP_DR & (uint8)(~ISR_CHECKP_MASK));
    ISR_CHECKP_DR = staticBits | ((uint8)(value << ISR_CHECKP_SHIFT) & ISR_CHECKP_MASK);
}


/*******************************************************************************
* Function Name: ISR_CHECKP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ISR_CHECKP_DM_STRONG     Strong Drive 
*  ISR_CHECKP_DM_OD_HI      Open Drain, Drives High 
*  ISR_CHECKP_DM_OD_LO      Open Drain, Drives Low 
*  ISR_CHECKP_DM_RES_UP     Resistive Pull Up 
*  ISR_CHECKP_DM_RES_DWN    Resistive Pull Down 
*  ISR_CHECKP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ISR_CHECKP_DM_DIG_HIZ    High Impedance Digital 
*  ISR_CHECKP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ISR_CHECKP_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ISR_CHECKP_0, mode);
}


/*******************************************************************************
* Function Name: ISR_CHECKP_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro ISR_CHECKP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ISR_CHECKP_Read(void) 
{
    return (ISR_CHECKP_PS & ISR_CHECKP_MASK) >> ISR_CHECKP_SHIFT;
}


/*******************************************************************************
* Function Name: ISR_CHECKP_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 ISR_CHECKP_ReadDataReg(void) 
{
    return (ISR_CHECKP_DR & ISR_CHECKP_MASK) >> ISR_CHECKP_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ISR_CHECKP_INTSTAT) 

    /*******************************************************************************
    * Function Name: ISR_CHECKP_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 ISR_CHECKP_ClearInterrupt(void) 
    {
        return (ISR_CHECKP_INTSTAT & ISR_CHECKP_MASK) >> ISR_CHECKP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
