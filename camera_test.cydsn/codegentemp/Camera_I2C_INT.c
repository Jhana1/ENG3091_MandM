/*******************************************************************************
* File Name: Camera_I2C_INT.c
* Version 3.50
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for the I2C component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Camera_I2C_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here.
********************************************************************************/
/* `#START Camera_I2C_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: Camera_I2C_ISR
********************************************************************************
*
* Summary:
*  The handler for the I2C interrupt. The slave and master operations are
*  handled here.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
CY_ISR(Camera_I2C_ISR)
{
#if (Camera_I2C_MODE_SLAVE_ENABLED)
   uint8  tmp8;
#endif  /* (Camera_I2C_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;

#if(Camera_I2C_TIMEOUT_FF_ENABLED)
    if(0u != Camera_I2C_TimeoutGetStatus())
    {
        Camera_I2C_TimeoutReset();
        Camera_I2C_state = Camera_I2C_SM_EXIT_IDLE;
        /* Camera_I2C_CSR_REG should be cleared after reset */
    }
#endif /* (Camera_I2C_TIMEOUT_FF_ENABLED) */


    tmpCsr = Camera_I2C_CSR_REG;      /* Make copy as interrupts clear */

#if(Camera_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED)
    if(Camera_I2C_CHECK_START_GEN(Camera_I2C_MCSR_REG))
    {
        Camera_I2C_CLEAR_START_GEN;

        /* Set transfer complete and error flags */
        Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_ERR_XFER |
                                        Camera_I2C_GET_MSTAT_CMPLT);

        /* Slave was addressed */
        Camera_I2C_state = Camera_I2C_SM_SLAVE;
    }
#endif /* (Camera_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED) */


#if(Camera_I2C_MODE_MULTI_MASTER_ENABLED)
    if(Camera_I2C_CHECK_LOST_ARB(tmpCsr))
    {
        /* Set errors */
        Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_ERR_XFER     |
                                        Camera_I2C_MSTAT_ERR_ARB_LOST |
                                        Camera_I2C_GET_MSTAT_CMPLT);

        Camera_I2C_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

        #if(Camera_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED)
            if(Camera_I2C_CHECK_ADDRESS_STS(tmpCsr))
            {
                /* Slave was addressed */
                Camera_I2C_state = Camera_I2C_SM_SLAVE;
            }
            else
            {
                Camera_I2C_BUS_RELEASE;

                Camera_I2C_state = Camera_I2C_SM_EXIT_IDLE;
            }
        #else
            Camera_I2C_BUS_RELEASE;

            Camera_I2C_state = Camera_I2C_SM_EXIT_IDLE;

        #endif /* (Camera_I2C_MODE_MULTI_MASTER_SLAVE_ENABLED) */
    }
#endif /* (Camera_I2C_MODE_MULTI_MASTER_ENABLED) */

    /* Check for master operation mode */
    if(Camera_I2C_CHECK_SM_MASTER)
    {
    #if(Camera_I2C_MODE_MASTER_ENABLED)
        if(Camera_I2C_CHECK_BYTE_COMPLETE(tmpCsr))
        {
            switch (Camera_I2C_state)
            {
            case Camera_I2C_SM_MSTR_WR_ADDR:  /* After address is sent, write data */
            case Camera_I2C_SM_MSTR_RD_ADDR:  /* After address is sent, read data */

                tmpCsr &= ((uint8) ~Camera_I2C_CSR_STOP_STATUS); /* Clear Stop bit history on address phase */

                if(Camera_I2C_CHECK_ADDR_ACK(tmpCsr))
                {
                    /* Setup for transmit or receive of data */
                    if(Camera_I2C_state == Camera_I2C_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                    {
                        /* Check if at least one byte to transfer */
                        if(Camera_I2C_mstrWrBufSize > 0u)
                        {
                            /* Load the 1st data byte */
                            Camera_I2C_DATA_REG = Camera_I2C_mstrWrBufPtr[0u];
                            Camera_I2C_TRANSMIT_DATA;
                            Camera_I2C_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                            /* Set transmit state until done */
                            Camera_I2C_state = Camera_I2C_SM_MSTR_WR_DATA;
                        }
                        /* End of buffer: complete writing */
                        else if(Camera_I2C_CHECK_NO_STOP(Camera_I2C_mstrControl))
                        {
                            /* Set write complete and master halted */
                            Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_XFER_HALT |
                                                            Camera_I2C_MSTAT_WR_CMPLT);

                            Camera_I2C_state = Camera_I2C_SM_MSTR_HALT; /* Expect ReStart */
                            Camera_I2C_DisableInt();
                        }
                        else
                        {
                            Camera_I2C_ENABLE_INT_ON_STOP; /* Enable interrupt on Stop, to catch it */
                            Camera_I2C_GENERATE_STOP;
                        }
                    }
                    else  /* Master receive data */
                    {
                        Camera_I2C_READY_TO_READ; /* Release bus to read data */

                        Camera_I2C_state  = Camera_I2C_SM_MSTR_RD_DATA;
                    }
                }
                /* Address is NACKed */
                else if(Camera_I2C_CHECK_ADDR_NAK(tmpCsr))
                {
                    /* Set Address NAK error */
                    Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_ERR_XFER |
                                                    Camera_I2C_MSTAT_ERR_ADDR_NAK);

                    if(Camera_I2C_CHECK_NO_STOP(Camera_I2C_mstrControl))
                    {
                        Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_XFER_HALT |
                                                        Camera_I2C_GET_MSTAT_CMPLT);

                        Camera_I2C_state = Camera_I2C_SM_MSTR_HALT; /* Expect RESTART */
                        Camera_I2C_DisableInt();
                    }
                    else  /* Do normal Stop */
                    {
                        Camera_I2C_ENABLE_INT_ON_STOP; /* Enable interrupt on Stop, to catch it */
                        Camera_I2C_GENERATE_STOP;
                    }
                }
                else
                {
                    /* Address phase is not set for some reason: error */
                    #if(Camera_I2C_TIMEOUT_ENABLED)
                        /* Exit interrupt to take chance for timeout timer to handle this case */
                        Camera_I2C_DisableInt();
                        Camera_I2C_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (Camera_I2C_TIMEOUT_ENABLED) */
                }
                break;

            case Camera_I2C_SM_MSTR_WR_DATA:

                if(Camera_I2C_CHECK_DATA_ACK(tmpCsr))
                {
                    /* Check if end of buffer */
                    if(Camera_I2C_mstrWrBufIndex  < Camera_I2C_mstrWrBufSize)
                    {
                        Camera_I2C_DATA_REG =
                                                 Camera_I2C_mstrWrBufPtr[Camera_I2C_mstrWrBufIndex];
                        Camera_I2C_TRANSMIT_DATA;
                        Camera_I2C_mstrWrBufIndex++;
                    }
                    /* End of buffer: complete writing */
                    else if(Camera_I2C_CHECK_NO_STOP(Camera_I2C_mstrControl))
                    {
                        /* Set write complete and master halted */
                        Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_XFER_HALT |
                                                        Camera_I2C_MSTAT_WR_CMPLT);

                        Camera_I2C_state = Camera_I2C_SM_MSTR_HALT;    /* Expect restart */
                        Camera_I2C_DisableInt();
                    }
                    else  /* Do normal Stop */
                    {
                        Camera_I2C_ENABLE_INT_ON_STOP;    /* Enable interrupt on Stop, to catch it */
                        Camera_I2C_GENERATE_STOP;
                    }
                }
                /* Last byte NAKed: end writing */
                else if(Camera_I2C_CHECK_NO_STOP(Camera_I2C_mstrControl))
                {
                    /* Set write complete, short transfer and master halted */
                    Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_ERR_XFER       |
                                                    Camera_I2C_MSTAT_ERR_SHORT_XFER |
                                                    Camera_I2C_MSTAT_XFER_HALT      |
                                                    Camera_I2C_MSTAT_WR_CMPLT);

                    Camera_I2C_state = Camera_I2C_SM_MSTR_HALT;    /* Expect ReStart */
                    Camera_I2C_DisableInt();
                }
                else  /* Do normal Stop */
                {
                    Camera_I2C_ENABLE_INT_ON_STOP;    /* Enable interrupt on Stop, to catch it */
                    Camera_I2C_GENERATE_STOP;

                    /* Set short transfer and error flag */
                    Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_ERR_SHORT_XFER |
                                                    Camera_I2C_MSTAT_ERR_XFER);
                }

                break;

            case Camera_I2C_SM_MSTR_RD_DATA:

                Camera_I2C_mstrRdBufPtr[Camera_I2C_mstrRdBufIndex] = Camera_I2C_DATA_REG;
                Camera_I2C_mstrRdBufIndex++;

                /* Check if end of buffer */
                if(Camera_I2C_mstrRdBufIndex < Camera_I2C_mstrRdBufSize)
                {
                    Camera_I2C_ACK_AND_RECEIVE;       /* ACK and receive byte */
                }
                /* End of buffer: complete reading */
                else if(Camera_I2C_CHECK_NO_STOP(Camera_I2C_mstrControl))
                {
                    /* Set read complete and master halted */
                    Camera_I2C_mstrStatus |= (Camera_I2C_MSTAT_XFER_HALT |
                                                    Camera_I2C_MSTAT_RD_CMPLT);

                    Camera_I2C_state = Camera_I2C_SM_MSTR_HALT;    /* Expect ReStart */
                    Camera_I2C_DisableInt();
                }
                else
                {
                    Camera_I2C_ENABLE_INT_ON_STOP;
                    Camera_I2C_NAK_AND_RECEIVE;       /* NACK and TRY to generate Stop */
                }
                break;

            default: /* This is an invalid state and should not occur */

            #if(Camera_I2C_TIMEOUT_ENABLED)
                /* Exit interrupt to take chance for timeout timer to handles this case */
                Camera_I2C_DisableInt();
                Camera_I2C_ClearPendingInt();
            #else
                /* Block execution flow: unexpected condition */
                CYASSERT(0u != 0u);
            #endif /* (Camera_I2C_TIMEOUT_ENABLED) */

                break;
            }
        }

        /* Catches Stop: end of transaction */
        if(Camera_I2C_CHECK_STOP_STS(tmpCsr))
        {
            Camera_I2C_mstrStatus |= Camera_I2C_GET_MSTAT_CMPLT;

            Camera_I2C_DISABLE_INT_ON_STOP;
            Camera_I2C_state = Camera_I2C_SM_IDLE;
        }
    #endif /* (Camera_I2C_MODE_MASTER_ENABLED) */
    }
    else if(Camera_I2C_CHECK_SM_SLAVE)
    {
    #if(Camera_I2C_MODE_SLAVE_ENABLED)

        if((Camera_I2C_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
           (Camera_I2C_CHECK_BYTE_COMPLETE(tmpCsr) && Camera_I2C_CHECK_ADDRESS_STS(tmpCsr)))
        {
            /* Catch end of master write transaction: use interrupt on Stop */
            /* The Stop bit history on address phase does not have correct state */
            if(Camera_I2C_SM_SL_WR_DATA == Camera_I2C_state)
            {
                Camera_I2C_DISABLE_INT_ON_STOP;

                Camera_I2C_slStatus &= ((uint8) ~Camera_I2C_SSTAT_WR_BUSY);
                Camera_I2C_slStatus |= ((uint8)  Camera_I2C_SSTAT_WR_CMPLT);

                Camera_I2C_state = Camera_I2C_SM_IDLE;
            }
        }

        if(Camera_I2C_CHECK_BYTE_COMPLETE(tmpCsr))
        {
            /* The address only issued after Start or ReStart: so check the address
               to catch these events:
                FF : sets an address phase with a byte_complete interrupt trigger.
                UDB: sets an address phase immediately after Start or ReStart. */
            if(Camera_I2C_CHECK_ADDRESS_STS(tmpCsr))
            {
            /* Check for software address detection */
            #if(Camera_I2C_SW_ADRR_DECODE)
                tmp8 = Camera_I2C_GET_SLAVE_ADDR(Camera_I2C_DATA_REG);

                if(tmp8 == Camera_I2C_slAddress)   /* Check for address match */
                {
                    if(0u != (Camera_I2C_DATA_REG & Camera_I2C_READ_FLAG))
                    {
                        /* Place code to prepare read buffer here                  */
                        /* `#START Camera_I2C_SW_PREPARE_READ_BUF_interrupt` */

                        /* `#END` */

                        /* Prepare next operation to read, get data and place in data register */
                        if(Camera_I2C_slRdBufIndex < Camera_I2C_slRdBufSize)
                        {
                            /* Load first data byte from array */
                            Camera_I2C_DATA_REG = Camera_I2C_slRdBufPtr[Camera_I2C_slRdBufIndex];
                            Camera_I2C_ACK_AND_TRANSMIT;
                            Camera_I2C_slRdBufIndex++;

                            Camera_I2C_slStatus |= Camera_I2C_SSTAT_RD_BUSY;
                        }
                        else    /* Overflow: provide 0xFF on bus */
                        {
                            Camera_I2C_DATA_REG = Camera_I2C_OVERFLOW_RETURN;
                            Camera_I2C_ACK_AND_TRANSMIT;

                            Camera_I2C_slStatus  |= (Camera_I2C_SSTAT_RD_BUSY |
                                                           Camera_I2C_SSTAT_RD_ERR_OVFL);
                        }

                        Camera_I2C_state = Camera_I2C_SM_SL_RD_DATA;
                    }
                    else  /* Write transaction: receive 1st byte */
                    {
                        Camera_I2C_ACK_AND_RECEIVE;
                        Camera_I2C_state = Camera_I2C_SM_SL_WR_DATA;

                        Camera_I2C_slStatus |= Camera_I2C_SSTAT_WR_BUSY;
                        Camera_I2C_ENABLE_INT_ON_STOP;
                    }
                }
                else
                {
                    /*     Place code to compare for additional address here    */
                    /* `#START Camera_I2C_SW_ADDR_COMPARE_interruptStart` */

                    /* `#END` */

                    Camera_I2C_NAK_AND_RECEIVE;   /* NACK address */

                    /* Place code to end of condition for NACK generation here */
                    /* `#START Camera_I2C_SW_ADDR_COMPARE_interruptEnd`  */

                    /* `#END` */
                }

            #else /* (Camera_I2C_HW_ADRR_DECODE) */

                if(0u != (Camera_I2C_DATA_REG & Camera_I2C_READ_FLAG))
                {
                    /* Place code to prepare read buffer here                  */
                    /* `#START Camera_I2C_HW_PREPARE_READ_BUF_interrupt` */

                    /* `#END` */

                    /* Prepare next operation to read, get data and place in data register */
                    if(Camera_I2C_slRdBufIndex < Camera_I2C_slRdBufSize)
                    {
                        /* Load first data byte from array */
                        Camera_I2C_DATA_REG = Camera_I2C_slRdBufPtr[Camera_I2C_slRdBufIndex];
                        Camera_I2C_ACK_AND_TRANSMIT;
                        Camera_I2C_slRdBufIndex++;

                        Camera_I2C_slStatus |= Camera_I2C_SSTAT_RD_BUSY;
                    }
                    else    /* Overflow: provide 0xFF on bus */
                    {
                        Camera_I2C_DATA_REG = Camera_I2C_OVERFLOW_RETURN;
                        Camera_I2C_ACK_AND_TRANSMIT;

                        Camera_I2C_slStatus  |= (Camera_I2C_SSTAT_RD_BUSY |
                                                       Camera_I2C_SSTAT_RD_ERR_OVFL);
                    }

                    Camera_I2C_state = Camera_I2C_SM_SL_RD_DATA;
                }
                else  /* Write transaction: receive 1st byte */
                {
                    Camera_I2C_ACK_AND_RECEIVE;
                    Camera_I2C_state = Camera_I2C_SM_SL_WR_DATA;

                    Camera_I2C_slStatus |= Camera_I2C_SSTAT_WR_BUSY;
                    Camera_I2C_ENABLE_INT_ON_STOP;
                }

            #endif /* (Camera_I2C_SW_ADRR_DECODE) */
            }
            /* Data states */
            /* Data master writes into slave */
            else if(Camera_I2C_state == Camera_I2C_SM_SL_WR_DATA)
            {
                if(Camera_I2C_slWrBufIndex < Camera_I2C_slWrBufSize)
                {
                    tmp8 = Camera_I2C_DATA_REG;
                    Camera_I2C_ACK_AND_RECEIVE;
                    Camera_I2C_slWrBufPtr[Camera_I2C_slWrBufIndex] = tmp8;
                    Camera_I2C_slWrBufIndex++;
                }
                else  /* of array: complete write, send NACK */
                {
                    Camera_I2C_NAK_AND_RECEIVE;

                    Camera_I2C_slStatus |= Camera_I2C_SSTAT_WR_ERR_OVFL;
                }
            }
            /* Data master reads from slave */
            else if(Camera_I2C_state == Camera_I2C_SM_SL_RD_DATA)
            {
                if(Camera_I2C_CHECK_DATA_ACK(tmpCsr))
                {
                    if(Camera_I2C_slRdBufIndex < Camera_I2C_slRdBufSize)
                    {
                         /* Get data from array */
                        Camera_I2C_DATA_REG = Camera_I2C_slRdBufPtr[Camera_I2C_slRdBufIndex];
                        Camera_I2C_TRANSMIT_DATA;
                        Camera_I2C_slRdBufIndex++;
                    }
                    else   /* Overflow: provide 0xFF on bus */
                    {
                        Camera_I2C_DATA_REG = Camera_I2C_OVERFLOW_RETURN;
                        Camera_I2C_TRANSMIT_DATA;

                        Camera_I2C_slStatus |= Camera_I2C_SSTAT_RD_ERR_OVFL;
                    }
                }
                else  /* Last byte was NACKed: read complete */
                {
                    /* Only NACK appears on bus */
                    Camera_I2C_DATA_REG = Camera_I2C_OVERFLOW_RETURN;
                    Camera_I2C_NAK_AND_TRANSMIT;

                    Camera_I2C_slStatus &= ((uint8) ~Camera_I2C_SSTAT_RD_BUSY);
                    Camera_I2C_slStatus |= ((uint8)  Camera_I2C_SSTAT_RD_CMPLT);

                    Camera_I2C_state = Camera_I2C_SM_IDLE;
                }
            }
            else
            {
            #if(Camera_I2C_TIMEOUT_ENABLED)
                /* Exit interrupt to take chance for timeout timer to handle this case */
                Camera_I2C_DisableInt();
                Camera_I2C_ClearPendingInt();
            #else
                /* Block execution flow: unexpected condition */
                CYASSERT(0u != 0u);
            #endif /* (Camera_I2C_TIMEOUT_ENABLED) */
            }
        }
    #endif /* (Camera_I2C_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        Camera_I2C_state = Camera_I2C_SM_IDLE;
    }
}


#if ((Camera_I2C_FF_IMPLEMENTED) && (Camera_I2C_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: Camera_I2C_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  The interrupt handler to trigger after a wakeup.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(Camera_I2C_WAKEUP_ISR)
    {
         /* Set flag to notify that matched address is received */
        Camera_I2C_wakeupSource = 1u;

        /* SCL is stretched until the I2C_Wake() is called */
    }
#endif /* ((Camera_I2C_FF_IMPLEMENTED) && (Camera_I2C_WAKEUP_ENABLED)) */


/* [] END OF FILE */
