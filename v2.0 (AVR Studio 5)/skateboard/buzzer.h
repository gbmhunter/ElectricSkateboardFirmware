/*
***************************************************************
* Geo's Wireless Skateboard: Skateboard ATmega8
* buzzer.h
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

//***Header Guard***
#ifndef _BUZZER_H
#define _BUZZER_H

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/definitions.h"

/*** Global Function Declarations ***/
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_single_beep(void);
void buzzer_update(void);

#endif
