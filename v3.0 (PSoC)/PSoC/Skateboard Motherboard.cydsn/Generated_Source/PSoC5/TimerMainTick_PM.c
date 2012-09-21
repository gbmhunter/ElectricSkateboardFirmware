/*******************************************************************************
* File Name: TimerMainTick_PM.c
* Version 2.20
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerMainTick.h"
static TimerMainTick_backupStruct TimerMainTick_backup;


/*******************************************************************************
* Function Name: TimerMainTick_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerMainTick_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
* Reentrant:
*    No
*
*******************************************************************************/
void TimerMainTick_SaveConfig(void)
{
    #if (!TimerMainTick_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
            TimerMainTick_backup.TimerUdb = TimerMainTick_ReadCounter();
            TimerMainTick_backup.TimerPeriod = TimerMainTick_ReadPeriod();
            TimerMainTick_backup.InterruptMaskValue = TimerMainTick_STATUS_MASK;
            #if (TimerMainTick_UsingHWCaptureCounter)
                TimerMainTick_backup.TimerCaptureCounter = TimerMainTick_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC3 ES2 and PSoC5 ES1 */
        #endif /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/

        #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
            TimerMainTick_backup.TimerUdb = TimerMainTick_ReadCounter();
            TimerMainTick_backup.InterruptMaskValue = TimerMainTick_STATUS_MASK;
            #if (TimerMainTick_UsingHWCaptureCounter)
                TimerMainTick_backup.TimerCaptureCounter = TimerMainTick_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3ES3 or PSoC5ES2 */

        #if(!TimerMainTick_ControlRegRemoved)
            TimerMainTick_backup.TimerControlRegister = TimerMainTick_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerMainTick_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerMainTick_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void TimerMainTick_RestoreConfig(void) 
{   
    #if (!TimerMainTick_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerMainTick_interruptState;

            TimerMainTick_WriteCounter(TimerMainTick_backup.TimerUdb);
            TimerMainTick_WritePeriod(TimerMainTick_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerMainTick_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TimerMainTick_STATUS_AUX_CTRL |= TimerMainTick_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerMainTick_interruptState);
            TimerMainTick_STATUS_MASK =TimerMainTick_backup.InterruptMaskValue;
            #if (TimerMainTick_UsingHWCaptureCounter)
                TimerMainTick_SetCaptureCount(TimerMainTick_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC3 ES2 and PSoC5 ES1 */
        #endif /* Restore the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/

        #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
            TimerMainTick_WriteCounter(TimerMainTick_backup.TimerUdb);
            TimerMainTick_STATUS_MASK =TimerMainTick_backup.InterruptMaskValue;
            #if (TimerMainTick_UsingHWCaptureCounter)
                TimerMainTick_SetCaptureCount(TimerMainTick_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3ES3 or PSoC5ES2 */

        #if(!TimerMainTick_ControlRegRemoved)
            TimerMainTick_WriteControlRegister(TimerMainTick_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerMainTick_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerMainTick_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
* Reentrant:
*    No
*
*******************************************************************************/
void TimerMainTick_Sleep(void)
{
    #if(!TimerMainTick_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerMainTick_CTRL_ENABLE == (TimerMainTick_CONTROL & TimerMainTick_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerMainTick_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerMainTick_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerMainTick_Stop();
    TimerMainTick_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerMainTick_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerMainTick_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void TimerMainTick_Wakeup(void) 
{
    TimerMainTick_RestoreConfig();
    #if(!TimerMainTick_ControlRegRemoved)
        if(TimerMainTick_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerMainTick_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
