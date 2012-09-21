#include "pdisp.h"

#define BV(x) (1 << (x))

void setled(int state,int x, int y)
{
	PORTD = ~BV(y);
	switch(x){
		case 1: 
			PORTC = ~4;
		break;
		case 2: 
			PORTC = ~8; 
		break;
		case 3: 
			PORTB = ~1;
		break;
		case 4: 
			PORTB = ~2;
		break;
		case 5: 
			PORTB = ~4;
		break;
	}
}

void *thread_main3( void *ptr )
{
		PORTD = ~0x00;
		PORTB = ~0x00;
		PORTC = ~0x00;
	/*while(1)
	{
		TCNT0 = 0;

		PORTD = PORTD ^ 2;
		PORTB = PORTB ^ 0x00;
		PORTC = PORTC ^ 0x04;

		while (TCNT0 < 50)
   		continue;
	}
	//return(0);
	*/
	setled(1,1,7);
	setled(1,1,6);
	setled(1,2,5);
	/*setled(1,2,4);
	setled(1,3,3);
	setled(1,3,2);
	setled(1,4,4);
	setled(1,4,5);
	setled(1,5,6);
	setled(1,5,7);
	setled(1,3,5);*/
}
