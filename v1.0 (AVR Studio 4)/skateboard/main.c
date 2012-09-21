/*
***************************************************************
* Geo's Wireless Skateboard: Skateboard ATmega8
* main.c 
* Written By: Geoffrey Hunter
* Last Modification: 04/01/2011
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
#define NUMBER_OF_LEDS 3



/***Variables***/
static uint16_t tick0;
static uint8_t msg[8];
// Status byte (shared with remote, both units can change bits, as set in definitions.h)
static uint8_t status_byte;

// True on the first time a different state is entered
static uint8_t first_time = true;

/***Function Definitions***/
void setup_comms(void);
void setup_leds(void);

//Toggles O.K. LED once per second
ISR(TIMER0_OVF_vect)
{
	
	tick0++;
	if(tick0 >= 30)
	{
		//led_toggle(0);
		tick0 = 0;
		//usart_send(msg, 4);
	}
}


int main(void){

	/***Variables***/
	static enum main_states_enum main_state = off;

	/***Intialisation Routines***/
	setup_leds();
	
	setup_comms();
	
	tcnt0_init();
	//tcnt2_init();
	motor_init();
	alarm_init();
	buzzer_init();
	uint16_t count_led = 0;

	sei();
	while(1)
	{
		
		comms_update();
		buzzer_update();
		alarm_update();

		if(alarm_is_triggered())
		{
			buzzer_single_beep();
			alarm_reset();
		}

		// Main state machine
		switch(main_state)
		{
			
			case off:
				if(first_time == true)
				{
					// Clear on bit in status byte
					status_byte &= ( (1<<ON_BIT_POS)^0xFF );
					// Clear in range bit
					status_byte &= ( (1<<IN_RANGE_BIT_POS)^0xFF );
					motor_disable();
					led_off(0);
					first_time = false;	
				}
			
				
				// Check if new packet has arrived from remote
				if(comms_is_new_packet())
				{
					main_state = in_range;
					first_time = true;
				}
				
				break;
			// Skateboard is in range of remote, but not turned on yet
			case in_range:
				if(first_time == true)
				{
					// Set in-range bit in status byte
					status_byte |= (1<<IN_RANGE_BIT_POS);
				}
				
				if(comms_is_new_packet())
				{
					if(comms_get_byte(STATUS_BYTE_POS) & (1<<ON_BIT_POS))
					{
						
						main_state = on;
						first_time = true;
					}
					msg[0] = 'r';
					msg[1] = 'm';
					msg[2] = 't';
					msg[3] = 0x03;
					msg[STATUS_BYTE_POS] = status_byte;
					msg[5] = 0x00;
					msg[6] = 0x00;
					msg[7] = '\0';
					comms_send(msg, 8);
				}
				/*
				if(comms_timeout())
				{
					// Turn off motor (user has lost all speed control)
					motor_set_speed(0);
					motor_disable();
					// Turn off skateboard if communication lost with remote
					main_state = off;
					first_time = true;
				}
				*/
				break;
			// Skateboard is on, and motor can be controlled
			case on:
				if(first_time == true)
				{
					// Set on bit in status byte
					status_byte |= (1 << ON_BIT_POS);
					// Enable motor
					motor_enable();
					// Turn power light on
					led_on(0);
					// Emit beep
					buzzer_single_beep();
					first_time = false;
				}
				
				
				
				status_byte |= (1 << ON_BIT_POS);
				if(comms_is_new_packet())
				{
					motor_update();
					if(!(comms_get_byte(STATUS_BYTE_POS) & (1<<ON_BIT_POS)))
					{
						main_state = off;
						first_time = true;
					}
					msg[0] = 'r';
					msg[1] = 'm';
					msg[2] = 't';
					msg[3] = 0x03;
					msg[STATUS_BYTE_POS] = status_byte;
					msg[5] = comms_get_byte(MOTOR_HIGH_BYTE_POS);
					msg[6] = comms_get_byte(MOTOR_LOW_BYTE_POS);
					msg[7] = '\0';
					comms_send(msg, 8);
				}


				/*
				// Check if comms has timed out (no packet received in limit set by COMMS_TIMEOUT_PERIOD)
				if(comms_timeout())
				{
					// Turn off motor (user has lost all speed control)
					motor_set_speed(0);
					motor_disable();
					// Turn off skateboard if communication lost with remote
					main_state = off;
				}
				*/
				// Check if remote has signalled to turn off
			

				break;
			default:
				break;
		}
		

		
		
		
		
		
		
	}
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

// Sets up XBee comms. Iden chars are used to identify first 3 bytes of INCOMING packets
void setup_comms(void)
{
	static uint8_t iden_chars[3];
	iden_chars[0] = 's';
	iden_chars[1] = 'k';
	iden_chars[2] = 't';
	
	comms_init(iden_chars);
}
