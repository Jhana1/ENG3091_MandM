/*******************************************************************************
* File Name: DB7.c  
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
#include "DB7.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DB7__PORT == 15 && ((DB7__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DB7_Write
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
void DB7_Write(uint8 value) 
{
    uint8 staticBits = (DB7_DR & (uint8)(~DB7_MASK));
    DB7_DR = staticBits | ((uint8)(value << DB7_SHIFT) & DB7_MASK);
}


/*******************************************************************************
* Function Name: DB7_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DB7_DM_STRONG     Strong Drive 
*  DB7_DM_OD_HI      Open Drain, Drives High 
*  DB7_DM_OD_LO      Open Drain, Drives Low 
*  DB7_DM_RES_UP     Resistive Pull Up 
*  DB7_DM_RES_DWN    Resistive Pull Down 
*  DB7_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DB7_DM_DIG_HIZ    High Impedance Digital 
*  DB7_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DB7_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DB7_0, mode);
}


/*******************************************************************************
* Function Name: DB7_Read
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
*  Macro DB7_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DB7_Read(void) 
{
    return (DB7_PS & DB7_MASK) >> DB7_SHIFT;
}


/*******************************************************************************
* Function Name: DB7_ReadDataReg
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
uint8 DB7_ReadDataReg(void) 
{
    return (DB7_DR & DB7_MASK) >> DB7_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DB7_INTSTAT) 

    /*******************************************************************************
    * Function Name: DB7_ClearInterrupt
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
    uint8 DB7_ClearInterrupt(void) 
    {
        return (DB7_INTSTAT & DB7_MASK) >> DB7_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
