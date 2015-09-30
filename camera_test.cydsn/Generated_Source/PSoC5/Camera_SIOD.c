/*******************************************************************************
* File Name: Camera_SIOD.c  
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
#include "Camera_SIOD.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Camera_SIOD__PORT == 15 && ((Camera_SIOD__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Camera_SIOD_Write
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
void Camera_SIOD_Write(uint8 value) 
{
    uint8 staticBits = (Camera_SIOD_DR & (uint8)(~Camera_SIOD_MASK));
    Camera_SIOD_DR = staticBits | ((uint8)(value << Camera_SIOD_SHIFT) & Camera_SIOD_MASK);
}


/*******************************************************************************
* Function Name: Camera_SIOD_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Camera_SIOD_DM_STRONG     Strong Drive 
*  Camera_SIOD_DM_OD_HI      Open Drain, Drives High 
*  Camera_SIOD_DM_OD_LO      Open Drain, Drives Low 
*  Camera_SIOD_DM_RES_UP     Resistive Pull Up 
*  Camera_SIOD_DM_RES_DWN    Resistive Pull Down 
*  Camera_SIOD_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Camera_SIOD_DM_DIG_HIZ    High Impedance Digital 
*  Camera_SIOD_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Camera_SIOD_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Camera_SIOD_0, mode);
}


/*******************************************************************************
* Function Name: Camera_SIOD_Read
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
*  Macro Camera_SIOD_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Camera_SIOD_Read(void) 
{
    return (Camera_SIOD_PS & Camera_SIOD_MASK) >> Camera_SIOD_SHIFT;
}


/*******************************************************************************
* Function Name: Camera_SIOD_ReadDataReg
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
uint8 Camera_SIOD_ReadDataReg(void) 
{
    return (Camera_SIOD_DR & Camera_SIOD_MASK) >> Camera_SIOD_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Camera_SIOD_INTSTAT) 

    /*******************************************************************************
    * Function Name: Camera_SIOD_ClearInterrupt
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
    uint8 Camera_SIOD_ClearInterrupt(void) 
    {
        return (Camera_SIOD_INTSTAT & Camera_SIOD_MASK) >> Camera_SIOD_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
