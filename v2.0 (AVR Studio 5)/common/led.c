/*
***************************************************************
* Geo's Wireless Skateboard
* led.c
* Written By: Geoffrey Hunter
* Last Modification: 14/12/2010
*
***************************************************************
*/

#include "led.h"

static uint8_t **led_port;
static uint8_t *led_pin;



/* 
	inputs: 
		led_port_in: pointer to an array containing the port address for each led (with '0\' terminating array)
		led_pin_in: pointer to an array containing the pin number for each led
	outputs: 
		none
	function: 
		Gets the address's pointing to the array holding led information
*/
void led_init(uint8_t** led_port_in, uint8_t* led_pin_in)
{
	led_port = led_port_in;
	led_pin = led_pin_in;

	//Assigns every pin that an LED is connected to as an output
	uint8_t x = 0;
	while(led_port[x] != '\0')
	{
		if(led_port[x] == &PORTB)
		{
			DDRB = DDRB | (1 << led_pin[x]);
		}
		else if(led_port[x] == &PORTC)
		{
			DDRC = DDRC | (1 << led_pin[x]);
		}
		else if(led_port[x] == &PORTD)
		{
			DDRD = DDRD | (1 << led_pin[x]);
		}
		x++;
	}

	
}

void led_on(uint8_t led_number)
{
	*led_port[led_number] = *led_port[led_number] | (1 << led_pin[led_number]);
}

void led_off(uint8_t led_number)
{
	*led_port[led_number] = *led_port[led_number] & (0xFF ^ (1 << led_pin[led_number]));
}

void led_toggle(uint8_t led_number)
{
	*led_port[led_number] = *led_port[led_number] ^ (1 << led_pin[led_number]);
}
