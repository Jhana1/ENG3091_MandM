/*******************************************************************************
* File Name: DB6.c  
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
#include "DB6.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DB6__PORT == 15 && ((DB6__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DB6_Write
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
void DB6_Write(uint8 value) 
{
    uint8 staticBits = (DB6_DR & (uint8)(~DB6_MASK));
    DB6_DR = staticBits | ((uint8)(value << DB6_SHIFT) & DB6_MASK);
}


/*******************************************************************************
* Function Name: DB6_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DB6_DM_STRONG     Strong Drive 
*  DB6_DM_OD_HI      Open Drain, Drives High 
*  DB6_DM_OD_LO      Open Drain, Drives Low 
*  DB6_DM_RES_UP     Resistive Pull Up 
*  DB6_DM_RES_DWN    Resistive Pull Down 
*  DB6_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DB6_DM_DIG_HIZ    High Impedance Digital 
*  DB6_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DB6_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DB6_0, mode);
}


/*******************************************************************************
* Function Name: DB6_Read
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
*  Macro DB6_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DB6_Read(void) 
{
    return (DB6_PS & DB6_MASK) >> DB6_SHIFT;
}


/*******************************************************************************
* Function Name: DB6_ReadDataReg
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
uint8 DB6_ReadDataReg(void) 
{
    return (DB6_DR & DB6_MASK) >> DB6_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DB6_INTSTAT) 

    /*******************************************************************************
    * Function Name: DB6_ClearInterrupt
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
    uint8 DB6_ClearInterrupt(void) 
    {
        return (DB6_INTSTAT & DB6_MASK) >> DB6_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
