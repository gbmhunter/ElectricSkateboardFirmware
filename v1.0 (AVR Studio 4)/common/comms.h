/***************************************************************
 * Geo's Wireless Skateboard: Common File
 * comms.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 04/01/2012
 *
 ***************************************************************
 */

//***Header Guard***
#ifndef _COMMS_H
#define _COMMS_H

//***Header Inclusions
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../common/definitions.h"
#include "../common/led.h"
#include "../common/usart.h"

//***Function Prototypes
void comms_init(uint8_t* iden_chars_in);
void comms_config(uint8_t *command, uint8_t *parameter, uint8_t parameter_bits);
void comms_update(void);
uint8_t comms_get_byte(uint8_t byte_num);
void comms_send(uint8_t *data, uint8_t num_of_bytes);
uint8_t comms_timeout(void);
uint8_t comms_is_new_packet(void);

/***ENUMERATIONS***/
enum comms_states_enum{
	idle,
	second_iden_char,
	third_iden_char,
	packet_data_count,
	packet_data,
	receiving_checksum,
	packet_complete,
};

typedef struct comms{
	uint16_t motor_speed;				//Range: 
} comms_data_t;

#endif
