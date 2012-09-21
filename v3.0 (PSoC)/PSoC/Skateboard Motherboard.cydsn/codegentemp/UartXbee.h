/*******************************************************************************
* File Name: UartXbee.h
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

#if !defined(CY_UART_UartXbee_H)
#define CY_UART_UartXbee_H


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UartXbee_RX_ENABLED                     (1u)
#define UartXbee_TX_ENABLED                     (1u)
#define UartXbee_HD_ENABLED                     (0u)
#define UartXbee_RX_INTERRUPT_ENABLED           (1u)
#define UartXbee_TX_INTERRUPT_ENABLED           (1u)
#define UartXbee_INTERNAL_CLOCK_USED            (1u)
#define UartXbee_RXHW_ADDRESS_ENABLED           (0u)
#define UartXbee_OVER_SAMPLE_COUNT              (8u)
#define UartXbee_PARITY_TYPE                    (0u)
#define UartXbee_PARITY_TYPE_SW                 (0u)
#define UartXbee_BREAK_DETECT                   (0u)
#define UartXbee_BREAK_BITS_TX                  (13u)
#define UartXbee_BREAK_BITS_RX                  (13u)
#define UartXbee_TXCLKGEN_DP                    (1u)
#define UartXbee_USE23POLLING                   (1u)
#define UartXbee_FLOW_CONTROL                   (0u)

/* Check to see if required defines such as CY_PSOC3 and CY_PSOC5 are available */
/* They are defined starting with cy_boot v2.30 */
#ifndef CY_PSOC3
    #error Component UART_v2_10 requires cy_boot v2.30 or later
#endif /* End CY_PSOC3 */

#if(CY_PSOC3_ES2 && (UartXbee_RX_INTERRUPT_ENABLED || UartXbee_TX_INTERRUPT_ENABLED))
    #include <intrins.h>
    #define UartXbee_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
#endif /* End CY_PSOC3_ES2 */

#ifdef UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartXbee_CONTROL_REG_REMOVED            (0u)
#else
    #define UartXbee_CONTROL_REG_REMOVED            (1u)
#endif /* End UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _UartXbee_backupStruct
{
    uint8 enableState;

    #if(UartXbee_CONTROL_REG_REMOVED == 0u)
        uint8 cr;            
    #endif /* End UartXbee_CONTROL_REG_REMOVED */    
    #if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 rx_mask;
            #if (UartXbee_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */
        #endif /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif  /* End (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED)*/

    #if(UartXbee_TX_ENABLED)
        #if(UartXbee_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
                uint8 tx_clk_compl;
            #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
        #else
            uint8 tx_period;
        #endif /*End UartXbee_TXCLKGEN_DP */
        #if (CY_PSOC3_ES2 || CY_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 tx_mask;
        #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif /*End UartXbee_TX_ENABLED */
} UartXbee_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UartXbee_Start(void) ;
void UartXbee_Stop(void) ;
uint8 UartXbee_ReadControlRegister(void) ;
void UartXbee_WriteControlRegister(uint8 control) ;

void UartXbee_Init(void) ;
void UartXbee_Enable(void) ;
void UartXbee_SaveConfig(void) ;
void UartXbee_RestoreConfig(void) ;
void UartXbee_Sleep(void) ;
void UartXbee_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )

    #if(UartXbee_RX_INTERRUPT_ENABLED)
        void  UartXbee_EnableRxInt(void) ;
        void  UartXbee_DisableRxInt(void) ;
        CY_ISR_PROTO(UartXbee_RXISR);
    #endif /* UartXbee_RX_INTERRUPT_ENABLED */

    void UartXbee_SetRxAddressMode(uint8 addressMode) 
                                                           ;
    void UartXbee_SetRxAddress1(uint8 address) ;
    void UartXbee_SetRxAddress2(uint8 address) ;

    void  UartXbee_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UartXbee_ReadRxData(void) ;
    uint8 UartXbee_ReadRxStatus(void) ;
    uint8 UartXbee_GetChar(void) ;
    uint16 UartXbee_GetByte(void) ;
    uint8 UartXbee_GetRxBufferSize(void)  
                                                            ;
    void UartXbee_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UartXbee_GetRxInterruptSource   UartXbee_ReadRxStatus

#endif /* End (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */

/* Only if TX is enabled */
#if(UartXbee_TX_ENABLED || UartXbee_HD_ENABLED)

    #if(UartXbee_TX_INTERRUPT_ENABLED)
        void UartXbee_EnableTxInt(void) ;
        void UartXbee_DisableTxInt(void) ;
        CY_ISR_PROTO(UartXbee_TXISR);
    #endif /* UartXbee_TX_INTERRUPT_ENABLED */

    void UartXbee_SetTxInterruptMode(uint8 intSrc) ;
    void UartXbee_WriteTxData(uint8 txDataByte) ;
    uint8 UartXbee_ReadTxStatus(void) ;
    void UartXbee_PutChar(uint8 txDataByte) ;
    void UartXbee_PutString(char* string) ;
    void UartXbee_PutArray(uint8* string, uint8 byteCount)
                                                            ;
    void UartXbee_PutCRLF(uint8 txDataByte) ;
    void UartXbee_ClearTxBuffer(void) ;
    void UartXbee_SetTxAddressMode(uint8 addressMode) ;
    void UartXbee_SendBreak(uint8 retMode) ;
    uint8 UartXbee_GetTxBufferSize(void) 
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UartXbee_PutStringConst         UartXbee_PutString
    #define UartXbee_PutArrayConst          UartXbee_PutArray
    #define UartXbee_GetTxInterruptSource   UartXbee_ReadTxStatus
    
#endif /* End UartXbee_TX_ENABLED || UartXbee_HD_ENABLED */

#if(UartXbee_HD_ENABLED)
    void UartXbee_LoadRxConfig(void) ;
    void UartXbee_LoadTxConfig(void) ;
#endif /* End UartXbee_HD_ENABLED */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UartXbee_SET_SPACE                              (0x00u)
#define UartXbee_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (UartXbee_TX_ENABLED) || (UartXbee_HD_ENABLED) )
    #if(UartXbee_TX_INTERRUPT_ENABLED)
        #define UartXbee_TX_VECT_NUM                UartXbee_TXInternalInterrupt__INTC_NUMBER
        #define UartXbee_TX_PRIOR_NUM               UartXbee_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UartXbee_TX_INTERRUPT_ENABLED */
    #if(UartXbee_TX_ENABLED) 
        #define UartXbee_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UartXbee_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UartXbee_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define UartXbee_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UartXbee_TX_ENABLED */
    #if(UartXbee_HD_ENABLED) 
        #define UartXbee_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UartXbee_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UartXbee_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define UartXbee_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UartXbee_HD_ENABLED */
    #define UartXbee_TX_STS_COMPLETE                (0x01u << UartXbee_TX_STS_COMPLETE_SHIFT)
    #define UartXbee_TX_STS_FIFO_EMPTY              (0x01u << UartXbee_TX_STS_FIFO_EMPTY_SHIFT)
    #define UartXbee_TX_STS_FIFO_FULL               (0x01u << UartXbee_TX_STS_FIFO_FULL_SHIFT)
    #define UartXbee_TX_STS_FIFO_NOT_FULL           (0x01u << UartXbee_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UartXbee_TX_ENABLED) || (UartXbee_HD_ENABLED)*/

#if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
    #if(UartXbee_RX_INTERRUPT_ENABLED)
        #define UartXbee_RX_VECT_NUM                UartXbee_RXInternalInterrupt__INTC_NUMBER
        #define UartXbee_RX_PRIOR_NUM               UartXbee_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UartXbee_RX_INTERRUPT_ENABLED */
    #define UartXbee_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UartXbee_RX_STS_BREAK_SHIFT             (0x01u)
    #define UartXbee_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UartXbee_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UartXbee_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UartXbee_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UartXbee_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UartXbee_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UartXbee_RX_STS_MRKSPC                  (0x01u << UartXbee_RX_STS_MRKSPC_SHIFT)
    #define UartXbee_RX_STS_BREAK                   (0x01u << UartXbee_RX_STS_BREAK_SHIFT)
    #define UartXbee_RX_STS_PAR_ERROR               (0x01u << UartXbee_RX_STS_PAR_ERROR_SHIFT)
    #define UartXbee_RX_STS_STOP_ERROR              (0x01u << UartXbee_RX_STS_STOP_ERROR_SHIFT)
    #define UartXbee_RX_STS_OVERRUN                 (0x01u << UartXbee_RX_STS_OVERRUN_SHIFT)
    #define UartXbee_RX_STS_FIFO_NOTEMPTY           (0x01u << UartXbee_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UartXbee_RX_STS_ADDR_MATCH              (0x01u << UartXbee_RX_STS_ADDR_MATCH_SHIFT)
    #define UartXbee_RX_STS_SOFT_BUFF_OVER          (0x01u << UartXbee_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UartXbee_RX_HW_MASK                     (0x7Fu)
#endif /* End (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */

/* Control Register definitions */
#define UartXbee_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UartXbee_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UartXbee_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UartXbee_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UartXbee_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UartXbee_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UartXbee_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UartXbee_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UartXbee_CTRL_HD_SEND                       (0x01u << UartXbee_CTRL_HD_SEND_SHIFT)
#define UartXbee_CTRL_HD_SEND_BREAK                 (0x01u << UartXbee_CTRL_HD_SEND_BREAK_SHIFT)
#define UartXbee_CTRL_MARK                          (0x01u << UartXbee_CTRL_MARK_SHIFT)
#define UartXbee_CTRL_PARITY_TYPE_MASK              (0x03u << UartXbee_CTRL_PARITY_TYPE0_SHIFT)
#define UartXbee_CTRL_RXADDR_MODE_MASK              (0x07u << UartXbee_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UartXbee_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UartXbee_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UartXbee_SEND_BREAK                         (0x00u)
#define UartXbee_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UartXbee_REINIT                             (0x02u)
#define UartXbee_SEND_WAIT_REINIT                   (0x03u)

#define UartXbee_OVER_SAMPLE_8                      (8u)
#define UartXbee_OVER_SAMPLE_16                     (16u)

#define UartXbee_BIT_CENTER                         (UartXbee_OVER_SAMPLE_COUNT - 1u)

#define UartXbee_FIFO_LENGTH                        (4u)
#define UartXbee_NUMBER_OF_START_BIT                (1u)

/* 8X always for count7 implementation*/
#define UartXbee_TXBITCTR_BREAKBITS8X   (UartXbee_BREAK_BITS_TX * UartXbee_OVER_SAMPLE_8 - 1u)
/* 8X or 16X for DP implementation*/
#define UartXbee_TXBITCTR_BREAKBITS   (UartXbee_BREAK_BITS_TX * UartXbee_OVER_SAMPLE_COUNT - 1u)

#if (UartXbee_OVER_SAMPLE_COUNT == UartXbee_OVER_SAMPLE_8)
    #define UartXbee_HD_TXBITCTR_INIT   ((UartXbee_BREAK_BITS_TX + \
        UartXbee_NUMBER_OF_START_BIT) * UartXbee_OVER_SAMPLE_COUNT - 1u)
    /* This parameter is increased on the 1 in 2 out of 3 mode to sample voting in the middle */
    #define UartXbee_HD_RXBITCTR_INIT   ((UartXbee_BREAK_BITS_RX + \
    UartXbee_NUMBER_OF_START_BIT) * UartXbee_OVER_SAMPLE_COUNT - 1u + \
    (UartXbee_OVER_SAMPLE_COUNT / 2u) + (UartXbee_USE23POLLING * 2u) - 1u)
#else /* UartXbee_OVER_SAMPLE_COUNT == UartXbee_OVER_SAMPLE_16 */
    #define UartXbee_HD_TXBITCTR_INIT   (8u * UartXbee_OVER_SAMPLE_COUNT - 1u)
    #define UartXbee_HD_RXBITCTR_INIT   (7u * UartXbee_OVER_SAMPLE_COUNT - 1u  +  \
       (UartXbee_OVER_SAMPLE_COUNT / 2u) + (UartXbee_USE23POLLING * 2u) - 1u)
#endif /* End UartXbee_OVER_SAMPLE_COUNT */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UartXbee__B_UART__AM_SW_BYTE_BYTE 1
#define UartXbee__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UartXbee__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UartXbee__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UartXbee__B_UART__AM_NONE 0

#define UartXbee__B_UART__NONE_REVB 0
#define UartXbee__B_UART__EVEN_REVB 1
#define UartXbee__B_UART__ODD_REVB 2
#define UartXbee__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

#define UartXbee_TXBUFFERSIZE           (50u)
#define UartXbee_RXBUFFERSIZE           (50u)
/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UartXbee_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UartXbee_NUMBER_OF_STOP_BITS    (1u)

#if (UartXbee_RXHW_ADDRESS_ENABLED)
    #define UartXbee_RXADDRESSMODE      (0u)
    #define UartXbee_RXHWADDRESS1       (0u)
    #define UartXbee_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define UartXbee_RXAddressMode      UartXbee_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define UartXbee_INIT_RX_INTERRUPTS_MASK \
                                          (1 << UartXbee_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UartXbee_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UartXbee_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UartXbee_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UartXbee_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UartXbee_RX_STS_BREAK_SHIFT) \
                                        | (0 << UartXbee_RX_STS_OVERRUN_SHIFT)

#define UartXbee_INIT_TX_INTERRUPTS_MASK \
                                          (0 << UartXbee_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << UartXbee_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UartXbee_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UartXbee_TX_STS_FIFO_NOT_FULL_SHIFT)


/***************************************
*              Registers
***************************************/

#ifdef UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartXbee_CONTROL_REG \
                            (* (reg8 *) UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
    #define UartXbee_CONTROL_PTR \
                            (  (reg8 *) UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(UartXbee_TX_ENABLED)
    #define UartXbee_TXDATA_REG          (* (reg8 *) UartXbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define UartXbee_TXDATA_PTR          (  (reg8 *) UartXbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define UartXbee_TXDATA_AUX_CTL_REG  (* (reg8 *) UartXbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UartXbee_TXDATA_AUX_CTL_PTR  (  (reg8 *) UartXbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UartXbee_TXSTATUS_REG        (* (reg8 *) UartXbee_BUART_sTX_TxSts__STATUS_REG)
    #define UartXbee_TXSTATUS_PTR        (  (reg8 *) UartXbee_BUART_sTX_TxSts__STATUS_REG)
    #define UartXbee_TXSTATUS_MASK_REG   (* (reg8 *) UartXbee_BUART_sTX_TxSts__MASK_REG)
    #define UartXbee_TXSTATUS_MASK_PTR   (  (reg8 *) UartXbee_BUART_sTX_TxSts__MASK_REG)
    #define UartXbee_TXSTATUS_ACTL_REG   (* (reg8 *) UartXbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UartXbee_TXSTATUS_ACTL_PTR   (  (reg8 *) UartXbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UartXbee_TXCLKGEN_DP)
        #define UartXbee_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UartXbee_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UartXbee_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UartXbee_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UartXbee_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UartXbee_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UartXbee_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UartXbee_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UartXbee_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UartXbee_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UartXbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UartXbee_TXCLKGEN_DP */

#endif /* End UartXbee_TX_ENABLED */

#if(UartXbee_HD_ENABLED)

    #define UartXbee_TXDATA_REG             (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define UartXbee_TXDATA_PTR             (  (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define UartXbee_TXDATA_AUX_CTL_REG     (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UartXbee_TXDATA_AUX_CTL_PTR     (  (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UartXbee_TXSTATUS_REG           (* (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_REG )
    #define UartXbee_TXSTATUS_PTR           (  (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_REG )
    #define UartXbee_TXSTATUS_MASK_REG      (* (reg8 *) UartXbee_BUART_sRX_RxSts__MASK_REG )
    #define UartXbee_TXSTATUS_MASK_PTR      (  (reg8 *) UartXbee_BUART_sRX_RxSts__MASK_REG )
    #define UartXbee_TXSTATUS_ACTL_REG      (* (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UartXbee_TXSTATUS_ACTL_PTR      (  (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UartXbee_HD_ENABLED */

#if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
    #define UartXbee_RXDATA_REG             (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define UartXbee_RXDATA_PTR             (  (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define UartXbee_RXADDRESS1_REG         (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define UartXbee_RXADDRESS1_PTR         (  (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define UartXbee_RXADDRESS2_REG         (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define UartXbee_RXADDRESS2_PTR         (  (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define UartXbee_RXDATA_AUX_CTL_REG     (* (reg8 *) UartXbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UartXbee_RXBITCTR_PERIOD_REG    (* (reg8 *) UartXbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UartXbee_RXBITCTR_PERIOD_PTR    (  (reg8 *) UartXbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UartXbee_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UartXbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UartXbee_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UartXbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UartXbee_RXBITCTR_COUNTER_REG   (* (reg8 *) UartXbee_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UartXbee_RXBITCTR_COUNTER_PTR   (  (reg8 *) UartXbee_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UartXbee_RXSTATUS_REG           (* (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_REG )
    #define UartXbee_RXSTATUS_PTR           (  (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_REG )
    #define UartXbee_RXSTATUS_MASK_REG      (* (reg8 *) UartXbee_BUART_sRX_RxSts__MASK_REG )
    #define UartXbee_RXSTATUS_MASK_PTR      (  (reg8 *) UartXbee_BUART_sRX_RxSts__MASK_REG )
    #define UartXbee_RXSTATUS_ACTL_REG      (* (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UartXbee_RXSTATUS_ACTL_PTR      (  (reg8 *) UartXbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */

#if(UartXbee_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UartXbee_INTCLOCK_CLKEN_REG     (* (reg8 *) UartXbee_IntClock__PM_ACT_CFG)
    #define UartXbee_INTCLOCK_CLKEN_PTR     (  (reg8 *) UartXbee_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UartXbee_INTCLOCK_CLKEN_MASK    UartXbee_IntClock__PM_ACT_MSK
#endif /* End UartXbee_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants              
***************************************/

#if(UartXbee_TX_ENABLED)
    #define UartXbee_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UartXbee_TX_ENABLED */

#if(UartXbee_HD_ENABLED)
    #define UartXbee_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UartXbee_HD_ENABLED */

#if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
    #define UartXbee_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/

#define UartXbee_initvar                    UartXbee_initVar

#define UartXbee_RX_Enabled                 UartXbee_RX_ENABLED
#define UartXbee_TX_Enabled                 UartXbee_TX_ENABLED
#define UartXbee_HD_Enabled                 UartXbee_HD_ENABLED
#define UartXbee_RX_IntInterruptEnabled     UartXbee_RX_INTERRUPT_ENABLED
#define UartXbee_TX_IntInterruptEnabled     UartXbee_TX_INTERRUPT_ENABLED
#define UartXbee_InternalClockUsed          UartXbee_INTERNAL_CLOCK_USED
#define UartXbee_RXHW_Address_Enabled       UartXbee_RXHW_ADDRESS_ENABLED
#define UartXbee_OverSampleCount            UartXbee_OVER_SAMPLE_COUNT
#define UartXbee_ParityType                 UartXbee_PARITY_TYPE

#if( UartXbee_TX_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
    #define UartXbee_TXBUFFER               UartXbee_txBuffer
    #define UartXbee_TXBUFFERREAD           UartXbee_txBufferRead 
    #define UartXbee_TXBUFFERWRITE          UartXbee_txBufferWrite 
#endif /* End UartXbee_TX_ENABLED */
#if( ( UartXbee_RX_ENABLED || UartXbee_HD_ENABLED ) && \
     (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) )
    #define UartXbee_RXBUFFER               UartXbee_rxBuffer
    #define UartXbee_RXBUFFERREAD           UartXbee_rxBufferRead 
    #define UartXbee_RXBUFFERWRITE          UartXbee_rxBufferWrite 
    #define UartXbee_RXBUFFERLOOPDETECT     UartXbee_rxBufferLoopDetect
    #define UartXbee_RXBUFFER_OVERFLOW      UartXbee_rxBufferOverflow
#endif /* End UartXbee_RX_ENABLED */

#ifdef UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG
    #define UartXbee_CONTROL                UartXbee_CONTROL_REG 
#endif /* End UartXbee_BUART_sCR_AsyncCtl_CtrlReg__CONTROL_REG */

#if(UartXbee_TX_ENABLED)
    #define UartXbee_TXDATA                 UartXbee_TXDATA_REG
    #define UartXbee_TXSTATUS               UartXbee_TXSTATUS_REG
    #define UartXbee_TXSTATUS_MASK          UartXbee_TXSTATUS_MASK_REG   
    #define UartXbee_TXSTATUS_ACTL          UartXbee_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UartXbee_TXCLKGEN_DP)
        #define UartXbee_TXBITCLKGEN_CTR        UartXbee_TXBITCLKGEN_CTR_REG
        #define UartXbee_TXBITCLKTX_COMPLETE    UartXbee_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UartXbee_TXBITCTR_PERIOD        UartXbee_TXBITCTR_PERIOD_REG
        #define UartXbee_TXBITCTR_CONTROL       UartXbee_TXBITCTR_CONTROL_REG
        #define UartXbee_TXBITCTR_COUNTER       UartXbee_TXBITCTR_COUNTER_REG
    #endif /* UartXbee_TXCLKGEN_DP */
#endif /* End UartXbee_TX_ENABLED */

#if(UartXbee_HD_ENABLED)
    #define UartXbee_TXDATA                 UartXbee_TXDATA_REG
    #define UartXbee_TXSTATUS               UartXbee_TXSTATUS_REG
    #define UartXbee_TXSTATUS_MASK          UartXbee_TXSTATUS_MASK_REG   
    #define UartXbee_TXSTATUS_ACTL          UartXbee_TXSTATUS_ACTL_REG
#endif /* End UartXbee_HD_ENABLED */

#if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
    #define UartXbee_RXDATA                 UartXbee_RXDATA_REG             
    #define UartXbee_RXADDRESS1             UartXbee_RXADDRESS1_REG
    #define UartXbee_RXADDRESS2             UartXbee_RXADDRESS2_REG
    #define UartXbee_RXBITCTR_PERIOD        UartXbee_RXBITCTR_PERIOD_REG
    #define UartXbee_RXBITCTR_CONTROL       UartXbee_RXBITCTR_CONTROL_REG
    #define UartXbee_RXBITCTR_COUNTER       UartXbee_RXBITCTR_COUNTER_REG
    #define UartXbee_RXSTATUS               UartXbee_RXSTATUS_REG
    #define UartXbee_RXSTATUS_MASK          UartXbee_RXSTATUS_MASK_REG
    #define UartXbee_RXSTATUS_ACTL          UartXbee_RXSTATUS_ACTL_REG
#endif /* End  (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */

#if(UartXbee_INTERNAL_CLOCK_USED)
    #define UartXbee_INTCLOCK_CLKEN         UartXbee_INTCLOCK_CLKEN_REG
#endif /* End UartXbee_INTERNAL_CLOCK_USED */

#define UartXbee_WAIT_FOR_COMLETE_REINIT    UartXbee_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UartXbee_H */


/* [] END OF FILE */
