#include "utilities.h"


/*
 * Convert a uint8_t value into a string of binary values for display
 */
char* binary_string(char result[], uint8_t value)
{
	int i;
	uint8_t mask = 0x80;
	
	result[0] = '0';
	result[1] = 'b';
	for(i=0; i < 8; i++)
	{
		if (value & mask)
		{
			result[i+2] = '1';
		}
		else
		{
			result[i+2] = '0';
		}
		mask = mask >> 1;
	}
	result[10] = '\0';
	return result;
}


/*
 * Convert a string of binary symbols into a uint8_t
 */
uint8_t binary_value(char string[])
{
	uint8_t value=0;
	int i;
	
	for(i=0; i < 8; i++)
	{
		if (string[9-i] == '1')
		{
			value = value + pow(2,i);
		}
	}
	
	return value;
}


