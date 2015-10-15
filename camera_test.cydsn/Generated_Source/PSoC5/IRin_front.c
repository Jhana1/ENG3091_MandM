/*******************************************************************************
* File Name: IRin_front.c  
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
#include "IRin_front.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 IRin_front__PORT == 15 && ((IRin_front__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: IRin_front_Write
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
void IRin_front_Write(uint8 value) 
{
    uint8 staticBits = (IRin_front_DR & (uint8)(~IRin_front_MASK));
    IRin_front_DR = staticBits | ((uint8)(value << IRin_front_SHIFT) & IRin_front_MASK);
}


/*******************************************************************************
* Function Name: IRin_front_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  IRin_front_DM_STRONG     Strong Drive 
*  IRin_front_DM_OD_HI      Open Drain, Drives High 
*  IRin_front_DM_OD_LO      Open Drain, Drives Low 
*  IRin_front_DM_RES_UP     Resistive Pull Up 
*  IRin_front_DM_RES_DWN    Resistive Pull Down 
*  IRin_front_DM_RES_UPDWN  Resistive Pull Up/Down 
*  IRin_front_DM_DIG_HIZ    High Impedance Digital 
*  IRin_front_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void IRin_front_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(IRin_front_0, mode);
}


/*******************************************************************************
* Function Name: IRin_front_Read
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
*  Macro IRin_front_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 IRin_front_Read(void) 
{
    return (IRin_front_PS & IRin_front_MASK) >> IRin_front_SHIFT;
}


/*******************************************************************************
* Function Name: IRin_front_ReadDataReg
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
uint8 IRin_front_ReadDataReg(void) 
{
    return (IRin_front_DR & IRin_front_MASK) >> IRin_front_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(IRin_front_INTSTAT) 

    /*******************************************************************************
    * Function Name: IRin_front_ClearInterrupt
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
    uint8 IRin_front_ClearInterrupt(void) 
    {
        return (IRin_front_INTSTAT & IRin_front_MASK) >> IRin_front_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
