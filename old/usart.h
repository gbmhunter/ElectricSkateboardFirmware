/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* usart.h
* Written By: Geoffrey Hunter
* Last Modification: 14/12/2010
*
***************************************************************
*/

//***Header Guard***
#ifndef _USART_H
#define _USART_H

//***File Inclusions***
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/led.h"
#include "../common/definitions.h"

/***Function Declarations***/

// Initialization function
void usart_init(uint8_t platform);
// Use to retrieve data. Returns the number of data bytes received and puts them into the array data
uint8_t usart_get_byte(uint8_t *data);
void usart_send(uint8_t *data, uint8_t num_of_bytes);
uint8_t usart_space_in_tx_buffer(void);
uint8_t usart_rx_overflow(void);


#endif
