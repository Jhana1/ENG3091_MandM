/*******************************************************************************
* File Name: mSerial_Dp.c  
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
#include "mSerial_Dp.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 mSerial_Dp__PORT == 15 && ((mSerial_Dp__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: mSerial_Dp_Write
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
void mSerial_Dp_Write(uint8 value) 
{
    uint8 staticBits = (mSerial_Dp_DR & (uint8)(~mSerial_Dp_MASK));
    mSerial_Dp_DR = staticBits | ((uint8)(value << mSerial_Dp_SHIFT) & mSerial_Dp_MASK);
}


/*******************************************************************************
* Function Name: mSerial_Dp_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  mSerial_Dp_DM_STRONG     Strong Drive 
*  mSerial_Dp_DM_OD_HI      Open Drain, Drives High 
*  mSerial_Dp_DM_OD_LO      Open Drain, Drives Low 
*  mSerial_Dp_DM_RES_UP     Resistive Pull Up 
*  mSerial_Dp_DM_RES_DWN    Resistive Pull Down 
*  mSerial_Dp_DM_RES_UPDWN  Resistive Pull Up/Down 
*  mSerial_Dp_DM_DIG_HIZ    High Impedance Digital 
*  mSerial_Dp_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void mSerial_Dp_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(mSerial_Dp_0, mode);
}


/*******************************************************************************
* Function Name: mSerial_Dp_Read
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
*  Macro mSerial_Dp_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 mSerial_Dp_Read(void) 
{
    return (mSerial_Dp_PS & mSerial_Dp_MASK) >> mSerial_Dp_SHIFT;
}


/*******************************************************************************
* Function Name: mSerial_Dp_ReadDataReg
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
uint8 mSerial_Dp_ReadDataReg(void) 
{
    return (mSerial_Dp_DR & mSerial_Dp_MASK) >> mSerial_Dp_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(mSerial_Dp_INTSTAT) 

    /*******************************************************************************
    * Function Name: mSerial_Dp_ClearInterrupt
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
    uint8 mSerial_Dp_ClearInterrupt(void) 
    {
        return (mSerial_Dp_INTSTAT & mSerial_Dp_MASK) >> mSerial_Dp_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
