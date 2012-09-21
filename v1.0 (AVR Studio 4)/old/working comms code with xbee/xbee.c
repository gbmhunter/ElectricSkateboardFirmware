/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* xbee.c
* Written By: Geoffrey Hunter
* Last Modification: 22/12/2010
*
***************************************************************
*/

/***Header Inclusions***/
#include "xbee.h"

/***Constants***/
#define NUM_OF_PACKET_BUFFERS 5
#define BUFFER_SIZE 50
#define RX_DATA_BUFFER_SIZE 50

// Bit positions of data in rx packet

#define MS1_BP 5	// Higher byte of motor speed
#define MS0_BP 6	// Lower byte of motor speed

/***Local Function Declarations***/
void xbee_retrieve_data();
uint8_t xbee_decode_packet();

/***Variables***/

//flags
static uint8_t new_packet_flg = false;
static uint8_t xbee_packet_buffer_overrun_flg = false;
static uint8_t xbee_init_complete_flg = false;

//rx variables
static xbee_data_t xbee_data;
static u_168bit_t motor_speed;
static uint8_t packet_buffer[BUFFER_SIZE];
static uint8_t* iden_chars;


/***Function Definitions***/

void xbee_init(uint8_t* iden_chars_in)
{
	led_on(0);
	iden_chars = iden_chars_in;
	
	// Intialise usart used to communicate with XBee
	usart_init();

	//Signal that intialisation is complete
	xbee_init_complete_flg = true;
}


void xbee_config(uint8_t *command, uint8_t *parameter, uint8_t parameter_bits)
{
	
	
}

uint8_t xbee_update()
{
	xbee_retrieve_data();

	//Decode if their are new packets present
	if(new_packet_flg)
	{
		new_packet_flg = false;
		return xbee_decode_packet();
	}
	else
	{
		return false;
	}
}

void xbee_retrieve_data()
{
	static enum xbee_states_enum xbee_state = idle;
	static uint8_t packet_buffer_pos = 0;
	static uint8_t num_of_data_bytes = 0;
	static uint8_t rx_data_byte;

	while(usart_get_byte(&rx_data_byte))
	{
		
		switch(xbee_state){
			case idle:
				
				packet_buffer_pos = 0;
				num_of_data_bytes = 0;
				if(rx_data_byte == iden_chars[0])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					xbee_state = second_iden_char;
				}
				break;
			case second_iden_char:
				if(rx_data_byte == iden_chars[1])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					xbee_state = third_iden_char;
				}
				else
				{
					// Go back to idle state if header not valid
					xbee_state = idle;
				}
				break;
			case third_iden_char:
				if(rx_data_byte == iden_chars[2])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					xbee_state = packet_data_count;
				}
				else
				{
					// Go back to idle state if header not valid
					xbee_state = idle;
				}
				break;
			case packet_data_count:
				xbee_state = packet_data;
				packet_buffer[packet_buffer_pos] = rx_data_byte;
				num_of_data_bytes = rx_data_byte;
				packet_buffer_pos++;
				break;

			case packet_data:
				
				packet_buffer[packet_buffer_pos] = rx_data_byte;
				packet_buffer_pos++;
				if(packet_buffer_pos >= 4+2) //EDITED
				{
					xbee_state = packet_complete;
				}
				
				break;
			case receiving_checksum:
				xbee_state = packet_complete;
				break;
			case packet_complete:
				// Set new packet flag true so xbee decode can be called
				new_packet_flg = true;
				led_toggle(2);
				xbee_state = idle;
				break;
			default:
				xbee_state = idle;
				break;
		}
		
		//packet_buffer_pos++;
		if(packet_buffer_pos > BUFFER_SIZE)					//Resets packet buffer index (shouldn't happen)
		{
			packet_buffer_pos = 0;
			xbee_packet_buffer_overrun_flg = true;
		}
	}
}

uint8_t xbee_decode_packet()
{
	return true;
	motor_speed.b[1] = packet_buffer[MS1_BP];
	motor_speed.b[0] = packet_buffer[MS0_BP];
}

uint16_t xbee_motor_speed()
{
	return motor_speed.w;
}

uint8_t xbee_get_byte(uint8_t byte_num)
{
	return packet_buffer[byte_num];
}
