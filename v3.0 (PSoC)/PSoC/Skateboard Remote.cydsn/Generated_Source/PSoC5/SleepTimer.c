/*******************************************************************************
* File Name: SleepTimer.c
* Version 2.1
*
* Description:
*  This file provides the source code to API for the Sleep Timer.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SleepTimer.h"
#include "CyLib.h"

/* Variables were not initialized */
uint8 SleepTimer_initVar = 0u;


/*******************************************************************************
* Function Name: SleepTimer_Start
********************************************************************************
*
* Summary:
*  Starts the Sleep Timer operation. If this function is called, then the
*  component will be initialized with values defined in the customizer. If
*  parameters need to be changed, then stop component, change needed parameters
*  by calling the desired API functions, and restart the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  The SleepTimer_initVar variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and
*  set to 1 the first time SleepTimer_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the SleepTimer_Start() routine.
*
* Reentrant:
*  No
*
* Side Effects:
*  Enables 1 kHz ILO clock and leaves it enabled after the Sleep Time component
*  is stopped.
*
*******************************************************************************/
void SleepTimer_Start(void) 
{
    /* Execute once in normal flow */
    if (0u == SleepTimer_initVar)
    {
        SleepTimer_Init();
        SleepTimer_initVar = 1u;
    }

    /* Enables the component operation */
    SleepTimer_Enable();
}


/*******************************************************************************
* Function Name: SleepTimer_Init
********************************************************************************
*
* Summary:
*  Initializes/Restores default configuration provided with the customizer.
*  Sets CTW interval period and enables/disables CTW interrupt (according to
*  the customizer's settings).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SleepTimer_Init(void)  
{
    /* Sets default (passed from customizer) interval */
    SleepTimer_SetInterval(SleepTimer_INTERVAL);

    /* Check if user sets to issue an interrupt in customizer */
    if (1u == SleepTimer_ENABLE_INTERRUPT)
    {
        /* Enable interrupt */
        SleepTimer_EnableInt();
    }
    else /* interrupt should be disabled */
    {
        /* Disable interrupt */
        SleepTimer_DisableInt();
    }   /* Interrupt is disabled  */
}


/*******************************************************************************
* Function Name: SleepTimer_Enable
********************************************************************************
* Summary:
*  Enables the 1kHz ILO clock, enables the CTW counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Enables 1 kHz ILO clocks and leaves it enabled after Sleep Time component
*  is stopped.
*
*******************************************************************************/
void SleepTimer_Enable(void) 
{
    uint8 interruptState;

    /* If 1kHz ILO is disabled */
    if(0u == (SleepTimer_ILO_CFG_REG & SleepTimer_ILO_1KHZ_EN))
    {
        /* Enter critical section */
        interruptState = CyEnterCriticalSection();

        /* Enable 1kHz ILO */
        SleepTimer_ILO_CFG_REG |=SleepTimer_ILO_1KHZ_EN;

        /* Enable the CTW counter */
        SleepTimer_TW_CFG_REG |= SleepTimer_CTW_EN;

        /* Exit critical section */
        CyExitCriticalSection(interruptState);
    }
    else /* If 1kHz ILO is enabled - enable CTW counter */
    {
        /* Enter critical section */
        interruptState = CyEnterCriticalSection();

        /* Enable the CTW counter */
        SleepTimer_TW_CFG_REG |= SleepTimer_CTW_EN;

        /* Exit critical section */
        CyExitCriticalSection(interruptState);
    }
}


/*******************************************************************************
* Function Name: SleepTimer_Stop
********************************************************************************
*
* Summary:
*  Stops the Sleep Timer operation: disables wake up on the Central Time Wheel
*  (CTW) counter terminal count reached.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Leaves the 1 kHz ILO clock enabled after Sleep Time component is stopped.
*
*******************************************************************************/
void SleepTimer_Stop(void) 
{
    uint8 interruptState;

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Disable CTW counter */
    SleepTimer_TW_CFG_REG &= ~SleepTimer_CTW_EN;

    /* Exit critical section */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: SleepTimer_EnableInt
********************************************************************************
*
* Summary:
*  Enables interrupt on the Central Time Wheel (CTW) terminal count reached.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SleepTimer_EnableInt(void) 
{
    uint8 interruptState;

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

     /* Enable interrupt on wake up */
    SleepTimer_TW_CFG_REG |= SleepTimer_CTW_IE;

    /* Exit critical section */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: SleepTimer_DisableInt
********************************************************************************
*
* Summary:
*  Disables interrupt on the Central Time Wheel (CTW) terminal count reached.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SleepTimer_DisableInt(void) 
{
    uint8 interruptState;

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Disable interrupt on wake up */
    SleepTimer_TW_CFG_REG &= ~SleepTimer_CTW_IE;

    /* Exit critical section */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: SleepTimer_SetInterval
********************************************************************************
*
* Summary:
*  Sets CTW interval period. The first interval can range from 1 to (period + 1)
*  milliseconds. Additional intervals occur at the nominal period.
*
* Parameters:
*  uint8 interval: interval?s value for the CTW.
*  PSoC 5: Only the 4, 8 and 16 ms selections are supported.
*
*           Name                    Value        Period
*   SleepTimer__CTW_2_MS      4'b0001        2 ms
*   SleepTimer__CTW_4_MS      4'b0010        4 ms
*   SleepTimer__CTW_8_MS      4'b0011        8 ms
*   SleepTimer__CTW_16_MS     4'b0100        16 ms
*   SleepTimer__CTW_32_MS     4'b0101        32 ms
*   SleepTimer__CTW_64_MS     4'b0110        64 ms
*   SleepTimer__CTW_128_MS    4'b0111        128 ms
*   SleepTimer__CTW_256_MS    4'b1000        256 ms
*   SleepTimer__CTW_512_MS    4'b1001        512 ms
*   SleepTimer__CTW_1024_MS   4'b1010        1024 ms
*   SleepTimer__CTW_2048_MS   4'b1011        2048 ms
*   SleepTimer__CTW_4096_MS   4'b1100        4096 ms
*
* Return:
*  None
*
* Side Effects:
*  Interval value can be only changed when component is stopped (CTW is
*  disabled).
*
*******************************************************************************/
void SleepTimer_SetInterval(uint8 interval) 
{
    /* Check if CTW is disabled */
    if (0u == (SleepTimer_TW_CFG_REG & SleepTimer_CTW_EN))
    {
        /* Device is PSoC 5 and the revision is ES1 or earlier. */
        #if(CY_PSOC5_ES1)

            CYASSERT((SleepTimer__CTW_4_MS  == interval) ||
                     (SleepTimer__CTW_8_MS  == interval) ||
                     (SleepTimer__CTW_16_MS == interval));

        #endif  /* CY_PSOC5_ES1 */

        /* Set CTW interval */
        SleepTimer_CTW_INTERVAL_REG = \
            (SleepTimer_CTW_INTERVAL_REG & ~SleepTimer_INTERVAL_MASK) | \
            (interval & SleepTimer_INTERVAL_MASK);
    }
    /* Do nothing if CTW is enabled. */
}


/*******************************************************************************
* Function Name: SleepTimer_GetStatus
********************************************************************************
*
* Summary:
*  This function should always be called (when the Sleep Timer?s interrupt is
*  disabled or enabled) after wake up to clear the ctw_int status bit.
*
* Parameters:
*  None
*
* Return:
*  uint8 with bits set if corresponding event has occurred
*            Name                             Description
*  SleepTimer_PM_INT_SR_ONEPPSP  A onepps event has occured
*  SleepTimer_PM_INT_SR_CTW      A central timewheel event occured
*  SleepTimer_PM_INT_SR_FTW      A fast timewheel event occured
*
* Side Effects:
*  If an interrupt gets generated at the same time as a register read/clear,
*  the bit will remain set (which causes another interrupt). Reports and then
*  clears all interrupt status bits in the Power Manager Interrupt Status
*  Register. Some of the bits are not relevant to operation of this component.
*
*  If the GetStatus() function is not called in an interrupt associated with
*  the SleepTimer, the interrupt is not cleared and as soon as the interrupt is
*  exited it will be re-entered.
*
*  Once the Sleep timer has expired, until the GetStatus() function is called
*  the sleep interval is functionally 0 ms, since GetStatus clears the ctw_int
*  bit.
*
*  This function must always be called (when the Sleep Timer's interrupt is
*  disabled or enabled) after wakeup to clear the ctw_int status bit. It is
*  required to call SleepTimer_GetStatus() within 1 ms (1 clock cycle of the
*  ILO) after the CTW event occurred.
*
*******************************************************************************/
uint8 SleepTimer_GetStatus(void) 
{
    /* Read to clear  */
    return CyPmReadStatus(CY_PM_CTW_INT);
}


/* [] END OF FILE */
