/*******************************************************************************
* File Name: TimerMainTick.h
* Version 2.20
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_20_TimerMainTick_H)
#define CY_Timer_v2_20_TimerMainTick_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

/***************************************
*   Conditional Compilation Parameters
***************************************/

/* PSoC3 ES2 or early */
#define TimerMainTick_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES1 or early */
#define TimerMainTick_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define TimerMainTick_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES2 or later */
#define TimerMainTick_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


/**************************************
*           Parameter Defaults
**************************************/

#define TimerMainTick_Resolution                 8u
#define TimerMainTick_UsingFixedFunction         0u
#define TimerMainTick_UsingHWCaptureCounter      0u
#define TimerMainTick_SoftwareCaptureMode        0u
#define TimerMainTick_SoftwareTriggerMode        0u
#define TimerMainTick_UsingHWEnable              0u
#define TimerMainTick_EnableTriggerMode          0u
#define TimerMainTick_InterruptOnCaptureCount    0u
#define TimerMainTick_RunModeUsed                0u
#define TimerMainTick_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/
/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct TimerMainTick_backupStruct
{
    uint8 TimerEnableState;
    #if(!TimerMainTick_UsingFixedFunction)
        #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
            uint8 TimerUdb;                 /* Timer internal counter value      */
            uint8 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (TimerMainTick_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in PSoC3 ES2, PSoC5 ES1 */

        #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
            uint8 TimerUdb;
            uint8 InterruptMaskValue;
            #if (TimerMainTick_UsingHWCaptureCounter)
                uint8 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in PSoC3 ES3 or PSoC5 ES2 */
        #endif 

        #if (!TimerMainTick_ControlRegRemoved)
        uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}TimerMainTick_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TimerMainTick_Start(void);
void    TimerMainTick_Stop(void) ;

void    TimerMainTick_SetInterruptMode(uint8 interruptMode) ;
uint8   TimerMainTick_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TimerMainTick_GetInterruptSource() TimerMainTick_ReadStatusRegister()

#if(!TimerMainTick_ControlRegRemoved)
    uint8   TimerMainTick_ReadControlRegister(void) ;
    void    TimerMainTick_WriteControlRegister(uint8 control) \
        ;
#endif

uint8  TimerMainTick_ReadPeriod(void) ;
void    TimerMainTick_WritePeriod(uint8 period) \
    ;
uint8  TimerMainTick_ReadCounter(void) ;
void    TimerMainTick_WriteCounter(uint8 counter) \
    ;
uint8  TimerMainTick_ReadCapture(void) ;
void    TimerMainTick_SoftwareCapture(void) ;


#if(!TimerMainTick_UsingFixedFunction) /* UDB Prototypes */
    #if (TimerMainTick_SoftwareCaptureMode)
        void    TimerMainTick_SetCaptureMode(uint8 captureMode) ;
    #endif

    #if (TimerMainTick_SoftwareTriggerMode)
        void    TimerMainTick_SetTriggerMode(uint8 triggerMode) ;
    #endif
    #if (TimerMainTick_EnableTriggerMode)
        void    TimerMainTick_EnableTrigger(void) ;
        void    TimerMainTick_DisableTrigger(void) ;
    #endif

    #if(TimerMainTick_InterruptOnCaptureCount)
        #if(!TimerMainTick_ControlRegRemoved)
            void    TimerMainTick_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif
    #endif

    #if (TimerMainTick_UsingHWCaptureCounter)
        void    TimerMainTick_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   TimerMainTick_ReadCaptureCount(void) ;
    #endif

    void TimerMainTick_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TimerMainTick_Init(void)          ;
void TimerMainTick_Enable(void)        ;
void TimerMainTick_SaveConfig(void);
void TimerMainTick_RestoreConfig(void) ;
void TimerMainTick_Sleep(void);
void TimerMainTick_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TimerMainTick__B_TIMER__CM_NONE 0
#define TimerMainTick__B_TIMER__CM_RISINGEDGE 1
#define TimerMainTick__B_TIMER__CM_FALLINGEDGE 2
#define TimerMainTick__B_TIMER__CM_EITHEREDGE 3
#define TimerMainTick__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TimerMainTick__B_TIMER__TM_NONE 0x00u
#define TimerMainTick__B_TIMER__TM_RISINGEDGE 0x04u
#define TimerMainTick__B_TIMER__TM_FALLINGEDGE 0x08u
#define TimerMainTick__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TimerMainTick__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TimerMainTick_INIT_PERIOD             9u
#define TimerMainTick_INIT_CAPTURE_MODE       (0u << TimerMainTick_CTRL_CAP_MODE_SHIFT)
#define TimerMainTick_INIT_TRIGGER_MODE       (0u << TimerMainTick_CTRL_TRIG_MODE_SHIFT)
#if (TimerMainTick_UsingFixedFunction)
    #define TimerMainTick_INIT_INTERRUPT_MODE ((1u << TimerMainTick_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (0 << TimerMainTick_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define TimerMainTick_INIT_INTERRUPT_MODE ((1u << TimerMainTick_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (0 << TimerMainTick_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                  (0 << TimerMainTick_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif
#define TimerMainTick_INIT_CAPTURE_COUNT      (2u)
#define TimerMainTick_INIT_INT_CAPTURE_COUNT  ((1u - 1) << TimerMainTick_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (TimerMainTick_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TimerMainTick_STATUS         (*(reg8 *) TimerMainTick_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TimerMainTick_STATUS_MASK    (*(reg8 *) TimerMainTick_TimerHW__SR0 )
    #define TimerMainTick_CONTROL        (*(reg8 *) TimerMainTick_TimerHW__CFG0)
    #define TimerMainTick_CONTROL2       (*(reg8 *) TimerMainTick_TimerHW__CFG1)
    #define TimerMainTick_CONTROL2_PTR   ( (reg8 *) TimerMainTick_TimerHW__CFG1)
    #define TimerMainTick_RT1            (*(reg8 *) TimerMainTick_TimerHW__RT1)
    #define TimerMainTick_RT1_PTR        ( (reg8 *) TimerMainTick_TimerHW__RT1)

    #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
        #define TimerMainTick_CONTROL3       (*(reg8 *) TimerMainTick_TimerHW__CFG2)
        #define TimerMainTick_CONTROL3_PTR   ( (reg8 *) TimerMainTick_TimerHW__CFG2)
    #endif
    #define TimerMainTick_GLOBAL_ENABLE  (*(reg8 *) TimerMainTick_TimerHW__PM_ACT_CFG)
    #define TimerMainTick_GLOBAL_STBY_ENABLE  (*(reg8 *) TimerMainTick_TimerHW__PM_STBY_CFG)

    #define TimerMainTick_CAPTURE_LSB         (* (reg16 *) TimerMainTick_TimerHW__CAP0 )
    #define TimerMainTick_CAPTURE_LSB_PTR       ((reg16 *) TimerMainTick_TimerHW__CAP0 )
    #define TimerMainTick_PERIOD_LSB          (* (reg16 *) TimerMainTick_TimerHW__PER0 )
    #define TimerMainTick_PERIOD_LSB_PTR        ((reg16 *) TimerMainTick_TimerHW__PER0 )
    #define TimerMainTick_COUNTER_LSB         (* (reg16 *) TimerMainTick_TimerHW__CNT_CMP0 )
    #define TimerMainTick_COUNTER_LSB_PTR       ((reg16 *) TimerMainTick_TimerHW__CNT_CMP0 )

    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TimerMainTick_BLOCK_EN_MASK                     TimerMainTick_TimerHW__PM_ACT_MSK
    #define TimerMainTick_BLOCK_STBY_EN_MASK                TimerMainTick_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TimerMainTick_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TimerMainTick_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TimerMainTick_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TimerMainTick_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TimerMainTick_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TimerMainTick_CTRL_ENABLE                        (0x01u << TimerMainTick_CTRL_ENABLE_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TimerMainTick_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TimerMainTick_CTRL2_IRQ_SEL                      (0x01u << TimerMainTick_CTRL2_IRQ_SEL_SHIFT)

    #if (TimerMainTick_PSOC3_ES2 || TimerMainTick_PSOC5_ES1)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TimerMainTick_CTRL_MODE_SHIFT                     0x01u
        #define TimerMainTick_CTRL_MODE_MASK                     (0x07u << TimerMainTick_CTRL_MODE_SHIFT)
    #endif
    #if (TimerMainTick_PSOC3_ES3 || TimerMainTick_PSOC5_ES2)
        /* Control3 Register Bit Locations */
        #define TimerMainTick_CTRL_RCOD_SHIFT        0x02u
        #define TimerMainTick_CTRL_ENBL_SHIFT        0x00u
        #define TimerMainTick_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TimerMainTick_CTRL_RCOD_MASK  (0x03u << TimerMainTick_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define TimerMainTick_CTRL_ENBL_MASK  (0x80u << TimerMainTick_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define TimerMainTick_CTRL_MODE_MASK  (0x03u << TimerMainTick_CTRL_MODE_SHIFT) /* Run mode bit mask */

        #define TimerMainTick_CTRL_RCOD       (0x03u << TimerMainTick_CTRL_RCOD_SHIFT)
        #define TimerMainTick_CTRL_ENBL       (0x80u << TimerMainTick_CTRL_ENBL_SHIFT)
    #endif

    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define TimerMainTick_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TimerMainTick_RT1_MASK                        (0x03u << TimerMainTick_RT1_SHIFT)
    #define TimerMainTick_SYNC                            (0x03u << TimerMainTick_RT1_SHIFT)
    #define TimerMainTick_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TimerMainTick_SYNCDSI_MASK                    (0x0Fu << TimerMainTick_SYNCDSI_SHIFT)
    /* Sync all DSI inputs */
    #define TimerMainTick_SYNCDSI_EN                      (0x0Fu << TimerMainTick_SYNCDSI_SHIFT)

    #define TimerMainTick_CTRL_MODE_PULSEWIDTH            (0x01u << TimerMainTick_CTRL_MODE_SHIFT)
    #define TimerMainTick_CTRL_MODE_PERIOD                (0x02u << TimerMainTick_CTRL_MODE_SHIFT)
    #define TimerMainTick_CTRL_MODE_CONTINUOUS            (0x00u << TimerMainTick_CTRL_MODE_SHIFT)

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerMainTick_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerMainTick_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TimerMainTick_STATUS_TC_INT_MASK_SHIFT        (TimerMainTick_STATUS_TC_SHIFT - 4)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TimerMainTick_STATUS_CAPTURE_INT_MASK_SHIFT   (TimerMainTick_STATUS_CAPTURE_SHIFT - 4)

    /* Status Register Bit Masks */
    #define TimerMainTick_STATUS_TC                       (0x01u << TimerMainTick_STATUS_TC_SHIFT)
    #define TimerMainTick_STATUS_CAPTURE                  (0x01u << TimerMainTick_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TimerMainTick_STATUS_TC_INT_MASK              (0x01u << TimerMainTick_STATUS_TC_INT_MASK_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TimerMainTick_STATUS_CAPTURE_INT_MASK         (0x01u << TimerMainTick_STATUS_CAPTURE_INT_MASK_SHIFT)

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TimerMainTick_STATUS              (* (reg8 *) TimerMainTick_TimerUDB_nrstSts_stsreg__STATUS_REG )
    #define TimerMainTick_STATUS_MASK         (* (reg8 *) TimerMainTick_TimerUDB_nrstSts_stsreg__MASK_REG)
    #define TimerMainTick_STATUS_AUX_CTRL     (* (reg8 *) TimerMainTick_TimerUDB_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TimerMainTick_CONTROL             (* (reg8 *) TimerMainTick_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG )

    #define TimerMainTick_CAPTURE_LSB         (* (reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__F0_REG )
    #define TimerMainTick_CAPTURE_LSB_PTR       ((reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__F0_REG )
    #define TimerMainTick_PERIOD_LSB          (* (reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__D0_REG )
    #define TimerMainTick_PERIOD_LSB_PTR        ((reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__D0_REG )
    #define TimerMainTick_COUNTER_LSB         (* (reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__A0_REG )
    #define TimerMainTick_COUNTER_LSB_PTR       ((reg8 *) TimerMainTick_TimerUDB_sT8_timerdp_u0__A0_REG )

    #if (TimerMainTick_UsingHWCaptureCounter)
        #define TimerMainTick_CAP_COUNT              (*(reg8 *) TimerMainTick_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerMainTick_CAP_COUNT_PTR          ( (reg8 *) TimerMainTick_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TimerMainTick_CAPTURE_COUNT_CTRL     (*(reg8 *) TimerMainTick_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TimerMainTick_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TimerMainTick_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TimerMainTick_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TimerMainTick_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TimerMainTick_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TimerMainTick_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TimerMainTick_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TimerMainTick_CTRL_INTCNT_MASK               (0x03u << TimerMainTick_CTRL_INTCNT_SHIFT)
    #define TimerMainTick_CTRL_TRIG_MODE_MASK            (0x03u << TimerMainTick_CTRL_TRIG_MODE_SHIFT)
    #define TimerMainTick_CTRL_TRIG_EN                   (0x01u << TimerMainTick_CTRL_TRIG_EN_SHIFT)
    #define TimerMainTick_CTRL_CAP_MODE_MASK             (0x03u << TimerMainTick_CTRL_CAP_MODE_SHIFT)
    #define TimerMainTick_CTRL_ENABLE                    (0x01u << TimerMainTick_CTRL_ENABLE_SHIFT)

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TimerMainTick_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TimerMainTick_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TimerMainTick_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TimerMainTick_STATUS_TC_INT_MASK_SHIFT       TimerMainTick_STATUS_TC_SHIFT
    #define TimerMainTick_STATUS_CAPTURE_INT_MASK_SHIFT  TimerMainTick_STATUS_CAPTURE_SHIFT
    #define TimerMainTick_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TimerMainTick_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TimerMainTick_STATUS_FIFOFULL_INT_MASK_SHIFT TimerMainTick_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TimerMainTick_STATUS_TC                      (0x01u << TimerMainTick_STATUS_TC_SHIFT)
    /* Sticky Capture Event Bit-Mask */
    #define TimerMainTick_STATUS_CAPTURE                 (0x01u << TimerMainTick_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TimerMainTick_STATUS_TC_INT_MASK             (0x01u << TimerMainTick_STATUS_TC_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TimerMainTick_STATUS_CAPTURE_INT_MASK        (0x01u << TimerMainTick_STATUS_CAPTURE_SHIFT)
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TimerMainTick_STATUS_FIFOFULL                (0x01u << TimerMainTick_STATUS_FIFOFULL_SHIFT)
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TimerMainTick_STATUS_FIFONEMP                (0x01u << TimerMainTick_STATUS_FIFONEMP_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TimerMainTick_STATUS_FIFOFULL_INT_MASK       (0x01u << TimerMainTick_STATUS_FIFOFULL_SHIFT)

    #define TimerMainTick_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TimerMainTick_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TimerMainTick_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TimerMainTick_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TimerMainTick_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TimerMainTick_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_20_TimerMainTick_H */


/* [] END OF FILE */
