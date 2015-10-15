/*******************************************************************************
* File Name: MLIN2.c  
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
#include "MLIN2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 MLIN2__PORT == 15 && ((MLIN2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: MLIN2_Write
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
void MLIN2_Write(uint8 value) 
{
    uint8 staticBits = (MLIN2_DR & (uint8)(~MLIN2_MASK));
    MLIN2_DR = staticBits | ((uint8)(value << MLIN2_SHIFT) & MLIN2_MASK);
}


/*******************************************************************************
* Function Name: MLIN2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MLIN2_DM_STRONG     Strong Drive 
*  MLIN2_DM_OD_HI      Open Drain, Drives High 
*  MLIN2_DM_OD_LO      Open Drain, Drives Low 
*  MLIN2_DM_RES_UP     Resistive Pull Up 
*  MLIN2_DM_RES_DWN    Resistive Pull Down 
*  MLIN2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MLIN2_DM_DIG_HIZ    High Impedance Digital 
*  MLIN2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MLIN2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MLIN2_0, mode);
}


/*******************************************************************************
* Function Name: MLIN2_Read
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
*  Macro MLIN2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MLIN2_Read(void) 
{
    return (MLIN2_PS & MLIN2_MASK) >> MLIN2_SHIFT;
}


/*******************************************************************************
* Function Name: MLIN2_ReadDataReg
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
uint8 MLIN2_ReadDataReg(void) 
{
    return (MLIN2_DR & MLIN2_MASK) >> MLIN2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MLIN2_INTSTAT) 

    /*******************************************************************************
    * Function Name: MLIN2_ClearInterrupt
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
    uint8 MLIN2_ClearInterrupt(void) 
    {
        return (MLIN2_INTSTAT & MLIN2_MASK) >> MLIN2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
