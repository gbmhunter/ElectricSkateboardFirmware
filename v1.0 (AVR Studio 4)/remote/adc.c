/***************************************************************
 * Geo's Wireless Skateboard: Remote Atmega8
 * adc.c 
 * Written By: Geoffrey Hunter
 * Last Modification: 18/12/2010
 *
 ***************************************************************
 */

//***Header Inclusions
#include "adc.h"

void adc_init(void)
{
	//Sets external Vref, Left-adjusted data register, ADC1 as input channel
	ADMUX = (0<<7 | 0<<6 | 0<<5 | 0<<4 | 0<<3 | 0<<2 | 0<<1 | 1<<0);
	//Enable ADC, start ADC, set in free-running mode, diable interrupt, divide XTAL by 64 (125kHz)
	ADCSRA = (1<<7 | 1<<6 | 1<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0);
}

uint16_t adc_get(void)
{
	uint8_t adc_l;
	uint8_t adc_h;
	adc_l = ADCL;
	adc_h = ADCH;
	return ((adc_h << 8) | adc_l);
}
