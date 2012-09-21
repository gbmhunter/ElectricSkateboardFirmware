#include "pdisp.h"

int letter[26][5] = {	{~0xF8, ~0x14, ~0x12, ~0x14, ~0xF8},
			{~0xFE, ~0x82, ~0x92, ~0x6C, ~0x00},
			{~0x7C, ~0x82, ~0x82, ~0x44, ~0x00}	};

void collumn(int x) // This is spelt wrongly!?!
{
	switch(x)
	{
		case 1: 
			PORTB = ~0;
			PORTC = ~4;
		break;
		case 2: 
			PORTB = ~0;
			PORTC = ~8; 
		break;
		case 3: 
			PORTB = ~1;
			PORTC = ~0;
		break;
		case 4: 
			PORTB = ~2;
			PORTC = ~0;
		break;
		case 5: 
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

	int char_start = 0;
	int count = 0;
	int col_num = 0;
	int col_on = 0;
	int position = 0;
	int char_actual = 0;

	while(1)
	{
		count = count + 1;
		
		if(count == 20){ // controls Speed of scrolling
			position = position + 1; //Moves the display once over every 20 times
			count = 0;
			if(position == 6){ // Increments starting character once 1st one has fully moved off screen
				char_start = char_start + 1;
				position = 0;
			}
			if(char_start == 4){
				char_start = 0;  //Resests back to A after displaying C
			}
		}
		col_num = position;	

		for(col_on = 1; col_on < 6; ++col_on)
		{
			TCNT1 = 0;

				if (col_num >= 6){ // Shows the start of the next letter
					char_actual = char_start + 1;
					PORTD = letter[char_actual][(col_num-5)];
				}
				else{
					char_actual = char_start;
					PORTD = letter[char_actual][(col_num)];
				}
				col_num = col_num + 1;
				collumn(col_on);
				
				

			while (TCNT1 < 5) // controls resolution
   				continue;
		}
		
		
	}
	//return(0);
}

