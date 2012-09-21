/***************************************************************
 * Geo's Wireless Skateboard: Common File
 * alarm.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 05/01/2012
 *
 ***************************************************************
 */

//***Header Guard***
#ifndef _ALARM_H
#define _ALARM_H

//***Header Inclusions
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/definitions.h"
void alarm_init(void);
void alarm_update(void);
void alarm_reset(void);
uint8_t alarm_is_triggered(void);

#endif
