/*
***************************************************************
* Geo's Wireless Skateboard
* definitions.h
* Written By: Geoffrey Hunter
* Last Modification: 23/12/2010
*
***************************************************************
*/

//***Header Guard***
#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#define true 1
#define false 0

// Definitions for remote to skateboard data packets (8 bit)
#define STATUS_BYTE_POS 4
#define MOTOR_HIGH_BYTE_POS 5
#define MOTOR_LOW_BYTE_POS 6
#define ON_BIT_POS 0
#define ALARM_BIT_POS 1
#define IN_RANGE_BIT_POS 2

// Number of state cycles that leds flash at (16-bit)
#define LED_FLASH_RATE 10000

// Number of state cycles before comms has time out if no packet has arrived (16-bit)
#define COMMS_TIMEOUT_PERIOD 50000
// Number of state cycles between each comms packet is sent
#define COMMS_SEND_CYCLES 1000

#define BUZZER_SINGLE_BEEP_CYCLES 50000

typedef union u_168bit{ uint16_t w;		//16 bit accessed as 1 uint
						uint8_t b[2];	//16 bit accessed as 2 bytes
} u_168bit_t;

#endif
