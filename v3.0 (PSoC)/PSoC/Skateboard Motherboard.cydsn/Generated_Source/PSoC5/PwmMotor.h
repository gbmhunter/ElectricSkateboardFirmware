/*******************************************************************************
* File Name: PwmMotor.h  
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

#if !defined(CY_PWM_PwmMotor_H)
#define CY_PWM_PwmMotor_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PwmMotor_Resolution 16u
#define PwmMotor_UsingFixedFunction 0u
#define PwmMotor_DeadBandMode 0u
#define PwmMotor_KillModeMinTime 0u
#define PwmMotor_KillMode 0u
#define PwmMotor_PWMMode 0u
#define PwmMotor_PWMModeIsCenterAligned 0u
#define PwmMotor_DeadBandUsed 0u
#define PwmMotor_DeadBand2_4 0u
#if !defined(PwmMotor_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define PwmMotor_UseStatus 1u
#else
    #define PwmMotor_UseStatus 0u
#endif
#if !defined(PwmMotor_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define PwmMotor_UseControl 1u
#else
    #define PwmMotor_UseControl 0u
#endif
#define PwmMotor_UseOneCompareMode 1u
#define PwmMotor_MinimumKillTime 1u
#define PwmMotor_EnableMode 0u

#define PwmMotor_CompareMode1SW 0u
#define PwmMotor_CompareMode2SW 0u

/* PSoC3 ES2 or early */
#define PwmMotor_PSOC3_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES1 or early */
#define PwmMotor_PSOC5_ES1   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* PSoC3 ES3 or later */
#define PwmMotor_PSOC3_ES3   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                     (CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* PSoC5 ES2 or later */
#define PwmMotor_PSOC5_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

/* Use Kill Mode Enumerated Types */
#define PwmMotor__B_PWM__DISABLED 0
#define PwmMotor__B_PWM__ASYNCHRONOUS 1
#define PwmMotor__B_PWM__SINGLECYCLE 2
#define PwmMotor__B_PWM__LATCHED 3
#define PwmMotor__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PwmMotor__B_PWM__DBMDISABLED 0
#define PwmMotor__B_PWM__DBM_2_4_CLOCKS 1
#define PwmMotor__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PwmMotor__B_PWM__ONE_OUTPUT 0
#define PwmMotor__B_PWM__TWO_OUTPUTS 1
#define PwmMotor__B_PWM__DUAL_EDGE 2
#define PwmMotor__B_PWM__CENTER_ALIGN 3
#define PwmMotor__B_PWM__DITHER 5
#define PwmMotor__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PwmMotor__B_PWM__LESS_THAN 1
#define PwmMotor__B_PWM__LESS_THAN_OR_EQUAL 2
#define PwmMotor__B_PWM__GREATER_THAN 3
#define PwmMotor__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PwmMotor__B_PWM__EQUAL 0
#define PwmMotor__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/

/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct PwmMotor_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!PwmMotor_UsingFixedFunction)
        #if (PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (PwmMotor_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            #if(PwmMotor_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif
            
            /* Backup for Deadband parameters */
            #if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS || PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(PwmMotor_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
            
        #endif
        
        #if (PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!PwmMotor_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif
            #if (PwmMotor_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            
            /* Backup for Deadband parameters */
            #if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS || PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(PwmMotor_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
        #endif
        
        
        /* Backup control register */
        #if(PwmMotor_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif
        
    #endif 
   
}PwmMotor_backupStruct;

/***************************************
*        Function Prototypes
 **************************************/
 
void    PwmMotor_Start(void);
void    PwmMotor_Stop(void) ;
#if (PwmMotor_UseStatus || PwmMotor_UsingFixedFunction)
    #define PwmMotor_SetInterruptMode(interruptMode) CY_SET_REG8(PwmMotor_STATUS_MASK_PTR, interruptMode)
    #define PwmMotor_ReadStatusRegister() CY_GET_REG8(PwmMotor_STATUS_PTR)
#endif
#define PwmMotor_GetInterruptSource() PwmMotor_ReadStatusRegister()
#if (PwmMotor_UseControl)
    #define PwmMotor_ReadControlRegister() CY_GET_REG8(PwmMotor_CONTROL_PTR) 
    #define PwmMotor_WriteControlRegister(control) CY_SET_REG8(PwmMotor_CONTROL_PTR, control)
#endif
#if (PwmMotor_UseOneCompareMode)
   #if (PwmMotor_CompareMode1SW)
       void    PwmMotor_SetCompareMode(uint8 comparemode) ;
   #endif
#else
    #if (PwmMotor_CompareMode1SW)
        void    PwmMotor_SetCompareMode1(uint8 comparemode) ;
    #endif
    #if (PwmMotor_CompareMode2SW)
        void    PwmMotor_SetCompareMode2(uint8 comparemode) ;
    #endif
#endif

#if (!PwmMotor_UsingFixedFunction)
    uint16   PwmMotor_ReadCounter(void) ;
    #define PwmMotor_ReadCapture() CY_GET_REG16(PwmMotor_CAPTURE_LSB_PTR)
    #if (PwmMotor_UseStatus)
        void PwmMotor_ClearFIFO(void) ;
    #endif
#endif

void    PwmMotor_WriteCounter(uint16 counter) ;
void    PwmMotor_WritePeriod(uint16 period) ;
#define PwmMotor_ReadPeriod() CY_GET_REG16(PwmMotor_PERIOD_LSB_PTR) 
#if (PwmMotor_UseOneCompareMode)
    void    PwmMotor_WriteCompare(uint16 compare) ;
    #define PwmMotor_ReadCompare() CY_GET_REG16(PwmMotor_COMPARE1_LSB_PTR) 
#else
    void    PwmMotor_WriteCompare1(uint16 compare) ;
    #define PwmMotor_ReadCompare1() CY_GET_REG16(PwmMotor_COMPARE1_LSB_PTR) 
    void    PwmMotor_WriteCompare2(uint16 compare) ;
    #define PwmMotor_ReadCompare2() CY_GET_REG16(PwmMotor_COMPARE2_LSB_PTR) 
#endif


#if (PwmMotor_DeadBandUsed)
    void    PwmMotor_WriteDeadTime(uint8 deadtime) ;
    uint8   PwmMotor_ReadDeadTime(void) ;
#endif

#if ( PwmMotor_KillModeMinTime)
    #define PwmMotor_WriteKillTime(killtime) CY_SET_REG8(PwmMotor_KILLMODEMINTIME_PTR, killtime) 
    #define PwmMotor_ReadKillTime() CY_GET_REG8(PwmMotor_KILLMODEMINTIME_PTR) 
#endif

void PwmMotor_Init(void) ;
void PwmMotor_Enable(void) ;
void PwmMotor_Sleep(void);
void PwmMotor_Wakeup(void) ;
void PwmMotor_SaveConfig(void);
void PwmMotor_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PwmMotor_INIT_PERIOD_VALUE        1091u
#define PwmMotor_INIT_COMPARE_VALUE1      0u
#define PwmMotor_INIT_COMPARE_VALUE2      63u
#define PwmMotor_INIT_INTERRUPTS_MODE     ((0u << PwmMotor_STATUS_TC_INT_EN_MASK_SHIFT) | (0 << PwmMotor_STATUS_CMP2_INT_EN_MASK_SHIFT) | (0 << PwmMotor_STATUS_CMP1_INT_EN_MASK_SHIFT ) | (0 << PwmMotor_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define PwmMotor_DEFAULT_COMPARE2_MODE    (1u << PwmMotor_CTRL_CMPMODE2_SHIFT)
#define PwmMotor_DEFAULT_COMPARE1_MODE    (1u << PwmMotor_CTRL_CMPMODE1_SHIFT)
#define PwmMotor_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (PwmMotor_UsingFixedFunction)
   #define PwmMotor_PERIOD_LSB          (*(reg16 *) PwmMotor_PWMHW__PER0)
   #define PwmMotor_PERIOD_LSB_PTR      ( (reg16 *) PwmMotor_PWMHW__PER0)
   #define PwmMotor_COMPARE1_LSB        (*(reg16 *) PwmMotor_PWMHW__CNT_CMP0)
   #define PwmMotor_COMPARE1_LSB_PTR    ( (reg16 *) PwmMotor_PWMHW__CNT_CMP0)
   #define PwmMotor_COMPARE2_LSB        0x00u
   #define PwmMotor_COMPARE2_LSB_PTR    0x00u
   #define PwmMotor_COUNTER_LSB         (*(reg16 *) PwmMotor_PWMHW__CNT_CMP0)
   #define PwmMotor_COUNTER_LSB_PTR     ( (reg16 *) PwmMotor_PWMHW__CNT_CMP0)
   #define PwmMotor_CAPTURE_LSB         (*(reg16 *) PwmMotor_PWMHW__CAP0)
   #define PwmMotor_CAPTURE_LSB_PTR     ( (reg16 *) PwmMotor_PWMHW__CAP0)
   #define PwmMotor_RT1                 (*(reg8 *)  PwmMotor_PWMHW__RT1)
   #define PwmMotor_RT1_PTR             ( (reg8 *)  PwmMotor_PWMHW__RT1)
      
#else
   #if(PwmMotor_PWMModeIsCenterAligned)
       #define PwmMotor_PERIOD_LSB      (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PwmMotor_PERIOD_LSB_PTR   ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #else
       #define PwmMotor_PERIOD_LSB      (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #define PwmMotor_PERIOD_LSB_PTR   ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__F0_REG)
   #endif
   #define PwmMotor_COMPARE1_LSB    (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PwmMotor_COMPARE1_LSB_PTR ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PwmMotor_COMPARE2_LSB    (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PwmMotor_COMPARE2_LSB_PTR ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PwmMotor_COUNTERCAP_LSB   *(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PwmMotor_COUNTERCAP_LSB_PTR ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PwmMotor_COUNTER_LSB     (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PwmMotor_COUNTER_LSB_PTR  ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PwmMotor_CAPTURE_LSB     (*(reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PwmMotor_CAPTURE_LSB_PTR  ((reg16 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PwmMotor_AUX_CONTROLDP0      (*(reg8 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PwmMotor_AUX_CONTROLDP0_PTR  ((reg8 *) PwmMotor_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #if (PwmMotor_Resolution == 16)
       #define PwmMotor_AUX_CONTROLDP1    (*(reg8 *) PwmMotor_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PwmMotor_AUX_CONTROLDP1_PTR  ((reg8 *) PwmMotor_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
   #endif
#endif
   
#if(PwmMotor_KillModeMinTime )
    #define PwmMotor_KILLMODEMINTIME      (*(reg8 *) PwmMotor_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PwmMotor_KILLMODEMINTIME_PTR   ((reg8 *) PwmMotor_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif

#if(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_256_CLOCKS)
    #define PwmMotor_DEADBAND_COUNT        (*(reg8 *) PwmMotor_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PwmMotor_DEADBAND_COUNT_PTR     ((reg8 *) PwmMotor_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PwmMotor_DEADBAND_LSB_PTR       ((reg8 *) PwmMotor_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PwmMotor_DEADBAND_LSB          (*(reg8 *) PwmMotor_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PwmMotor_DeadBandMode == PwmMotor__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PwmMotor_UsingFixedFunction)
        #define PwmMotor_DEADBAND_COUNT        (*(reg8 *) PwmMotor_PWMHW__CFG0) 
        #define PwmMotor_DEADBAND_COUNT_PTR     ((reg8 *) PwmMotor_PWMHW__CFG0)
        #define PwmMotor_DEADBAND_COUNT_MASK    (0x03u << PwmMotor_DEADBAND_COUNT_SHIFT) 
        #define PwmMotor_DEADBAND_COUNT_SHIFT   0x06u /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */ 
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PwmMotor_DEADBAND_COUNT        (*(reg8 *) PwmMotor_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PwmMotor_DEADBAND_COUNT_PTR     ((reg8 *) PwmMotor_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PwmMotor_DEADBAND_COUNT_MASK    (0x03u << PwmMotor_DEADBAND_COUNT_SHIFT) 
        #define PwmMotor_DEADBAND_COUNT_SHIFT   0x00u /* As defined by the verilog implementation of the Control Register */
    #endif
#endif



#if (PwmMotor_UsingFixedFunction)
    #define PwmMotor_STATUS                (*(reg8 *) PwmMotor_PWMHW__SR0)
    #define PwmMotor_STATUS_PTR            ((reg8 *) PwmMotor_PWMHW__SR0)
    #define PwmMotor_STATUS_MASK           (*(reg8 *) PwmMotor_PWMHW__SR0)
    #define PwmMotor_STATUS_MASK_PTR       ((reg8 *) PwmMotor_PWMHW__SR0)
    #define PwmMotor_CONTROL               (*(reg8 *) PwmMotor_PWMHW__CFG0)
    #define PwmMotor_CONTROL_PTR           ((reg8 *) PwmMotor_PWMHW__CFG0)    
    #define PwmMotor_CONTROL2              (*(reg8 *) PwmMotor_PWMHW__CFG1)    
    #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
        #define PwmMotor_CONTROL3              (*(reg8 *) PwmMotor_PWMHW__CFG2)
    #endif
    #define PwmMotor_GLOBAL_ENABLE         (*(reg8 *) PwmMotor_PWMHW__PM_ACT_CFG)
    #define PwmMotor_GLOBAL_ENABLE_PTR       ( (reg8 *) PwmMotor_PWMHW__PM_ACT_CFG)
    #define PwmMotor_GLOBAL_STBY_ENABLE      (*(reg8 *) PwmMotor_PWMHW__PM_STBY_CFG)
    #define PwmMotor_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PwmMotor_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/
    /* Fixed Function Block Chosen */
    #define PwmMotor_BLOCK_EN_MASK          PwmMotor_PWMHW__PM_ACT_MSK
    #define PwmMotor_BLOCK_STBY_EN_MASK     PwmMotor_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PwmMotor_CTRL_ENABLE_SHIFT      0x00u
    
    #if(PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
        #define PwmMotor_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif
    #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
        #define PwmMotor_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif
    
    #define PwmMotor_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define PwmMotor_CFG0_MODE              0x02u   /*  Set to compare mode */
    //#define PwmMotor_CFG0_ENABLE            0x01u   /* Enable the block to run */
    #define PwmMotor_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PwmMotor_CTRL_ENABLE            (0x01u << PwmMotor_CTRL_ENABLE_SHIFT)
    #define PwmMotor_CTRL_RESET             (0x01u << PwmMotor_CTRL_RESET_SHIFT)
    #define PwmMotor_CTRL_CMPMODE2_MASK     (0x07u << PwmMotor_CTRL_CMPMODE2_SHIFT)
    #if(PwmMotor_PSOC3_ES2 || PwmMotor_PSOC5_ES1)
        #define PwmMotor_CTRL_CMPMODE1_MASK     (0x07u << PwmMotor_CTRL_CMPMODE1_SHIFT)
    #endif
    #if(PwmMotor_PSOC3_ES3 || PwmMotor_PSOC5_ES2)
        #define PwmMotor_CTRL_CMPMODE1_MASK     (0x07u << PwmMotor_CTRL_CMPMODE1_SHIFT)
    #endif
    
    /* Control2 Register Bit Masks */
    #define PwmMotor_CTRL2_IRQ_SEL_SHIFT    0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PwmMotor_CTRL2_IRQ_SEL          (0x01u << PwmMotor_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PwmMotor_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PwmMotor_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PwmMotor_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PwmMotor_STATUS_TC_INT_EN_MASK_SHIFT            (PwmMotor_STATUS_TC_SHIFT - 4)
    #define PwmMotor_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PwmMotor_STATUS_CMP1_INT_EN_MASK_SHIFT          (PwmMotor_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define PwmMotor_STATUS_TC              (0x01u << PwmMotor_STATUS_TC_SHIFT)
    #define PwmMotor_STATUS_CMP1            (0x01u << PwmMotor_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define PwmMotor_STATUS_TC_INT_EN_MASK              (PwmMotor_STATUS_TC >> 4)
    #define PwmMotor_STATUS_CMP1_INT_EN_MASK            (PwmMotor_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define PwmMotor_RT1_SHIFT              0x04u
    #define PwmMotor_RT1_MASK               (0x03u << PwmMotor_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define PwmMotor_SYNC                   (0x03u << PwmMotor_RT1_SHIFT)
    #define PwmMotor_SYNCDSI_SHIFT          0x00u
    #define PwmMotor_SYNCDSI_MASK           (0x0Fu << PwmMotor_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PwmMotor_SYNCDSI_EN             (0x0Fu << PwmMotor_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PwmMotor_STATUS                (*(reg8 *) PwmMotor_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PwmMotor_STATUS_PTR            ((reg8 *) PwmMotor_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PwmMotor_STATUS_MASK           (*(reg8 *) PwmMotor_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PwmMotor_STATUS_MASK_PTR       ((reg8 *) PwmMotor_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PwmMotor_STATUS_AUX_CTRL       (*(reg8 *) PwmMotor_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PwmMotor_CONTROL               (*(reg8 *) PwmMotor_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    #define PwmMotor_CONTROL_PTR           ((reg8 *) PwmMotor_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/
    /* Control Register definitions */
    #define PwmMotor_CTRL_ENABLE_SHIFT      0x07u
    #define PwmMotor_CTRL_RESET_SHIFT       0x06u
    #define PwmMotor_CTRL_CMPMODE2_SHIFT    0x03u
    #define PwmMotor_CTRL_CMPMODE1_SHIFT    0x00u
    #define PwmMotor_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PwmMotor_CTRL_ENABLE            (0x01u << PwmMotor_CTRL_ENABLE_SHIFT)
    #define PwmMotor_CTRL_RESET             (0x01u << PwmMotor_CTRL_RESET_SHIFT)
    #define PwmMotor_CTRL_CMPMODE2_MASK     (0x07u << PwmMotor_CTRL_CMPMODE2_SHIFT)
    #define PwmMotor_CTRL_CMPMODE1_MASK     (0x07u << PwmMotor_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PwmMotor_STATUS_KILL_SHIFT          0x05u
    #define PwmMotor_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PwmMotor_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PwmMotor_STATUS_TC_SHIFT            0x02u
    #define PwmMotor_STATUS_CMP2_SHIFT          0x01u
    #define PwmMotor_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PwmMotor_STATUS_KILL_INT_EN_MASK_SHIFT          PwmMotor_STATUS_KILL_SHIFT          
    #define PwmMotor_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PwmMotor_STATUS_FIFONEMPTY_SHIFT    
    #define PwmMotor_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PwmMotor_STATUS_FIFOFULL_SHIFT        
    #define PwmMotor_STATUS_TC_INT_EN_MASK_SHIFT            PwmMotor_STATUS_TC_SHIFT            
    #define PwmMotor_STATUS_CMP2_INT_EN_MASK_SHIFT          PwmMotor_STATUS_CMP2_SHIFT          
    #define PwmMotor_STATUS_CMP1_INT_EN_MASK_SHIFT          PwmMotor_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PwmMotor_STATUS_KILL            (0x00u << PwmMotor_STATUS_KILL_SHIFT )
    #define PwmMotor_STATUS_FIFOFULL        (0x01u << PwmMotor_STATUS_FIFOFULL_SHIFT)
    #define PwmMotor_STATUS_FIFONEMPTY      (0x01u << PwmMotor_STATUS_FIFONEMPTY_SHIFT)
    #define PwmMotor_STATUS_TC              (0x01u << PwmMotor_STATUS_TC_SHIFT)
    #define PwmMotor_STATUS_CMP2            (0x01u << PwmMotor_STATUS_CMP2_SHIFT) 
    #define PwmMotor_STATUS_CMP1            (0x01u << PwmMotor_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PwmMotor_STATUS_KILL_INT_EN_MASK            PwmMotor_STATUS_KILL
    #define PwmMotor_STATUS_FIFOFULL_INT_EN_MASK        PwmMotor_STATUS_FIFOFULL
    #define PwmMotor_STATUS_FIFONEMPTY_INT_EN_MASK      PwmMotor_STATUS_FIFONEMPTY
    #define PwmMotor_STATUS_TC_INT_EN_MASK              PwmMotor_STATUS_TC
    #define PwmMotor_STATUS_CMP2_INT_EN_MASK            PwmMotor_STATUS_CMP2
    #define PwmMotor_STATUS_CMP1_INT_EN_MASK            PwmMotor_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PwmMotor_AUX_CTRL_FIFO0_CLR     0x01u
    #define PwmMotor_AUX_CTRL_FIFO1_CLR     0x02u
    #define PwmMotor_AUX_CTRL_FIFO0_LVL     0x04u
    #define PwmMotor_AUX_CTRL_FIFO1_LVL     0x08u
    #define PwmMotor_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PwmMotor_UsingFixedFunction */

#endif  /* CY_PWM_PwmMotor_H */
