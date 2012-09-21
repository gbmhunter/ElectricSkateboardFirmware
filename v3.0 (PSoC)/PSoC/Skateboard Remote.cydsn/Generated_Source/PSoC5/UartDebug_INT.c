/*******************************************************************************
* File Name: UartDebug_INT.c
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

#include "UartDebug.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (UartDebug_RX_ENABLED || UartDebug_HD_ENABLED) && \
     (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))

    extern volatile uint8 UartDebug_rxBuffer[];
    extern volatile uint8 UartDebug_rxBufferRead;
    extern volatile uint8 UartDebug_rxBufferWrite;
    extern volatile uint8 UartDebug_rxBufferLoopDetect;
    extern volatile uint8 UartDebug_rxBufferOverflow;
    #if (UartDebug_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UartDebug_rxAddressMode;
        extern volatile uint8 UartDebug_rxAddressDetected;
    #endif /* End EnableHWAddress */    

    /*******************************************************************************
    * Function Name: UartDebug_RXISR
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
    *  UartDebug_rxBuffer - RAM buffer pointer for save received data.
    *  UartDebug_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     increments after each byte saved to buffer.
    *  UartDebug_rxBufferRead - cyclic index for read from rxBuffer, 
    *     checked to detect overflow condition.
    *  UartDebug_rxBufferOverflow - software overflow flag. Set to one
    *     when UartDebug_rxBufferWrite index overtakes 
    *     UartDebug_rxBufferRead index.
    *  UartDebug_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UartDebug_rxBufferWrite is equal to 
    *    UartDebug_rxBufferRead
    *  UartDebug_rxAddressMode - this variable contains the Address mode, 
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UartDebug_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UartDebug_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0;

        /* User code required at start of ISR */
        /* `#START UartDebug_RXISR_START` */

        /* `#END` */

        readData = UartDebug_RXSTATUS_REG;

        if((readData & (UartDebug_RX_STS_BREAK | UartDebug_RX_STS_PAR_ERROR |
                        UartDebug_RX_STS_STOP_ERROR | UartDebug_RX_STS_OVERRUN)) != 0)
        {
            /* ERROR handling. */
            /* `#START UartDebug_RXISR_ERROR` */

            /* `#END` */
        }

        while(readData & UartDebug_RX_STS_FIFO_NOTEMPTY)
        {
            
            #if (UartDebug_RXHW_ADDRESS_ENABLED)
                if(UartDebug_rxAddressMode == UartDebug__B_UART__AM_SW_DETECT_TO_BUFFER) 
                {
                    if((readData & UartDebug_RX_STS_MRKSPC) != 0u )
                    {  
                        if ((readData & UartDebug_RX_STS_ADDR_MATCH) != 0)
                        {
                            UartDebug_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UartDebug_rxAddressDetected = 0u;
                        }
                    }

                    readData = UartDebug_RXDATA_REG;
                    if(UartDebug_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        UartDebug_rxBuffer[UartDebug_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    UartDebug_rxBuffer[UartDebug_rxBufferWrite] = UartDebug_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                UartDebug_rxBuffer[UartDebug_rxBufferWrite] = UartDebug_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */
            
            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(UartDebug_rxBufferLoopDetect)
                {   /* Set Software Buffer status Overflow */
                    UartDebug_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UartDebug_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UartDebug_rxBufferWrite >= UartDebug_RXBUFFERSIZE)
                {
                    UartDebug_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(UartDebug_rxBufferWrite == UartDebug_rxBufferRead)
                {
                    UartDebug_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(UartDebug_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        UartDebug_RXSTATUS_MASK_REG  &= ~UartDebug_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UartDebug_RX_VECT_NUM); 
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End UartDebug_FLOW_CONTROL != 0 */    
                }
            }

            /* Check again if there is data. */
            readData = UartDebug_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UartDebug_RXISR_END` */

        /* `#END` */

        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(CY_PSOC3_ES2 && (UartDebug_RXInternalInterrupt__ES2_PATCH))
            UartDebug_ISR_PATCH();
        #endif /* End CY_PSOC3_ES2*/
    }

#endif /* End UartDebug_RX_ENABLED && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) */


#if(UartDebug_TX_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))

    extern volatile uint8 UartDebug_txBuffer[];
    extern volatile uint8 UartDebug_txBufferRead;
    extern uint8 UartDebug_txBufferWrite;


    /*******************************************************************************
    * Function Name: UartDebug_TXISR
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
    *  UartDebug_txBuffer - RAM buffer pointer for transmit data from.
    *  UartDebug_txBufferRead - cyclic index for read and transmit data 
    *     from txBuffer, increments after each transmited byte.
    *  UartDebug_rxBufferWrite - cyclic index for write to txBuffer, 
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UartDebug_TXISR)
    {

        /* User code required at start of ISR */
        /* `#START UartDebug_TXISR_START` */

        /* `#END` */

        while((UartDebug_txBufferRead != UartDebug_txBufferWrite) && \
             !(UartDebug_TXSTATUS_REG & UartDebug_TX_STS_FIFO_FULL))
        {
            /* Check pointer. */
            if(UartDebug_txBufferRead >= UartDebug_TXBUFFERSIZE)
            {
                UartDebug_txBufferRead = 0u;
            }

            UartDebug_TXDATA_REG = UartDebug_txBuffer[UartDebug_txBufferRead];

            /* Set next pointer. */
            UartDebug_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UartDebug_TXISR_END` */

        /* `#END` */
        
        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(CY_PSOC3_ES2 && (UartDebug_TXInternalInterrupt__ES2_PATCH))
            UartDebug_ISR_PATCH();
        #endif /* End CY_PSOC3_ES2*/
    }

#endif /* End UartDebug_TX_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH) */


/* [] END OF FILE */
