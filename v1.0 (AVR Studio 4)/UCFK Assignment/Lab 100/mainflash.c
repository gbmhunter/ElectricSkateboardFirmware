#include "pdisp.h"

int letter[26][7] = {	{~0xF8, ~0x14, ~0x12, ~0x14, ~0xF8},
			{~0xFE, ~0x82, ~0x92, ~0x6C, ~0x00},
			{~0x7C, ~0x82, ~0x82, ~0x44, ~0x00}	};

void collumn(int x)
{
	switch(x)
	{
		case 0: 
			PORTB = ~0;
			PORTC = ~4;
		break;
		case 1: 
			PORTB = ~0;
			PORTC = ~8; 
		break;
		case 2: 
			PORTB = ~1;
			PORTC = ~0;
		break;
		case 3: 
			PORTB = ~2;
			PORTC = ~0;
		break;
		case 4: 
			PORTB = ~4;
			PORTC = ~0;
		break;
	}
}

void *thread_main3( void *ptr )
{
	PORTD = ~0x00;
	PORTB = ~0x00;
	PORTC = ~0x00;

	int character = 0;
	int count = 0;
	int colnum = 0;

	while(1)
	{
		count = count + 1;
		character = (count - (count % 50)) / 50;

		for(colnum = 0; colnum < 5; ++colnum)
		{
			TCNT1 = 0;
			PORTD = letter[character][colnum];
			collumn(colnum);
			while (TCNT1 < 5)
   				continue;
		}
		
	}
	//return(0);
}
