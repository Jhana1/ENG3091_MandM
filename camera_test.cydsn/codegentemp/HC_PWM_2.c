/*******************************************************************************
* File Name: HC_PWM_2.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "HC_PWM_2.h"

/* Error message for removed <resource> through optimization */
#ifdef HC_PWM_2_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* HC_PWM_2_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 HC_PWM_2_initVar = 0u;


/*******************************************************************************
* Function Name: HC_PWM_2_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HC_PWM_2_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void HC_PWM_2_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(HC_PWM_2_initVar == 0u)
    {
        HC_PWM_2_Init();
        HC_PWM_2_initVar = 1u;
    }
    HC_PWM_2_Enable();

}


/*******************************************************************************
* Function Name: HC_PWM_2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  HC_PWM_2_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void HC_PWM_2_Init(void) 
{
    #if (HC_PWM_2_UsingFixedFunction || HC_PWM_2_UseControl)
        uint8 ctrl;
    #endif /* (HC_PWM_2_UsingFixedFunction || HC_PWM_2_UseControl) */

    #if(!HC_PWM_2_UsingFixedFunction)
        #if(HC_PWM_2_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 HC_PWM_2_interruptState;
        #endif /* (HC_PWM_2_UseStatus) */
    #endif /* (!HC_PWM_2_UsingFixedFunction) */

    #if (HC_PWM_2_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        HC_PWM_2_CONTROL |= HC_PWM_2_CFG0_MODE;
        #if (HC_PWM_2_DeadBand2_4)
            HC_PWM_2_CONTROL |= HC_PWM_2_CFG0_DB;
        #endif /* (HC_PWM_2_DeadBand2_4) */

        ctrl = HC_PWM_2_CONTROL3 & ((uint8 )(~HC_PWM_2_CTRL_CMPMODE1_MASK));
        HC_PWM_2_CONTROL3 = ctrl | HC_PWM_2_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        HC_PWM_2_RT1 &= ((uint8)(~HC_PWM_2_RT1_MASK));
        HC_PWM_2_RT1 |= HC_PWM_2_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        HC_PWM_2_RT1 &= ((uint8)(~HC_PWM_2_SYNCDSI_MASK));
        HC_PWM_2_RT1 |= HC_PWM_2_SYNCDSI_EN;

    #elif (HC_PWM_2_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = HC_PWM_2_CONTROL & ((uint8)(~HC_PWM_2_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~HC_PWM_2_CTRL_CMPMODE1_MASK));
        HC_PWM_2_CONTROL = ctrl | HC_PWM_2_DEFAULT_COMPARE2_MODE |
                                   HC_PWM_2_DEFAULT_COMPARE1_MODE;
    #endif /* (HC_PWM_2_UsingFixedFunction) */

    #if (!HC_PWM_2_UsingFixedFunction)
        #if (HC_PWM_2_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            HC_PWM_2_AUX_CONTROLDP0 |= (HC_PWM_2_AUX_CTRL_FIFO0_CLR);
        #else /* (HC_PWM_2_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            HC_PWM_2_AUX_CONTROLDP0 |= (HC_PWM_2_AUX_CTRL_FIFO0_CLR);
            HC_PWM_2_AUX_CONTROLDP1 |= (HC_PWM_2_AUX_CTRL_FIFO0_CLR);
        #endif /* (HC_PWM_2_Resolution == 8) */

        HC_PWM_2_WriteCounter(HC_PWM_2_INIT_PERIOD_VALUE);
    #endif /* (!HC_PWM_2_UsingFixedFunction) */

    HC_PWM_2_WritePeriod(HC_PWM_2_INIT_PERIOD_VALUE);

        #if (HC_PWM_2_UseOneCompareMode)
            HC_PWM_2_WriteCompare(HC_PWM_2_INIT_COMPARE_VALUE1);
        #else
            HC_PWM_2_WriteCompare1(HC_PWM_2_INIT_COMPARE_VALUE1);
            HC_PWM_2_WriteCompare2(HC_PWM_2_INIT_COMPARE_VALUE2);
        #endif /* (HC_PWM_2_UseOneCompareMode) */

        #if (HC_PWM_2_KillModeMinTime)
            HC_PWM_2_WriteKillTime(HC_PWM_2_MinimumKillTime);
        #endif /* (HC_PWM_2_KillModeMinTime) */

        #if (HC_PWM_2_DeadBandUsed)
            HC_PWM_2_WriteDeadTime(HC_PWM_2_INIT_DEAD_TIME);
        #endif /* (HC_PWM_2_DeadBandUsed) */

    #if (HC_PWM_2_UseStatus || HC_PWM_2_UsingFixedFunction)
        HC_PWM_2_SetInterruptMode(HC_PWM_2_INIT_INTERRUPTS_MODE);
    #endif /* (HC_PWM_2_UseStatus || HC_PWM_2_UsingFixedFunction) */

    #if (HC_PWM_2_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        HC_PWM_2_GLOBAL_ENABLE |= HC_PWM_2_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        HC_PWM_2_CONTROL2 |= HC_PWM_2_CTRL2_IRQ_SEL;
    #else
        #if(HC_PWM_2_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            HC_PWM_2_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            HC_PWM_2_STATUS_AUX_CTRL |= HC_PWM_2_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(HC_PWM_2_interruptState);

            /* Clear the FIFO to enable the HC_PWM_2_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            HC_PWM_2_ClearFIFO();
        #endif /* (HC_PWM_2_UseStatus) */
    #endif /* (HC_PWM_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HC_PWM_2_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void HC_PWM_2_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (HC_PWM_2_UsingFixedFunction)
        HC_PWM_2_GLOBAL_ENABLE |= HC_PWM_2_BLOCK_EN_MASK;
        HC_PWM_2_GLOBAL_STBY_ENABLE |= HC_PWM_2_BLOCK_STBY_EN_MASK;
    #endif /* (HC_PWM_2_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (HC_PWM_2_UseControl || HC_PWM_2_UsingFixedFunction)
        HC_PWM_2_CONTROL |= HC_PWM_2_CTRL_ENABLE;
    #endif /* (HC_PWM_2_UseControl || HC_PWM_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HC_PWM_2_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void HC_PWM_2_Stop(void) 
{
    #if (HC_PWM_2_UseControl || HC_PWM_2_UsingFixedFunction)
        HC_PWM_2_CONTROL &= ((uint8)(~HC_PWM_2_CTRL_ENABLE));
    #endif /* (HC_PWM_2_UseControl || HC_PWM_2_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (HC_PWM_2_UsingFixedFunction)
        HC_PWM_2_GLOBAL_ENABLE &= ((uint8)(~HC_PWM_2_BLOCK_EN_MASK));
        HC_PWM_2_GLOBAL_STBY_ENABLE &= ((uint8)(~HC_PWM_2_BLOCK_STBY_EN_MASK));
    #endif /* (HC_PWM_2_UsingFixedFunction) */
}

#if (HC_PWM_2_UseOneCompareMode)
    #if (HC_PWM_2_CompareMode1SW)


        /*******************************************************************************
        * Function Name: HC_PWM_2_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void HC_PWM_2_SetCompareMode(uint8 comparemode) 
        {
            #if(HC_PWM_2_UsingFixedFunction)

                #if(0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << HC_PWM_2_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT) */

                HC_PWM_2_CONTROL3 &= ((uint8)(~HC_PWM_2_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                HC_PWM_2_CONTROL3 |= comparemodemasked;

            #elif (HC_PWM_2_UseControl)

                #if(0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << HC_PWM_2_CTRL_CMPMODE1_SHIFT)) &
                                                HC_PWM_2_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & HC_PWM_2_CTRL_CMPMODE1_MASK;
                #endif /* (0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT) */

                #if(0 != HC_PWM_2_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << HC_PWM_2_CTRL_CMPMODE2_SHIFT)) &
                                               HC_PWM_2_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & HC_PWM_2_CTRL_CMPMODE2_MASK;
                #endif /* (0 != HC_PWM_2_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                HC_PWM_2_CONTROL &= ((uint8)(~(HC_PWM_2_CTRL_CMPMODE1_MASK |
                                            HC_PWM_2_CTRL_CMPMODE2_MASK)));
                HC_PWM_2_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (HC_PWM_2_UsingFixedFunction) */
        }
    #endif /* HC_PWM_2_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (HC_PWM_2_CompareMode1SW)


        /*******************************************************************************
        * Function Name: HC_PWM_2_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void HC_PWM_2_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << HC_PWM_2_CTRL_CMPMODE1_SHIFT)) &
                                           HC_PWM_2_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & HC_PWM_2_CTRL_CMPMODE1_MASK;
            #endif /* (0 != HC_PWM_2_CTRL_CMPMODE1_SHIFT) */

            #if (HC_PWM_2_UseControl)
                HC_PWM_2_CONTROL &= ((uint8)(~HC_PWM_2_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                HC_PWM_2_CONTROL |= comparemodemasked;
            #endif /* (HC_PWM_2_UseControl) */
        }
    #endif /* HC_PWM_2_CompareMode1SW */

#if (HC_PWM_2_CompareMode2SW)


    /*******************************************************************************
    * Function Name: HC_PWM_2_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != HC_PWM_2_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << HC_PWM_2_CTRL_CMPMODE2_SHIFT)) &
                                                 HC_PWM_2_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & HC_PWM_2_CTRL_CMPMODE2_MASK;
        #endif /* (0 != HC_PWM_2_CTRL_CMPMODE2_SHIFT) */

        #if (HC_PWM_2_UseControl)
            HC_PWM_2_CONTROL &= ((uint8)(~HC_PWM_2_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            HC_PWM_2_CONTROL |= comparemodemasked;
        #endif /* (HC_PWM_2_UseControl) */
    }
    #endif /*HC_PWM_2_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!HC_PWM_2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void HC_PWM_2_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(HC_PWM_2_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 HC_PWM_2_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(HC_PWM_2_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(HC_PWM_2_CAPTURE_LSB_PTR));
    }

    #if (HC_PWM_2_UseStatus)


        /*******************************************************************************
        * Function Name: HC_PWM_2_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void HC_PWM_2_ClearFIFO(void) 
        {
            while(0u != (HC_PWM_2_ReadStatusRegister() & HC_PWM_2_STATUS_FIFONEMPTY))
            {
                (void)HC_PWM_2_ReadCapture();
            }
        }

    #endif /* HC_PWM_2_UseStatus */

#endif /* !HC_PWM_2_UsingFixedFunction */


/*******************************************************************************
* Function Name: HC_PWM_2_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void HC_PWM_2_WritePeriod(uint16 period) 
{
    #if(HC_PWM_2_UsingFixedFunction)
        CY_SET_REG16(HC_PWM_2_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(HC_PWM_2_PERIOD_LSB_PTR, period);
    #endif /* (HC_PWM_2_UsingFixedFunction) */
}

#if (HC_PWM_2_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void HC_PWM_2_WriteCompare(uint16 compare) \
                                       
    {
        #if(HC_PWM_2_UsingFixedFunction)
            CY_SET_REG16(HC_PWM_2_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(HC_PWM_2_COMPARE1_LSB_PTR, compare);
        #endif /* (HC_PWM_2_UsingFixedFunction) */

        #if (HC_PWM_2_PWMMode == HC_PWM_2__B_PWM__DITHER)
            #if(HC_PWM_2_UsingFixedFunction)
                CY_SET_REG16(HC_PWM_2_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(HC_PWM_2_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (HC_PWM_2_UsingFixedFunction) */
        #endif /* (HC_PWM_2_PWMMode == HC_PWM_2__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_WriteCompare1(uint16 compare) \
                                        
    {
        #if(HC_PWM_2_UsingFixedFunction)
            CY_SET_REG16(HC_PWM_2_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(HC_PWM_2_COMPARE1_LSB_PTR, compare);
        #endif /* (HC_PWM_2_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_WriteCompare2(uint16 compare) \
                                        
    {
        #if(HC_PWM_2_UsingFixedFunction)
            CY_SET_REG16(HC_PWM_2_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(HC_PWM_2_COMPARE2_LSB_PTR, compare);
        #endif /* (HC_PWM_2_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (HC_PWM_2_DeadBandUsed)


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!HC_PWM_2_DeadBand2_4)
            CY_SET_REG8(HC_PWM_2_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            HC_PWM_2_DEADBAND_COUNT &= ((uint8)(~HC_PWM_2_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(HC_PWM_2_DEADBAND_COUNT_SHIFT)
                HC_PWM_2_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << HC_PWM_2_DEADBAND_COUNT_SHIFT)) &
                                                    HC_PWM_2_DEADBAND_COUNT_MASK;
            #else
                HC_PWM_2_DEADBAND_COUNT |= deadtime & HC_PWM_2_DEADBAND_COUNT_MASK;
            #endif /* (HC_PWM_2_DEADBAND_COUNT_SHIFT) */

        #endif /* (!HC_PWM_2_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 HC_PWM_2_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!HC_PWM_2_DeadBand2_4)
            return (CY_GET_REG8(HC_PWM_2_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(HC_PWM_2_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(HC_PWM_2_DEADBAND_COUNT & HC_PWM_2_DEADBAND_COUNT_MASK)) >>
                                                                           HC_PWM_2_DEADBAND_COUNT_SHIFT));
            #else
                return (HC_PWM_2_DEADBAND_COUNT & HC_PWM_2_DEADBAND_COUNT_MASK);
            #endif /* (HC_PWM_2_DEADBAND_COUNT_SHIFT) */
        #endif /* (!HC_PWM_2_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (HC_PWM_2_UseStatus || HC_PWM_2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: HC_PWM_2_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(HC_PWM_2_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 HC_PWM_2_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(HC_PWM_2_STATUS_PTR));
    }

#endif /* (HC_PWM_2_UseStatus || HC_PWM_2_UsingFixedFunction) */


#if (HC_PWM_2_UseControl)


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 HC_PWM_2_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(HC_PWM_2_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(HC_PWM_2_CONTROL_PTR, control);
    }

#endif /* (HC_PWM_2_UseControl) */


#if (!HC_PWM_2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 HC_PWM_2_ReadCapture(void) 
    {
        return (CY_GET_REG16(HC_PWM_2_CAPTURE_LSB_PTR));
    }

#endif /* (!HC_PWM_2_UsingFixedFunction) */


#if (HC_PWM_2_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 HC_PWM_2_ReadCompare(void) 
    {
        #if(HC_PWM_2_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(HC_PWM_2_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(HC_PWM_2_COMPARE1_LSB_PTR));
        #endif /* (HC_PWM_2_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 HC_PWM_2_ReadCompare1(void) 
    {
        return (CY_GET_REG16(HC_PWM_2_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 HC_PWM_2_ReadCompare2(void) 
    {
        return (CY_GET_REG16(HC_PWM_2_COMPARE2_LSB_PTR));
    }

#endif /* (HC_PWM_2_UseOneCompareMode) */


/*******************************************************************************
* Function Name: HC_PWM_2_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 HC_PWM_2_ReadPeriod(void) 
{
    #if(HC_PWM_2_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HC_PWM_2_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(HC_PWM_2_PERIOD_LSB_PTR));
    #endif /* (HC_PWM_2_UsingFixedFunction) */
}

#if ( HC_PWM_2_KillModeMinTime)


    /*******************************************************************************
    * Function Name: HC_PWM_2_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void HC_PWM_2_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(HC_PWM_2_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: HC_PWM_2_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 HC_PWM_2_ReadKillTime(void) 
    {
        return (CY_GET_REG8(HC_PWM_2_KILLMODEMINTIME_PTR));
    }

#endif /* ( HC_PWM_2_KillModeMinTime) */

/* [] END OF FILE */
