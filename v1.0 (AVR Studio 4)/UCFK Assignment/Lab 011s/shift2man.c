#include <stdio.h>
#include "utilities.h"

int main()
{
	uint8_t value;
	uint8_t result;
	unsigned int shift;
	char string[12];
	
	printf("Enter a binary string (eg 0b10100101):\t\t");
	scanf("%s", string);
	value = binary_value(string);
	
	printf("Enter a desired shift value (should be less than 8):\t");
	scanf("%ui", &shift);
	
	printf("\nYou entered the binary string %s which also has the unsigned value of %u\n", string, value);
	
	result = value << shift;
	printf("The binary string when shifted %u position to the left is  %s with unsigned value of %u\n", shift, binary_string(string, result), result);

	result = value >> shift;
	printf("The binary string when shifted %u position to the right is %s with unsigned value of %u\n", shift, binary_string(string, result), result);

	return EXIT_SUCCESS;
}
