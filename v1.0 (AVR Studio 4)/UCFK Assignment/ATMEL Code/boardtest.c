#include <avr/io.h>
#include <stdint.h>

void collumn(int x) // This is spelt wrongly!?!
{
	switch(x)
	{
		case 1: 
			PORTB = ~1;
			PORTC = ~0;
		break;
		case 2: 
			PORTB = ~2;
			PORTC = ~0; 
		break;
		case 3: 
			PORTB = ~4;
			PORTC = ~0;
		break;
		case 4: 
			PORTB = ~0;
			PORTC = ~4;
		break;
		case 5: 
			PORTB = ~0;
			PORTC = ~8;
		break;
	}
}

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

		PORTD = ~0xFE;
		PORTB = ~0x00;
		PORTC = ~0x00;

int x = 0;

	while(1)
	{
		for(x=0; x<=5; ++x)
		{
				collumn(x);
			TCNT1 = 0;
			while (TCNT1 < 0x0400) 
			{
				continue;
			}
		}

		
	}
	return(0);
}

