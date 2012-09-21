/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* alarm.c
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

/***Header Inclusions***/
#include "alarm.h"

/***Constants***/
static uint8_t alarm_triggered_flg = false;

void alarm_init(void)
{
	// Sets tilt switch as input
	DDRD &= (0<<PD4)^0xFF;
}

void alarm_update(void)
{
	if(!(PIND & (1<<PD4)))
	{
		alarm_triggered_flg = true;
	}
}

void alarm_reset(void)
{
	alarm_triggered_flg = false;
}

uint8_t alarm_is_triggered(void)
{
	return alarm_triggered_flg;
}
