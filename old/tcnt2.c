/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* tcnt2.c
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

/***Header Inclusions***/
#include "tcnt2.h"

/***Constants***/



/***Local Function Declarations***/


/***Variables***/


void tcnt2_init(void)
{
	// Enable OC2 pin as an output
	DDRB |= (1<<PB3);

	// Set clock surce as main clock
	ASSR = (0<<AS2);
	OCR2 = 100;
	// OC2 output toggle, compare match mode, no clock (use tcnt2_enable to enable clock and start operation)
	TCCR2 = (0<<FOC2) | (1<<WGM21) | (0<<5) | (1<<4) | (0<<WGM20) | (1<<CS22) | (1<<CS21) | (0<<CS20);
	OCR2 = 100;
}

void tcnt2_set_limit(uint8_t limit)
{
	OCR2 = limit;
}

void tcnt2_enable(void)
{
	TCCR2 = (0<<FOC2) | (1<<WGM21) | (0<<COM21) | (1<<COM20) | (0<<WGM20) | (1<<CS22) | (1<<CS21) | (0<<CS20);
}

void tcnt2_disable(void)
{
	TCCR2 = (0<<FOC2) | (1<<WGM21) | (0<<COM21) | (1<<COM20) | (0<<WGM20) | (0<<CS22) | (0<<CS21) | (0<<CS20);
}
