/*
***************************************************************
* Geo's Wireless Skateboard: Remote ATmega8
* main.h
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

//***Header Guard***
#ifndef _MAIN_H
#define _MAIN_H

//***File Inclusions***
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/comms.h"
#include "../common/led.h"
#include "../common/tcnt0.h"
#include "../common/usart.h"
#include "adc.h"
#include "button.h"

//***Function Prototypes***

/***ENUMERATIONS***/
typedef enum{
	off,
	in_range,
	on,
	alarm
} main_state_t;

#endif
