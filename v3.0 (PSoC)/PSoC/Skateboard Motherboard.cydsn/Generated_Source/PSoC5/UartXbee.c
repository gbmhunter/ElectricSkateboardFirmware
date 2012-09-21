/*******************************************************************************
* File Name: UartXbee.c
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


#include "UartXbee.h"
#include "CyLib.h"


/***************************************
* Global data allocation
***************************************/

#if( UartXbee_TX_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
    volatile uint8 UartXbee_txBuffer[UartXbee_TXBUFFERSIZE];
    volatile uint8 UartXbee_txBufferRead = 0u;
    uint8 UartXbee_txBufferWrite = 0u;
#endif /* End UartXbee_TX_ENABLED */
#if( ( UartXbee_RX_ENABLED || UartXbee_HD_ENABLED ) && \
     (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) )
    volatile uint8 UartXbee_rxBuffer[UartXbee_RXBUFFERSIZE];
    volatile uint8 UartXbee_rxBufferRead = 0u;
    volatile uint8 UartXbee_rxBufferWrite = 0u;
    volatile uint8 UartXbee_rxBufferLoopDetect = 0u;
    volatile uint8 UartXbee_rxBufferOverflow = 0u;
    #if (UartXbee_RXHW_ADDRESS_ENABLED)
        volatile uint8 UartXbee_rxAddressMode = UartXbee_RXADDRESSMODE;
        volatile uint8 UartXbee_rxAddressDetected = 0u;
    #endif /* End EnableHWAddress */    
#endif /* End UartXbee_RX_ENABLED */


/***************************************
* Local data allocation
***************************************/

uint8 UartXbee_initVar = 0u;


/*******************************************************************************
* Function Name: UartXbee_Start
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
*  The UartXbee_intiVar variable is used to indicate initial 
*  configuration of this component. The variable is initialized to zero (0u) 
*  and set to one (1u) the first time UART_Start() is called. This allows for 
*  component initialization without re-initialization in all subsequent calls 
*  to the UartXbee_Start() routine. 
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartXbee_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(UartXbee_initVar == 0u)
    {
        UartXbee_Init();
        UartXbee_initVar = 1u;
    }
    UartXbee_Enable();
}


/*******************************************************************************
* Function Name: UartXbee_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  UartXbee_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void UartXbee_Init(void) 
{
    #if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)

        #if(UartXbee_RX_INTERRUPT_ENABLED && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            CyIntSetVector(UartXbee_RX_VECT_NUM,   UartXbee_RXISR);
            CyIntSetPriority(UartXbee_RX_VECT_NUM, UartXbee_RX_PRIOR_NUM);
        #endif /* End UartXbee_RX_INTERRUPT_ENABLED */

        #if (UartXbee_RXHW_ADDRESS_ENABLED)
            UartXbee_SetRxAddressMode(UartXbee_RXAddressMode);
            UartXbee_SetRxAddress1(UartXbee_RXHWADDRESS1);
            UartXbee_SetRxAddress2(UartXbee_RXHWADDRESS2);
        #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */

        /* Configure the Initial RX interrupt mask */
        UartXbee_RXSTATUS_MASK_REG  = UartXbee_INIT_RX_INTERRUPTS_MASK;
    #endif /* End UartXbee_RX_ENABLED || UartXbee_HD_ENABLED*/

    #if(UartXbee_TX_ENABLED)
        #if(UartXbee_TX_INTERRUPT_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            CyIntSetVector(UartXbee_TX_VECT_NUM,   UartXbee_TXISR);
            CyIntSetPriority(UartXbee_TX_VECT_NUM, UartXbee_TX_PRIOR_NUM);
        #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(UartXbee_TXCLKGEN_DP)
            UartXbee_TXBITCLKGEN_CTR_REG = UartXbee_BIT_CENTER;
            UartXbee_TXBITCLKTX_COMPLETE_REG = (UartXbee_NUMBER_OF_DATA_BITS + \
                                                    UartXbee_NUMBER_OF_START_BIT) * \
                                                    UartXbee_OVER_SAMPLE_COUNT;
        #else
            UartXbee_TXBITCTR_COUNTER_REG = (UartXbee_NUMBER_OF_DATA_BITS + \
                                                    UartXbee_NUMBER_OF_START_BIT) * \
                                                    UartXbee_OVER_SAMPLE_8;
        #endif /* End UartXbee_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(UartXbee_TX_INTERRUPT_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            UartXbee_TXSTATUS_MASK_REG = UartXbee_TX_STS_FIFO_EMPTY;
        #else
            UartXbee_TXSTATUS_MASK_REG = UartXbee_INIT_TX_INTERRUPTS_MASK;
        #endif /*End UartXbee_TX_INTERRUPT_ENABLED*/
        
    #endif /* End UartXbee_TX_ENABLED */

    #if(UartXbee_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        UartXbee_WriteControlRegister( \
            (UartXbee_ReadControlRegister() & ~UartXbee_CTRL_PARITY_TYPE_MASK) | \
            (UartXbee_PARITY_TYPE << UartXbee_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End UartXbee_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: UartXbee_Enable
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
*  UartXbee_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void UartXbee_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();
    
    #if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        UartXbee_RXBITCTR_CONTROL_REG |= UartXbee_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        UartXbee_RXSTATUS_ACTL_REG  |= UartXbee_INT_ENABLE;
        #if(UartXbee_RX_INTERRUPT_ENABLED && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            CyIntEnable(UartXbee_RX_VECT_NUM);
            #if (UartXbee_RXHW_ADDRESS_ENABLED)
                UartXbee_rxAddressDetected = 0u;
            #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */
        #endif /* End UartXbee_RX_INTERRUPT_ENABLED */
    #endif /* End UartXbee_RX_ENABLED || UartXbee_HD_ENABLED*/

    #if(UartXbee_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!UartXbee_TXCLKGEN_DP)
            UartXbee_TXBITCTR_CONTROL_REG |= UartXbee_CNTR_ENABLE;
        #endif /* End UartXbee_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        UartXbee_TXSTATUS_ACTL_REG |= UartXbee_INT_ENABLE;
        #if(UartXbee_TX_INTERRUPT_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            CyIntEnable(UartXbee_TX_VECT_NUM);
        #endif /* End UartXbee_TX_INTERRUPT_ENABLED*/
     #endif /* End UartXbee_TX_ENABLED */

    #if(UartXbee_INTERNAL_CLOCK_USED)
        /* Set the bit to enable the clock. */
        UartXbee_INTCLOCK_CLKEN_REG |= UartXbee_INTCLOCK_CLKEN_MASK;
    #endif /* End UartXbee_INTERNAL_CLOCK_USED */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UartXbee_Stop
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
void UartXbee_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /*Write Bit Counter Disable */
    #if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)
        UartXbee_RXBITCTR_CONTROL_REG &= ~UartXbee_CNTR_ENABLE;
    #endif /* End UartXbee_RX_ENABLED */

    #if(UartXbee_TX_ENABLED)
        #if(!UartXbee_TXCLKGEN_DP)
            UartXbee_TXBITCTR_CONTROL_REG &= ~UartXbee_CNTR_ENABLE;
        #endif /* End UartXbee_TXCLKGEN_DP */
    #endif /* UartXbee_TX_ENABLED */

    #if(UartXbee_INTERNAL_CLOCK_USED)
        /* Clear the bit to enable the clock. */
        UartXbee_INTCLOCK_CLKEN_REG &= ~UartXbee_INTCLOCK_CLKEN_MASK;
    #endif /* End UartXbee_INTERNAL_CLOCK_USED */
    
    /*Disable internal interrupt component*/
    #if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)
        UartXbee_RXSTATUS_ACTL_REG  &= ~UartXbee_INT_ENABLE;
        #if(UartXbee_RX_INTERRUPT_ENABLED && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            UartXbee_DisableRxInt();
        #endif /* End UartXbee_RX_INTERRUPT_ENABLED */
    #endif /* End UartXbee_RX_ENABLED */
    
    #if(UartXbee_TX_ENABLED)
        UartXbee_TXSTATUS_ACTL_REG &= ~UartXbee_INT_ENABLE;
        #if(UartXbee_TX_INTERRUPT_ENABLED && (UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            UartXbee_DisableTxInt();
        #endif /* End UartXbee_TX_INTERRUPT_ENABLED */
    #endif /* End UartXbee_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: UartXbee_ReadControlRegister
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
uint8 UartXbee_ReadControlRegister(void) 
{
    #if( UartXbee_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(UartXbee_CONTROL_REG);
    #endif /* End UartXbee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UartXbee_WriteControlRegister
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
void  UartXbee_WriteControlRegister(uint8 control) 
{
    #if( UartXbee_CONTROL_REG_REMOVED )
        control = control;      /* Reassigning to release compiler warning */ 
    #else
       UartXbee_CONTROL_REG = control;
    #endif /* End UartXbee_CONTROL_REG_REMOVED */
}


#if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)

    #if(UartXbee_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: UartXbee_EnableRxInt
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
        void UartXbee_EnableRxInt(void) 
        {
            CyIntEnable(UartXbee_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: UartXbee_DisableRxInt
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
        void UartXbee_DisableRxInt(void) 
        {
            CyIntDisable(UartXbee_RX_VECT_NUM);
        }

    #endif /* UartXbee_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: UartXbee_SetRxInterruptMode
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
    void UartXbee_SetRxInterruptMode(uint8 intSrc) 
    {
        UartXbee_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: UartXbee_ReadRxData
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
    *  UartXbee_rxBuffer - RAM buffer pointer for save received data.
    *  UartXbee_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  UartXbee_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  UartXbee_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UartXbee_ReadRxData(void) 
    {
        uint8 rxData;

        #if(UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_DisableRxInt();
            #endif /* End UartXbee_RX_INTERRUPT_ENABLED */

            if( (UartXbee_rxBufferRead != UartXbee_rxBufferWrite) ||
                (UartXbee_rxBufferLoopDetect > 0u) )
            {

                rxData = UartXbee_rxBuffer[UartXbee_rxBufferRead];

                UartXbee_rxBufferRead++;

                if(UartXbee_rxBufferRead >= UartXbee_RXBUFFERSIZE)
                {
                    UartXbee_rxBufferRead = 0u;
                }

                if(UartXbee_rxBufferLoopDetect > 0u )
                {
                    UartXbee_rxBufferLoopDetect = 0u;
                    #if( (UartXbee_RX_INTERRUPT_ENABLED) && (UartXbee_FLOW_CONTROL != 0u) && \
                         (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( UartXbee_HD_ENABLED )
                            if((UartXbee_CONTROL_REG & UartXbee_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                UartXbee_RXSTATUS_MASK_REG  |= UartXbee_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            UartXbee_RXSTATUS_MASK_REG  |= UartXbee_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end UartXbee_HD_ENABLED */
                    #endif /* UartXbee_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = UartXbee_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_EnableRxInt();
            #endif /* End UartXbee_RX_INTERRUPT_ENABLED */

        #else /* UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = UartXbee_RXDATA_REG;

        #endif /* UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UartXbee_ReadRxStatus
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
    *  UartXbee_rxBufferOverflow - used to indicate overload condition. 
    *   It set to one in RX interrupt when there isn?t free space in 
    *   UartXbee_rxBufferRead to write new data. This condition returned 
    *   and cleared to zero by this API as an 
    *   UartXbee_RX_STS_SOFT_BUFF_OVER bit along with RX Status register 
    *   bits.
    *
    *******************************************************************************/
    uint8 UartXbee_ReadRxStatus(void) 
    {
        uint8 status;

        status = UartXbee_RXSTATUS_REG;
        status &= UartXbee_RX_HW_MASK;

        #if(UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH)
            if( UartXbee_rxBufferOverflow )
            {
                status |= UartXbee_RX_STS_SOFT_BUFF_OVER;
                UartXbee_rxBufferOverflow = 0u;
            }
        #endif /* UartXbee_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: UartXbee_GetChar
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
    *  UartXbee_rxBuffer - RAM buffer pointer for save received data.
    *  UartXbee_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  UartXbee_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  UartXbee_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 UartXbee_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_DisableRxInt();
            #endif /* UartXbee_RX_INTERRUPT_ENABLED */

            if( (UartXbee_rxBufferRead != UartXbee_rxBufferWrite) ||
                (UartXbee_rxBufferLoopDetect > 0u) )
            {
                rxData = UartXbee_rxBuffer[UartXbee_rxBufferRead];

                UartXbee_rxBufferRead++;

                if(UartXbee_rxBufferRead >= UartXbee_RXBUFFERSIZE)
                {
                    UartXbee_rxBufferRead = 0u;
                }

                if(UartXbee_rxBufferLoopDetect > 0u ) 
                {
                    UartXbee_rxBufferLoopDetect = 0u;
                    #if( (UartXbee_RX_INTERRUPT_ENABLED) && (UartXbee_FLOW_CONTROL != 0u) && \
                         (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) )
                        /* When Hardware Flow Control selected - return RX mask */
                        #if( UartXbee_HD_ENABLED )
                            if((UartXbee_CONTROL_REG & UartXbee_CTRL_HD_SEND) == 0)
                            {   /* In Half duplex mode return RX mask only in RX configuration set, otherwise 
                                *  mask will be returned in LoadRxConfig() API. 
                                */
                                UartXbee_RXSTATUS_MASK_REG  |= UartXbee_RX_STS_FIFO_NOTEMPTY;
                            }
                        #else
                            UartXbee_RXSTATUS_MASK_REG  |= UartXbee_RX_STS_FIFO_NOTEMPTY;
                        #endif /* end UartXbee_HD_ENABLED */
                    #endif /* UartXbee_RX_INTERRUPT_ENABLED and Hardware flow control*/
                }

            }
            else
            {   rxStatus =UartXbee_RXSTATUS_REG;
                if(rxStatus & UartXbee_RX_STS_FIFO_NOTEMPTY)
                {   /* Read received data from FIFO*/
                    rxData = UartXbee_RXDATA_REG;
                    /*Check status on error*/
                    if(rxStatus & (UartXbee_RX_STS_BREAK | UartXbee_RX_STS_PAR_ERROR |
                                   UartXbee_RX_STS_STOP_ERROR | UartXbee_RX_STS_OVERRUN))
                    {
                        rxData = 0u;
                    }    
                }
            }

            /* Enable Rx interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_EnableRxInt();
            #endif /* UartXbee_RX_INTERRUPT_ENABLED */

        #else /* UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

            rxStatus =UartXbee_RXSTATUS_REG;
            if(rxStatus & UartXbee_RX_STS_FIFO_NOTEMPTY)
            {   /* Read received data from FIFO*/
                rxData = UartXbee_RXDATA_REG;
                /*Check status on error*/
                if(rxStatus & (UartXbee_RX_STS_BREAK | UartXbee_RX_STS_PAR_ERROR |
                               UartXbee_RX_STS_STOP_ERROR | UartXbee_RX_STS_OVERRUN))
                {
                    rxData = 0u;
                }
            }
        #endif /* UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: UartXbee_GetByte
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
    uint16 UartXbee_GetByte(void) 
    {
        return ( ((uint16)UartXbee_ReadRxStatus() << 8u) | UartXbee_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: UartXbee_GetRxBufferSize
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
    *  UartXbee_rxBufferWrite - used to calculate left bytes. 
    *  UartXbee_rxBufferRead - used to calculate left bytes.
    *  UartXbee_rxBufferLoopDetect - checked to decide left bytes amount. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 UartXbee_GetRxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_DisableRxInt();
            #endif /* UartXbee_RX_INTERRUPT_ENABLED */

            if(UartXbee_rxBufferRead == UartXbee_rxBufferWrite)
            {
                if(UartXbee_rxBufferLoopDetect > 0u)
                {
                    size = UartXbee_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(UartXbee_rxBufferRead < UartXbee_rxBufferWrite)
            {
                size = (UartXbee_rxBufferWrite - UartXbee_rxBufferRead);
            }
            else
            {
                size = (UartXbee_RXBUFFERSIZE - UartXbee_rxBufferRead) + UartXbee_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_EnableRxInt();
            #endif /* End UartXbee_RX_INTERRUPT_ENABLED */

        #else /* UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = (UartXbee_RXSTATUS_REG & UartXbee_RX_STS_FIFO_NOTEMPTY) ? 1u : 0u;

        #endif /* End UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: UartXbee_ClearRxBuffer
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
    *  UartXbee_rxBufferWrite - cleared to zero. 
    *  UartXbee_rxBufferRead - cleared to zero.
    *  UartXbee_rxBufferLoopDetect - cleared to zero. 
    *  UartXbee_rxBufferOverflow - cleared to zero. 
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
    void UartXbee_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* clear the HW FIFO */
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        UartXbee_RXDATA_AUX_CTL_REG |=  UartXbee_RX_FIFO_CLR;
        UartXbee_RXDATA_AUX_CTL_REG &= ~UartXbee_RX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
        
        #if(UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_DisableRxInt();
            #endif /* End UartXbee_RX_INTERRUPT_ENABLED */

            UartXbee_rxBufferRead = 0u;
            UartXbee_rxBufferWrite = 0u;
            UartXbee_rxBufferLoopDetect = 0u;
            UartXbee_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(UartXbee_RX_INTERRUPT_ENABLED)
                UartXbee_EnableRxInt();
            #endif /* End UartXbee_RX_INTERRUPT_ENABLED */
        #endif /* End UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH */
        
    }


    /*******************************************************************************
    * Function Name: UartXbee_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  UartXbee__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address 
    *                                               detection
    *  UartXbee__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer 
    *                                               address detection
    *  UartXbee__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address 
    *                                               detection
    *  UartXbee__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer 
    *                                               address detection
    *  UartXbee__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UartXbee_rxAddressMode - the parameter stored in this variable for 
    *   the farther usage in RX ISR.
    *  UartXbee_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void UartXbee_SetRxAddressMode(uint8 addressMode)  
                                                        
    {
        #if(UartXbee_RXHW_ADDRESS_ENABLED)
            #if(UartXbee_CONTROL_REG_REMOVED)
                addressMode = addressMode;
            #else /* UartXbee_CONTROL_REG_REMOVED */
                uint8 tmpCtrl = 0u;
                tmpCtrl = UartXbee_CONTROL_REG & ~UartXbee_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= ((addressMode << UartXbee_CTRL_RXADDR_MODE0_SHIFT) & 
                           UartXbee_CTRL_RXADDR_MODE_MASK);
                UartXbee_CONTROL_REG = tmpCtrl;
                #if(UartXbee_RX_INTERRUPT_ENABLED && \
                   (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH) )
                    UartXbee_rxAddressMode = addressMode;
                    UartXbee_rxAddressDetected = 0u;
                #endif /* End UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH*/   
            #endif /* End UartXbee_CONTROL_REG_REMOVED */
        #else /* UartXbee_RXHW_ADDRESS_ENABLED */
            addressMode = addressMode;
        #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: UartXbee_SetRxAddress1
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
    void UartXbee_SetRxAddress1(uint8 address) 

    {
        UartXbee_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: UartXbee_SetRxAddress2
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
    void UartXbee_SetRxAddress2(uint8 address) 
    {
        UartXbee_RXADDRESS2_REG = address;
    }
        
#endif  /* UartXbee_RX_ENABLED || UartXbee_HD_ENABLED*/


#if( (UartXbee_TX_ENABLED) || (UartXbee_HD_ENABLED) )

    #if(UartXbee_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: UartXbee_EnableTxInt
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
        void UartXbee_EnableTxInt(void) 
        {
            CyIntEnable(UartXbee_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: UartXbee_DisableTxInt
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
        void UartXbee_DisableTxInt(void) 
        {
            CyIntDisable(UartXbee_TX_VECT_NUM);
        }

    #endif /* UartXbee_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: UartXbee_SetTxInterruptMode
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
    void UartXbee_SetTxInterruptMode(uint8 intSrc) 
    {
        UartXbee_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: UartXbee_WriteTxData
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
    *  UartXbee_txBuffer - RAM buffer pointer for save data for transmission
    *  UartXbee_txBufferWrite - cyclic index for write to txBuffer, 
    *    incremented after each byte saved to buffer.
    *  UartXbee_txBufferRead - cyclic index for read from txBuffer, 
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  UartXbee_initVar - checked to identify that the component has been  
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartXbee_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(UartXbee_initVar != 0u)
        {
            #if(UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(UartXbee_TX_INTERRUPT_ENABLED)
                    UartXbee_DisableTxInt();
                #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

                if( (UartXbee_txBufferRead == UartXbee_txBufferWrite) &&
                   !(UartXbee_TXSTATUS_REG & UartXbee_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    UartXbee_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(UartXbee_txBufferWrite >= UartXbee_TXBUFFERSIZE)
                    {
                        UartXbee_txBufferWrite = 0;
                    }

                    UartXbee_txBuffer[UartXbee_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    UartXbee_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(UartXbee_TX_INTERRUPT_ENABLED)
                    UartXbee_EnableTxInt();
                #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

            #else /* UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                UartXbee_TXDATA_REG = txDataByte;

            #endif /* End UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: UartXbee_ReadTxStatus
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
    uint8 UartXbee_ReadTxStatus(void) 
    {
        return(UartXbee_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: UartXbee_PutChar
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
    *  UartXbee_txBuffer - RAM buffer pointer for save data for transmission
    *  UartXbee_txBufferWrite - cyclic index for write to txBuffer, 
    *     checked to identify free space in txBuffer and incremented after each byte 
    *     saved to buffer.
    *  UartXbee_txBufferRead - cyclic index for read from txBuffer, 
    *     checked to identify free space in txBuffer.
    *  UartXbee_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void UartXbee_PutChar(uint8 txDataByte) 
    {
            #if(UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH)

                /* Block if buffer is full, so we dont overwrite. */
                while( UartXbee_txBufferWrite == (UartXbee_txBufferRead - 1u) ||
                    (uint8)(UartXbee_txBufferWrite - UartXbee_txBufferRead) ==
                    (uint8)(UartXbee_TXBUFFERSIZE - 1u) )
                {
                    /* Software buffer is full. */
                }
                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(UartXbee_TX_INTERRUPT_ENABLED)
                    UartXbee_DisableTxInt();
                #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

                if( (UartXbee_txBufferRead == UartXbee_txBufferWrite) &&
                   !(UartXbee_TXSTATUS_REG & UartXbee_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    UartXbee_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(UartXbee_txBufferWrite >= UartXbee_TXBUFFERSIZE)
                    {
                        UartXbee_txBufferWrite = 0;
                    }

                    UartXbee_txBuffer[UartXbee_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    UartXbee_txBufferWrite++;

                }

                /* Enable Rx interrupt. */
                #if(UartXbee_TX_INTERRUPT_ENABLED)
                    UartXbee_EnableTxInt();
                #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

            #else /* UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */

                /* Block if there isnt room. */
                while(UartXbee_TXSTATUS_REG & UartXbee_TX_STS_FIFO_FULL);

                /* Add directly to the FIFO. */
                UartXbee_TXDATA_REG = txDataByte;

            #endif /* End UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: UartXbee_PutString
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
    *  UartXbee_initVar - checked to identify that the component has been  
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
    void UartXbee_PutString(char* string) 
    {
        /* If not Initialized then skip this function*/
        if(UartXbee_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(*string != 0u)
            {
                UartXbee_PutChar(*string++);
            }
        }
    }


    /*******************************************************************************
    * Function Name: UartXbee_PutArray
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
    *  UartXbee_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartXbee_PutArray(uint8* string, uint8 byteCount) 
                                                                    
    {
        /* If not Initialized then skip this function*/
        if(UartXbee_initVar != 0u)
        {
            while(byteCount > 0u)
            {
                UartXbee_PutChar(*string++);
                byteCount--;
            }
        }
    }


    /*******************************************************************************
    * Function Name: UartXbee_PutCRLF
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
    *  UartXbee_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void UartXbee_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(UartXbee_initVar != 0u)
        {
            UartXbee_PutChar(txDataByte);
            UartXbee_PutChar(0x0Du);
            UartXbee_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: UartXbee_GetTxBufferSize
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
    *  UartXbee_txBufferWrite - used to calculate left space. 
    *  UartXbee_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 UartXbee_GetTxBufferSize(void) 
                                                            
    {
        uint8 size;

        #if(UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_TX_INTERRUPT_ENABLED)
                UartXbee_DisableTxInt();
            #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

            if(UartXbee_txBufferRead == UartXbee_txBufferWrite)
            {
                size = 0u;
            }
            else if(UartXbee_txBufferRead < UartXbee_txBufferWrite)
            {
                size = (UartXbee_txBufferWrite - UartXbee_txBufferRead);
            }
            else
            {
                size = (UartXbee_TXBUFFERSIZE - UartXbee_txBufferRead) + UartXbee_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(UartXbee_TX_INTERRUPT_ENABLED)
                UartXbee_EnableTxInt();
            #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

        #else /* UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */

            size = UartXbee_TXSTATUS_REG;

            /* Is the fifo is full. */
            if(size & UartXbee_TX_STS_FIFO_FULL)
            {
                size = UartXbee_FIFO_LENGTH;
            }
            else if(size & UartXbee_TX_STS_FIFO_EMPTY)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: UartXbee_ClearTxBuffer
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
    *  UartXbee_txBufferWrite - cleared to zero. 
    *  UartXbee_txBufferRead - cleared to zero.
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
    void UartXbee_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;
        
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();        
        /* clear the HW FIFO */
        UartXbee_TXDATA_AUX_CTL_REG |=  UartXbee_TX_FIFO_CLR;
        UartXbee_TXDATA_AUX_CTL_REG &= ~UartXbee_TX_FIFO_CLR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);

        #if(UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(UartXbee_TX_INTERRUPT_ENABLED)
                UartXbee_DisableTxInt();
            #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

            UartXbee_txBufferRead = 0u;
            UartXbee_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(UartXbee_TX_INTERRUPT_ENABLED)
                UartXbee_EnableTxInt();
            #endif /* End UartXbee_TX_INTERRUPT_ENABLED */

        #endif /* End UartXbee_TXBUFFERSIZE > UartXbee_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: UartXbee_SendBreak
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
    *  UartXbee_initVar - checked to identify that the component has been  
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
    void UartXbee_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(UartXbee_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(UartXbee_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == UartXbee_SEND_BREAK) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() |
                                                          UartXbee_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    UartXbee_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = UartXbee_TXSTATUS_REG;
                    }while(tmpStat & UartXbee_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == UartXbee_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = UartXbee_TXSTATUS_REG;
                    }while(~tmpStat & UartXbee_TX_STS_COMPLETE);
                }

                if( (retMode == UartXbee_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartXbee_REINIT) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT) )
                {
                    UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() &
                                                         ~UartXbee_CTRL_HD_SEND_BREAK);
                }

            #else /* UartXbee_HD_ENABLED Full Duplex mode */

                static uint8 tx_period; 
                
                if( (retMode == UartXbee_SEND_BREAK) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit @ Break signal in Full Duplex mode*/
                    if( (UartXbee_PARITY_TYPE != UartXbee__B_UART__NONE_REVB) ||
                         UartXbee_PARITY_TYPE_SW )
                    {
                        UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() |
                                                              UartXbee_CTRL_HD_SEND_BREAK);
                    }                                                          

                    #if(UartXbee_TXCLKGEN_DP)
                        tx_period = UartXbee_TXBITCLKTX_COMPLETE_REG;
                        UartXbee_TXBITCLKTX_COMPLETE_REG = UartXbee_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = UartXbee_TXBITCTR_PERIOD_REG;
                        UartXbee_TXBITCTR_PERIOD_REG = UartXbee_TXBITCTR_BREAKBITS8X;
                    #endif /* End UartXbee_TXCLKGEN_DP */

                    /* Send zeros*/
                    UartXbee_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = UartXbee_TXSTATUS_REG;
                    }while(tmpStat & UartXbee_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == UartXbee_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = UartXbee_TXSTATUS_REG;
                    }while(~tmpStat & UartXbee_TX_STS_COMPLETE);
                }

                if( (retMode == UartXbee_WAIT_FOR_COMPLETE_REINIT) ||
                    (retMode == UartXbee_REINIT) ||
                    (retMode == UartXbee_SEND_WAIT_REINIT) )
                {

                    #if(UartXbee_TXCLKGEN_DP)
                        UartXbee_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        UartXbee_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End UartXbee_TXCLKGEN_DP */

                    if( (UartXbee_PARITY_TYPE != UartXbee__B_UART__NONE_REVB) || 
                         UartXbee_PARITY_TYPE_SW )
                    {
                        UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() &
                                                             ~UartXbee_CTRL_HD_SEND_BREAK);
                    }                                     
                }
            #endif    /* End UartXbee_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: UartXbee_SetTxAddressMode
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
    void UartXbee_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
            UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() | UartXbee_CTRL_MARK);
        }
        else
        {
            UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() & ~UartXbee_CTRL_MARK);
        }
    }

#endif  /* EndUartXbee_TX_ENABLED */

#if(UartXbee_HD_ENABLED)


    /*******************************************************************************
    * Function Name: UartXbee_LoadTxConfig
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
    void UartXbee_LoadTxConfig(void) 
    {
        #if((UartXbee_RX_INTERRUPT_ENABLED) && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            /* Disable RX interrupts before set TX configuration */
            UartXbee_SetRxInterruptMode(0);
        #endif /* UartXbee_RX_INTERRUPT_ENABLED */

        UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() | UartXbee_CTRL_HD_SEND);
        UartXbee_RXBITCTR_PERIOD_REG = UartXbee_HD_TXBITCTR_INIT;
    }


    /*******************************************************************************
    * Function Name: UartXbee_LoadRxConfig
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
    void UartXbee_LoadRxConfig(void) 
    {
        #if((UartXbee_RX_INTERRUPT_ENABLED) && (UartXbee_RXBUFFERSIZE > UartXbee_FIFO_LENGTH))
            /* Enable RX interrupt mask before set RX configuration */
            UartXbee_SetRxInterruptMode(UartXbee_INIT_RX_INTERRUPTS_MASK);    
        #endif /* UartXbee_RX_INTERRUPT_ENABLED */
        
        UartXbee_WriteControlRegister(UartXbee_ReadControlRegister() & ~UartXbee_CTRL_HD_SEND);
        UartXbee_RXBITCTR_PERIOD_REG = UartXbee_HD_RXBITCTR_INIT;
    }

#endif  /* UartXbee_HD_ENABLED */


/* [] END OF FILE */
