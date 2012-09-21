/*******************************************************************************
* File Name: PwmPiezo_PM.c
* Version 2.10
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PwmPiezo.h"

static PwmPiezo_backupStruct PwmPiezo_backup;


/*******************************************************************************
* Function Name: PwmPiezo_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PwmPiezo_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PwmPiezo_SaveConfig(void)
{
    
    #if(!PwmPiezo_UsingFixedFunction)
        #if (PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
            PwmPiezo_backup.PWMUdb = PwmPiezo_ReadCounter();
            PwmPiezo_backup.PWMPeriod = PwmPiezo_ReadPeriod();
            #if (PwmPiezo_UseStatus)
                PwmPiezo_backup.InterruptMaskValue = PwmPiezo_STATUS_MASK;
            #endif
            
            #if(PwmPiezo_UseOneCompareMode)
                PwmPiezo_backup.PWMCompareValue = PwmPiezo_ReadCompare();
            #else
                PwmPiezo_backup.PWMCompareValue1 = PwmPiezo_ReadCompare1();
                PwmPiezo_backup.PWMCompareValue2 = PwmPiezo_ReadCompare2();
            #endif
            
           #if(PwmPiezo_DeadBandUsed)
                PwmPiezo_backup.PWMdeadBandValue = PwmPiezo_ReadDeadTime();
            #endif
          
            #if ( PwmPiezo_KillModeMinTime)
                PwmPiezo_backup.PWMKillCounterPeriod = PwmPiezo_ReadKillTime();
            #endif
        #endif
        
        #if (PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
            #if(!PwmPiezo_PWMModeIsCenterAligned)
                PwmPiezo_backup.PWMPeriod = PwmPiezo_ReadPeriod();
            #endif
            PwmPiezo_backup.PWMUdb = PwmPiezo_ReadCounter();
            #if (PwmPiezo_UseStatus)
                PwmPiezo_backup.InterruptMaskValue = PwmPiezo_STATUS_MASK;
            #endif
            
            #if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS || PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
                PwmPiezo_backup.PWMdeadBandValue = PwmPiezo_ReadDeadTime();
            #endif
            
            #if(PwmPiezo_KillModeMinTime)
                 PwmPiezo_backup.PWMKillCounterPeriod = PwmPiezo_ReadKillTime();
            #endif
        #endif
        
        #if(PwmPiezo_UseControl)
            PwmPiezo_backup.PWMControlRegister = PwmPiezo_ReadControlRegister();
        #endif
    #endif  
}


/*******************************************************************************
* Function Name: PwmPiezo_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PwmPiezo_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void PwmPiezo_RestoreConfig(void) 
{
        #if(!PwmPiezo_UsingFixedFunction)
            #if (PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
                /* Interrupt State Backup for Critical Region*/
                uint8 PwmPiezo_interruptState;
                /* Enter Critical Region*/
                PwmPiezo_interruptState = CyEnterCriticalSection();
                #if (PwmPiezo_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PwmPiezo_STATUS_AUX_CTRL |= PwmPiezo_STATUS_ACTL_INT_EN_MASK;
                    
                    PwmPiezo_STATUS_MASK = PwmPiezo_backup.InterruptMaskValue;
                #endif
                
                #if (PwmPiezo_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PwmPiezo_AUX_CONTROLDP0 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
                #else /* (PwmPiezo_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PwmPiezo_AUX_CONTROLDP0 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
                    PwmPiezo_AUX_CONTROLDP1 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
                #endif
                /* Exit Critical Region*/
                CyExitCriticalSection(PwmPiezo_interruptState);
                
                PwmPiezo_WriteCounter(PwmPiezo_backup.PWMUdb);
                PwmPiezo_WritePeriod(PwmPiezo_backup.PWMPeriod);
                
                #if(PwmPiezo_UseOneCompareMode)
                    PwmPiezo_WriteCompare(PwmPiezo_backup.PWMCompareValue);
                #else
                    PwmPiezo_WriteCompare1(PwmPiezo_backup.PWMCompareValue1);
                    PwmPiezo_WriteCompare2(PwmPiezo_backup.PWMCompareValue2);
                #endif
                
               #if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS || PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
                    PwmPiezo_WriteDeadTime(PwmPiezo_backup.PWMdeadBandValue);
                #endif
            
                #if ( PwmPiezo_KillModeMinTime)
                    PwmPiezo_WriteKillTime(PwmPiezo_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if (PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
                #if(!PwmPiezo_PWMModeIsCenterAligned)
                    PwmPiezo_WritePeriod(PwmPiezo_backup.PWMPeriod);
                #endif
                PwmPiezo_WriteCounter(PwmPiezo_backup.PWMUdb);
                #if (PwmPiezo_UseStatus)
                    PwmPiezo_STATUS_MASK = PwmPiezo_backup.InterruptMaskValue;
                #endif
                
                #if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS || PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
                    PwmPiezo_WriteDeadTime(PwmPiezo_backup.PWMdeadBandValue);
                #endif
                
                #if(PwmPiezo_KillModeMinTime)
                    PwmPiezo_WriteKillTime(PwmPiezo_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if(PwmPiezo_UseControl)
                PwmPiezo_WriteControlRegister(PwmPiezo_backup.PWMControlRegister); 
            #endif
        #endif  
    }


/*******************************************************************************
* Function Name: PwmPiezo_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PwmPiezo_backup.PWMEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PwmPiezo_Sleep(void)
{
    #if(PwmPiezo_UseControl)
        if(PwmPiezo_CTRL_ENABLE == (PwmPiezo_CONTROL & PwmPiezo_CTRL_ENABLE))
        {
            /*Component is enabled */
            PwmPiezo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PwmPiezo_backup.PWMEnableState = 0u;
        }
    #endif
    /* Stop component */
    PwmPiezo_Stop();
    
    /* Save registers configuration */
    PwmPiezo_SaveConfig();
}


/*******************************************************************************
* Function Name: PwmPiezo_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PwmPiezo_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmPiezo_Wakeup(void) 
{
     /* Restore registers values */
    PwmPiezo_RestoreConfig();
    
    if(PwmPiezo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PwmPiezo_Enable();
    } /* Do nothing if component's block was disabled before */
    
}

/* [] END OF FILE */
