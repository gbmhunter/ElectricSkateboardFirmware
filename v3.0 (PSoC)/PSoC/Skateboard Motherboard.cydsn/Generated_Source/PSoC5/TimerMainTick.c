/*******************************************************************************
* File Name: TimerMainTick.c
* Version 2.20
*
* Description:
*  The Timer User Module consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerMainTick.h"

uint8 TimerMainTick_initVar = 0u;


/*******************************************************************************
* Function Name: TimerMainTick_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TimerMainTick_Init(void) 
{
    #if(!TimerMainTick_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerMainTick_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (TimerMainTick_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        TimerMainTick_CONTROL &= TimerMainTick_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
            TimerMainTick_CONTROL2 &= ~TimerMainTick_CTRL_MODE_MASK;
        #endif /* Clear bits in CONTROL2 only in PSoC3 ES2 or PSOC5ES1 */

        #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
            TimerMainTick_CONTROL3 &= ~TimerMainTick_CTRL_MODE_MASK;
        #endif /* CONTROL3 register exists only in PSoC3 ES3 OR PSoC5 ES2*/

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (TimerMainTick_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            TimerMainTick_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (TimerMainTick_RunModeUsed == 2)
            #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                TimerMainTick_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC3ES2 or PSoC5ES1 */

            #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                TimerMainTick_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3ES3 or PSoC5ES2 */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (TimerMainTick_UsingHWEnable != 0)
            #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
                /* Set the default Run Mode of the Timer to Continuous */
                TimerMainTick_CONTROL2 |= TimerMainTick_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC3ES2 or PSoC5ES1 */

            #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
                /* Clear and Set ROD and COD bits of CFG2 register */
                TimerMainTick_CONTROL3 &= ~TimerMainTick_CTRL_RCOD_MASK;
                TimerMainTick_CONTROL3 |= TimerMainTick_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                TimerMainTick_CONTROL3 &= ~TimerMainTick_CTRL_ENBL_MASK;
                TimerMainTick_CONTROL3 |= TimerMainTick_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                TimerMainTick_CONTROL3 |= TimerMainTick_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5ES2*/

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        TimerMainTick_RT1 &= ~TimerMainTick_RT1_MASK;
        TimerMainTick_RT1 |= TimerMainTick_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        TimerMainTick_RT1 &= ~(TimerMainTick_SYNCDSI_MASK);
        TimerMainTick_RT1 |= TimerMainTick_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        TimerMainTick_CONTROL2 |= TimerMainTick_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    TimerMainTick_WritePeriod(TimerMainTick_INIT_PERIOD);
    TimerMainTick_WriteCounter(TimerMainTick_INIT_PERIOD);

    #if (TimerMainTick_UsingHWCaptureCounter)/* Capture counter is enabled */
        TimerMainTick_CAPTURE_COUNT_CTRL |= TimerMainTick_CNTR_ENABLE;
        TimerMainTick_SetCaptureCount(TimerMainTick_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!TimerMainTick_UsingFixedFunction)
        #if (TimerMainTick_SoftwareCaptureMode)
            TimerMainTick_SetCaptureMode(TimerMainTick_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (TimerMainTick_SoftwareTriggerMode)
            if (!(TimerMainTick_CONTROL & TimerMainTick__B_TIMER__TM_SOFTWARE))
            {
                TimerMainTick_SetTriggerMode(TimerMainTick_INIT_TRIGGER_MODE);
            }
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        TimerMainTick_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        TimerMainTick_STATUS_AUX_CTRL |= TimerMainTick_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(TimerMainTick_interruptState);

        #if (TimerMainTick_EnableTriggerMode)
            TimerMainTick_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/

        #if (TimerMainTick_InterruptOnCaptureCount)
             #if (!TimerMainTick_ControlRegRemoved)
                TimerMainTick_SetInterruptCount(TimerMainTick_INIT_INT_CAPTURE_COUNT);
            #endif /* Set interrupt count in control register if control register is not removed */
        #endif /*Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        TimerMainTick_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    TimerMainTick_SetInterruptMode(TimerMainTick_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: TimerMainTick_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TimerMainTick_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (TimerMainTick_UsingFixedFunction)
        TimerMainTick_GLOBAL_ENABLE |= TimerMainTick_BLOCK_EN_MASK;
        TimerMainTick_GLOBAL_STBY_ENABLE |= TimerMainTick_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!TimerMainTick_ControlRegRemoved || TimerMainTick_UsingFixedFunction)
        TimerMainTick_CONTROL |= TimerMainTick_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: TimerMainTick_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerMainTick_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
* Reentrant
*  No
*
*******************************************************************************/
void TimerMainTick_Start(void)
{
    if(TimerMainTick_initVar == 0u)
    {
        TimerMainTick_Init();

        TimerMainTick_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    TimerMainTick_Enable();
}


/*******************************************************************************
* Function Name: TimerMainTick_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_Stop(void) 
{
    /* Disable Timer */
    #if(!TimerMainTick_ControlRegRemoved || TimerMainTick_UsingFixedFunction)
        TimerMainTick_CONTROL &= ~TimerMainTick_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (TimerMainTick_UsingFixedFunction)
        TimerMainTick_GLOBAL_ENABLE &= ~TimerMainTick_BLOCK_EN_MASK;
        TimerMainTick_GLOBAL_STBY_ENABLE &= ~TimerMainTick_BLOCK_STBY_EN_MASK;
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: TimerMainTick_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SetInterruptMode(uint8 interruptMode) 
{
    TimerMainTick_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: TimerMainTick_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    CY_GET_REG8(TimerMainTick_COUNTER_LSB_PTR);
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: TimerMainTick_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8   TimerMainTick_ReadStatusRegister(void) 
{
    return TimerMainTick_STATUS;
}


#if (!TimerMainTick_ControlRegRemoved) /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TimerMainTick_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8 TimerMainTick_ReadControlRegister(void) 
{
    return TimerMainTick_CONTROL;
}


/*******************************************************************************
* Function Name: TimerMainTick_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_WriteControlRegister(uint8 control) 
{
    TimerMainTick_CONTROL = control;
}
#endif /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TimerMainTick_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8 TimerMainTick_ReadPeriod(void) 
{
   return ( CY_GET_REG8(TimerMainTick_PERIOD_LSB_PTR) );
}


/*******************************************************************************
* Function Name: TimerMainTick_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_WritePeriod(uint8 period) 
{
    #if(TimerMainTick_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(TimerMainTick_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG8(TimerMainTick_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: TimerMainTick_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8 TimerMainTick_ReadCapture(void) 
{
   return ( CY_GET_REG8(TimerMainTick_CAPTURE_LSB_PTR) );
}


/*******************************************************************************
* Function Name: TimerMainTick_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_WriteCounter(uint8 counter) 
{
   #if(TimerMainTick_UsingFixedFunction)
        counter = counter;
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        /* uint16 counter_temp = (uint16)counter;
         * CY_SET_REG16(TimerMainTick_COUNTER_LSB_PTR, counter_temp);
         */
    #else
        CY_SET_REG8(TimerMainTick_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: TimerMainTick_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8 TimerMainTick_ReadCounter(void) 
{

    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(TimerMainTick_COUNTER_LSB_PTR);

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG8(TimerMainTick_CAPTURE_LSB_PTR));
}


#if(!TimerMainTick_UsingFixedFunction) /* UDB Specific Functions */

/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (TimerMainTick_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: TimerMainTick_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define TimerMainTick__B_TIMER__CM_NONE 0
#define TimerMainTick__B_TIMER__CM_RISINGEDGE 1
#define TimerMainTick__B_TIMER__CM_FALLINGEDGE 2
#define TimerMainTick__B_TIMER__CM_EITHEREDGE 3
#define TimerMainTick__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  TimerMainTick__B_TIMER__CM_NONE        - Set Capture mode to None
*  TimerMainTick__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  TimerMainTick__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  TimerMainTick__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = (captureMode << TimerMainTick_CTRL_CAP_MODE_SHIFT);
    captureMode &= (TimerMainTick_CTRL_CAP_MODE_MASK);

    /* Clear the Current Setting */
    TimerMainTick_CONTROL &= ~TimerMainTick_CTRL_CAP_MODE_MASK;

    /* Write The New Setting */
    TimerMainTick_CONTROL |= captureMode;
}
#endif /* Remove API if Capture Mode is not Software Controlled */

#if (TimerMainTick_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: TimerMainTick_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define TimerMainTick__B_TIMER__TM_NONE 0x00
    #define TimerMainTick__B_TIMER__TM_RISINGEDGE 0x04
    #define TimerMainTick__B_TIMER__TM_FALLINGEDGE 0x08
    #define TimerMainTick__B_TIMER__TM_EITHEREDGE 0x0C
    #define TimerMainTick__B_TIMER__TM_SOFTWARE 0x10
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= TimerMainTick_CTRL_TRIG_MODE_MASK;

    /* Clear the Current Setting */
    TimerMainTick_CONTROL &= ~TimerMainTick_CTRL_TRIG_MODE_MASK;

    /* Write The New Setting */
    TimerMainTick_CONTROL |= (triggerMode | TimerMainTick__B_TIMER__TM_SOFTWARE);

}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (TimerMainTick_EnableTriggerMode)


/*******************************************************************************
* Function Name: TimerMainTick_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_EnableTrigger(void) 
{
    #if (!TimerMainTick_ControlRegRemoved)   /* Remove assignment if control register is removed */
        TimerMainTick_CONTROL |= TimerMainTick_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: TimerMainTick_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_DisableTrigger(void) 
{
    #if (!TimerMainTick_ControlRegRemoved)   /* Remove assignment if control register is removed */
        TimerMainTick_CONTROL &= ~TimerMainTick_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */


#if(TimerMainTick_InterruptOnCaptureCount)
#if (!TimerMainTick_ControlRegRemoved)   /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TimerMainTick_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= TimerMainTick_CTRL_INTCNT_MASK;

    /* Clear the Current Setting */
    TimerMainTick_CONTROL &= ~TimerMainTick_CTRL_INTCNT_MASK;
    /* Write The New Setting */
    TimerMainTick_CONTROL |= interruptCount;
}
#endif /* Remove API if control register is removed */
#endif /* TimerMainTick_InterruptOnCaptureCount */


#if (TimerMainTick_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: TimerMainTick_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_SetCaptureCount(uint8 captureCount) 
{
    TimerMainTick_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: TimerMainTick_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 TimerMainTick_ReadCaptureCount(void) 
{
    return TimerMainTick_CAP_COUNT ;
}
#endif /* TimerMainTick_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: TimerMainTick_ClearFIFO
********************************************************************************
*
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void TimerMainTick_ClearFIFO(void) 
{
    while(TimerMainTick_ReadStatusRegister() & TimerMainTick_STATUS_FIFONEMP)
    {
        TimerMainTick_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */
