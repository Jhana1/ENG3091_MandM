/*******************************************************************************
* File Name: WHITE.c  
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
#include "WHITE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 WHITE__PORT == 15 && ((WHITE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: WHITE_Write
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
void WHITE_Write(uint8 value) 
{
    uint8 staticBits = (WHITE_DR & (uint8)(~WHITE_MASK));
    WHITE_DR = staticBits | ((uint8)(value << WHITE_SHIFT) & WHITE_MASK);
}


/*******************************************************************************
* Function Name: WHITE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  WHITE_DM_STRONG     Strong Drive 
*  WHITE_DM_OD_HI      Open Drain, Drives High 
*  WHITE_DM_OD_LO      Open Drain, Drives Low 
*  WHITE_DM_RES_UP     Resistive Pull Up 
*  WHITE_DM_RES_DWN    Resistive Pull Down 
*  WHITE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  WHITE_DM_DIG_HIZ    High Impedance Digital 
*  WHITE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void WHITE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(WHITE_0, mode);
}


/*******************************************************************************
* Function Name: WHITE_Read
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
*  Macro WHITE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 WHITE_Read(void) 
{
    return (WHITE_PS & WHITE_MASK) >> WHITE_SHIFT;
}


/*******************************************************************************
* Function Name: WHITE_ReadDataReg
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
uint8 WHITE_ReadDataReg(void) 
{
    return (WHITE_DR & WHITE_MASK) >> WHITE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(WHITE_INTSTAT) 

    /*******************************************************************************
    * Function Name: WHITE_ClearInterrupt
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
    uint8 WHITE_ClearInterrupt(void) 
    {
        return (WHITE_INTSTAT & WHITE_MASK) >> WHITE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
