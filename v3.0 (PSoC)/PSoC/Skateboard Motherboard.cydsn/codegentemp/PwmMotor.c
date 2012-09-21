/*******************************************************************************
* File Name: PwmMotor.c  
* Version 2.10
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
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "PwmMotor.h"

uint8 PwmMotor_initVar = 0u;

/*******************************************************************************
* Function Name: PwmMotor_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  PwmMotor_initVar: Is modified when this function is called for the first 
*   time. Is used to ensure that initialization happens only once.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PwmMotor_initVar == 0u)
    {
        PwmMotor_Init();
        PwmMotor_initVar = 1u;
    }
    PwmMotor_Enable();

}


/*******************************************************************************
* Function Name: PwmMotor_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  PwmMotor_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_Init(void) 
{
    #if (PwmMotor_UsingFixedFunction || PwmMotor_UseControl)
        uint8 ctrl;
    #endif
    
    #if(!PwmMotor_UsingFixedFunction) 
        #if(PwmMotor_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PwmMotor_interruptState;
        #endif
    #endif
    
   #if (PwmMotor_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PwmMotor_CONTROL |= PwmMotor_CFG0_MODE;
        #if (PwmMotor_DeadBand2_4)
            PwmMotor_CONTROL |= PwmMotor_CFG0_DB;
        #endif
                
        /* Set the default Compare Mode */
        #if(PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
                ctrl = PwmMotor_CONTROL2 & ~PwmMotor_CTRL_CMPMODE1_MASK;
                PwmMotor_CONTROL2 = ctrl | PwmMotor_DEFAULT_COMPARE1_MODE;
        #endif
        #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
                ctrl = PwmMotor_CONTROL3 & ~PwmMotor_CTRL_CMPMODE1_MASK;
                PwmMotor_CONTROL3 = ctrl | PwmMotor_DEFAULT_COMPARE1_MODE;
        #endif
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PwmMotor_RT1 &= ~PwmMotor_RT1_MASK;
        PwmMotor_RT1 |= PwmMotor_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        PwmMotor_RT1 &= ~(PwmMotor_SYNCDSI_MASK);
        PwmMotor_RT1 |= PwmMotor_SYNCDSI_EN;
       
    #elif (PwmMotor_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PwmMotor_CONTROL & ~PwmMotor_CTRL_CMPMODE2_MASK & ~PwmMotor_CTRL_CMPMODE1_MASK;
        PwmMotor_CONTROL = ctrl | PwmMotor_DEFAULT_COMPARE2_MODE | PwmMotor_DEFAULT_COMPARE1_MODE;
    #endif 
        
    #if (!PwmMotor_UsingFixedFunction)
        #if (PwmMotor_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PwmMotor_AUX_CONTROLDP0 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
        #else /* (PwmMotor_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PwmMotor_AUX_CONTROLDP0 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
            PwmMotor_AUX_CONTROLDP1 |= (PwmMotor_AUX_CTRL_FIFO0_CLR);
        #endif
    #endif
        
    PwmMotor_WritePeriod(PwmMotor_INIT_PERIOD_VALUE);
    PwmMotor_WriteCounter(PwmMotor_INIT_PERIOD_VALUE);
        
        #if (PwmMotor_UseOneCompareMode)
            PwmMotor_WriteCompare(PwmMotor_INIT_COMPARE_VALUE1);
        #else
            PwmMotor_WriteCompare1(PwmMotor_INIT_COMPARE_VALUE1);
            PwmMotor_WriteCompare2(PwmMotor_INIT_COMPARE_VALUE2);
        #endif
        
        #if (PwmMotor_KillModeMinTime)
            PwmMotor_WriteKillTime(PwmMotor_MinimumKillTime);
        #endif
        
        #if (PwmMotor_DeadBandUsed)
            PwmMotor_WriteDeadTime(PwmMotor_INIT_DEAD_TIME);
        #endif

    #if (PwmMotor_UseStatus || PwmMotor_UsingFixedFunction)
        PwmMotor_SetInterruptMode(PwmMotor_INIT_INTERRUPTS_MODE);
    #endif
        
    #if (PwmMotor_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PwmMotor_GLOBAL_ENABLE |= PwmMotor_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PwmMotor_CONTROL2 |= PwmMotor_CTRL2_IRQ_SEL;
    #else
        #if(PwmMotor_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PwmMotor_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PwmMotor_STATUS_AUX_CTRL |= PwmMotor_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(PwmMotor_interruptState);
            
            /* Clear the FIFO to enable the PwmMotor_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PwmMotor_ClearFIFO();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: PwmMotor_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PwmMotor_UsingFixedFunction)
        PwmMotor_GLOBAL_ENABLE |= PwmMotor_BLOCK_EN_MASK;
        PwmMotor_GLOBAL_STBY_ENABLE |= PwmMotor_BLOCK_STBY_EN_MASK;
    #endif 
    
    /* Enable the PWM from the control register  */
    #if (PwmMotor_UseControl || PwmMotor_UsingFixedFunction)
        PwmMotor_CONTROL |= PwmMotor_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: PwmMotor_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_Stop(void) 
{
    #if (PwmMotor_UseControl || PwmMotor_UsingFixedFunction)
        PwmMotor_CONTROL &= ~PwmMotor_CTRL_ENABLE;
    #endif
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PwmMotor_UsingFixedFunction)
        PwmMotor_GLOBAL_ENABLE &= ~PwmMotor_BLOCK_EN_MASK;
        PwmMotor_GLOBAL_STBY_ENABLE &= ~PwmMotor_BLOCK_STBY_EN_MASK;
    #endif
}


#if (PwmMotor_UseOneCompareMode)
#if (PwmMotor_CompareMode1SW)
/*******************************************************************************
* Function Name: PwmMotor_SetCompareMode
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_SetCompareMode(uint8 comparemode) 
{
    #if(PwmMotor_UsingFixedFunction)
            #if(PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
                        uint8 comparemodemasked = (comparemode << PwmMotor_CTRL_CMPMODE1_SHIFT);
                        PwmMotor_CONTROL2 &= ~PwmMotor_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
                        PwmMotor_CONTROL2 |= comparemodemasked;  
                #endif
                
            #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
                    uint8 comparemodemasked = (comparemode << PwmMotor_CTRL_CMPMODE1_SHIFT);
            PwmMotor_CONTROL3 &= ~PwmMotor_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            PwmMotor_CONTROL3 |= comparemodemasked;     
                #endif
                
    #elif (PwmMotor_UseControl)
        uint8 comparemode1masked = (comparemode << PwmMotor_CTRL_CMPMODE1_SHIFT) & PwmMotor_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << PwmMotor_CTRL_CMPMODE2_SHIFT) & PwmMotor_CTRL_CMPMODE2_MASK;
        PwmMotor_CONTROL &= ~(PwmMotor_CTRL_CMPMODE1_MASK | PwmMotor_CTRL_CMPMODE2_MASK); /*Clear existing mode */
        PwmMotor_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif
}
#endif /* PwmMotor_CompareMode1SW */

#else /* UseOneCompareMode */


#if (PwmMotor_CompareMode1SW)
/*******************************************************************************
* Function Name: PwmMotor_SetCompareMode1
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << PwmMotor_CTRL_CMPMODE1_SHIFT) & PwmMotor_CTRL_CMPMODE1_MASK;
    #if(PwmMotor_UsingFixedFunction)
            #if(PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
                        PwmMotor_CONTROL2 &= PwmMotor_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        PwmMotor_CONTROL2 |= comparemodemasked; 
            #endif
                
                #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
                    PwmMotor_CONTROL3 &= PwmMotor_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        PwmMotor_CONTROL3 |= comparemodemasked; 
            #endif
                
    #elif (PwmMotor_UseControl)
        PwmMotor_CONTROL &= PwmMotor_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        PwmMotor_CONTROL |= comparemodemasked;
    #endif    
}
#endif /* PwmMotor_CompareMode1SW */


#if (PwmMotor_CompareMode2SW)
/*******************************************************************************
* Function Name: PwmMotor_SetCompareMode2
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_SetCompareMode2(uint8 comparemode) 
{
    #if(PwmMotor_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block*/ 
    #elif (PwmMotor_UseControl)
    uint8 comparemodemasked = (comparemode << PwmMotor_CTRL_CMPMODE2_SHIFT) & PwmMotor_CTRL_CMPMODE2_MASK;
    PwmMotor_CONTROL &= PwmMotor_CTRL_CMPMODE2_MASK; /*Clear existing mode */
    PwmMotor_CONTROL |= comparemodemasked;
    #endif    
}
#endif /*PwmMotor_CompareMode2SW */
#endif /* UseOneCompareMode */


/*******************************************************************************
* Function Name: PwmMotor_WriteCounter
********************************************************************************
* 
* Summary:
*  This function is used to change the counter value.
*
* Parameters:  
*  counter:  This value may be between 1 and (2^Resolution)-1.   
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WriteCounter(uint16 counter) 
{
    #if(PwmMotor_UsingFixedFunction)
        CY_SET_REG16(PwmMotor_COUNTER_LSB_PTR, (uint16)counter);
    #else
        CY_SET_REG16(PwmMotor_COUNTER_LSB_PTR, counter);
    #endif
}


#if (!PwmMotor_UsingFixedFunction)
/*******************************************************************************
* Function Name: PwmMotor_ReadCounter
********************************************************************************
* 
* Summary:
*  This function returns the current value of the counter.  It doesn't matter
*  if the counter is enabled or running.
*
* Parameters:  
*  void  
*
* Return: 
*  The current value of the counter.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint16 PwmMotor_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(PwmMotor_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG16(PwmMotor_CAPTURE_LSB_PTR));
}


#if (PwmMotor_UseStatus)
/*******************************************************************************
* Function Name: PwmMotor_ClearFIFO
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
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_ClearFIFO(void) 
{
    while(PwmMotor_ReadStatusRegister() & PwmMotor_STATUS_FIFONEMPTY)
        PwmMotor_ReadCapture();
}
#endif /* PwmMotor_UseStatus */
#endif /* !PwmMotor_UsingFixedFunction */


/*******************************************************************************
* Function Name: PwmMotor_WritePeriod
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WritePeriod(uint16 period) 
{
    #if(PwmMotor_UsingFixedFunction)
        CY_SET_REG16(PwmMotor_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(PwmMotor_PERIOD_LSB_PTR, period);
    #endif
}


#if (PwmMotor_UseOneCompareMode)
/*******************************************************************************
* Function Name: PwmMotor_WriteCompare
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
*  void
*
* Side Effects:
*  This function is only available if the PWM mode parameter is set to
*  Dither Mode, Center Aligned Mode or One Output Mode
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WriteCompare(uint16 compare) 
{
   CY_SET_REG16(PwmMotor_COMPARE1_LSB_PTR, compare);
   #if (PwmMotor_PWMMode == PwmMotor__B_PWM__DITHER)
        CY_SET_REG16(PwmMotor_COMPARE2_LSB_PTR, compare+1);
   #endif
}


#else


/*******************************************************************************
* Function Name: PwmMotor_WriteCompare1
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WriteCompare1(uint16 compare) 
{
    #if(PwmMotor_UsingFixedFunction)
        CY_SET_REG16(PwmMotor_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(PwmMotor_COMPARE1_LSB_PTR, compare);
    #endif
}


/*******************************************************************************
* Function Name: PwmMotor_WriteCompare2
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
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WriteCompare2(uint16 compare) 
{
    #if(PwmMotor_UsingFixedFunction)
        CY_SET_REG16(PwmMotor_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG16(PwmMotor_COMPARE2_LSB_PTR, compare);
    #endif
}
#endif /* UseOneCompareMode */


#if (PwmMotor_DeadBandUsed)
/*******************************************************************************
* Function Name: PwmMotor_WriteDeadTime
********************************************************************************
* 
* Summary:
*  This function writes the dead-band counts to the corresponding register
*
* Parameters:  
*  deadtime:  Number of counts for dead time 
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmMotor_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!PwmMotor_DeadBand2_4)
        CY_SET_REG8(PwmMotor_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        PwmMotor_DEADBAND_COUNT &= ~PwmMotor_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        PwmMotor_DEADBAND_COUNT |= (deadtime << PwmMotor_DEADBAND_COUNT_SHIFT) & PwmMotor_DEADBAND_COUNT_MASK; 
    #endif
}


/*******************************************************************************
* Function Name: PwmMotor_ReadDeadTime
********************************************************************************
* 
* Summary:
*  This function reads the dead-band counts from the corresponding register
*
* Parameters:  
*  void
*
* Return: 
*  Dead Band Counts
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint8 PwmMotor_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!PwmMotor_DeadBand2_4)
        return (CY_GET_REG8(PwmMotor_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((PwmMotor_DEADBAND_COUNT & PwmMotor_DEADBAND_COUNT_MASK) >> PwmMotor_DEADBAND_COUNT_SHIFT);
    #endif
}
#endif /* DeadBandUsed */

