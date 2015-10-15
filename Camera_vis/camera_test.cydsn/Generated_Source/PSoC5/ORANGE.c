/*******************************************************************************
* File Name: ORANGE.c  
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
#include "ORANGE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ORANGE__PORT == 15 && ((ORANGE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ORANGE_Write
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
void ORANGE_Write(uint8 value) 
{
    uint8 staticBits = (ORANGE_DR & (uint8)(~ORANGE_MASK));
    ORANGE_DR = staticBits | ((uint8)(value << ORANGE_SHIFT) & ORANGE_MASK);
}


/*******************************************************************************
* Function Name: ORANGE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ORANGE_DM_STRONG     Strong Drive 
*  ORANGE_DM_OD_HI      Open Drain, Drives High 
*  ORANGE_DM_OD_LO      Open Drain, Drives Low 
*  ORANGE_DM_RES_UP     Resistive Pull Up 
*  ORANGE_DM_RES_DWN    Resistive Pull Down 
*  ORANGE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ORANGE_DM_DIG_HIZ    High Impedance Digital 
*  ORANGE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ORANGE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ORANGE_0, mode);
}


/*******************************************************************************
* Function Name: ORANGE_Read
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
*  Macro ORANGE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ORANGE_Read(void) 
{
    return (ORANGE_PS & ORANGE_MASK) >> ORANGE_SHIFT;
}


/*******************************************************************************
* Function Name: ORANGE_ReadDataReg
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
uint8 ORANGE_ReadDataReg(void) 
{
    return (ORANGE_DR & ORANGE_MASK) >> ORANGE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ORANGE_INTSTAT) 

    /*******************************************************************************
    * Function Name: ORANGE_ClearInterrupt
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
    uint8 ORANGE_ClearInterrupt(void) 
    {
        return (ORANGE_INTSTAT & ORANGE_MASK) >> ORANGE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
