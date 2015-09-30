/*******************************************************************************
* File Name: Camera_VSYNC.c  
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
#include "Camera_VSYNC.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Camera_VSYNC__PORT == 15 && ((Camera_VSYNC__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Camera_VSYNC_Write
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
void Camera_VSYNC_Write(uint8 value) 
{
    uint8 staticBits = (Camera_VSYNC_DR & (uint8)(~Camera_VSYNC_MASK));
    Camera_VSYNC_DR = staticBits | ((uint8)(value << Camera_VSYNC_SHIFT) & Camera_VSYNC_MASK);
}


/*******************************************************************************
* Function Name: Camera_VSYNC_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Camera_VSYNC_DM_STRONG     Strong Drive 
*  Camera_VSYNC_DM_OD_HI      Open Drain, Drives High 
*  Camera_VSYNC_DM_OD_LO      Open Drain, Drives Low 
*  Camera_VSYNC_DM_RES_UP     Resistive Pull Up 
*  Camera_VSYNC_DM_RES_DWN    Resistive Pull Down 
*  Camera_VSYNC_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Camera_VSYNC_DM_DIG_HIZ    High Impedance Digital 
*  Camera_VSYNC_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Camera_VSYNC_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Camera_VSYNC_0, mode);
}


/*******************************************************************************
* Function Name: Camera_VSYNC_Read
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
*  Macro Camera_VSYNC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Camera_VSYNC_Read(void) 
{
    return (Camera_VSYNC_PS & Camera_VSYNC_MASK) >> Camera_VSYNC_SHIFT;
}


/*******************************************************************************
* Function Name: Camera_VSYNC_ReadDataReg
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
uint8 Camera_VSYNC_ReadDataReg(void) 
{
    return (Camera_VSYNC_DR & Camera_VSYNC_MASK) >> Camera_VSYNC_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Camera_VSYNC_INTSTAT) 

    /*******************************************************************************
    * Function Name: Camera_VSYNC_ClearInterrupt
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
    uint8 Camera_VSYNC_ClearInterrupt(void) 
    {
        return (Camera_VSYNC_INTSTAT & Camera_VSYNC_MASK) >> Camera_VSYNC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
