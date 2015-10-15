/*******************************************************************************
* File Name: DB4.c  
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
#include "DB4.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DB4__PORT == 15 && ((DB4__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DB4_Write
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
void DB4_Write(uint8 value) 
{
    uint8 staticBits = (DB4_DR & (uint8)(~DB4_MASK));
    DB4_DR = staticBits | ((uint8)(value << DB4_SHIFT) & DB4_MASK);
}


/*******************************************************************************
* Function Name: DB4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DB4_DM_STRONG     Strong Drive 
*  DB4_DM_OD_HI      Open Drain, Drives High 
*  DB4_DM_OD_LO      Open Drain, Drives Low 
*  DB4_DM_RES_UP     Resistive Pull Up 
*  DB4_DM_RES_DWN    Resistive Pull Down 
*  DB4_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DB4_DM_DIG_HIZ    High Impedance Digital 
*  DB4_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DB4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DB4_0, mode);
}


/*******************************************************************************
* Function Name: DB4_Read
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
*  Macro DB4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DB4_Read(void) 
{
    return (DB4_PS & DB4_MASK) >> DB4_SHIFT;
}


/*******************************************************************************
* Function Name: DB4_ReadDataReg
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
uint8 DB4_ReadDataReg(void) 
{
    return (DB4_DR & DB4_MASK) >> DB4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DB4_INTSTAT) 

    /*******************************************************************************
    * Function Name: DB4_ClearInterrupt
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
    uint8 DB4_ClearInterrupt(void) 
    {
        return (DB4_INTSTAT & DB4_MASK) >> DB4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
