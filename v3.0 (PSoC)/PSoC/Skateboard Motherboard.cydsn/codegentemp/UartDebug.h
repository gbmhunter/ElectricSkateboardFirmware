/*******************************************************************************
* File Name: UartDebug.h
* Version 2.10
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
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

#if !defined(CY_UART_UartDebug_H)
#define CY_UART_UartDebug_H


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UartDebug_RX_ENABLED                     (1u)
#define UartDebug_TX_ENABLED                     (1u)
#define UartDebug_HD_ENABLED                     (0u)
#define UartDebug_RX_INTERRUPT_ENABLED           (1u)
#define UartDebug_TX_INTERRUPT_ENABLED           (1u)
#define UartDebug_INTERNAL_CLOCK_USED            (1u)
#define UartDebug_RXHW_ADDRESS_ENABLED           (0u)
#define UartDebug_OVER_SAMPLE_COUNT              (8u)
#define UartDebug_PARITY_TYPE                    (0u)
#define UartDebug_PARITY_TYPE_SW                 (0u)
#define UartDebug_BREAK_DETECT                   (0u)
#define UartDebug_BREAK_BITS_TX                  (13u)
#define UartDebug_BREAK_BITS_RX                  (13u)
#define UartDebug_TXCLKGEN_DP                    (1u)
#define UartDebug_USE23POLLING                   (1u)
#define UartDebug_FLOW_CONTROL                   (0u)

/* Check to see if required defines such as CY_PSOC3 and CY_PSOC5 are available */
/* They are defined starting with cy_boot v2.30 */
#ifndef CY_PSOC3
    #error Component UART_v2_10 requires cy_boot v2.30 or later
#endif /* End CY_PSOC3 */

#if(CY_PSOC3_ES2 && (UartDebug_RX_INTERRUPT_ENABLED || UartDebug_TX_INTERRUPT_ENABLED))
    #include <intrins.h>
    #define UartDebug_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
#endif /* End CY_PSOC3_ES2 */

#ifdef UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartDebug_CONTROL_REG_REMOVED            (0u)
#else
    #define UartDebug_CONTROL_REG_REMOVED            (1u)
#endif /* End UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _UartDebug_backupStruct
{
    uint8 enableState;

    #if(UartDebug_CONTROL_REG_REMOVED == 0u)
        uint8 cr;            
    #endif /* End UartDebug_CONTROL_REG_REMOVED */    
    #if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 rx_mask;
            #if (UartDebug_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */
        #endif /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif  /* End (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED)*/

    #if(UartDebug_TX_ENABLED)
        #if(UartDebug_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
                uint8 tx_clk_compl;
            #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
        #else
            uint8 tx_period;
        #endif /*End UartDebug_TXCLKGEN_DP */
        #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 tx_mask;
        #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif /*End UartDebug_TX_ENABLED */
} UartDebug_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UartDebug_Start(void) ;
void UartDebug_Stop(void) ;
uint8 UartDebug_ReadControlRegister(void) ;
void UartDebug_WriteControlRegister(uint8 control) ;

void UartDebug_Init(void) ;
void UartDebug_Enable(void) ;
void UartDebug_SaveConfig(void) ;
void UartDebug_RestoreConfig(void) ;
void UartDebug_Sleep(void) ;
void UartDebug_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )

    #if(UartDebug_RX_INTERRUPT_ENABLED)
        void  UartDebug_EnableRxInt(void) ;
        void  UartDebug_DisableRxInt(void) ;
        CY_ISR_PROTO(UartDebug_RXISR);
    #endif /* UartDebug_RX_INTERRUPT_ENABLED */

    void UartDebug_SetRxAddressMode(uint8 addressMode) 
                                                           ;
    void UartDebug_SetRxAddress1(uint8 address) ;
    void UartDebug_SetRxAddress2(uint8 address) ;

    void  UartDebug_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UartDebug_ReadRxData(void) ;
    uint8 UartDebug_ReadRxStatus(void) ;
    uint8 UartDebug_GetChar(void) ;
    uint16 UartDebug_GetByte(void) ;
    uint8 UartDebug_GetRxBufferSize(void)  
                                                            ;
    void UartDebug_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UartDebug_GetRxInterruptSource   UartDebug_ReadRxStatus

#endif /* End (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */

/* Only if TX is enabled */
#if(UartDebug_TX_ENABLED || UartDebug_HD_ENABLED)

    #if(UartDebug_TX_INTERRUPT_ENABLED)
        void UartDebug_EnableTxInt(void) ;
        void UartDebug_DisableTxInt(void) ;
        CY_ISR_PROTO(UartDebug_TXISR);
    #endif /* UartDebug_TX_INTERRUPT_ENABLED */

    void UartDebug_SetTxInterruptMode(uint8 intSrc) ;
    void UartDebug_WriteTxData(uint8 txDataByte) ;
    uint8 UartDebug_ReadTxStatus(void) ;
    void UartDebug_PutChar(uint8 txDataByte) ;
    void UartDebug_PutString(char* string) ;
    void UartDebug_PutArray(uint8* string, uint8 byteCount)
                                                            ;
    void UartDebug_PutCRLF(uint8 txDataByte) ;
    void UartDebug_ClearTxBuffer(void) ;
    void UartDebug_SetTxAddressMode(uint8 addressMode) ;
    void UartDebug_SendBreak(uint8 retMode) ;
    uint8 UartDebug_GetTxBufferSize(void) 
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UartDebug_PutStringConst         UartDebug_PutString
    #define UartDebug_PutArrayConst          UartDebug_PutArray
    #define UartDebug_GetTxInterruptSource   UartDebug_ReadTxStatus
    
#endif /* End UartDebug_TX_ENABLED || UartDebug_HD_ENABLED */

#if(UartDebug_HD_ENABLED)
    void UartDebug_LoadRxConfig(void) ;
    void UartDebug_LoadTxConfig(void) ;
#endif /* End UartDebug_HD_ENABLED */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UartDebug_SET_SPACE                              (0x00u)
#define UartDebug_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (UartDebug_TX_ENABLED) || (UartDebug_HD_ENABLED) )
    #if(UartDebug_TX_INTERRUPT_ENABLED)
        #define UartDebug_TX_VECT_NUM                UartDebug_TXInternalInterrupt__INTC_NUMBER
        #define UartDebug_TX_PRIOR_NUM               UartDebug_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UartDebug_TX_INTERRUPT_ENABLED */
    #if(UartDebug_TX_ENABLED) 
        #define UartDebug_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UartDebug_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UartDebug_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define UartDebug_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UartDebug_TX_ENABLED */
    #if(UartDebug_HD_ENABLED) 
        #define UartDebug_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UartDebug_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UartDebug_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define UartDebug_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UartDebug_HD_ENABLED */
    #define UartDebug_TX_STS_COMPLETE                (0x01u << UartDebug_TX_STS_COMPLETE_SHIFT)
    #define UartDebug_TX_STS_FIFO_EMPTY              (0x01u << UartDebug_TX_STS_FIFO_EMPTY_SHIFT)
    #define UartDebug_TX_STS_FIFO_FULL               (0x01u << UartDebug_TX_STS_FIFO_FULL_SHIFT)
    #define UartDebug_TX_STS_FIFO_NOT_FULL           (0x01u << UartDebug_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UartDebug_TX_ENABLED) || (UartDebug_HD_ENABLED)*/

#if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
    #if(UartDebug_RX_INTERRUPT_ENABLED)
        #define UartDebug_RX_VECT_NUM                UartDebug_RXInternalInterrupt__INTC_NUMBER
        #define UartDebug_RX_PRIOR_NUM               UartDebug_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UartDebug_RX_INTERRUPT_ENABLED */
    #define UartDebug_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UartDebug_RX_STS_BREAK_SHIFT             (0x01u)
    #define UartDebug_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UartDebug_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UartDebug_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UartDebug_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UartDebug_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UartDebug_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UartDebug_RX_STS_MRKSPC                  (0x01u << UartDebug_RX_STS_MRKSPC_SHIFT)
    #define UartDebug_RX_STS_BREAK                   (0x01u << UartDebug_RX_STS_BREAK_SHIFT)
    #define UartDebug_RX_STS_PAR_ERROR               (0x01u << UartDebug_RX_STS_PAR_ERROR_SHIFT)
    #define UartDebug_RX_STS_STOP_ERROR              (0x01u << UartDebug_RX_STS_STOP_ERROR_SHIFT)
    #define UartDebug_RX_STS_OVERRUN                 (0x01u << UartDebug_RX_STS_OVERRUN_SHIFT)
    #define UartDebug_RX_STS_FIFO_NOTEMPTY           (0x01u << UartDebug_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UartDebug_RX_STS_ADDR_MATCH              (0x01u << UartDebug_RX_STS_ADDR_MATCH_SHIFT)
    #define UartDebug_RX_STS_SOFT_BUFF_OVER          (0x01u << UartDebug_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UartDebug_RX_HW_MASK                     (0x7Fu)
#endif /* End (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */

/* Control Register definitions */
#define UartDebug_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UartDebug_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UartDebug_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UartDebug_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UartDebug_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UartDebug_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UartDebug_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UartDebug_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UartDebug_CTRL_HD_SEND                       (0x01u << UartDebug_CTRL_HD_SEND_SHIFT)
#define UartDebug_CTRL_HD_SEND_BREAK                 (0x01u << UartDebug_CTRL_HD_SEND_BREAK_SHIFT)
#define UartDebug_CTRL_MARK                          (0x01u << UartDebug_CTRL_MARK_SHIFT)
#define UartDebug_CTRL_PARITY_TYPE_MASK              (0x03u << UartDebug_CTRL_PARITY_TYPE0_SHIFT)
#define UartDebug_CTRL_RXADDR_MODE_MASK              (0x07u << UartDebug_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UartDebug_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UartDebug_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UartDebug_SEND_BREAK                         (0x00u)
#define UartDebug_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UartDebug_REINIT                             (0x02u)
#define UartDebug_SEND_WAIT_REINIT                   (0x03u)

#define UartDebug_OVER_SAMPLE_8                      (8u)
#define UartDebug_OVER_SAMPLE_16                     (16u)

#define UartDebug_BIT_CENTER                         (UartDebug_OVER_SAMPLE_COUNT - 1u)

#define UartDebug_FIFO_LENGTH                        (4u)
#define UartDebug_NUMBER_OF_START_BIT                (1u)

/* 8X always for count7 implementation*/
#define UartDebug_TXBITCTR_BREAKBITS8X   (UartDebug_BREAK_BITS_TX * UartDebug_OVER_SAMPLE_8 - 1u)
/* 8X or 16X for DP implementation*/
#define UartDebug_TXBITCTR_BREAKBITS   (UartDebug_BREAK_BITS_TX * UartDebug_OVER_SAMPLE_COUNT - 1u)

#if (UartDebug_OVER_SAMPLE_COUNT == UartDebug_OVER_SAMPLE_8)
    #define UartDebug_HD_TXBITCTR_INIT   ((UartDebug_BREAK_BITS_TX + \
        UartDebug_NUMBER_OF_START_BIT) * UartDebug_OVER_SAMPLE_COUNT - 1u)
    /* This parameter is increased on the 1 in 2 out of 3 mode to sample voting in the middle */
    #define UartDebug_HD_RXBITCTR_INIT   ((UartDebug_BREAK_BITS_RX + \
    UartDebug_NUMBER_OF_START_BIT) * UartDebug_OVER_SAMPLE_COUNT - 1u + \
    (UartDebug_OVER_SAMPLE_COUNT / 2u) + (UartDebug_USE23POLLING * 2u) - 1u)
#else /* UartDebug_OVER_SAMPLE_COUNT == UartDebug_OVER_SAMPLE_16 */
    #define UartDebug_HD_TXBITCTR_INIT   (8u * UartDebug_OVER_SAMPLE_COUNT - 1u)
    #define UartDebug_HD_RXBITCTR_INIT   (7u * UartDebug_OVER_SAMPLE_COUNT - 1u  +  \
       (UartDebug_OVER_SAMPLE_COUNT / 2u) + (UartDebug_USE23POLLING * 2u) - 1u)
#endif /* End UartDebug_OVER_SAMPLE_COUNT */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UartDebug__B_UART__AM_SW_BYTE_BYTE 1
#define UartDebug__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UartDebug__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UartDebug__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UartDebug__B_UART__AM_NONE 0

#define UartDebug__B_UART__NONE_REVB 0
#define UartDebug__B_UART__EVEN_REVB 1
#define UartDebug__B_UART__ODD_REVB 2
#define UartDebug__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

#define UartDebug_TXBUFFERSIZE           (50u)
#define UartDebug_RXBUFFERSIZE           (50u)
/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UartDebug_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UartDebug_NUMBER_OF_STOP_BITS    (1u)

#if (UartDebug_RXHW_ADDRESS_ENABLED)
    #define UartDebug_RXADDRESSMODE      (0u)
    #define UartDebug_RXHWADDRESS1       (0u)
    #define UartDebug_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define UartDebug_RXAddressMode      UartDebug_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define UartDebug_INIT_RX_INTERRUPTS_MASK \
                                          (1 << UartDebug_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UartDebug_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UartDebug_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UartDebug_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UartDebug_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UartDebug_RX_STS_BREAK_SHIFT) \
                                        | (0 << UartDebug_RX_STS_OVERRUN_SHIFT)

#define UartDebug_INIT_TX_INTERRUPTS_MASK \
                                          (0 << UartDebug_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << UartDebug_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UartDebug_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UartDebug_TX_STS_FIFO_NOT_FULL_SHIFT)


/***************************************
*              Registers
***************************************/

#ifdef UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartDebug_CONTROL_REG \
                            (* (reg8 *) UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
    #define UartDebug_CONTROL_PTR \
                            (  (reg8 *) UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(UartDebug_TX_ENABLED)
    #define UartDebug_TXDATA_REG          (* (reg8 *) UartDebug_BUART_sTX_TxShifter_u0__F0_REG)
    #define UartDebug_TXDATA_PTR          (  (reg8 *) UartDebug_BUART_sTX_TxShifter_u0__F0_REG)
    #define UartDebug_TXDATA_AUX_CTL_REG  (* (reg8 *) UartDebug_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UartDebug_TXDATA_AUX_CTL_PTR  (  (reg8 *) UartDebug_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UartDebug_TXSTATUS_REG        (* (reg8 *) UartDebug_BUART_sTX_TxSts__STATUS_REG)
    #define UartDebug_TXSTATUS_PTR        (  (reg8 *) UartDebug_BUART_sTX_TxSts__STATUS_REG)
    #define UartDebug_TXSTATUS_MASK_REG   (* (reg8 *) UartDebug_BUART_sTX_TxSts__MASK_REG)
    #define UartDebug_TXSTATUS_MASK_PTR   (  (reg8 *) UartDebug_BUART_sTX_TxSts__MASK_REG)
    #define UartDebug_TXSTATUS_ACTL_REG   (* (reg8 *) UartDebug_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UartDebug_TXSTATUS_ACTL_PTR   (  (reg8 *) UartDebug_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UartDebug_TXCLKGEN_DP)
        #define UartDebug_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UartDebug_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UartDebug_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UartDebug_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UartDebug_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UartDebug_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UartDebug_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UartDebug_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UartDebug_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UartDebug_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UartDebug_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UartDebug_TXCLKGEN_DP */

#endif /* End UartDebug_TX_ENABLED */

#if(UartDebug_HD_ENABLED)

    #define UartDebug_TXDATA_REG             (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__F1_REG )
    #define UartDebug_TXDATA_PTR             (  (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__F1_REG )
    #define UartDebug_TXDATA_AUX_CTL_REG     (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UartDebug_TXDATA_AUX_CTL_PTR     (  (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UartDebug_TXSTATUS_REG           (* (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_REG )
    #define UartDebug_TXSTATUS_PTR           (  (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_REG )
    #define UartDebug_TXSTATUS_MASK_REG      (* (reg8 *) UartDebug_BUART_sRX_RxSts__MASK_REG )
    #define UartDebug_TXSTATUS_MASK_PTR      (  (reg8 *) UartDebug_BUART_sRX_RxSts__MASK_REG )
    #define UartDebug_TXSTATUS_ACTL_REG      (* (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UartDebug_TXSTATUS_ACTL_PTR      (  (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UartDebug_HD_ENABLED */

#if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
    #define UartDebug_RXDATA_REG             (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__F0_REG )
    #define UartDebug_RXDATA_PTR             (  (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__F0_REG )
    #define UartDebug_RXADDRESS1_REG         (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__D0_REG )
    #define UartDebug_RXADDRESS1_PTR         (  (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__D0_REG )
    #define UartDebug_RXADDRESS2_REG         (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__D1_REG )
    #define UartDebug_RXADDRESS2_PTR         (  (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__D1_REG )
    #define UartDebug_RXDATA_AUX_CTL_REG     (* (reg8 *) UartDebug_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UartDebug_RXBITCTR_PERIOD_REG    (* (reg8 *) UartDebug_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UartDebug_RXBITCTR_PERIOD_PTR    (  (reg8 *) UartDebug_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UartDebug_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UartDebug_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UartDebug_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UartDebug_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UartDebug_RXBITCTR_COUNTER_REG   (* (reg8 *) UartDebug_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UartDebug_RXBITCTR_COUNTER_PTR   (  (reg8 *) UartDebug_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UartDebug_RXSTATUS_REG           (* (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_REG )
    #define UartDebug_RXSTATUS_PTR           (  (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_REG )
    #define UartDebug_RXSTATUS_MASK_REG      (* (reg8 *) UartDebug_BUART_sRX_RxSts__MASK_REG )
    #define UartDebug_RXSTATUS_MASK_PTR      (  (reg8 *) UartDebug_BUART_sRX_RxSts__MASK_REG )
    #define UartDebug_RXSTATUS_ACTL_REG      (* (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UartDebug_RXSTATUS_ACTL_PTR      (  (reg8 *) UartDebug_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */

#if(UartDebug_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UartDebug_INTCLOCK_CLKEN_REG     (* (reg8 *) UartDebug_IntClock__PM_ACT_CFG)
    #define UartDebug_INTCLOCK_CLKEN_PTR     (  (reg8 *) UartDebug_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UartDebug_INTCLOCK_CLKEN_MASK    UartDebug_IntClock__PM_ACT_MSK
#endif /* End UartDebug_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants              
***************************************/

#if(UartDebug_TX_ENABLED)
    #define UartDebug_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UartDebug_TX_ENABLED */

#if(UartDebug_HD_ENABLED)
    #define UartDebug_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UartDebug_HD_ENABLED */

#if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
    #define UartDebug_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/

#define UartDebug_initvar                    UartDebug_initVar

#define UartDebug_RX_Enabled                 UartDebug_RX_ENABLED
#define UartDebug_TX_Enabled                 UartDebug_TX_ENABLED
#define UartDebug_HD_Enabled                 UartDebug_HD_ENABLED
#define UartDebug_RX_IntInterruptEnabled     UartDebug_RX_INTERRUPT_ENABLED
#define UartDebug_TX_IntInterruptEnabled     UartDebug_TX_INTERRUPT_ENABLED
#define UartDebug_InternalClockUsed          UartDebug_INTERNAL_CLOCK_USED
#define UartDebug_RXHW_Address_Enabled       UartDebug_RXHW_ADDRESS_ENABLED
#define UartDebug_OverSampleCount            UartDebug_OVER_SAMPLE_COUNT
#define UartDebug_ParityType                 UartDebug_PARITY_TYPE

#if( UartDebug_TX_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
    #define UartDebug_TXBUFFER               UartDebug_txBuffer
    #define UartDebug_TXBUFFERREAD           UartDebug_txBufferRead 
    #define UartDebug_TXBUFFERWRITE          UartDebug_txBufferWrite 
#endif /* End UartDebug_TX_ENABLED */
#if( ( UartDebug_RX_ENABLED || UartDebug_HD_ENABLED ) && \
     (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) )
    #define UartDebug_RXBUFFER               UartDebug_rxBuffer
    #define UartDebug_RXBUFFERREAD           UartDebug_rxBufferRead 
    #define UartDebug_RXBUFFERWRITE          UartDebug_rxBufferWrite 
    #define UartDebug_RXBUFFERLOOPDETECT     UartDebug_rxBufferLoopDetect
    #define UartDebug_RXBUFFER_OVERFLOW      UartDebug_rxBufferOverflow
#endif /* End UartDebug_RX_ENABLED */

#ifdef UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartDebug_CONTROL                UartDebug_CONTROL_REG 
#endif /* End UartDebug_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(UartDebug_TX_ENABLED)
    #define UartDebug_TXDATA                 UartDebug_TXDATA_REG
    #define UartDebug_TXSTATUS               UartDebug_TXSTATUS_REG
    #define UartDebug_TXSTATUS_MASK          UartDebug_TXSTATUS_MASK_REG   
    #define UartDebug_TXSTATUS_ACTL          UartDebug_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UartDebug_TXCLKGEN_DP)
        #define UartDebug_TXBITCLKGEN_CTR        UartDebug_TXBITCLKGEN_CTR_REG
        #define UartDebug_TXBITCLKTX_COMPLETE    UartDebug_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UartDebug_TXBITCTR_PERIOD        UartDebug_TXBITCTR_PERIOD_REG
        #define UartDebug_TXBITCTR_CONTROL       UartDebug_TXBITCTR_CONTROL_REG
        #define UartDebug_TXBITCTR_COUNTER       UartDebug_TXBITCTR_COUNTER_REG
    #endif /* UartDebug_TXCLKGEN_DP */
#endif /* End UartDebug_TX_ENABLED */

#if(UartDebug_HD_ENABLED)
    #define UartDebug_TXDATA                 UartDebug_TXDATA_REG
    #define UartDebug_TXSTATUS               UartDebug_TXSTATUS_REG
    #define UartDebug_TXSTATUS_MASK          UartDebug_TXSTATUS_MASK_REG   
    #define UartDebug_TXSTATUS_ACTL          UartDebug_TXSTATUS_ACTL_REG
#endif /* End UartDebug_HD_ENABLED */

#if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
    #define UartDebug_RXDATA                 UartDebug_RXDATA_REG             
    #define UartDebug_RXADDRESS1             UartDebug_RXADDRESS1_REG
    #define UartDebug_RXADDRESS2             UartDebug_RXADDRESS2_REG
    #define UartDebug_RXBITCTR_PERIOD        UartDebug_RXBITCTR_PERIOD_REG
    #define UartDebug_RXBITCTR_CONTROL       UartDebug_RXBITCTR_CONTROL_REG
    #define UartDebug_RXBITCTR_COUNTER       UartDebug_RXBITCTR_COUNTER_REG
    #define UartDebug_RXSTATUS               UartDebug_RXSTATUS_REG
    #define UartDebug_RXSTATUS_MASK          UartDebug_RXSTATUS_MASK_REG
    #define UartDebug_RXSTATUS_ACTL          UartDebug_RXSTATUS_ACTL_REG
#endif /* End  (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */

#if(UartDebug_INTERNAL_CLOCK_USED)
    #define UartDebug_INTCLOCK_CLKEN         UartDebug_INTCLOCK_CLKEN_REG
#endif /* End UartDebug_INTERNAL_CLOCK_USED */

#define UartDebug_WAIT_FOR_COMLETE_REINIT    UartDebug_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UartDebug_H */


/* [] END OF FILE */
