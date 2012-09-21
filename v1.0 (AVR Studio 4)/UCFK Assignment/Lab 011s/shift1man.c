#include <stdio.h>
#include "utilities.h"

int main()
{
	uint8_t value;
	uint8_t result;
	unsigned int shift;
	char string[12];
	
	value = 5;
	printf("Consider the unsigned value %u which in binary is %s, then\n\n", value, binary_string(string, value));
	
	for(shift=0; shift < 8; shift++)
	{
		result = value << shift;
		printf("A left shift of %u gives value %u which in binary is\t %s\n", shift, result, binary_string(string, result));
	}
	return EXIT_SUCCESS;
}
