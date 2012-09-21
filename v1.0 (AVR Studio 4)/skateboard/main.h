/***************************************************************
 * Geo's Wireless Skateboard: Skateboard Atmega8
 * main.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 23/12/2010
 *
 **************************************************************/

//***Header Guard***
#ifndef _MAIN_H
#define _MAIN_H

//***Header Inclusions
#include "../common/tcnt0.h"
//#include "../common/tcnt2.h"
#include "../common/usart.h"
#include "../common/comms.h"
#include "motor.h"
#include "buzzer.h"
#include "alarm.h"

//***Function Prototypes
void setup_leds(void);
void setup_xbee(void);

/***ENUMERATIONS***/
enum main_states_enum{
	off,
	in_range,
	on,
	alarm
};

#endif
