#include <stdio.h>
#include "utilities.h"

int main()
{
	uint8_t character;
	
	printf("Enter an ascii character:\t");
	scanf("%c", &character);
	
	printf("\nYou entered the character %c which also has the unsigned value of %u\n", character, character);
	printf("The character 3 positions before on the ASCII table is %c\n", character-3);
	printf("The character 3 positions after on the ASCII table is %c\n", character+3);
	
	return EXIT_SUCCESS;
}
