/*******************************************************************************
* File Name: PwmPiezo.h  
* Version 2.10
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

#if !defined(CY_PWM_PwmPiezo_H)
#define CY_PWM_PwmPiezo_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PwmPiezo_Resolution 16u
#define PwmPiezo_UsingFixedFunction 0u
#define PwmPiezo_DeadBandMode 0u
#define PwmPiezo_KillModeMinTime 0u
#define PwmPiezo_KillMode 0u
#define PwmPiezo_PWMMode 0u
#define PwmPiezo_PWMModeIsCenterAligned 0u
#define PwmPiezo_DeadBandUsed 0u
#define PwmPiezo_DeadBand2_4 0u
#if !defined(PwmPiezo_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define PwmPiezo_UseStatus 1u
#else
    #define PwmPiezo_UseStatus 0u
#endif
#if !defined(PwmPiezo_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define PwmPiezo_UseControl 1u
#else
    #define PwmPiezo_UseControl 0u
#endif
#define PwmPiezo_UseOneCompareMode 1u
#define PwmPiezo_MinimumKillTime 1u
#define PwmPiezo_EnableMode 0u

#define PwmPiezo_CompareMode1SW 0u
#define PwmPiezo_CompareMode2SW 0u

/* PSoC3 ES2 or early */
#define PwmPiezo_PSOC3_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES1 or early */
#define PwmPiezo_PSOC5_ES1   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* PSoC3 ES3 or later */
#define PwmPiezo_PSOC3_ES3   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                     (CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* PSoC5 ES2 or later */
#define PwmPiezo_PSOC5_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

/* Use Kill Mode Enumerated Types */
#define PwmPiezo__B_PWM__DISABLED 0
#define PwmPiezo__B_PWM__ASYNCHRONOUS 1
#define PwmPiezo__B_PWM__SINGLECYCLE 2
#define PwmPiezo__B_PWM__LATCHED 3
#define PwmPiezo__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PwmPiezo__B_PWM__DBMDISABLED 0
#define PwmPiezo__B_PWM__DBM_2_4_CLOCKS 1
#define PwmPiezo__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PwmPiezo__B_PWM__ONE_OUTPUT 0
#define PwmPiezo__B_PWM__TWO_OUTPUTS 1
#define PwmPiezo__B_PWM__DUAL_EDGE 2
#define PwmPiezo__B_PWM__CENTER_ALIGN 3
#define PwmPiezo__B_PWM__DITHER 5
#define PwmPiezo__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PwmPiezo__B_PWM__LESS_THAN 1
#define PwmPiezo__B_PWM__LESS_THAN_OR_EQUAL 2
#define PwmPiezo__B_PWM__GREATER_THAN 3
#define PwmPiezo__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PwmPiezo__B_PWM__EQUAL 0
#define PwmPiezo__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/

/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct PwmPiezo_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!PwmPiezo_UsingFixedFunction)
        #if (PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (PwmPiezo_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            #if(PwmPiezo_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif
            
            /* Backup for Deadband parameters */
            #if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS || PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(PwmPiezo_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
            
        #endif
        
        #if (PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!PwmPiezo_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif
            #if (PwmPiezo_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            
            /* Backup for Deadband parameters */
            #if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS || PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(PwmPiezo_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
        #endif
        
        
        /* Backup control register */
        #if(PwmPiezo_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif
        
    #endif 
   
}PwmPiezo_backupStruct;

/***************************************
*        Function Prototypes
 **************************************/
 
void    PwmPiezo_Start(void);
void    PwmPiezo_Stop(void) ;
#if (PwmPiezo_UseStatus || PwmPiezo_UsingFixedFunction)
    #define PwmPiezo_SetInterruptMode(interruptMode) CY_SET_REG8(PwmPiezo_STATUS_MASK_PTR, interruptMode)
    #define PwmPiezo_ReadStatusRegister() CY_GET_REG8(PwmPiezo_STATUS_PTR)
#endif
#define PwmPiezo_GetInterruptSource() PwmPiezo_ReadStatusRegister()
#if (PwmPiezo_UseControl)
    #define PwmPiezo_ReadControlRegister() CY_GET_REG8(PwmPiezo_CONTROL_PTR) 
    #define PwmPiezo_WriteControlRegister(control) CY_SET_REG8(PwmPiezo_CONTROL_PTR, control)
#endif
#if (PwmPiezo_UseOneCompareMode)
   #if (PwmPiezo_CompareMode1SW)
       void    PwmPiezo_SetCompareMode(uint8 comparemode) ;
   #endif
#else
    #if (PwmPiezo_CompareMode1SW)
        void    PwmPiezo_SetCompareMode1(uint8 comparemode) ;
    #endif
    #if (PwmPiezo_CompareMode2SW)
        void    PwmPiezo_SetCompareMode2(uint8 comparemode) ;
    #endif
#endif

#if (!PwmPiezo_UsingFixedFunction)
    uint16   PwmPiezo_ReadCounter(void) ;
    #define PwmPiezo_ReadCapture() CY_GET_REG16(PwmPiezo_CAPTURE_LSB_PTR)
    #if (PwmPiezo_UseStatus)
        void PwmPiezo_ClearFIFO(void) ;
    #endif
#endif

void    PwmPiezo_WriteCounter(uint16 counter) ;
void    PwmPiezo_WritePeriod(uint16 period) ;
#define PwmPiezo_ReadPeriod() CY_GET_REG16(PwmPiezo_PERIOD_LSB_PTR) 
#if (PwmPiezo_UseOneCompareMode)
    void    PwmPiezo_WriteCompare(uint16 compare) ;
    #define PwmPiezo_ReadCompare() CY_GET_REG16(PwmPiezo_COMPARE1_LSB_PTR) 
#else
    void    PwmPiezo_WriteCompare1(uint16 compare) ;
    #define PwmPiezo_ReadCompare1() CY_GET_REG16(PwmPiezo_COMPARE1_LSB_PTR) 
    void    PwmPiezo_WriteCompare2(uint16 compare) ;
    #define PwmPiezo_ReadCompare2() CY_GET_REG16(PwmPiezo_COMPARE2_LSB_PTR) 
#endif


#if (PwmPiezo_DeadBandUsed)
    void    PwmPiezo_WriteDeadTime(uint8 deadtime) ;
    uint8   PwmPiezo_ReadDeadTime(void) ;
#endif

#if ( PwmPiezo_KillModeMinTime)
    #define PwmPiezo_WriteKillTime(killtime) CY_SET_REG8(PwmPiezo_KILLMODEMINTIME_PTR, killtime) 
    #define PwmPiezo_ReadKillTime() CY_GET_REG8(PwmPiezo_KILLMODEMINTIME_PTR) 
#endif

void PwmPiezo_Init(void) ;
void PwmPiezo_Enable(void) ;
void PwmPiezo_Sleep(void);
void PwmPiezo_Wakeup(void) ;
void PwmPiezo_SaveConfig(void);
void PwmPiezo_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PwmPiezo_INIT_PERIOD_VALUE        197u
#define PwmPiezo_INIT_COMPARE_VALUE1      127u
#define PwmPiezo_INIT_COMPARE_VALUE2      128u
#define PwmPiezo_INIT_INTERRUPTS_MODE     ((0u << PwmPiezo_STATUS_TC_INT_EN_MASK_SHIFT) | (0 << PwmPiezo_STATUS_CMP2_INT_EN_MASK_SHIFT) | (0 << PwmPiezo_STATUS_CMP1_INT_EN_MASK_SHIFT ) | (0 << PwmPiezo_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define PwmPiezo_DEFAULT_COMPARE2_MODE    (3u << PwmPiezo_CTRL_CMPMODE2_SHIFT)
#define PwmPiezo_DEFAULT_COMPARE1_MODE    (3u << PwmPiezo_CTRL_CMPMODE1_SHIFT)
#define PwmPiezo_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (PwmPiezo_UsingFixedFunction)
   #define PwmPiezo_PERIOD_LSB          (*(reg16 *) PwmPiezo_PWMHW__PER0)
   #define PwmPiezo_PERIOD_LSB_PTR      ( (reg16 *) PwmPiezo_PWMHW__PER0)
   #define PwmPiezo_COMPARE1_LSB        (*(reg16 *) PwmPiezo_PWMHW__CNT_CMP0)
   #define PwmPiezo_COMPARE1_LSB_PTR    ( (reg16 *) PwmPiezo_PWMHW__CNT_CMP0)
   #define PwmPiezo_COMPARE2_LSB        0x00u
   #define PwmPiezo_COMPARE2_LSB_PTR    0x00u
   #define PwmPiezo_COUNTER_LSB         (*(reg16 *) PwmPiezo_PWMHW__CNT_CMP0)
   #define PwmPiezo_COUNTER_LSB_PTR     ( (reg16 *) PwmPiezo_PWMHW__CNT_CMP0)
   #define PwmPiezo_CAPTURE_LSB         (*(reg16 *) PwmPiezo_PWMHW__CAP0)
   #define PwmPiezo_CAPTURE_LSB_PTR     ( (reg16 *) PwmPiezo_PWMHW__CAP0)
   #define PwmPiezo_RT1                 (*(reg8 *)  PwmPiezo_PWMHW__RT1)
   #define PwmPiezo_RT1_PTR             ( (reg8 *)  PwmPiezo_PWMHW__RT1)
      
#else
   #if(PwmPiezo_PWMModeIsCenterAligned)
       #define PwmPiezo_PERIOD_LSB      (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PwmPiezo_PERIOD_LSB_PTR   ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #else
       #define PwmPiezo_PERIOD_LSB      (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #define PwmPiezo_PERIOD_LSB_PTR   ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__F0_REG)
   #endif
   #define PwmPiezo_COMPARE1_LSB    (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PwmPiezo_COMPARE1_LSB_PTR ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PwmPiezo_COMPARE2_LSB    (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PwmPiezo_COMPARE2_LSB_PTR ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PwmPiezo_COUNTERCAP_LSB   *(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PwmPiezo_COUNTERCAP_LSB_PTR ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PwmPiezo_COUNTER_LSB     (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PwmPiezo_COUNTER_LSB_PTR  ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PwmPiezo_CAPTURE_LSB     (*(reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PwmPiezo_CAPTURE_LSB_PTR  ((reg16 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PwmPiezo_AUX_CONTROLDP0      (*(reg8 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PwmPiezo_AUX_CONTROLDP0_PTR  ((reg8 *) PwmPiezo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #if (PwmPiezo_Resolution == 16)
       #define PwmPiezo_AUX_CONTROLDP1    (*(reg8 *) PwmPiezo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PwmPiezo_AUX_CONTROLDP1_PTR  ((reg8 *) PwmPiezo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
   #endif
#endif
   
#if(PwmPiezo_KillModeMinTime )
    #define PwmPiezo_KILLMODEMINTIME      (*(reg8 *) PwmPiezo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PwmPiezo_KILLMODEMINTIME_PTR   ((reg8 *) PwmPiezo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif

#if(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_256_CLOCKS)
    #define PwmPiezo_DEADBAND_COUNT        (*(reg8 *) PwmPiezo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PwmPiezo_DEADBAND_COUNT_PTR     ((reg8 *) PwmPiezo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PwmPiezo_DEADBAND_LSB_PTR       ((reg8 *) PwmPiezo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PwmPiezo_DEADBAND_LSB          (*(reg8 *) PwmPiezo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PwmPiezo_DeadBandMode == PwmPiezo__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PwmPiezo_UsingFixedFunction)
        #define PwmPiezo_DEADBAND_COUNT        (*(reg8 *) PwmPiezo_PWMHW__CFG0) 
        #define PwmPiezo_DEADBAND_COUNT_PTR     ((reg8 *) PwmPiezo_PWMHW__CFG0)
        #define PwmPiezo_DEADBAND_COUNT_MASK    (0x03u << PwmPiezo_DEADBAND_COUNT_SHIFT) 
        #define PwmPiezo_DEADBAND_COUNT_SHIFT   0x06u /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */ 
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PwmPiezo_DEADBAND_COUNT        (*(reg8 *) PwmPiezo_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PwmPiezo_DEADBAND_COUNT_PTR     ((reg8 *) PwmPiezo_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PwmPiezo_DEADBAND_COUNT_MASK    (0x03u << PwmPiezo_DEADBAND_COUNT_SHIFT) 
        #define PwmPiezo_DEADBAND_COUNT_SHIFT   0x00u /* As defined by the verilog implementation of the Control Register */
    #endif
#endif



#if (PwmPiezo_UsingFixedFunction)
    #define PwmPiezo_STATUS                (*(reg8 *) PwmPiezo_PWMHW__SR0)
    #define PwmPiezo_STATUS_PTR            ((reg8 *) PwmPiezo_PWMHW__SR0)
    #define PwmPiezo_STATUS_MASK           (*(reg8 *) PwmPiezo_PWMHW__SR0)
    #define PwmPiezo_STATUS_MASK_PTR       ((reg8 *) PwmPiezo_PWMHW__SR0)
    #define PwmPiezo_CONTROL               (*(reg8 *) PwmPiezo_PWMHW__CFG0)
    #define PwmPiezo_CONTROL_PTR           ((reg8 *) PwmPiezo_PWMHW__CFG0)    
    #define PwmPiezo_CONTROL2              (*(reg8 *) PwmPiezo_PWMHW__CFG1)    
    #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
        #define PwmPiezo_CONTROL3              (*(reg8 *) PwmPiezo_PWMHW__CFG2)
    #endif
    #define PwmPiezo_GLOBAL_ENABLE         (*(reg8 *) PwmPiezo_PWMHW__PM_ACT_CFG)
    #define PwmPiezo_GLOBAL_ENABLE_PTR       ( (reg8 *) PwmPiezo_PWMHW__PM_ACT_CFG)
    #define PwmPiezo_GLOBAL_STBY_ENABLE      (*(reg8 *) PwmPiezo_PWMHW__PM_STBY_CFG)
    #define PwmPiezo_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PwmPiezo_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/
    /* Fixed Function Block Chosen */
    #define PwmPiezo_BLOCK_EN_MASK          PwmPiezo_PWMHW__PM_ACT_MSK
    #define PwmPiezo_BLOCK_STBY_EN_MASK     PwmPiezo_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PwmPiezo_CTRL_ENABLE_SHIFT      0x00u
    
    #if(PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
        #define PwmPiezo_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif
    #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
        #define PwmPiezo_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif
    
    #define PwmPiezo_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define PwmPiezo_CFG0_MODE              0x02u   /*  Set to compare mode */
    //#define PwmPiezo_CFG0_ENABLE            0x01u   /* Enable the block to run */
    #define PwmPiezo_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PwmPiezo_CTRL_ENABLE            (0x01u << PwmPiezo_CTRL_ENABLE_SHIFT)
    #define PwmPiezo_CTRL_RESET             (0x01u << PwmPiezo_CTRL_RESET_SHIFT)
    #define PwmPiezo_CTRL_CMPMODE2_MASK     (0x07u << PwmPiezo_CTRL_CMPMODE2_SHIFT)
    #if(PwmPiezo_PSOC3_ES2 || PwmPiezo_PSOC5_ES1)
        #define PwmPiezo_CTRL_CMPMODE1_MASK     (0x07u << PwmPiezo_CTRL_CMPMODE1_SHIFT)
    #endif
    #if(PwmPiezo_PSOC3_ES3 || PwmPiezo_PSOC5_ES2)
        #define PwmPiezo_CTRL_CMPMODE1_MASK     (0x07u << PwmPiezo_CTRL_CMPMODE1_SHIFT)
    #endif
    
    /* Control2 Register Bit Masks */
    #define PwmPiezo_CTRL2_IRQ_SEL_SHIFT    0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PwmPiezo_CTRL2_IRQ_SEL          (0x01u << PwmPiezo_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PwmPiezo_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PwmPiezo_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PwmPiezo_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PwmPiezo_STATUS_TC_INT_EN_MASK_SHIFT            (PwmPiezo_STATUS_TC_SHIFT - 4)
    #define PwmPiezo_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PwmPiezo_STATUS_CMP1_INT_EN_MASK_SHIFT          (PwmPiezo_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define PwmPiezo_STATUS_TC              (0x01u << PwmPiezo_STATUS_TC_SHIFT)
    #define PwmPiezo_STATUS_CMP1            (0x01u << PwmPiezo_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define PwmPiezo_STATUS_TC_INT_EN_MASK              (PwmPiezo_STATUS_TC >> 4)
    #define PwmPiezo_STATUS_CMP1_INT_EN_MASK            (PwmPiezo_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define PwmPiezo_RT1_SHIFT              0x04u
    #define PwmPiezo_RT1_MASK               (0x03u << PwmPiezo_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define PwmPiezo_SYNC                   (0x03u << PwmPiezo_RT1_SHIFT)
    #define PwmPiezo_SYNCDSI_SHIFT          0x00u
    #define PwmPiezo_SYNCDSI_MASK           (0x0Fu << PwmPiezo_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PwmPiezo_SYNCDSI_EN             (0x0Fu << PwmPiezo_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PwmPiezo_STATUS                (*(reg8 *) PwmPiezo_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PwmPiezo_STATUS_PTR            ((reg8 *) PwmPiezo_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PwmPiezo_STATUS_MASK           (*(reg8 *) PwmPiezo_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PwmPiezo_STATUS_MASK_PTR       ((reg8 *) PwmPiezo_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PwmPiezo_STATUS_AUX_CTRL       (*(reg8 *) PwmPiezo_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PwmPiezo_CONTROL               (*(reg8 *) PwmPiezo_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    #define PwmPiezo_CONTROL_PTR           ((reg8 *) PwmPiezo_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/
    /* Control Register definitions */
    #define PwmPiezo_CTRL_ENABLE_SHIFT      0x07u
    #define PwmPiezo_CTRL_RESET_SHIFT       0x06u
    #define PwmPiezo_CTRL_CMPMODE2_SHIFT    0x03u
    #define PwmPiezo_CTRL_CMPMODE1_SHIFT    0x00u
    #define PwmPiezo_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PwmPiezo_CTRL_ENABLE            (0x01u << PwmPiezo_CTRL_ENABLE_SHIFT)
    #define PwmPiezo_CTRL_RESET             (0x01u << PwmPiezo_CTRL_RESET_SHIFT)
    #define PwmPiezo_CTRL_CMPMODE2_MASK     (0x07u << PwmPiezo_CTRL_CMPMODE2_SHIFT)
    #define PwmPiezo_CTRL_CMPMODE1_MASK     (0x07u << PwmPiezo_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PwmPiezo_STATUS_KILL_SHIFT          0x05u
    #define PwmPiezo_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PwmPiezo_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PwmPiezo_STATUS_TC_SHIFT            0x02u
    #define PwmPiezo_STATUS_CMP2_SHIFT          0x01u
    #define PwmPiezo_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PwmPiezo_STATUS_KILL_INT_EN_MASK_SHIFT          PwmPiezo_STATUS_KILL_SHIFT          
    #define PwmPiezo_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PwmPiezo_STATUS_FIFONEMPTY_SHIFT    
    #define PwmPiezo_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PwmPiezo_STATUS_FIFOFULL_SHIFT        
    #define PwmPiezo_STATUS_TC_INT_EN_MASK_SHIFT            PwmPiezo_STATUS_TC_SHIFT            
    #define PwmPiezo_STATUS_CMP2_INT_EN_MASK_SHIFT          PwmPiezo_STATUS_CMP2_SHIFT          
    #define PwmPiezo_STATUS_CMP1_INT_EN_MASK_SHIFT          PwmPiezo_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PwmPiezo_STATUS_KILL            (0x00u << PwmPiezo_STATUS_KILL_SHIFT )
    #define PwmPiezo_STATUS_FIFOFULL        (0x01u << PwmPiezo_STATUS_FIFOFULL_SHIFT)
    #define PwmPiezo_STATUS_FIFONEMPTY      (0x01u << PwmPiezo_STATUS_FIFONEMPTY_SHIFT)
    #define PwmPiezo_STATUS_TC              (0x01u << PwmPiezo_STATUS_TC_SHIFT)
    #define PwmPiezo_STATUS_CMP2            (0x01u << PwmPiezo_STATUS_CMP2_SHIFT) 
    #define PwmPiezo_STATUS_CMP1            (0x01u << PwmPiezo_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PwmPiezo_STATUS_KILL_INT_EN_MASK            PwmPiezo_STATUS_KILL
    #define PwmPiezo_STATUS_FIFOFULL_INT_EN_MASK        PwmPiezo_STATUS_FIFOFULL
    #define PwmPiezo_STATUS_FIFONEMPTY_INT_EN_MASK      PwmPiezo_STATUS_FIFONEMPTY
    #define PwmPiezo_STATUS_TC_INT_EN_MASK              PwmPiezo_STATUS_TC
    #define PwmPiezo_STATUS_CMP2_INT_EN_MASK            PwmPiezo_STATUS_CMP2
    #define PwmPiezo_STATUS_CMP1_INT_EN_MASK            PwmPiezo_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PwmPiezo_AUX_CTRL_FIFO0_CLR     0x01u
    #define PwmPiezo_AUX_CTRL_FIFO1_CLR     0x02u
    #define PwmPiezo_AUX_CTRL_FIFO0_LVL     0x04u
    #define PwmPiezo_AUX_CTRL_FIFO1_LVL     0x08u
    #define PwmPiezo_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PwmPiezo_UsingFixedFunction */

#endif  /* CY_PWM_PwmPiezo_H */
