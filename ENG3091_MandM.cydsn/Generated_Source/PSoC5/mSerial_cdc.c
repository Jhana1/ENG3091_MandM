/*******************************************************************************
* File Name: mSerial_cdc.c
* Version 2.80
*
* Description:
*  USB CDC class request handler.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "mSerial.h"

#if defined(mSerial_ENABLE_CDC_CLASS)

#include "mSerial_cdc.h"
#include "mSerial_pvt.h"


/***************************************
*    CDC Variables
***************************************/

volatile uint8 mSerial_lineCoding[mSerial_LINE_CODING_SIZE] =
{
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
};
volatile uint8 mSerial_lineChanged;
volatile uint16 mSerial_lineControlBitmap;
volatile uint8 mSerial_cdc_data_in_ep;
volatile uint8 mSerial_cdc_data_out_ep;


/***************************************
*     Static Function Prototypes
***************************************/
#if (mSerial_ENABLE_CDC_CLASS_API != 0u)
    static uint16 mSerial_StrLen(const char8 string[]) ;
#endif /* (mSerial_ENABLE_CDC_CLASS_API != 0u) */


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: mSerial_DispatchCDCClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches CDC class requests.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   mSerial_lineCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   mSerial_lineControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   mSerial_lineChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 mSerial_DispatchCDCClassRqst(void) 
{
    uint8 requestHandled = mSerial_FALSE;

    if ((CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_DIR_MASK) == mSerial_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(mSerial_bRequest))
        {
            case mSerial_CDC_GET_LINE_CODING:
                mSerial_currentTD.count = mSerial_LINE_CODING_SIZE;
                mSerial_currentTD.pData = mSerial_lineCoding;
                requestHandled  = mSerial_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(mSerial_bmRequestType) & mSerial_RQST_DIR_MASK) == \
                                                                            mSerial_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(mSerial_bRequest))
        {
            case mSerial_CDC_SET_LINE_CODING:
                mSerial_currentTD.count = mSerial_LINE_CODING_SIZE;
                mSerial_currentTD.pData = mSerial_lineCoding;
                mSerial_lineChanged |= mSerial_LINE_CODING_CHANGED;
                requestHandled = mSerial_InitControlWrite();
                break;

            case mSerial_CDC_SET_CONTROL_LINE_STATE:
                mSerial_lineControlBitmap = CY_GET_REG8(mSerial_wValueLo);
                mSerial_lineChanged |= mSerial_LINE_CONTROL_CHANGED;
                requestHandled = mSerial_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (mSerial_ENABLE_CDC_CLASS_API != 0u)

    /*******************************************************************************
    * Function Name: mSerial_CDC_Init
    ********************************************************************************
    *
    * Summary:
    *  This function initialize the CDC interface to be ready for the receive data
    *  from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   mSerial_lineChanged: Initialized to zero.
    *   mSerial_cdc_data_out_ep: Used as an OUT endpoint number.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void mSerial_CDC_Init(void) 
    {
        mSerial_lineChanged = 0u;
        mSerial_EnableOutEP(mSerial_cdc_data_out_ep);
    }


    /*******************************************************************************
    * Function Name: mSerial_PutData
    ********************************************************************************
    *
    * Summary:
    *  This function sends a specified number of bytes from the location specified
    *  by a pointer to the PC. The mSerial_CDCIsReady() function should be
    *  called before sending new data, to be sure that the previous data has
    *  finished sending.
    *  If the last sent packet is less than maximum packet size the USB transfer
    *  of this short packet will identify the end of the segment. If the last sent
    *  packet is exactly maximum packet size, it shall be followed by a zero-length
    *  packet (which is a short packet) to assure the end of segment is properly
    *  identified. To send zero-length packet, use mSerial_PutData() API
    *  with length parameter set to zero.
    *
    * Parameters:
    *  pData: pointer to the buffer containing data to be sent.
    *  length: Specifies the number of bytes to send from the pData
    *  buffer. Maximum length will be limited by the maximum packet
    *  size for the endpoint. Data will be lost if length is greater than Max
    *  Packet Size.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   mSerial_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void mSerial_PutData(const uint8* pData, uint16 length) 
    {
        /* Limits length to maximum packet size for the EP */
        if(length > mSerial_EP[mSerial_cdc_data_in_ep].bufferSize)
        {
            /* Caution: Data will be lost if length is greater than Max Packet Length */
            length = mSerial_EP[mSerial_cdc_data_in_ep].bufferSize;
             /* Halt CPU in debug mode */
            CYASSERT(0u != 0u);
        }
        mSerial_LoadInEP(mSerial_cdc_data_in_ep, pData, length);
    }


    /*******************************************************************************
    * Function Name: mSerial_StrLen
    ********************************************************************************
    *
    * Summary:
    *  Calculates length of a null terminated string.
    *
    * Parameters:
    *  string: pointer to the string.
    *
    * Return:
    *  Length of the string
    *
    *******************************************************************************/
    static uint16 mSerial_StrLen(const char8 string[]) 
    {
        uint16 len = 0u;

        while (string[len] != (char8)0)
        {
            len++;
        }

        return (len);
    }


    /*******************************************************************************
    * Function Name: mSerial_PutString
    ********************************************************************************
    *
    * Summary:
    *  This function sends a null terminated string to the PC. This function will
    *  block if there is not enough memory to place the whole string. It will block
    *  until the entire string has been written to the transmit buffer.
    *  The USBUART_CDCIsReady() function should be called before sending data with
    *  a new call to mSerial_PutString(), to be sure that the previous data
    *  has finished sending.
    *
    * Parameters:
    *  string: pointer to the string to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   mSerial_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void mSerial_PutString(const char8 string[]) 
    {
        uint16 strLength;
        uint16 sendLength;
        uint16 bufIndex = 0u;

        /* Get length of the null terminated string */
        strLength = mSerial_StrLen(string);
        do
        {
            /* Limits length to maximum packet size for the EP */
            sendLength = (strLength > mSerial_EP[mSerial_cdc_data_in_ep].bufferSize) ?
                          mSerial_EP[mSerial_cdc_data_in_ep].bufferSize : strLength;
             /* Enable IN transfer */
            mSerial_LoadInEP(mSerial_cdc_data_in_ep, (const uint8 *)&string[bufIndex], sendLength);
            strLength -= sendLength;

            /* If more data are present to send or full packet was sent */
            if((strLength > 0u) || (sendLength == mSerial_EP[mSerial_cdc_data_in_ep].bufferSize))
            {
                bufIndex += sendLength;
                /* Wait for the Host to read it. */
                while(mSerial_EP[mSerial_cdc_data_in_ep].apiEpState ==
                                          mSerial_IN_BUFFER_FULL)
                {
                    ;
                }
                /* If the last sent packet is exactly maximum packet size,
                *  it shall be followed by a zero-length packet to assure the
                *  end of segment is properly identified by the terminal.
                */
                if(strLength == 0u)
                {
                    mSerial_LoadInEP(mSerial_cdc_data_in_ep, NULL, 0u);
                }
            }
        }while(strLength > 0u);
    }


    /*******************************************************************************
    * Function Name: mSerial_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Writes a single character to the PC.
    *
    * Parameters:
    *  txDataByte: Character to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   mSerial_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void mSerial_PutChar(char8 txDataByte) 
    {
        uint8 dataByte;
        dataByte = (uint8)txDataByte;

        mSerial_LoadInEP(mSerial_cdc_data_in_ep, &dataByte, 1u);
    }


    /*******************************************************************************
    * Function Name: mSerial_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Sends a carriage return (0x0D) and line feed (0x0A) to the PC
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   mSerial_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void mSerial_PutCRLF(void) 
    {
        const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

        mSerial_LoadInEP(mSerial_cdc_data_in_ep, (const uint8 *)txData, 2u);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetCount
    ********************************************************************************
    *
    * Summary:
    *  This function returns the number of bytes that were received from the PC.
    *  The returned length value should be passed to mSerial_GetData() as
    *  a parameter to read all received data. If all of the received data is not
    *  read at one time by the mSerial_GetData() API, the unread data will
    *  be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of received bytes. The maximum amount of received data at
    *  a time is limited by the maximum packet size for the endpoint.
    *
    * Global variables:
    *   mSerial_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint16 mSerial_GetCount(void) 
    {
        uint16 bytesCount;

        if (mSerial_EP[mSerial_cdc_data_out_ep].apiEpState == mSerial_OUT_BUFFER_FULL)
        {
            bytesCount = mSerial_GetEPCount(mSerial_cdc_data_out_ep);
        }
        else
        {
            bytesCount = 0u;
        }

        return(bytesCount);
    }


    /*******************************************************************************
    * Function Name: mSerial_DataIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component received data or received
    *  zero-length packet. The mSerial_GetAll() or
    *  mSerial_GetData() API should be called to read data from the buffer
    *  and re-init OUT endpoint even when zero-length packet received.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the OUT packet received this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   mSerial_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint8 mSerial_DataIsReady(void) 
    {
        return(mSerial_EP[mSerial_cdc_data_out_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: mSerial_CDCIsReady
    ********************************************************************************
    *
    * Summary:
    *  This function returns a nonzero value if the component is ready to send more
    *  data to the PC; otherwise, it returns zero. The function should be called
    *  before sending new data when using any of the following APIs:
    *  mSerial_PutData(),mSerial_PutString(),
    *  mSerial_PutChar or mSerial_PutCRLF(),
    *  to be sure that the previous data has finished sending.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the buffer can accept new data, this function returns a nonzero value.
    *  Otherwise, it returns zero.
    *
    * Global variables:
    *   mSerial_cdc_data_in_ep: CDC IN endpoint number used.
    *
    *******************************************************************************/
    uint8 mSerial_CDCIsReady(void) 
    {
        return(mSerial_EP[mSerial_cdc_data_in_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetData
    ********************************************************************************
    *
    * Summary:
    *  This function gets a specified number of bytes from the input buffer and
    *  places them in a data array specified by the passed pointer.
    *  The mSerial_DataIsReady() API should be called first, to be sure
    *  that data is received from the host. If all received data will not be read at
    *  once, the unread data will be lost. The mSerial_GetData() API should
    *  be called to get the number of bytes that were received.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *  Length: Number of bytes to read into the data array from the RX buffer.
    *          Maximum length is limited by the the number of received bytes.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   mSerial_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 mSerial_GetData(uint8* pData, uint16 length) 
    {
        return(mSerial_ReadOutEP(mSerial_cdc_data_out_ep, pData, length));
    }


    /*******************************************************************************
    * Function Name: mSerial_GetAll
    ********************************************************************************
    *
    * Summary:
    *  Gets all bytes of received data from the input buffer and places it into a
    *  specified data array. mSerial_DataIsReady() API should be called
    *  before, to be sure that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   mSerial_cdc_data_out_ep: CDC OUT endpoint number used.
    *   mSerial_EP[].bufferSize: EP max packet size is used as a length
    *     to read all data from the EP buffer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 mSerial_GetAll(uint8* pData) 
    {
        return (mSerial_ReadOutEP(mSerial_cdc_data_out_ep, pData,
                                           mSerial_EP[mSerial_cdc_data_out_ep].bufferSize));
    }


    /*******************************************************************************
    * Function Name: mSerial_GetChar
    ********************************************************************************
    *
    * Summary:
    *  This function reads one byte of received data from the buffer. If more than
    *  one byte has been received from the host, the rest of the data will be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received one character.
    *
    * Global variables:
    *   mSerial_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 mSerial_GetChar(void) 
    {
         uint8 rxData;

        (void) mSerial_ReadOutEP(mSerial_cdc_data_out_ep, &rxData, 1u);

        return(rxData);
    }

    /*******************************************************************************
    * Function Name: mSerial_IsLineChanged
    ********************************************************************************
    *
    * Summary:
    *  This function returns clear on read status of the line. It returns not zero
    *  value when the host sends updated coding or control information to the
    *  device. The mSerial_GetDTERate(), mSerial_GetCharFormat()
    *  or mSerial_GetParityType() or mSerial_GetDataBits() API
    *  should be called to read data coding information.
    *  The mSerial_GetLineControl() API should be called to read line
    *  control information.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE requests are received, it
    *  returns a nonzero value. Otherwise, it returns zero.
    *
    * Global variables:
    *  mSerial_transferState: it is checked to be sure then OUT data
    *    phase has been complete, and data written to the lineCoding or Control
    *    Bitmap buffer.
    *  mSerial_lineChanged: used as a flag to be aware that Host has been
    *    sent request for changing Line Coding or Control Bitmap.
    *
    *******************************************************************************/
    uint8 mSerial_IsLineChanged(void) 
    {
        uint8 state = 0u;

        /* transferState is checked to be sure then OUT data phase has been complete */
        if(mSerial_transferState == mSerial_TRANS_STATE_IDLE)
        {
            if(mSerial_lineChanged != 0u)
            {
                state = mSerial_lineChanged;
                mSerial_lineChanged = 0u;
            }
        }

        return(state);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetDTERate
    ********************************************************************************
    *
    * Summary:
    *  Returns the data terminal rate set for this port in bits per second.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a uint32 value of the data rate in bits per second.
    *
    * Global variables:
    *  mSerial_lineCoding: First four bytes converted to uint32
    *    depend on compiler, and returned as a data rate.
    *
    *******************************************************************************/
    uint32 mSerial_GetDTERate(void) 
    {
        uint32 rate;

        rate = mSerial_lineCoding[mSerial_LINE_CODING_RATE + 3u];
        rate = (rate << 8u) | mSerial_lineCoding[mSerial_LINE_CODING_RATE + 2u];
        rate = (rate << 8u) | mSerial_lineCoding[mSerial_LINE_CODING_RATE + 1u];
        rate = (rate << 8u) | mSerial_lineCoding[mSerial_LINE_CODING_RATE];

        return(rate);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetCharFormat
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of stop bits.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of stop bits.
    *
    * Global variables:
    *  mSerial_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 mSerial_GetCharFormat(void) 
    {
        return(mSerial_lineCoding[mSerial_LINE_CODING_STOP_BITS]);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetParityType
    ********************************************************************************
    *
    * Summary:
    *  Returns the parity type for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the parity type.
    *
    * Global variables:
    *  mSerial_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 mSerial_GetParityType(void) 
    {
        return(mSerial_lineCoding[mSerial_LINE_CODING_PARITY]);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of data bits for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of data bits.
    *  The number of data bits can be 5, 6, 7, 8 or 16.
    *
    * Global variables:
    *  mSerial_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 mSerial_GetDataBits(void) 
    {
        return(mSerial_lineCoding[mSerial_LINE_CODING_DATA_BITS]);
    }


    /*******************************************************************************
    * Function Name: mSerial_GetLineControl
    ********************************************************************************
    *
    * Summary:
    *  Returns Line control bitmap.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns Line control bitmap.
    *
    * Global variables:
    *  mSerial_lineControlBitmap: used to get a parameter.
    *
    *******************************************************************************/
    uint16 mSerial_GetLineControl(void) 
    {
        return(mSerial_lineControlBitmap);
    }

#endif  /*  mSerial_ENABLE_CDC_CLASS_API*/


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  mSerial_ENABLE_CDC_CLASS*/


/* [] END OF FILE */
