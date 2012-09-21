/***************************************************************
 * Geo's Wireless Skateboard
 * motor.c 
 * Written By: Geoffrey Hunter
 * Last Modification: 04/01/2011
 *
 ***************************************************************
 */

/***Header Inclusions***/
#include "motor.h"

/***Constants***/
#define MIN_THROTTLE 450
#define MAX_THROTTLE 870
#define MAX_CONTROL_VALUE 1024



/***Variables***/
static uint8_t enable = false;


void motor_init(void)
{
	// Set up PWM

	//(0xA0) Enabes OC1A and OC1B pin and clears on compare match
	TCCR1A= (1<<7 | 0<<6 | 1<<5 | 0<<4 | 0<<3 | 0<<2 | 0<<1 | 0<<0); 
	//(0x12) Input noise canceller deactivated,  
	TCCR1B= (0<<7 | 0<<6 | 0<<5 | 1<<4 | 0<<3 | 0<<2 | 1<<1 | 0<<0);
	//(0x00) Set initial timer value to 0
	TCNT1H=0x00; 
	TCNT1L=0x00; 
	// Sets the counters top value
	ICR1=9100;     // 50hz 20ms (9000 = 50Hz)
	//Sets output compares to 0
	OCR1AH=0x00; 
	OCR1AL=0x00; 
	OCR1BH=0x00; 
	OCR1BL=0x00;
	DDRB = 0x02;
	//Sets external Vref, Left-adjusted data register, ADC0 as input channel
	ADMUX = (0<<7 | 0<<6 | 0<<5 | 0<<4 | 0<<3 | 0<<2 | 0<<1 | 0<<0);
	//Enable ADC, start ADC, set in free-running mode, diable interrupt, divide XTAL by 64 (125kHz)
	ADCSRA = (1<<7 | 1<<6 | 1<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0);


}

void motor_update(void)
{
	static uint16_t motor_speed;
	motor_speed = ((comms_get_byte(MOTOR_HIGH_BYTE_POS)<<8) | (comms_get_byte(MOTOR_LOW_BYTE_POS)));
	motor_set_speed(motor_speed);
}


//Accepts value from 0 to 1000
void motor_set_speed(uint16_t value)
{
	if(enable == true)
	{
		uint16_t difference = MAX_THROTTLE - MIN_THROTTLE;
		OCR1A = (value*(difference/100))/(MAX_CONTROL_VALUE/100) + MIN_THROTTLE;
	}
}

// Enables motor
void motor_enable(void)
{
	// Allows speed to be set by calling motor_set_speed
	enable = true;
}

// Disables motor
void motor_disable(void)
{
	// Turn of command to motor
	motor_set_speed(0);
	// Don't allow speed to be set untill re-enabled
	enable = false;
}
