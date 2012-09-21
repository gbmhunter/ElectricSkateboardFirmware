/***************************************************************
 * Geo's Wireless Skateboard: Remote ATmega8
 * adc.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 18/12/2010
 *
 ***************************************************************
 */

//***Header Guard***
#ifndef _ADC_H
#define _ADC_H

//***Header Inclusions
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//***Function Prototypes
void adc_init(void);
uint16_t adc_get(void);

#endif
