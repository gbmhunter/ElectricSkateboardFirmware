/*******************************************************************************
* File Name: UartXbee_INT.c
* Version 2.10
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UartXbee.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (UartXbee_RX_ENABLED || UartXbee_HD_ENABLED) && \
     (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))

    extern volatile uint8 UartXbee_rxBuffer[];
    extern volatile uint8 UartXbee_rxBufferRead;
    extern volatile uint8 UartXbee_rxBufferWrite;
    extern volatile uint8 UartXbee_rxBufferLoopDetect;
    extern volatile uint8 UartXbee_rxBufferOverflow;
    #if (UartXbee_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UartXbee_rxAddressMode;
        extern volatile uint8 UartXbee_rxAddressDetected;
    #endif /* End EnableHWAddress */    

    /*******************************************************************************
    * Function Name: UartXbee_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartXbee_rxBuffer - RAM buffer pointer for save received data.
    *  UartXbee_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     increments after each byte saved to buffer.
    *  UartXbee_rxBufferRead - cyclic index for read from rxBuffer, 
    *     checked to detect overflow condition.
    *  UartXbee_rxBufferOverflow - software overflow flag. Set to one
    *     when UartXbee_rxBufferWrite index overtakes 
    *     UartXbee_rxBufferRead index.
    *  UartXbee_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UartXbee_rxBufferWrite is equal to 
    *    UartXbee_rxBufferRead
    *  UartXbee_rxAddressMode - this variable contains the Address mode, 
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UartXbee_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UartXbee_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0;

        /* User code required at start of ISR */
        /* `#START UartXbee_RXISR_START` */

        /* `#END` */

        readData = UartXbee_RXSTATUS_REG;

        if((readData & (UartXbee_RX_STS_BREAK | UartXbee_RX_STS_PAR_ERROR |
                        UartXbee_RX_STS_STOP_ERROR | UartXbee_RX_STS_OVERRUN)) != 0)
        {
            /* ERROR handling. */
            /* `#START UartXbee_RXISR_ERROR` */

            /* `#END` */
        }

        while(readData & UartXbee_RX_STS_FIFO_NOTEMPTY)
        {
            
            #if (UartXbee_RXHW_ADDRESS_ENABLED)
                if(UartXbee_rxAddressMode == UartXbee__B_UART__AM_SW_DETECT_TO_BUFFER) 
                {
                    if((readData & UartXbee_RX_STS_MRKSPC) != 0u )
                    {  
                        if ((readData & UartXbee_RX_STS_ADDR_MATCH) != 0)
                        {
                            UartXbee_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UartXbee_rxAddressDetected = 0u;
                        }
                    }

                    readData = UartXbee_RXDATA_REG;
                    if(UartXbee_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        UartXbee_rxBuffer[UartXbee_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    UartXbee_rxBuffer[UartXbee_rxBufferWrite] = UartXbee_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                UartXbee_rxBuffer[UartXbee_rxBufferWrite] = UartXbee_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */
            
            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(UartXbee_rxBufferLoopDetect)
                {   /* Set Software Buffer status Overflow */
                    UartXbee_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UartXbee_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UartXbee_rxBufferWrite >= UartXbee_RXBUFFERSIZE)
                {
                    UartXbee_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(UartXbee_rxBufferWrite == UartXbee_rxBufferRead)
                {
                    UartXbee_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(UartXbee_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        UartXbee_RXSTATUS_MASK_REG  &= ~UartXbee_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UartXbee_RX_VECT_NUM); 
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End UartXbee_FLOW_CONTROL != 0 */    
                }
            }

            /* Check again if there is data. */
            readData = UartXbee_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UartXbee_RXISR_END` */

        /* `#END` */

        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(CY_PSOC3_ES2 && (UartXbee_RXInternalInterrupt__ES2_PATCH))
            UartXbee_ISR_PATCH();
        #endif /* End CY_PSOC3_ES2*/
    }

#endif /* End UartXbee_RX_ENABLED && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) */


#if(UartXbee_TX_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))

    extern volatile uint8 UartXbee_txBuffer[];
    extern volatile uint8 UartXbee_txBufferRead;
    extern uint8 UartXbee_txBufferWrite;


    /*******************************************************************************
    * Function Name: UartXbee_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartXbee_txBuffer - RAM buffer pointer for transmit data from.
    *  UartXbee_txBufferRead - cyclic index for read and transmit data 
    *     from txBuffer, increments after each transmited byte.
    *  UartXbee_rxBufferWrite - cyclic index for write to txBuffer, 
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UartXbee_TXISR)
    {

        /* User code required at start of ISR */
        /* `#START UartXbee_TXISR_START` */

        /* `#END` */

        while((UartXbee_txBufferRead != UartXbee_txBufferWrite) && \
             !(UartXbee_TXSTATUS_REG & UartXbee_TX_STS_FIFO_FULL))
        {
            /* Check pointer. */
            if(UartXbee_txBufferRead >= UartXbee_TXBUFFERSIZE)
            {
                UartXbee_txBufferRead = 0u;
            }

            UartXbee_TXDATA_REG = UartXbee_txBuffer[UartXbee_txBufferRead];

            /* Set next pointer. */
            UartXbee_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UartXbee_TXISR_END` */

        /* `#END` */
        
        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(CY_PSOC3_ES2 && (UartXbee_TXInternalInterrupt__ES2_PATCH))
            UartXbee_ISR_PATCH();
        #endif /* End CY_PSOC3_ES2*/
    }

#endif /* End UartXbee_TX_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH) */


/* [] END OF FILE */
