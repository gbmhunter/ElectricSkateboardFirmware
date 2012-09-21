/*
***************************************************************
* Geo's Wireless Skateboard
* button.c
* Written By: Geoffrey Hunter
* Last Modification: 14/12/2010
*
***************************************************************
*/

#include "button.h"

#define MAX_NO_OF_BUTTONS 10

typedef enum{
	low,
	high_debounce,
	high,
	low_debounce
} button_state_t;

static uint8_t **button_pin;
static uint8_t *button_pin_num;
static button_state_t button_state[MAX_NO_OF_BUTTONS];
static uint8_t button_pressed_flg[MAX_NO_OF_BUTTONS];


/* 
	inputs: 
		button_pin_in: pointer to an array containing the port address for each button (with '0\' terminating array)
		button_pin_num_in: pointer to an array containing the pin number for each button
	outputs: 
		none
	function: 
		Gets the address's pointing to the array holding button information
*/
void button_init(uint8_t** button_pin_in, uint8_t* button_pin_num_in)
{
	button_pin = button_pin_in;
	button_pin_num = button_pin_num_in;

	//Assigns every pin that an button is connected to as an input and sets the correct pin buffer
	uint8_t x = 0;
	while(button_pin[x] != '\0')
	{
		if(button_pin[x] == &PINB)
		{
			DDRB = DDRB | (0 << button_pin_num[x]);
		}
		else if(button_pin[x] == &PINC)
		{
			DDRC = DDRC | (0 << button_pin_num[x]);
		}
		else if(button_pin[x] == &PIND)
		{
			DDRD = DDRD | (0 << button_pin_num[x]);
		}
		x++;
	}

	
}

void button_update(void)
{
	uint8_t x = 0;
	static uint16_t count;
	while(button_pin[x] != '\0')
	{
		// Button Debounce State Machine
		switch(button_state[x])
		{
			case low:
				if((*button_pin[x] & (1 << button_pin_num[x])) == false)
				{
					count = 0;
					// Go into high debounce state if button state was orginally low and now the button is high
					button_state[x] = high_debounce;
				}
				break;
			case high_debounce:
				if(button_state[x] == high_debounce)
				{
					// Increment debounce counter
					count++;
					if(count == DEBOUNCE_TIME)
					{
						if((*button_pin[x] & (0 << button_pin_num[x])) == false)
						{
							
							button_state[x] = high;
							// Set the button pressed flag for external functions to check
							button_pressed_flg[x] = true;
					
						}
						else
						{
							// Set state back to low if button is not high after DEBOUNCE_TIME
							button_state[x] = low;
						}
						count = 0;
					}
				}
				break;
			case high:
				// If button state is high and button is now low
				if((*button_pin[x] & (1 << button_pin_num[x])) != false)
				{
					count = 0;
					button_state[x] = low_debounce;
				}
				break;
			case low_debounce:
				// Increment debounce counter
				count++;
				if(count == DEBOUNCE_TIME)
				{
					if((*button_pin[x] & (1 << button_pin_num[x])) != false)
					{
						button_state[x] = low;
						// Set the button pressed flag for external functions to check
						
				
					}
					else
					{
						// Set state back to high if button is not low after DEBOUNCE_TIME
						button_state[x] = high;
					}
					count = 0;
				}
				break;
		}
		//Increment button to check
		x++;
	}
}

uint8_t button_been_pressed(uint8_t button_num)
{
	if(button_pressed_flg[button_num] == true)
	{
		// Set pressed flag back to false once it has been checked
		button_pressed_flg[button_num] = false;
		return true;
	}
	else
	{
		return false;
	}
}
