#include <stdio.h>
#include "utilities.h"

int main()
{
	uint8_t value;
	uint8_t mask;
	uint8_t result;
	unsigned int shift;
	char string[12];
	
	printf("Enter an a binary string (eg 0b10100101):\t\t");
	scanf("%s", string);
	value = binary_value(string);
	
	printf("\nYou entered the binary string %s which also has the unsigned value of %u\n", string, value);

	for(shift=0; shift < 8; shift++)
	{
		mask = 1 << shift;
		result = value & mask;
		if (result)
			printf("The bit at position %u is 1 and has value %u.\tThis bit is SET\n", shift, result);
		else
			printf("The bit at position %u is 0 and has value %u.\tThis bit is CLEAR\n", shift, result);
	}
	
	result = value | 0x0A;
	printf("The binary string when setting bits 1 and 3 has the pattern %s and unsigned value of %u\n", binary_string(string, result), result);
	result = value & ~0x14;
	printf("The binary string when clearing bits 2 and 4 has the pattern %s and unsigned value of %u\n", binary_string(string, result), result);

	return EXIT_SUCCESS;
}
