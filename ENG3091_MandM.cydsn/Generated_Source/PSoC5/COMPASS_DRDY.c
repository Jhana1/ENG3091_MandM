/*******************************************************************************
* File Name: COMPASS_DRDY.c  
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
#include "COMPASS_DRDY.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 COMPASS_DRDY__PORT == 15 && ((COMPASS_DRDY__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: COMPASS_DRDY_Write
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
void COMPASS_DRDY_Write(uint8 value) 
{
    uint8 staticBits = (COMPASS_DRDY_DR & (uint8)(~COMPASS_DRDY_MASK));
    COMPASS_DRDY_DR = staticBits | ((uint8)(value << COMPASS_DRDY_SHIFT) & COMPASS_DRDY_MASK);
}


/*******************************************************************************
* Function Name: COMPASS_DRDY_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  COMPASS_DRDY_DM_STRONG     Strong Drive 
*  COMPASS_DRDY_DM_OD_HI      Open Drain, Drives High 
*  COMPASS_DRDY_DM_OD_LO      Open Drain, Drives Low 
*  COMPASS_DRDY_DM_RES_UP     Resistive Pull Up 
*  COMPASS_DRDY_DM_RES_DWN    Resistive Pull Down 
*  COMPASS_DRDY_DM_RES_UPDWN  Resistive Pull Up/Down 
*  COMPASS_DRDY_DM_DIG_HIZ    High Impedance Digital 
*  COMPASS_DRDY_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void COMPASS_DRDY_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(COMPASS_DRDY_0, mode);
}


/*******************************************************************************
* Function Name: COMPASS_DRDY_Read
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
*  Macro COMPASS_DRDY_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 COMPASS_DRDY_Read(void) 
{
    return (COMPASS_DRDY_PS & COMPASS_DRDY_MASK) >> COMPASS_DRDY_SHIFT;
}


/*******************************************************************************
* Function Name: COMPASS_DRDY_ReadDataReg
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
uint8 COMPASS_DRDY_ReadDataReg(void) 
{
    return (COMPASS_DRDY_DR & COMPASS_DRDY_MASK) >> COMPASS_DRDY_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(COMPASS_DRDY_INTSTAT) 

    /*******************************************************************************
    * Function Name: COMPASS_DRDY_ClearInterrupt
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
    uint8 COMPASS_DRDY_ClearInterrupt(void) 
    {
        return (COMPASS_DRDY_INTSTAT & COMPASS_DRDY_MASK) >> COMPASS_DRDY_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
