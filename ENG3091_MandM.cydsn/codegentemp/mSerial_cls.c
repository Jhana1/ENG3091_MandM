/*******************************************************************************
* File Name: mSerial_cls.c
* Version 2.80
*
* Description:
*  USB Class request handler.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "mSerial.h"

#if(mSerial_EXTERN_CLS == mSerial_FALSE)

#include "mSerial_pvt.h"


/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: mSerial_DispatchClassRqst
********************************************************************************
* Summary:
*  This routine dispatches class specific requests depend on interface class.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_DispatchClassRqst(void) 
{
    uint8 requestHandled = mSerial_FALSE;
    uint8 interfaceNumber = 0u;

    switch(CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_RCPT_MASK)
    {
        case mSerial_RQST_RCPT_IFC:        /* Class-specific request directed to an interface */
            interfaceNumber = CY_GET_REG8(mSerial_wIndexLo); /* wIndexLo contain Interface number */
            break;
        case mSerial_RQST_RCPT_EP:         /* Class-specific request directed to the endpoint */
            /* Find related interface to the endpoint, wIndexLo contain EP number */
            interfaceNumber = mSerial_EP[CY_GET_REG8(mSerial_wIndexLo) &
                              mSerial_DIR_UNUSED].interface;
            break;
        default:    /* RequestHandled is initialized as FALSE by default */
            break;
    }
    /* Handle Class request depend on interface type */
    switch(mSerial_interfaceClass[interfaceNumber])
    {
        case mSerial_CLASS_HID:
            #if defined(mSerial_ENABLE_HID_CLASS)
                requestHandled = mSerial_DispatchHIDClassRqst();
            #endif /* mSerial_ENABLE_HID_CLASS */
            break;
        case mSerial_CLASS_AUDIO:
            #if defined(mSerial_ENABLE_AUDIO_CLASS)
                requestHandled = mSerial_DispatchAUDIOClassRqst();
            #endif /* mSerial_CLASS_AUDIO */
            break;
        case mSerial_CLASS_CDC:
            #if defined(mSerial_ENABLE_CDC_CLASS)
                requestHandled = mSerial_DispatchCDCClassRqst();
            #endif /* mSerial_ENABLE_CDC_CLASS */
            break;
        default:    /* requestHandled is initialized as FALSE by default */
            break;
    }

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* mSerial_EXTERN_CLS */


/* [] END OF FILE */
