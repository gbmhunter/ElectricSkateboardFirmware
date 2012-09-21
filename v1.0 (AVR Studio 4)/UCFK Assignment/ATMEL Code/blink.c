#include <avr/io.h>
#include <stdint.h>

int main(void)
{	
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

	PORTD = ~0x00;
	while(1)
	{
		TCNT1 = 0;

		PORTD = (PORTD ^ 0x02);
		PORTB = ~0x00;
		PORTC = ~0x04;

		while (TCNT1 < 0x0400) 
		{
			continue;
		}
	}
	return(0);
}
