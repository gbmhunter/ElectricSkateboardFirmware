/*
***************************************************************
* Geo's Wireless Skateboard: Remote ATmega8
* button.h
* Written By: Geoffrey Hunter
* Last Modification: 04/01/2011
*
***************************************************************
*/

//***Header Guard***
#ifndef _BUTTON_H
#define _BUTTON_H

//***File Inclusions***
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/definitions.h"
#include "../common/led.h"

//***Function Prototypes***
void button_init(uint8_t** button_port_in, uint8_t* button_pin_in);
void button_update(void);
uint8_t button_been_pressed(uint8_t button_num);

/*** Definitions ***/
//Number to call cycles for debouncing
#define DEBOUNCE_TIME 10

#endif
