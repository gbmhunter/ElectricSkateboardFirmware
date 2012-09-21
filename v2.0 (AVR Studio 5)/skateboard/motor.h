/***************************************************************
 * Geo's Wireless Skateboard
 * motor.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 14/12/2010
 *
 ***************************************************************
 */

//***Header Guard***
#ifndef _MOTOR_H
#define _MOTOR_H

//***Header Inclusions
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/comms.h"
#include "../common/definitions.h"

//***Function Prototypes
void motor_disable(void);
void motor_enable(void);
void motor_init(void);
void motor_set_speed(uint16_t value);
void motor_update(void);

#endif
