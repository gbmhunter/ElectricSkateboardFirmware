/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* buzzer.c
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

/***Header Inclusions***/
#include "buzzer.h"

/*** Constants ***/



/*** Local Function Declarations ***/


/*** Variables ***/
static uint16_t count = 0;
static uint16_t count_limit = 0;

void buzzer_init(void)
{
	// Set buzzer pin as output
	DDRB |= (1<<PB0);
}

void buzzer_on(void)
{
	// Set pin high
	PORTB |= (1<<PB0);
}

void buzzer_off(void)
{
	// Set pin low
	PORTB &= ((1<<PB0)^0xFF);
}

void buzzer_single_beep(void)
{
	
	count = 0;
	count_limit = BUZZER_SINGLE_BEEP_CYCLES;
	buzzer_on();	
}

void buzzer_update(void)
{
	if(count_limit != 0)
	{
		count++;
		if(count == count_limit)
		{
			 buzzer_off();
			 count = 0;
			 count_limit = 0;
		}
	}
}
