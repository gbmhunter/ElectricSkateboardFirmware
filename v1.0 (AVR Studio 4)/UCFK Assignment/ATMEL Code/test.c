#include <stdint.h>
#include <stdio.h>

int messagearray[50][6];
char message[] = "HAPPY :-) SAD :-( HUNGRY :-O DEAD X-( KISS :-X RICH $-) ";
int stringlength = sizeof(message);


void messagecreator()
{

	int asciicode;
	int i;
	int j;
	for(i=0; i<stringlength; i++)
	{
		for(j=0; j<5; j++)
		{
			asciicode = message[i] - 32;
			messagearray[i][j] = ~font[asciicode*5+j];
		}
	messagearray[i][5] = ~0x00;
	}
}	

printf(messagearray[1][5]);
