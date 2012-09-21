/*******************************************************************************
* File Name: UartDebug.c
* Version 2.10
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
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
* Global data allocation
***************************************/

#if( UartDebug_TX_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
    volatile uint8 UartDebug_txBuffer[UartDebug_TXBUFFERSIZE];
    volatile uint8 UartDebug_txBufferRead = 0u;
    uint8 UartDebug_txBufferWrite = 0u;
#endif /* End UartDebug_TX_ENABLED */
#if( ( UartDebug_RX_ENABLED || UartDebug_HD_ENABLED ) && \
     (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) )
    volatile uint8 UartDebug_rxBuffer[UartDebug_RXBUFFERSIZE];
    volatile uint8 UartDebug_rxBufferRead = 0u;
    volatile uint8 UartDebug_rxBufferWrite = 0u;
    volatile uint8 UartDebug_rxBufferLoopDetect = 0u;
    volatile uint8 UartDebug_rxBufferOverflow = 0u;
    #if (UartDebug_RXHW_ADDRESS_ENABLED)
        volatile uint8 UartDebug_rxAddressMode = UartDebug_RXADDRESSMODE;
        volatile uint8 UartDebug_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */    
#endif /* End UartDebug_RX_ENABLED */


/***************************************
* Local data allocation
***************************************/

uint8 UartDebug_initVar = 0u;


/*******************************************************************************
* Function Name: UartDebug_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The UartDebug_intiVar variable is used to indicate initial 
*  configuration of this component. The variable is initialized to zero (0u) 
*  and set to one (1u) the first time UART_Start() is called. This allows for 
*  component initialization without re-initialization in all subsequent calls 
*  to the UartDebug_Start() routine. 
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartDebug_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(UartDebug_initVar == 0u)
    {
        UartDebug_Init();
        UartDebug_initVar = 1u;
    }
    UartDebug_Enable();
}


/*******************************************************************************
* Function Name: UartDebug_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  UartDebug_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UartDebug_Init(void) 
{
    #if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)

        #if(UartDebug_RX_INTERRUPT_ENABLED && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            CyIntSetVector(UartDebug_RX_VECT_NUM,   UartDebug_RXISR);
            CyIntSetPriority(UartDebug_RX_VECT_NUM, UartDebug_RX_PRIOR_NUM);
        #endif /* End UartDebug_RX_INTERRUPT_ENABLED */

        #if (UartDebug_RXHW_ADDRESS_ENABLED)
            UartDebug_SetRxAddressMode(UartDebug_RXAddressMode);
            UartDebug_SetRxAddress1(UartDebug_RXHWADDRESS1);
            UartDebug_SetRxAddress2(UartDebug_RXHWADDRESS2);
        #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */

        /* Configure the Initial RX interrupt mask */
        UartDebug_RXSTATUS_MASK_REG  = UartDebug_INIT_RX_INTERRUPTS_MASK;
    #endif /* End UartDebug_RX_ENABLED || UartDebug_HD_ENABLED*/

    #if(UartDebug_TX_ENABLED)
        #if(UartDebug_TX_INTERRUPT_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            CyIntSetVector(UartDebug_TX_VECT_NUM,   UartDebug_TXISR);
            CyIntSetPriority(UartDebug_TX_VECT_NUM, UartDebug_TX_PRIOR_NUM);
        #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(UartDebug_TXCLKGEN_DP)
            UartDebug_TXBITCLKGEN_CTR_REG = UartDebug_BIT_CENTER;
            UartDebug_TXBITCLKTX_COMPLETE_REG = (UartDebug_NUMBER_OF_DATA_BITS + \
                                                    UartDebug_NUMBER_OF_START_BIT) * \
                                                    UartDebug_OVER_SAMPLE_COUNT;
        #else
            UartDebug_TXBITCTR_COUNTER_REG = (UartDebug_NUMBER_OF_DATA_BITS + \
                                                    UartDebug_NUMBER_OF_START_BIT) * \
                                                    UartDebug_OVER_SAMPLE_8;
        #endif /* End UartDebug_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(UartDebug_TX_INTERRUPT_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            UartDebug_TXSTATUS_MASK_REG = UartDebug_TX_STS_FIFO_EMPTY;
        #else
            UartDebug_TXSTATUS_MASK_REG = UartDebug_INIT_TX_INTERRUPTS_MASK;
        #endif /*End UartDebug_TX_INTERRUPT_ENABLED*/
        
    #endif /* End UartDebug_TX_ENABLED */

    #if(UartDebug_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        UartDebug_WriteControlRegister( \
            (UartDebug_ReadControlRegister() & ~UartDebug_CTRL_PARITY_TYPE_MASK) | \
            (UartDebug_PARITY_TYPE << UartDebug_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End UartDebug_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: UartDebug_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UartDebug_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void UartDebug_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();
    
    #if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        UartDebug_RXBITCTR_CONTROL_REG |= UartDebug_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        UartDebug_RXSTATUS_ACTL_REG  |= UartDebug_INT_ENABLE;
        #if(UartDebug_RX_INTERRUPT_ENABLED && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            CyIntEnable(UartDebug_RX_VECT_NUM);
            #if (UartDebug_RXHW_ADDRESS_ENABLED)
                UartDebug_rxAddressDetected = 0u;
            #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */
        #endif /* End UartDebug_RX_INTERRUPT_ENABLED */
    #endif /* End UartDebug_RX_ENABLED || UartDebug_HD_ENABLED*/

    #if(UartDebug_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!UartDebug_TXCLKGEN_DP)
            UartDebug_TXBITCTR_CONTROL_REG |= UartDebug_CNTR_ENABLE;
        #endif /* End UartDebug_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        UartDebug_TXSTATUS_ACTL_REG |= UartDebug_INT_ENABLE;
        #if(UartDebug_TX_INTERRUPT_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            CyIntEnable(UartDebug_TX_VECT_NUM);
        #endif /* End UartDebug_TX_INTERRUPT_ENABLED*/
     #endif /* End UartDebug_TX_ENABLED */

    #if(UartDebug_INTERNAL_CLOCK_USED)
        /* Set the bit to enable the clock. */
        UartDebug_INTCLOCK_CLKEN_REG |= UartDebug_INTCLOCK_CLKEN_MASK;
    #endif /* End UartDebug_INTERNAL_CLOCK_USED */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UartDebug_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UartDebug_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /*Write Bit Counter Disable */
    #if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)
        UartDebug_RXBITCTR_CONTROL_REG &= ~UartDebug_CNTR_ENABLE;
    #endif /* End UartDebug_RX_ENABLED */

    #if(UartDebug_TX_ENABLED)
        #if(!UartDebug_TXCLKGEN_DP)
            UartDebug_TXBITCTR_CONTROL_REG &= ~UartDebug_CNTR_ENABLE;
        #endif /* End UartDebug_TXCLKGEN_DP */
    #endif /* UartDebug_TX_ENABLED */

    #if(UartDebug_INTERNAL_CLOCK_USED)
        /* Clear the bit to enable the clock. */
        UartDebug_INTCLOCK_CLKEN_REG &= ~UartDebug_INTCLOCK_CLKEN_MASK;
    #endif /* End UartDebug_INTERNAL_CLOCK_USED */
    
    /*Disable internal interrupt component*/
    #if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)
        UartDebug_RXSTATUS_ACTL_REG  &= ~UartDebug_INT_ENABLE;
        #if(UartDebug_RX_INTERRUPT_ENABLED && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            UartDebug_DisableRxInt();
        #endif /* End UartDebug_RX_INTERRUPT_ENABLED */
    #endif /* End UartDebug_RX_ENABLED */
    
    #if(UartDebug_TX_ENABLED)
        UartDebug_TXSTATUS_ACTL_REG &= ~UartDebug_INT_ENABLE;
        #if(UartDebug_TX_INTERRUPT_ENABLED && (UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            UartDebug_DisableTxInt();
        #endif /* End UartDebug_TX_INTERRUPT_ENABLED */
    #endif /* End UartDebug_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UartDebug_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 UartDebug_ReadControlRegister(void) 
{
    #if( UartDebug_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(UartDebug_CONTROL_REG);
    #endif /* End UartDebug_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UartDebug_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  UartDebug_WriteControlRegister(uint8 control) 
{
    #if( UartDebug_CONTROL_REG_REMOVED )
        control = control;      /* Reassigning to release compiler warning */ 
    #else
       UartDebug_CONTROL_REG = control;
    #endif /* End UartDebug_CONTROL_REG_REMOVED */
}


#if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)

    #if(UartDebug_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: UartDebug_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void UartDebug_EnableRxInt(void) 
        {
            CyIntEnable(UartDebug_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: UartDebug_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void UartDebug_DisableRxInt(void) 
        {
            CyIntDisable(UartDebug_RX_VECT_NUM);
        }

    #endif /* UartDebug_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: UartDebug_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void UartDebug_SetRxInterruptMode(uint8 intSrc) 
    {
        UartDebug_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: UartDebug_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to 
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  UartDebug_rxBuffer - RAM buffer pointer for save received data.
    *  UartDebug_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  UartDebug_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  UartDebug_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UartDebug_ReadRxData(void) 
    {
        uint8 rxData;

        #if(UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_DisableRxInt();
            #endif /* End UartDebug_RX_INTERRUPT_ENABLED */

            if( (UartDebug_rxBufferRead != UartDebug_rxBufferWrite) ||
                (UartDebug_rxBufferLoopDetect > 0u) )
            {

                rxData = UartDebug_rxBuffer[UartDebug_rxBufferRead];

                UartDebug_rxBufferRead++;

                if(UartDebug_rxBufferRead >= UartDebug_RXBUFFERSIZE)
                {
                    UartDebug_rxBufferRead = 0u;
                }

                if(UartDebug_rxBufferLoopDetect > 0u )
                {
                    UartDebug_rxBufferLoopDetect = 0u;
                    #if( (UartDebug_RX_INTERRUPT_ENABLED) && (UartDebug_FLOW_CONTROL != 0u) && \
                         (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( UartDebug_HD_ENABLED )
                            if((UartDebug_CONTROL_REG & UartDebug_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                UartDebug_RXSTATUS_MASK_REG  |= UartDebug_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            UartDebug_RXSTATUS_MASK_REG  |= UartDebug_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end UartDebug_HD_ENABLED */
                    #endif /* UartDebug_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = UartDebug_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_EnableRxInt();
            #endif /* End UartDebug_RX_INTERRUPT_ENABLED */

        #else /* UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = UartDebug_RXDATA_REG;

        #endif /* UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UartDebug_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  UartDebug_rxBufferOverflow - used to indicate overload condition. 
    *   It set to one in RX interrupt when there isn?t free space in 
    *   UartDebug_rxBufferRead to write new data. This condition returned 
    *   and cleared to zero by this API as an 
    *   UartDebug_RX_STS_SOFT_BUFF_OVER bit along with RX Status register 
    *   bits.
    *
    *******************************************************************************/
    uint8 UartDebug_ReadRxStatus(void) 
    {
        uint8 status;

        status = UartDebug_RXSTATUS_REG;
        status &= UartDebug_RX_HW_MASK;

        #if(UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH)
            if( UartDebug_rxBufferOverflow )
            {
                status |= UartDebug_RX_STS_SOFT_BUFF_OVER;
                UartDebug_rxBufferOverflow = 0u;
            }
        #endif /* UartDebug_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: UartDebug_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error 
    *  condition exists, zero is returned; otherwise, character is read and 
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  UartDebug_rxBuffer - RAM buffer pointer for save received data.
    *  UartDebug_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  UartDebug_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  UartDebug_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UartDebug_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_DisableRxInt();
            #endif /* UartDebug_RX_INTERRUPT_ENABLED */

            if( (UartDebug_rxBufferRead != UartDebug_rxBufferWrite) ||
                (UartDebug_rxBufferLoopDetect > 0u) )
            {
                rxData = UartDebug_rxBuffer[UartDebug_rxBufferRead];

                UartDebug_rxBufferRead++;

                if(UartDebug_rxBufferRead >= UartDebug_RXBUFFERSIZE)
                {
                    UartDebug_rxBufferRead = 0u;
                }

                if(UartDebug_rxBufferLoopDetect > 0u ) 
                {
                    UartDebug_rxBufferLoopDetect = 0u;
                    #if( (UartDebug_RX_INTERRUPT_ENABLED) && (UartDebug_FLOW_CONTROL != 0u) && \
                         (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( UartDebug_HD_ENABLED )
                            if((UartDebug_CONTROL_REG & UartDebug_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                UartDebug_RXSTATUS_MASK_REG  |= UartDebug_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            UartDebug_RXSTATUS_MASK_REG  |= UartDebug_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end UartDebug_HD_ENABLED */
                    #endif /* UartDebug_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus =UartDebug_RXSTATUS_REG;
                if(rxStatus & UartDebug_RX_STS_FIFO_NOTEMPTY)
                {   /* Read received data from FIFO*/
                    rxData = UartDebug_RXDATA_REG;
                    /*Check status on error*/
                    if(rxStatus & (UartDebug_RX_STS_BREAK | UartDebug_RX_STS_PAR_ERROR |
                                   UartDebug_RX_STS_STOP_ERROR | UartDebug_RX_STS_OVERRUN))
                    {
                        rxData = 0u;
                    }    
                }
            }

            /* Enable Rx interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_EnableRxInt();
            #endif /* UartDebug_RX_INTERRUPT_ENABLED */

        #else /* UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

            rxStatus =UartDebug_RXSTATUS_REG;
            if(rxStatus & UartDebug_RX_STS_FIFO_NOTEMPTY)
            {   /* Read received data from FIFO*/
                rxData = UartDebug_RXDATA_REG;
                /*Check status on error*/
                if(rxStatus & (UartDebug_RX_STS_BREAK | UartDebug_RX_STS_PAR_ERROR |
                               UartDebug_RX_STS_STOP_ERROR | UartDebug_RX_STS_OVERRUN))
                {
                    rxData = 0u;
                }
            }
        #endif /* UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UartDebug_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 UartDebug_GetByte(void) 
    {
        return ( ((uint16)UartDebug_ReadRxStatus() << 8u) | UartDebug_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: UartDebug_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left 
    *  in the RX buffer
    *
    * Global Variables:
    *  UartDebug_rxBufferWrite - used to calculate left bytes. 
    *  UartDebug_rxBufferRead - used to calculate left bytes.
    *  UartDebug_rxBufferLoopDetect - checked to decide left bytes amount. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 UartDebug_GetRxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_DisableRxInt();
            #endif /* UartDebug_RX_INTERRUPT_ENABLED */

            if(UartDebug_rxBufferRead == UartDebug_rxBufferWrite)
            {
                if(UartDebug_rxBufferLoopDetect > 0u)
                {
                    size = UartDebug_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(UartDebug_rxBufferRead < UartDebug_rxBufferWrite)
            {
                size = (UartDebug_rxBufferWrite - UartDebug_rxBufferRead);
            }
            else
            {
                size = (UartDebug_RXBUFFERSIZE - UartDebug_rxBufferRead) + UartDebug_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_EnableRxInt();
            #endif /* End UartDebug_RX_INTERRUPT_ENABLED */

        #else /* UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = (UartDebug_RXSTATUS_REG & UartDebug_RX_STS_FIFO_NOTEMPTY) ? 1u : 0u;

        #endif /* End UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: UartDebug_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the RX RAM buffer by setting the read and write pointers both to zero.
    *  Clears hardware RX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_rxBufferWrite - cleared to zero. 
    *  UartDebug_rxBufferRead - cleared to zero.
    *  UartDebug_rxBufferLoopDetect - cleared to zero. 
    *  UartDebug_rxBufferOverflow - cleared to zero. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may 
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *******************************************************************************/
    void UartDebug_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        UartDebug_RXDATA_AUX_CTL_REG |=  UartDebug_RX_FIFO_CLR;
        UartDebug_RXDATA_AUX_CTL_REG &= ~UartDebug_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
        
        #if(UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_DisableRxInt();
            #endif /* End UartDebug_RX_INTERRUPT_ENABLED */

            UartDebug_rxBufferRead = 0u;
            UartDebug_rxBufferWrite = 0u;
            UartDebug_rxBufferLoopDetect = 0u;
            UartDebug_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(UartDebug_RX_INTERRUPT_ENABLED)
                UartDebug_EnableRxInt();
            #endif /* End UartDebug_RX_INTERRUPT_ENABLED */
        #endif /* End UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH */
        
    }


    /*******************************************************************************
    * Function Name: UartDebug_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  UartDebug__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address 
    *                                               detection
    *  UartDebug__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer 
    *                                               address detection
    *  UartDebug__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address 
    *                                               detection
    *  UartDebug__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer 
    *                                               address detection
    *  UartDebug__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_rxAddressMode - the parameter stored in this variable for 
    *   the farther usage in RX ISR.
    *  UartDebug_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void UartDebug_SetRxAddressMode(uint8 addressMode)  
                                                        
    {
        #if(UartDebug_RXHW_ADDRESS_ENABLED)
            #if(UartDebug_CONTROL_REG_REMOVED)
                addressMode = addressMode;
            #else /* UartDebug_CONTROL_REG_REMOVED */
                uint8 tmpCtrl = 0u;
                tmpCtrl = UartDebug_CONTROL_REG & ~UartDebug_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= ((addressMode << UartDebug_CTRL_RXADDR_MODE0_SHIFT) & 
                           UartDebug_CTRL_RXADDR_MODE_MASK);
                UartDebug_CONTROL_REG = tmpCtrl;
                #if(UartDebug_RX_INTERRUPT_ENABLED && \
                   (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH) )
                    UartDebug_rxAddressMode = addressMode;
                    UartDebug_rxAddressDetected = 0u;
                #endif /* End UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH*/   
            #endif /* End UartDebug_CONTROL_REG_REMOVED */
        #else /* UartDebug_RXHW_ADDRESS_ENABLED */
            addressMode = addressMode;
        #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: UartDebug_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void UartDebug_SetRxAddress1(uint8 address) 

    {
        UartDebug_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: UartDebug_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void UartDebug_SetRxAddress2(uint8 address) 
    {
        UartDebug_RXADDRESS2_REG = address;
    }
        
#endif  /* UartDebug_RX_ENABLED || UartDebug_HD_ENABLED*/


#if( (UartDebug_TX_ENABLED) || (UartDebug_HD_ENABLED) )

    #if(UartDebug_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: UartDebug_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void UartDebug_EnableTxInt(void) 
        {
            CyIntEnable(UartDebug_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: UartDebug_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void UartDebug_DisableTxInt(void) 
        {
            CyIntDisable(UartDebug_TX_VECT_NUM);
        }

    #endif /* UartDebug_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: UartDebug_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void UartDebug_SetTxInterruptMode(uint8 intSrc) 
    {
        UartDebug_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: UartDebug_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the 
    *  bus is available. WriteTxData sends a byte without checking for buffer room 
    *  or status. It is up to the user to separately check status.    
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  UartDebug_txBuffer - RAM buffer pointer for save data for transmission
    *  UartDebug_txBufferWrite - cyclic index for write to txBuffer, 
    *    incremented after each byte saved to buffer.
    *  UartDebug_txBufferRead - cyclic index for read from txBuffer, 
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  UartDebug_initVar - checked to identify that the component has been  
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartDebug_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(UartDebug_initVar != 0u)
        {
            #if(UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(UartDebug_TX_INTERRUPT_ENABLED)
                    UartDebug_DisableTxInt();
                #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

                if( (UartDebug_txBufferRead == UartDebug_txBufferWrite) &&
                   !(UartDebug_TXSTATUS_REG & UartDebug_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    UartDebug_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(UartDebug_txBufferWrite >= UartDebug_TXBUFFERSIZE)
                    {
                        UartDebug_txBufferWrite = 0;
                    }

                    UartDebug_txBuffer[UartDebug_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    UartDebug_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(UartDebug_TX_INTERRUPT_ENABLED)
                    UartDebug_EnableTxInt();
                #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

            #else /* UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                UartDebug_TXDATA_REG = txDataByte;

            #endif /* End UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: UartDebug_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to 
    *  the user to handle all bits in this return value accordingly, even if the bit 
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.    
    *
    *******************************************************************************/
    uint8 UartDebug_ReadTxStatus(void) 
    {
        return(UartDebug_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: UartDebug_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_txBuffer - RAM buffer pointer for save data for transmission
    *  UartDebug_txBufferWrite - cyclic index for write to txBuffer, 
    *     checked to identify free space in txBuffer and incremented after each byte 
    *     saved to buffer.
    *  UartDebug_txBufferRead - cyclic index for read from txBuffer, 
    *     checked to identify free space in txBuffer.
    *  UartDebug_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void UartDebug_PutChar(uint8 txDataByte) 
    {
            #if(UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH)

                /* Block if buffer is full, so we dont overwrite. */
                while( UartDebug_txBufferWrite == (UartDebug_txBufferRead - 1u) ||
                    (uint8)(UartDebug_txBufferWrite - UartDebug_txBufferRead) ==
                    (uint8)(UartDebug_TXBUFFERSIZE - 1u) )
                {
                    /* Software buffer is full. */
                }
                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(UartDebug_TX_INTERRUPT_ENABLED)
                    UartDebug_DisableTxInt();
                #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

                if( (UartDebug_txBufferRead == UartDebug_txBufferWrite) &&
                   !(UartDebug_TXSTATUS_REG & UartDebug_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    UartDebug_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(UartDebug_txBufferWrite >= UartDebug_TXBUFFERSIZE)
                    {
                        UartDebug_txBufferWrite = 0;
                    }

                    UartDebug_txBuffer[UartDebug_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    UartDebug_txBufferWrite++;

                }

                /* Enable Rx interrupt. */
                #if(UartDebug_TX_INTERRUPT_ENABLED)
                    UartDebug_EnableTxInt();
                #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

            #else /* UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */

                /* Block if there isnt room. */
                while(UartDebug_TXSTATUS_REG & UartDebug_TX_STS_FIFO_FULL);

                /* Add directly to the FIFO. */
                UartDebug_TXDATA_REG = txDataByte;

            #endif /* End UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: UartDebug_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: char pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole 
    *  string, it will block until the entire string has been written to the 
    *  transmit buffer.
    *
    *******************************************************************************/
    void UartDebug_PutString(char* string) 
    {
        /* If not Initialized then skip this function*/
        if(UartDebug_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(*string != 0u)
            {
                UartDebug_PutChar(*string++);
            }
        }
    }


    /*******************************************************************************
    * Function Name: UartDebug_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartDebug_PutArray(uint8* string, uint8 byteCount) 
                                                                    
    {
        /* If not Initialized then skip this function*/
        if(UartDebug_initVar != 0u)
        {
            while(byteCount > 0u)
            {
                UartDebug_PutChar(*string++);
                byteCount--;
            }
        }
    }


    /*******************************************************************************
    * Function Name: UartDebug_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartDebug_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(UartDebug_initVar != 0u)
        {
            UartDebug_PutChar(txDataByte);
            UartDebug_PutChar(0x0Du);
            UartDebug_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: UartDebug_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  UartDebug_txBufferWrite - used to calculate left space. 
    *  UartDebug_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 UartDebug_GetTxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_TX_INTERRUPT_ENABLED)
                UartDebug_DisableTxInt();
            #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

            if(UartDebug_txBufferRead == UartDebug_txBufferWrite)
            {
                size = 0u;
            }
            else if(UartDebug_txBufferRead < UartDebug_txBufferWrite)
            {
                size = (UartDebug_txBufferWrite - UartDebug_txBufferRead);
            }
            else
            {
                size = (UartDebug_TXBUFFERSIZE - UartDebug_txBufferRead) + UartDebug_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(UartDebug_TX_INTERRUPT_ENABLED)
                UartDebug_EnableTxInt();
            #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

        #else /* UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */

            size = UartDebug_TXSTATUS_REG;

            /* Is the fifo is full. */
            if(size & UartDebug_TX_STS_FIFO_FULL)
            {
                size = UartDebug_FIFO_LENGTH;
            }
            else if(size & UartDebug_TX_STS_FIFO_EMPTY)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: UartDebug_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the TX RAM buffer by setting the read and write pointers both to zero.
    *  Clears the hardware TX FIFO.  Any data present in the FIFO will not be sent.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_txBufferWrite - cleared to zero. 
    *  UartDebug_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void UartDebug_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        /* clear the HW FIFO */
        UartDebug_TXDATA_AUX_CTL_REG |=  UartDebug_TX_FIFO_CLR;
        UartDebug_TXDATA_AUX_CTL_REG &= ~UartDebug_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartDebug_TX_INTERRUPT_ENABLED)
                UartDebug_DisableTxInt();
            #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

            UartDebug_txBufferRead = 0u;
            UartDebug_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(UartDebug_TX_INTERRUPT_ENABLED)
                UartDebug_EnableTxInt();
            #endif /* End UartDebug_TX_INTERRUPT_ENABLED */

        #endif /* End UartDebug_TXBUFFERSIZE > UartDebug_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: UartDebug_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return 
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartDebug_initVar - checked to identify that the component has been  
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition 
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed 
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete 
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void UartDebug_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(UartDebug_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(UartDebug_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == UartDebug_SEND_BREAK) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() |
                                                          UartDebug_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    UartDebug_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = UartDebug_TXSTATUS_REG;
                    }while(tmpStat & UartDebug_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == UartDebug_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = UartDebug_TXSTATUS_REG;
                    }while(~tmpStat & UartDebug_TX_STS_COMPLETE);
                }

                if( (retMode == UartDebug_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartDebug_REINIT) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT) )
                {
                    UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() &
                                                         ~UartDebug_CTRL_HD_SEND_BREAK);
                }

            #else /* UartDebug_HD_ENABLED Full Duplex mode */

                static uint8 tx_period; 
                
                if( (retMode == UartDebug_SEND_BREAK) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit @ Break signal in Full Duplex mode*/
                    if( (UartDebug_PARITY_TYPE != UartDebug__B_UART__NONE_REVB) ||
                         UartDebug_PARITY_TYPE_SW )
                    {
                        UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() |
                                                              UartDebug_CTRL_HD_SEND_BREAK);
                    }                                                          

                    #if(UartDebug_TXCLKGEN_DP)
                        tx_period = UartDebug_TXBITCLKTX_COMPLETE_REG;
                        UartDebug_TXBITCLKTX_COMPLETE_REG = UartDebug_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = UartDebug_TXBITCTR_PERIOD_REG;
                        UartDebug_TXBITCTR_PERIOD_REG = UartDebug_TXBITCTR_BREAKBITS8X;
                    #endif /* End UartDebug_TXCLKGEN_DP */

                    /* Send zeros*/
                    UartDebug_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = UartDebug_TXSTATUS_REG;
                    }while(tmpStat & UartDebug_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == UartDebug_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = UartDebug_TXSTATUS_REG;
                    }while(~tmpStat & UartDebug_TX_STS_COMPLETE);
                }

                if( (retMode == UartDebug_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartDebug_REINIT) ||
                    (retMode == UartDebug_SEND_WAIT_REINIT) )
                {

                    #if(UartDebug_TXCLKGEN_DP)
                        UartDebug_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        UartDebug_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End UartDebug_TXCLKGEN_DP */

                    if( (UartDebug_PARITY_TYPE != UartDebug__B_UART__NONE_REVB) || 
                         UartDebug_PARITY_TYPE_SW )
                    {
                        UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() &
                                                             ~UartDebug_CTRL_HD_SEND_BREAK);
                    }                                     
                }
            #endif    /* End UartDebug_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: UartDebug_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void UartDebug_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
            UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() | UartDebug_CTRL_MARK);
        }
        else
        {
            UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() & ~UartDebug_CTRL_MARK);
        }
    }

#endif  /* EndUartDebug_TX_ENABLED */

#if(UartDebug_HD_ENABLED)


    /*******************************************************************************
    * Function Name: UartDebug_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART. 
    *
    * Side Effects:
    *  Disable RX interrupt mask, when software buffer has been used.
    *
    *******************************************************************************/
    void UartDebug_LoadTxConfig(void) 
    {
        #if((UartDebug_RX_INTERRUPT_ENABLED) && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            UartDebug_SetRxInterruptMode(0);
        #endif /* UartDebug_RX_INTERRUPT_ENABLED */

        UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() | UartDebug_CTRL_HD_SEND);
        UartDebug_RXBITCTR_PERIOD_REG = UartDebug_HD_TXBITCTR_INIT;
    }


    /*******************************************************************************
    * Function Name: UartDebug_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    * Side Effects:
    *  Set RX interrupt mask based on customizer settings, when software buffer 
    *  has been used.
    *
    *******************************************************************************/
    void UartDebug_LoadRxConfig(void) 
    {
        #if((UartDebug_RX_INTERRUPT_ENABLED) && (UartDebug_RXBUFFERSIZE > UartDebug_FIFO_LENGTH))
            /* Enable RX interrupt mask before set RX configuration */
            UartDebug_SetRxInterruptMode(UartDebug_INIT_RX_INTERRUPTS_MASK);    
        #endif /* UartDebug_RX_INTERRUPT_ENABLED */
        
        UartDebug_WriteControlRegister(UartDebug_ReadControlRegister() & ~UartDebug_CTRL_HD_SEND);
        UartDebug_RXBITCTR_PERIOD_REG = UartDebug_HD_RXBITCTR_INIT;
    }

#endif  /* UartDebug_HD_ENABLED */


/* [] END OF FILE */
