/*******************************************************************************
* File Name: MRIN1.c  
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
#include "MRIN1.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 MRIN1__PORT == 15 && ((MRIN1__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: MRIN1_Write
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
void MRIN1_Write(uint8 value) 
{
    uint8 staticBits = (MRIN1_DR & (uint8)(~MRIN1_MASK));
    MRIN1_DR = staticBits | ((uint8)(value << MRIN1_SHIFT) & MRIN1_MASK);
}


/*******************************************************************************
* Function Name: MRIN1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MRIN1_DM_STRONG     Strong Drive 
*  MRIN1_DM_OD_HI      Open Drain, Drives High 
*  MRIN1_DM_OD_LO      Open Drain, Drives Low 
*  MRIN1_DM_RES_UP     Resistive Pull Up 
*  MRIN1_DM_RES_DWN    Resistive Pull Down 
*  MRIN1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MRIN1_DM_DIG_HIZ    High Impedance Digital 
*  MRIN1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MRIN1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MRIN1_0, mode);
}


/*******************************************************************************
* Function Name: MRIN1_Read
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
*  Macro MRIN1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MRIN1_Read(void) 
{
    return (MRIN1_PS & MRIN1_MASK) >> MRIN1_SHIFT;
}


/*******************************************************************************
* Function Name: MRIN1_ReadDataReg
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
uint8 MRIN1_ReadDataReg(void) 
{
    return (MRIN1_DR & MRIN1_MASK) >> MRIN1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MRIN1_INTSTAT) 

    /*******************************************************************************
    * Function Name: MRIN1_ClearInterrupt
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
    uint8 MRIN1_ClearInterrupt(void) 
    {
        return (MRIN1_INTSTAT & MRIN1_MASK) >> MRIN1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
