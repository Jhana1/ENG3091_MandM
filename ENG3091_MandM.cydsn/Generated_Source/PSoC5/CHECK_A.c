/*******************************************************************************
* File Name: CHECK_A.c  
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
#include "CHECK_A.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 CHECK_A__PORT == 15 && ((CHECK_A__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: CHECK_A_Write
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
void CHECK_A_Write(uint8 value) 
{
    uint8 staticBits = (CHECK_A_DR & (uint8)(~CHECK_A_MASK));
    CHECK_A_DR = staticBits | ((uint8)(value << CHECK_A_SHIFT) & CHECK_A_MASK);
}


/*******************************************************************************
* Function Name: CHECK_A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  CHECK_A_DM_STRONG     Strong Drive 
*  CHECK_A_DM_OD_HI      Open Drain, Drives High 
*  CHECK_A_DM_OD_LO      Open Drain, Drives Low 
*  CHECK_A_DM_RES_UP     Resistive Pull Up 
*  CHECK_A_DM_RES_DWN    Resistive Pull Down 
*  CHECK_A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  CHECK_A_DM_DIG_HIZ    High Impedance Digital 
*  CHECK_A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void CHECK_A_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(CHECK_A_0, mode);
}


/*******************************************************************************
* Function Name: CHECK_A_Read
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
*  Macro CHECK_A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CHECK_A_Read(void) 
{
    return (CHECK_A_PS & CHECK_A_MASK) >> CHECK_A_SHIFT;
}


/*******************************************************************************
* Function Name: CHECK_A_ReadDataReg
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
uint8 CHECK_A_ReadDataReg(void) 
{
    return (CHECK_A_DR & CHECK_A_MASK) >> CHECK_A_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CHECK_A_INTSTAT) 

    /*******************************************************************************
    * Function Name: CHECK_A_ClearInterrupt
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
    uint8 CHECK_A_ClearInterrupt(void) 
    {
        return (CHECK_A_INTSTAT & CHECK_A_MASK) >> CHECK_A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
