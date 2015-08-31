/*******************************************************************************
* File Name: M2EN.c  
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
#include "M2EN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 M2EN__PORT == 15 && ((M2EN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: M2EN_Write
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
void M2EN_Write(uint8 value) 
{
    uint8 staticBits = (M2EN_DR & (uint8)(~M2EN_MASK));
    M2EN_DR = staticBits | ((uint8)(value << M2EN_SHIFT) & M2EN_MASK);
}


/*******************************************************************************
* Function Name: M2EN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  M2EN_DM_STRONG     Strong Drive 
*  M2EN_DM_OD_HI      Open Drain, Drives High 
*  M2EN_DM_OD_LO      Open Drain, Drives Low 
*  M2EN_DM_RES_UP     Resistive Pull Up 
*  M2EN_DM_RES_DWN    Resistive Pull Down 
*  M2EN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  M2EN_DM_DIG_HIZ    High Impedance Digital 
*  M2EN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void M2EN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(M2EN_0, mode);
}


/*******************************************************************************
* Function Name: M2EN_Read
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
*  Macro M2EN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 M2EN_Read(void) 
{
    return (M2EN_PS & M2EN_MASK) >> M2EN_SHIFT;
}


/*******************************************************************************
* Function Name: M2EN_ReadDataReg
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
uint8 M2EN_ReadDataReg(void) 
{
    return (M2EN_DR & M2EN_MASK) >> M2EN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(M2EN_INTSTAT) 

    /*******************************************************************************
    * Function Name: M2EN_ClearInterrupt
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
    uint8 M2EN_ClearInterrupt(void) 
    {
        return (M2EN_INTSTAT & M2EN_MASK) >> M2EN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
