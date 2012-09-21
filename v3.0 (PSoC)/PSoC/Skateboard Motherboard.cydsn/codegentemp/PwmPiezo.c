/*******************************************************************************
* File Name: PwmPiezo.c  
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
#include "PwmPiezo.h"

uint8 PwmPiezo_initVar = 0u;

/*******************************************************************************
* Function Name: PwmPiezo_Start
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
*  PwmPiezo_initVar: Is modified when this function is called for the first 
*   time. Is used to ensure that initialization happens only once.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void PwmPiezo_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PwmPiezo_initVar == 0u)
    {
        PwmPiezo_Init();
        PwmPiezo_initVar = 1u;
    }
    PwmPiezo_Enable();

}


/*******************************************************************************
* Function Name: PwmPiezo_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  PwmPiezo_Start().
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
void PwmPiezo_Init(void) 
{
    #if (PwmPiezo_UsingFixedFunction || PwmPiezo_UseControl)
        uint8 ctrl;
    #endif
    
    #if(!PwmPiezo_UsingFixedFunction) 
        #if(PwmPiezo_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PwmPiezo_interruptState;
        #endif
    #endif
    
   #if (PwmPiezo_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PwmPiezo_CONTROL |= PwmPiezo_CFG0_MODE;
        #if (PwmPiezo_DeadBand2_4)
            PwmPiezo_CONTROL |= PwmPiezo_CFG0_DB;
        #endif
                
        /* Set the default Compare Mode */
        #if(PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
                ctrl = PwmPiezo_CONTROL2 & ~PwmPiezo_CTRL_CMPMODE1_MASK;
                PwmPiezo_CONTROL2 = ctrl | PwmPiezo_DEFAULT_COMPARE1_MODE;
        #endif
        #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
                ctrl = PwmPiezo_CONTROL3 & ~PwmPiezo_CTRL_CMPMODE1_MASK;
                PwmPiezo_CONTROL3 = ctrl | PwmPiezo_DEFAULT_COMPARE1_MODE;
        #endif
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PwmPiezo_RT1 &= ~PwmPiezo_RT1_MASK;
        PwmPiezo_RT1 |= PwmPiezo_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        PwmPiezo_RT1 &= ~(PwmPiezo_SYNCDSI_MASK);
        PwmPiezo_RT1 |= PwmPiezo_SYNCDSI_EN;
       
    #elif (PwmPiezo_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PwmPiezo_CONTROL & ~PwmPiezo_CTRL_CMPMODE2_MASK & ~PwmPiezo_CTRL_CMPMODE1_MASK;
        PwmPiezo_CONTROL = ctrl | PwmPiezo_DEFAULT_COMPARE2_MODE | PwmPiezo_DEFAULT_COMPARE1_MODE;
    #endif 
        
    #if (!PwmPiezo_UsingFixedFunction)
        #if (PwmPiezo_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PwmPiezo_AUX_CONTROLDP0 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
        #else /* (PwmPiezo_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PwmPiezo_AUX_CONTROLDP0 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
            PwmPiezo_AUX_CONTROLDP1 |= (PwmPiezo_AUX_CTRL_FIFO0_CLR);
        #endif
    #endif
        
    PwmPiezo_WritePeriod(PwmPiezo_INIT_PERIOD_VALUE);
    PwmPiezo_WriteCounter(PwmPiezo_INIT_PERIOD_VALUE);
        
        #if (PwmPiezo_UseOneCompareMode)
            PwmPiezo_WriteCompare(PwmPiezo_INIT_COMPARE_VALUE1);
        #else
            PwmPiezo_WriteCompare1(PwmPiezo_INIT_COMPARE_VALUE1);
            PwmPiezo_WriteCompare2(PwmPiezo_INIT_COMPARE_VALUE2);
        #endif
        
        #if (PwmPiezo_KillModeMinTime)
            PwmPiezo_WriteKillTime(PwmPiezo_MinimumKillTime);
        #endif
        
        #if (PwmPiezo_DeadBandUsed)
            PwmPiezo_WriteDeadTime(PwmPiezo_INIT_DEAD_TIME);
        #endif

    #if (PwmPiezo_UseStatus || PwmPiezo_UsingFixedFunction)
        PwmPiezo_SetInterruptMode(PwmPiezo_INIT_INTERRUPTS_MODE);
    #endif
        
    #if (PwmPiezo_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PwmPiezo_GLOBAL_ENABLE |= PwmPiezo_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PwmPiezo_CONTROL2 |= PwmPiezo_CTRL2_IRQ_SEL;
    #else
        #if(PwmPiezo_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PwmPiezo_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PwmPiezo_STATUS_AUX_CTRL |= PwmPiezo_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(PwmPiezo_interruptState);
            
            /* Clear the FIFO to enable the PwmPiezo_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PwmPiezo_ClearFIFO();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: PwmPiezo_Enable
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
void PwmPiezo_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PwmPiezo_UsingFixedFunction)
        PwmPiezo_GLOBAL_ENABLE |= PwmPiezo_BLOCK_EN_MASK;
        PwmPiezo_GLOBAL_STBY_ENABLE |= PwmPiezo_BLOCK_STBY_EN_MASK;
    #endif 
    
    /* Enable the PWM from the control register  */
    #if (PwmPiezo_UseControl || PwmPiezo_UsingFixedFunction)
        PwmPiezo_CONTROL |= PwmPiezo_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: PwmPiezo_Stop
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
void PwmPiezo_Stop(void) 
{
    #if (PwmPiezo_UseControl || PwmPiezo_UsingFixedFunction)
        PwmPiezo_CONTROL &= ~PwmPiezo_CTRL_ENABLE;
    #endif
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PwmPiezo_UsingFixedFunction)
        PwmPiezo_GLOBAL_ENABLE &= ~PwmPiezo_BLOCK_EN_MASK;
        PwmPiezo_GLOBAL_STBY_ENABLE &= ~PwmPiezo_BLOCK_STBY_EN_MASK;
    #endif
}


#if (PwmPiezo_UseOneCompareMode)
#if (PwmPiezo_CompareMode1SW)
/*******************************************************************************
* Function Name: PwmPiezo_SetCompareMode
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
void PwmPiezo_SetCompareMode(uint8 comparemode) 
{
    #if(PwmPiezo_UsingFixedFunction)
            #if(PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
                        uint8 comparemodemasked = (comparemode << PwmPiezo_CTRL_CMPMODE1_SHIFT);
                        PwmPiezo_CONTROL2 &= ~PwmPiezo_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
                        PwmPiezo_CONTROL2 |= comparemodemasked;  
                #endif
                
            #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
                    uint8 comparemodemasked = (comparemode << PwmPiezo_CTRL_CMPMODE1_SHIFT);
            PwmPiezo_CONTROL3 &= ~PwmPiezo_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            PwmPiezo_CONTROL3 |= comparemodemasked;     
                #endif
                
    #elif (PwmPiezo_UseControl)
        uint8 comparemode1masked = (comparemode << PwmPiezo_CTRL_CMPMODE1_SHIFT) & PwmPiezo_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << PwmPiezo_CTRL_CMPMODE2_SHIFT) & PwmPiezo_CTRL_CMPMODE2_MASK;
        PwmPiezo_CONTROL &= ~(PwmPiezo_CTRL_CMPMODE1_MASK | PwmPiezo_CTRL_CMPMODE2_MASK); /*Clear existing mode */
        PwmPiezo_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif
}
#endif /* PwmPiezo_CompareMode1SW */

#else /* UseOneCompareMode */


#if (PwmPiezo_CompareMode1SW)
/*******************************************************************************
* Function Name: PwmPiezo_SetCompareMode1
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
void PwmPiezo_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << PwmPiezo_CTRL_CMPMODE1_SHIFT) & PwmPiezo_CTRL_CMPMODE1_MASK;
    #if(PwmPiezo_UsingFixedFunction)
            #if(PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
                        PwmPiezo_CONTROL2 &= PwmPiezo_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        PwmPiezo_CONTROL2 |= comparemodemasked; 
            #endif
                
                #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
                    PwmPiezo_CONTROL3 &= PwmPiezo_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        PwmPiezo_CONTROL3 |= comparemodemasked; 
            #endif
                
    #elif (PwmPiezo_UseControl)
        PwmPiezo_CONTROL &= PwmPiezo_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        PwmPiezo_CONTROL |= comparemodemasked;
    #endif    
}
#endif /* PwmPiezo_CompareMode1SW */


#if (PwmPiezo_CompareMode2SW)
/*******************************************************************************
* Function Name: PwmPiezo_SetCompareMode2
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
void PwmPiezo_SetCompareMode2(uint8 comparemode) 
{
    #if(PwmPiezo_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block*/ 
    #elif (PwmPiezo_UseControl)
    uint8 comparemodemasked = (comparemode << PwmPiezo_CTRL_CMPMODE2_SHIFT) & PwmPiezo_CTRL_CMPMODE2_MASK;
    PwmPiezo_CONTROL &= PwmPiezo_CTRL_CMPMODE2_MASK; /*Clear existing mode */
    PwmPiezo_CONTROL |= comparemodemasked;
    #endif    
}
#endif /*PwmPiezo_CompareMode2SW */
#endif /* UseOneCompareMode */


/*******************************************************************************
* Function Name: PwmPiezo_WriteCounter
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
void PwmPiezo_WriteCounter(uint16 counter) 
{
    #if(PwmPiezo_UsingFixedFunction)
        CY_SET_REG16(PwmPiezo_COUNTER_LSB_PTR, (uint16)counter);
    #else
        CY_SET_REG16(PwmPiezo_COUNTER_LSB_PTR, counter);
    #endif
}


#if (!PwmPiezo_UsingFixedFunction)
/*******************************************************************************
* Function Name: PwmPiezo_ReadCounter
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
uint16 PwmPiezo_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(PwmPiezo_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG16(PwmPiezo_CAPTURE_LSB_PTR));
}


#if (PwmPiezo_UseStatus)
/*******************************************************************************
* Function Name: PwmPiezo_ClearFIFO
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
void PwmPiezo_ClearFIFO(void) 
{
    while(PwmPiezo_ReadStatusRegister() & PwmPiezo_STATUS_FIFONEMPTY)
        PwmPiezo_ReadCapture();
}
#endif /* PwmPiezo_UseStatus */
#endif /* !PwmPiezo_UsingFixedFunction */


/*******************************************************************************
* Function Name: PwmPiezo_WritePeriod
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
void PwmPiezo_WritePeriod(uint16 period) 
{
    #if(PwmPiezo_UsingFixedFunction)
        CY_SET_REG16(PwmPiezo_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(PwmPiezo_PERIOD_LSB_PTR, period);
    #endif
}


#if (PwmPiezo_UseOneCompareMode)
/*******************************************************************************
* Function Name: PwmPiezo_WriteCompare
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
void PwmPiezo_WriteCompare(uint16 compare) 
{
   CY_SET_REG16(PwmPiezo_COMPARE1_LSB_PTR, compare);
   #if (PwmPiezo_PWMMode == PwmPiezo__B_PWM__DITHER)
        CY_SET_REG16(PwmPiezo_COMPARE2_LSB_PTR, compare+1);
   #endif
}


#else


/*******************************************************************************
* Function Name: PwmPiezo_WriteCompare1
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
void PwmPiezo_WriteCompare1(uint16 compare) 
{
    #if(PwmPiezo_UsingFixedFunction)
        CY_SET_REG16(PwmPiezo_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(PwmPiezo_COMPARE1_LSB_PTR, compare);
    #endif
}


/*******************************************************************************
* Function Name: PwmPiezo_WriteCompare2
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
void PwmPiezo_WriteCompare2(uint16 compare) 
{
    #if(PwmPiezo_UsingFixedFunction)
        CY_SET_REG16(PwmPiezo_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG16(PwmPiezo_COMPARE2_LSB_PTR, compare);
    #endif
}
#endif /* UseOneCompareMode */


#if (PwmPiezo_DeadBandUsed)
/*******************************************************************************
* Function Name: PwmPiezo_WriteDeadTime
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
void PwmPiezo_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!PwmPiezo_DeadBand2_4)
        CY_SET_REG8(PwmPiezo_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        PwmPiezo_DEADBAND_COUNT &= ~PwmPiezo_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        PwmPiezo_DEADBAND_COUNT |= (deadtime << PwmPiezo_DEADBAND_COUNT_SHIFT) & PwmPiezo_DEADBAND_COUNT_MASK; 
    #endif
}


/*******************************************************************************
* Function Name: PwmPiezo_ReadDeadTime
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
uint8 PwmPiezo_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!PwmPiezo_DeadBand2_4)
        return (CY_GET_REG8(PwmPiezo_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((PwmPiezo_DEADBAND_COUNT & PwmPiezo_DEADBAND_COUNT_MASK) >> PwmPiezo_DEADBAND_COUNT_SHIFT);
    #endif
}
#endif /* DeadBandUsed */

