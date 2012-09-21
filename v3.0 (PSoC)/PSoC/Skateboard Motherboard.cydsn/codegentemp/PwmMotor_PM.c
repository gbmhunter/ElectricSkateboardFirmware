/*******************************************************************************
* File Name: PwmMotor_PM.c
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
#include "PwmMotor.h"

static PwmMotor_backupStruct PwmMotor_backup;


/*******************************************************************************
* Function Name: PwmMotor_SaveConfig
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
*  PwmMotor_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PwmMotor_SaveConfig(void)
{
    
    #if(!PwmMotor_UsingFixedFunction)
        #if (PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
            PwmMotor_backup.PWMUdb = PwmMotor_ReadCounter();
            PwmMotor_backup.PWMPeriod = PwmMotor_ReadPeriod();
            #if (PwmMotor_UseStatus)
                PwmMotor_backup.InterruptMaskValue = PwmMotor_STATUS_MASK;
            #endif
            
            #if(PwmMotor_UseOneCompareMode)
                PwmMotor_backup.PWMCompareValue = PwmMotor_ReadCompare();
            #else
                PwmMotor_backup.PWMCompareValue1 = PwmMotor_ReadCompare1();
                PwmMotor_backup.PWMCompareValue2 = PwmMotor_ReadCompare2();
            #endif
            
           #if(PwmMotor_DeadBandUsed)
                PwmMotor_backup.PWMdeadBandValue = PwmMotor_ReadDeadTime();
            #endif
          
            #if ( PwmMotor_KillModeMinTime)
                PwmMotor_backup.PWMKillCounterPeriod = PwmMotor_ReadKillTime();
            #endif
        #endif
        
        #if (PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
            #if(!PwmMotor_PWMModeIsCenterAligned)
                PwmMotor_backup.PWMPeriod = PwmMotor_ReadPeriod();
            #endif
            PwmMotor_backup.PWMUdb = PwmMotor_ReadCounter();
            #if (PwmMotor_UseStatus)
                PwmMotor_backup.InterruptMaskValue = PwmMotor_STATUS_MASK;
            #endif
            
            #if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS || PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
                PwmMotor_backup.PWMdeadBandValue = PwmMotor_ReadDeadTime();
            #endif
            
            #if(PwmMotor_KillModeMinTime)
                 PwmMotor_backup.PWMKillCounterPeriod = PwmMotor_ReadKillTime();
            #endif
        #endif
        
        #if(PwmMotor_UseControl)
            PwmMotor_backup.PWMControlRegister = PwmMotor_ReadControlRegister();
        #endif
    #endif  
}


/*******************************************************************************
* Function Name: PwmMotor_RestoreConfig
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
*  PwmMotor_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void PwmMotor_RestoreConfig(void) 
{
        #if(!PwmMotor_UsingFixedFunction)
            #if (PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
                /* Interrupt State Backup for Critical Region*/
                uint8 PwmMotor_interruptState;
                /* Enter Critical Region*/
                PwmMotor_interruptState = CyEnterCriticalSection();
                #if (PwmMotor_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PwmMotor_STATUS_AUX_CTRL |= PwmMotor_STATUS_ACTL_INT_EN_MASK;
                    
                    PwmMotor_STATUS_MASK = PwmMotor_backup.InterruptMaskValue;
                #endif
                
                #if (PwmMotor_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PwmMotor_AUX_CONTROLDP0 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
                #else /* (PwmMotor_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PwmMotor_AUX_CONTROLDP0 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
                    PwmMotor_AUX_CONTROLDP1 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
                #endif
                /* Exit Critical Region*/
                CyExitCriticalSection(PwmMotor_interruptState);
                
                PwmMotor_WriteCounter(PwmMotor_backup.PWMUdb);
                PwmMotor_WritePeriod(PwmMotor_backup.PWMPeriod);
                
                #if(PwmMotor_UseOneCompareMode)
                    PwmMotor_WriteCompare(PwmMotor_backup.PWMCompareValue);
                #else
                    PwmMotor_WriteCompare1(PwmMotor_backup.PWMCompareValue1);
                    PwmMotor_WriteCompare2(PwmMotor_backup.PWMCompareValue2);
                #endif
                
               #if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS || PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
                    PwmMotor_WriteDeadTime(PwmMotor_backup.PWMdeadBandValue);
                #endif
            
                #if ( PwmMotor_KillModeMinTime)
                    PwmMotor_WriteKillTime(PwmMotor_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if (PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
                #if(!PwmMotor_PWMModeIsCenterAligned)
                    PwmMotor_WritePeriod(PwmMotor_backup.PWMPeriod);
                #endif
                PwmMotor_WriteCounter(PwmMotor_backup.PWMUdb);
                #if (PwmMotor_UseStatus)
                    PwmMotor_STATUS_MASK = PwmMotor_backup.InterruptMaskValue;
                #endif
                
                #if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS || PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
                    PwmMotor_WriteDeadTime(PwmMotor_backup.PWMdeadBandValue);
                #endif
                
                #if(PwmMotor_KillModeMinTime)
                    PwmMotor_WriteKillTime(PwmMotor_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if(PwmMotor_UseControl)
                PwmMotor_WriteControlRegister(PwmMotor_backup.PWMControlRegister); 
            #endif
        #endif  
    }


/*******************************************************************************
* Function Name: PwmMotor_Sleep
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
*  PwmMotor_backup.PWMEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PwmMotor_Sleep(void)
{
    #if(PwmMotor_UseControl)
        if(PwmMotor_CTRL_ENABLE == (PwmMotor_CONTROL & PwmMotor_CTRL_ENABLE))
        {
            /*Component is enabled */
            PwmMotor_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PwmMotor_backup.PWMEnableState = 0u;
        }
    #endif
    /* Stop component */
    PwmMotor_Stop();
    
    /* Save registers configuration */
    PwmMotor_SaveConfig();
}


/*******************************************************************************
* Function Name: PwmMotor_Wakeup
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
*  PwmMotor_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_Wakeup(void) 
{
     /* Restore registers values */
    PwmMotor_RestoreConfig();
    
    if(PwmMotor_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PwmMotor_Enable();
    } /* Do nothing if component's block was disabled before */
    
}

/* [] END OF FILE */
