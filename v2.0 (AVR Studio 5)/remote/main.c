/*
***************************************************************
* Geo's Wireless Skateboard: Remote ATmega8
* main.c 
* Written By: Geoffrey Hunter
* Last Modification: 06/04/2011
*
***************************************************************
*/

/*
***Information***
Micro-controller: ATmega8

*/

/***Header Inclusions***/
#include "main.h"

/***Constants***/

// Used for preprocessor to input code specific to remote or board


//Total number of leds connected to micro
#define NUMBER_OF_LEDS 3

#define number_of_buttons 2
#define adc_resolution 1024

// Timeout cycles for comms (16-bit)
#define COMMS_TIMEOUT 1000

/***Private Function Declarations***/
void setup_comms(void);
void setup_leds(void);
void delay(uint16_t counts);

/***Variables***/
static uint8_t tick0;
static uint8_t msg[8];
// Status byte
static uint8_t status_byte = 0x00;
// True on the first time a different state is entered
static uint8_t first_time = true;
// Main state variable
static main_state_t main_state = off;
// Counter variables
static uint16_t count_led;
static uint16_t count_comms;

/***Function Definitions***/

//Toggles O.K. LED once per second
ISR(TIMER0_OVF_vect)
{
	
	tick0++;
	if(tick0 >= 30)
	{
		tick0 = 0;
	}
}

int main(void){

	OSCCAL = 0x9F;
	

	/***Button Intialisation***/
	uint8_t *button_pin[number_of_buttons + 1];
	uint8_t button_pin_num[number_of_buttons + 1];
	button_pin[0] = &PIND;
	button_pin_num[0] = 3;
	button_pin[1] = &PIND;
	button_pin_num[1] = 4;
	button_pin[2] = '\0';
	button_pin_num[2] = '\0';
	
	/***Intialisation Routines***/
	setup_leds();
	button_init(button_pin, button_pin_num);
	adc_init();
	tcnt0_init();
	//usart_init();
	setup_comms();

	/***Default led states***/
	led_off(1);
	led_off(0);
	led_off(2);

	// Stores values from ADC
	uint16_t adc_value_temp = 0;
	uint16_t adc_value = 0;
	msg[0] = 's';
	msg[1] = 'k';
	msg[2] = 't';
	msg[3] = status_byte;
	msg[4] = 0x02;
	msg[5] = 0x2C;
	msg[6] = 0x00;

	//Enable interrupts
	sei();

	///***Main Loop***
	while(1){
		
		// Check for usart data
		comms_update();
		
		// Main state machine
		switch(main_state)
		{
			case off:
				if(first_time == true)
				{
					count_led = 0;
					count_comms = 0;
					// Clears on bit in status byte
					status_byte &= ((1<<ON_BIT_POS)^0xFF);
					first_time = false;
				}
				
				// Flash first LED
				count_led++;
				if(count_led >= LED_FLASH_RATE)
				{
					led_toggle(0);
					count_led = 0;
				}
				
				// Determines speed of packages
				if(count_comms >= COMMS_SEND_CYCLES)
				{
					// 3 header chars indentifing message
					msg[0] = 's';
					msg[1] = 'k';
					msg[2] = 't';
					// Number of data bytes following...
					msg[3] = 0x03;
					// Status byte
					msg[STATUS_BYTE_POS] = status_byte;
					// Motor speed value (16-bit) (make 0 when off)
					msg[5] = 0;
					msg[6] = 0;
					msg[7] = '\0';
					// Send message to skateboard
					comms_send(msg, 8);
					count_comms = 0;
				}
				
				count_comms++;
				// Check for new packet
				if(comms_is_new_packet())
				{
					// True is skateboard has received msg from remote and replied with o.k.
					if((comms_get_byte(STATUS_BYTE_POS) & (1<<IN_RANGE_BIT_POS)) != 0x00)
					{
						main_state = in_range;
						first_time = true;
						led_off(0);
					}
				}
				
				break;
				
			case in_range:
				if(first_time == true)
				{
					// Reset counters
					count_led = 0;
					count_comms = 0;
					first_time = false;
				}
				
				// Update button states
				button_update();
				
				// Check for comms timeout. Comms has been dropped (out of range), so go back to off state.
				if(comms_timeout())
				{
					main_state = off;
					first_time = true;
					led_off(1);
				}
				
				// Flash second LED
				count_led++;
				if(count_led >= LED_FLASH_RATE)
				{
					led_toggle(1);
					count_led = 0;
				}

				// Check if user has pressed on button, set on bit if true
				if(button_been_pressed(0))
				{
					// Set on bit in status byte
					status_byte |= (1 << ON_BIT_POS);
					
				}
				
				// Send packet to skateboard
				if(count_comms >= COMMS_SEND_CYCLES)
				{
						// 3 header chars indentifying message
						msg[0] = 's';
						msg[1] = 'k';
						msg[2] = 't';
						// Number of data bytes following...
						msg[3] = 0x03;
						// Status byte
						msg[STATUS_BYTE_POS] = status_byte;
						// Motor speed value (16-bit)
						msg[MOTOR_HIGH_BYTE_POS] = 0;
						msg[MOTOR_LOW_BYTE_POS] = 0;
						msg[7] = 0x00;
						// Send message to skateboard
						comms_send(msg, 8);
						// Reset counter
						count_comms = 0;
				}
				count_comms++;

				if(comms_is_new_packet())
				{
					
					// True is skateboard has received msg from remote and replied with on
					if(comms_get_byte(STATUS_BYTE_POS) & (1<<ON_BIT_POS))
					{
						
						main_state = on;
						first_time = true;
						led_off(1);
					}
				}
				
				break;
			

			// ON STATE
			case on:
				
				if(first_time == true)
				{
					// Set on bit in status byte
					status_byte |= (1 << ON_BIT_POS);
					first_time = false;
				}
				
				// Check for comms timeout. If comms has been dropped, go to off state
				if(comms_timeout())
				{
					led_on(0);
					
					led_on(2);
					delay(10000);
					led_off(0);
					
					led_off(2);
					main_state = off;
					first_time = true;
				}
				
				// Flash third LED
				count_led++;
				if(count_led >= LED_FLASH_RATE)
				{
					led_toggle(2);
					count_led = 0;
				}
				
				// Read throttle value (varies from 1.1 to 2.1V or 365 to 521) FIX
				adc_value_temp = adc_get();
				// For some reason this next line is necessary
				adc_value = adc_value_temp;
				// Make sure ADC value is within correct range (ignore if not)
				if ((adc_value_temp) >= 370 && (adc_value_temp < 21845))
				{
					adc_value = ((adc_value - 370)*35)/10;
					if(adc_value > 1024)
					{
						adc_value = 1024;
					}
				}
				else
				{
					adc_value = 0;
				}
				
				// Check for any button presses
				button_update();
				
				// Check if user has pressed on button, clear on bit if true (to turn off)
				if(button_been_pressed(0))
				{
					// Clear on bit in status byte
					status_byte &= ((1<<ON_BIT_POS)^0xFF);
					main_state = off;
					first_time = true;
				}
				
				// Send a new packet to skateboard periodically
				if(count_comms >= COMMS_SEND_CYCLES)
				{
						// 3 header chars identifying message
						msg[0] = 's';
						msg[1] = 'k';
						msg[2] = 't';
						// Number of data bytes following...
						msg[3] = 0x03;
						// Status byte
						msg[STATUS_BYTE_POS] = status_byte;
						// Motor speed value (16-bit)
						msg[MOTOR_HIGH_BYTE_POS] = (adc_value>>8) & 0xFF;
						msg[MOTOR_LOW_BYTE_POS] = adc_value & 0xFF;
						msg[7] = 0x00;
						// Send message to skateboard
						comms_send(msg, 8);
				
						// Reset counter
						count_comms = 0;
				}
				// Increment counter
				count_comms++;
				/*
				// Check for new packet received from skateboard
				if(comms_is_new_packet())
				{
					
					// True is skateboard has received msg from remote and replied with off
					if((comms_get_byte(STATUS_BYTE_POS) & (1<<ON_BIT_POS)) == 0x00)
					{
						main_state = off;
						first_time = true;
						led_off(2);
					}
					
				}
				*/
				break;
			
		}
	}

}

// Sets up XBee comms. Iden chars are used to identify first 3 bytes of INCOMING packets
void setup_comms(void)
{
	static uint8_t iden_chars[3];
	iden_chars[0] = 'r';
	iden_chars[1] = 'm';
	iden_chars[2] = 't';
	
	comms_init(iden_chars);
}

// Sets up leds. Once setup, use led_on(led_number), led_off(...) or led_toggle(...)
void setup_leds(void)
{
	static uint8_t *led_port[NUMBER_OF_LEDS + 1];
	static uint8_t led_pin[NUMBER_OF_LEDS + 1];
	// Define which port and pin each led is connected to, and then call led_init
	led_port[0] = &PORTD;
	led_pin[0] = 5;
	led_port[1] = &PORTD;
	led_pin[1] = 6;
	led_port[2] = &PORTD;
	led_pin[2] = 7;
	led_port[3] = '\0';
	led_pin[3] = '\0';
	led_init(led_port, led_pin);
}

// Simple software delay timer
void delay(uint16_t counts)
{
	uint16_t counter = 0;
	while(counter <= counts)
	{
		counter++;
	}
}
