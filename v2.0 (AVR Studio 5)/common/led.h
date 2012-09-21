/*
***************************************************************
* Geo's Wireless Skateboard: Common Files
* led.h
* Written By: Geoffrey Hunter
* Last Modification: 14/12/2010
*
***************************************************************
*/

//***Header Guard***
#ifndef _LEDS_H
#define _LEDS_H

//***File Inclusions***
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//***Function Prototypes***
void led_init(uint8_t** led_port_in, uint8_t* led_pin_in);
void led_on(uint8_t led_number);
void led_off(uint8_t led_number);
void led_toggle(uint8_t led_number);

#endif
