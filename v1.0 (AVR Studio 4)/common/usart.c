/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* usart.c
* Written By: Geoffrey Hunter
* Last Modification: 22/12/2010
*
***************************************************************
*/

/***Header Inclusions***/
#include "usart.h"

/***Constants***/
#define BAUD

//TX/RX Buffer Size
#define BUFFER_SIZE 50

/***Function Declarations***/
void usart_send_byte(void);

/***Variables***/
static uint8_t rx_buffer[BUFFER_SIZE];
static uint8_t rx_read_buffer_pos = 0;
static uint8_t rx_write_buffer_pos = 0;
static uint8_t tx_buffer[BUFFER_SIZE];
static uint8_t tx_read_buffer_pos = 0;
static uint8_t tx_write_buffer_pos = 0;
static uint8_t rx_buffer_ovf_flg = false;

/***ISR's***/

//Store received byte into buffer when interrupt is triggered
ISR(USART_RXC_vect)
{
	if( ((rx_write_buffer_pos + 1) == rx_read_buffer_pos) || 
		( (rx_write_buffer_pos == (BUFFER_SIZE - 1)) && (rx_read_buffer_pos == 0)) )
	{	
		// Read from register to clear interrupt
		rx_buffer_ovf_flg = UDR;
		//	Overflow has occured
		rx_buffer_ovf_flg = true;
	}
	else
	{
		// Check if buffer has reached end of buffer
		if(rx_write_buffer_pos == (BUFFER_SIZE - 1))
		{
			rx_write_buffer_pos = 0;
		}
		else
		{
			rx_write_buffer_pos++;
		}
	}
	// Write received data to buffer
	rx_buffer[rx_write_buffer_pos] = UDR;
	
}

//On clear register, insert byte if write_buffer is not the same as the write buffer
ISR(USART_UDRE_vect)
{
	
	// Check if there is more data to send in buffer
	if(tx_read_buffer_pos == tx_write_buffer_pos)
    {
		//Disable interrupts
        UCSRB &= ~(1<<UDRIE);
    }
	else
	{
		if(tx_read_buffer_pos == (BUFFER_SIZE-1))
		{
			tx_read_buffer_pos = 0;
			
		}
		else
		{
			tx_read_buffer_pos++;
			
		}
        UDR = tx_buffer[tx_read_buffer_pos];
    }

}




void usart_init(void)
{
	// Set baud rate (9600)
	UBRRH = 0;
	UBRRL = 48; //51 //48 works for remote //49 works for skateboard
	// Enabe TX and RX, enable rx interrups (tx interrupts enabled when data loaded into tx buffer)
	UCSRB = (1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN)| (1<<TXEN) | (0<<UCSZ2);
	// Select UCSRC, 1-stop bit, 8-bits of data
	UCSRC = (1<<URSEL) | (0<<UMSEL) | (UPM1<<0) | (UPM0<<0) | (USBS<<0) | (1<<UCSZ1) | (1<<UCSZ0);

	// Clear the tx buffer ready flag as usart is interrupt driven (do this set after intialising usart)
	UCSRA = (0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<PE) | (0<<U2X);
}

// Loads data into transmit buffer. Stops when finds null string (make sure to add one to input!).
// Terminates if message is longer than BUFFER_SIZE
void usart_write_to_tx_buffer(uint8_t data)
{
	//Stall untill there is free space to insert character into buffer
	while( ((tx_write_buffer_pos + 1) == tx_read_buffer_pos) || ( (tx_write_buffer_pos == BUFFER_SIZE) && (tx_read_buffer_pos == 0) ))
	{
		
	}
	
	//Increment write buffer
	if(tx_write_buffer_pos == (BUFFER_SIZE-1))
	{
		tx_write_buffer_pos = 0;
	}
	else
	{
		tx_write_buffer_pos++;
	}
	
	//Write data to tx buffer
	tx_buffer[tx_write_buffer_pos] = data;

	//Enables data register empty interrupt
	 UCSRB |= (1<<UDRIE);
}

uint8_t usart_space_in_tx_buffer(void)
{
	if( (tx_write_buffer_pos + 1) != tx_read_buffer_pos)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

void usart_send(uint8_t *data, uint8_t num_of_bytes)
{
	uint8_t x = 0;
	// Place bytes in tx buffer
	while(x != num_of_bytes)
	{
		usart_write_to_tx_buffer(data[x]);
		x++;
	}
}

//Returns true if there is a new byte present in rx buffer, and stores it in data. Else returns false.
uint8_t usart_get_byte(uint8_t* data)
{
	if(rx_read_buffer_pos != rx_write_buffer_pos)
	{
		if(rx_read_buffer_pos == (BUFFER_SIZE - 1))
		{
			rx_read_buffer_pos = 0;
		}
		else
		{
			rx_read_buffer_pos++;
		}
		data[0] = rx_buffer[rx_read_buffer_pos];
		return true;
	}
	else
	{
		return false;
	}
}

uint8_t usart_rx_overflow(void)
{
	return rx_buffer_ovf_flg;
}

