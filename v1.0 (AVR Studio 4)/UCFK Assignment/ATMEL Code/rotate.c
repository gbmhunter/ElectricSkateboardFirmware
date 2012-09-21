#include <avr/io.h>
#include <stdint.h>

int main(void)
{
	uint8_t position;
	
	/*
	 *   Initialisation
	 * 		- Set data direction registers
	 * 		- Set timer controls
	 */
	DDRB = 0x07;
	DDRC = 0x0C;
	DDRD = 0xFE;
	TCCR1A = 0x00;
	TCCR1B = 0x05;

	position = 0x02;
	while(1)
	{
		TCNT1 = 0;

		PORTD = ~position;
		PORTB = ~0x00;
		PORTC = ~0x04;

		position = position << 1;
		if (position == 0)
			position = 0x02;

		while (TCNT1 < 0x0400) 
		{
			continue;
		}
	}
	return(0);
}

