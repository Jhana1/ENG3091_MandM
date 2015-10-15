/*******************************************************************************
* File Name: PWDN.c  
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
#include "PWDN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PWDN__PORT == 15 && ((PWDN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PWDN_Write
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
void PWDN_Write(uint8 value) 
{
    uint8 staticBits = (PWDN_DR & (uint8)(~PWDN_MASK));
    PWDN_DR = staticBits | ((uint8)(value << PWDN_SHIFT) & PWDN_MASK);
}


/*******************************************************************************
* Function Name: PWDN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PWDN_DM_STRONG     Strong Drive 
*  PWDN_DM_OD_HI      Open Drain, Drives High 
*  PWDN_DM_OD_LO      Open Drain, Drives Low 
*  PWDN_DM_RES_UP     Resistive Pull Up 
*  PWDN_DM_RES_DWN    Resistive Pull Down 
*  PWDN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PWDN_DM_DIG_HIZ    High Impedance Digital 
*  PWDN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PWDN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PWDN_0, mode);
}


/*******************************************************************************
* Function Name: PWDN_Read
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
*  Macro PWDN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWDN_Read(void) 
{
    return (PWDN_PS & PWDN_MASK) >> PWDN_SHIFT;
}


/*******************************************************************************
* Function Name: PWDN_ReadDataReg
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
uint8 PWDN_ReadDataReg(void) 
{
    return (PWDN_DR & PWDN_MASK) >> PWDN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWDN_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWDN_ClearInterrupt
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
    uint8 PWDN_ClearInterrupt(void) 
    {
        return (PWDN_INTSTAT & PWDN_MASK) >> PWDN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
