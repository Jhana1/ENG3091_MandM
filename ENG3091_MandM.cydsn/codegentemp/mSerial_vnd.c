/*******************************************************************************
* File Name: mSerial_vnd.c
* Version 2.80
*
* Description:
*  USB vendor request handler.
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
#include "mSerial_pvt.h"

#if(mSerial_EXTERN_VND == mSerial_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: mSerial_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
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
uint8 mSerial_HandleVendorRqst(void) 
{
    uint8 requestHandled = mSerial_FALSE;

    if ((CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_DIR_MASK) == mSerial_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(mSerial_bRequest))
        {
            case mSerial_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(mSerial_ENABLE_MSOS_STRING)
                    mSerial_currentTD.pData = (volatile uint8 *)&mSerial_MSOS_CONFIGURATION_DESCR[0u];
                    mSerial_currentTD.count = mSerial_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  = mSerial_InitControlRead();
                #endif /*  mSerial_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* mSerial_EXTERN_VND */


/* [] END OF FILE */
