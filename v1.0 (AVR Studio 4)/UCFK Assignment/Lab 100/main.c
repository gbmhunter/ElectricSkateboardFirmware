#include "pdisp.h"

void *thread_main3( void *ptr )
{
	while(1)
	{
		PORTD = ~0x02;
		PORTB = ~0x00;
		PORTC = ~0x04;
	}
	//return(0);
}
