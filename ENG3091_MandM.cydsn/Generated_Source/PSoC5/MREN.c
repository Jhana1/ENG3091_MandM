/*******************************************************************************
* File Name: MREN.c  
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
#include "MREN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 MREN__PORT == 15 && ((MREN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: MREN_Write
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
void MREN_Write(uint8 value) 
{
    uint8 staticBits = (MREN_DR & (uint8)(~MREN_MASK));
    MREN_DR = staticBits | ((uint8)(value << MREN_SHIFT) & MREN_MASK);
}


/*******************************************************************************
* Function Name: MREN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MREN_DM_STRONG     Strong Drive 
*  MREN_DM_OD_HI      Open Drain, Drives High 
*  MREN_DM_OD_LO      Open Drain, Drives Low 
*  MREN_DM_RES_UP     Resistive Pull Up 
*  MREN_DM_RES_DWN    Resistive Pull Down 
*  MREN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MREN_DM_DIG_HIZ    High Impedance Digital 
*  MREN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MREN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MREN_0, mode);
}


/*******************************************************************************
* Function Name: MREN_Read
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
*  Macro MREN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MREN_Read(void) 
{
    return (MREN_PS & MREN_MASK) >> MREN_SHIFT;
}


/*******************************************************************************
* Function Name: MREN_ReadDataReg
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
uint8 MREN_ReadDataReg(void) 
{
    return (MREN_DR & MREN_MASK) >> MREN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MREN_INTSTAT) 

    /*******************************************************************************
    * Function Name: MREN_ClearInterrupt
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
    uint8 MREN_ClearInterrupt(void) 
    {
        return (MREN_INTSTAT & MREN_MASK) >> MREN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
