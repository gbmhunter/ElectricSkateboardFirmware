/***************************************************************
 * Geo's Wireless Skateboard: Common File
 * xbee.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 22/12/2010
 *
 ***************************************************************
 */

//***Header Guard***
#ifndef _XBEE_H
#define _XBEE_H

//***Header Inclusions
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/definitions.h"
#include "../common/led.h"
#include "../common/usart.h"

//***Function Prototypes
void xbee_init(uint8_t* iden_chars_in);
void xbee_config(uint8_t *command, uint8_t *parameter, uint8_t parameter_bits);
uint8_t xbee_update();
uint16_t xbee_motor_speed();
uint8_t xbee_get_byte(uint8_t byte_num);

/***ENUMERATIONS***/
enum xbee_states_enum{
	idle,
	second_iden_char,
	third_iden_char,
	packet_data_count,
	packet_data,
	receiving_checksum,
	packet_complete,
};

typedef struct xbee{
	uint16_t motor_speed;				//Range: 
} xbee_data_t;

#endif
