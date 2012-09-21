/*
***************************************************************
* Geo's Wireless Skateboard: Common Files
* tcnt0.c
* Written By: Geoffrey Hunter
* Last Modification: 22/12/2010
*
***************************************************************
*/

/***Header Inclusions***/
#include "tcnt0.h"

/***Constants***/

void tcnt0_init(void)
{
	// Set up timer/counter with 1024 clk divisor
	TCCR0 = (1<<CS02) | (0<<CS01) | (1<<CS00);
	
	//Enable overflow interrupt on TCNT0
	TIMSK = TIMSK  | (1<<TOIE0);

}
