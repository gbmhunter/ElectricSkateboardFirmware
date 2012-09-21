/*
***************************************************************
* Geo's Wireless Skateboard: Common File
* comms.c
* Written By: Geoffrey Hunter
* Last Modification: 24/04/2011
*
***************************************************************
*/

/***Header Inclusions***/
#include "comms.h"

/***Constants***/
#define NUM_OF_PACKET_BUFFERS 5
#define BUFFER_SIZE 50
#define RX_DATA_BUFFER_SIZE 50

// Bit positions of data in rx packet

#define MS1_BP 5	// Higher byte of motor speed
#define MS0_BP 6	// Lower byte of motor speed

/***Local Function Declarations***/
void comms_retrieve_data();
uint8_t comms_decode_packet();

/***Variables***/

//flags
static uint8_t new_packet_flg = false;
// Set when a byte has not been read from a new data packet
static uint8_t unread_data_flg = false;
static uint8_t comms_packet_buffer_overrun_flg = false;
static uint8_t comms_init_complete_flg = false;
static uint8_t comms_timeout_flg = true;

//rx variables
static comms_data_t comms_data;
static uint8_t packet_buffer[BUFFER_SIZE];
static uint8_t* iden_chars;

// Counter for comms timeout
static uint16_t timeout_counter = 0;

/***Function Definitions***/

void comms_init(uint8_t* iden_chars_in)
{
	iden_chars = iden_chars_in;
	
	// Intialise usart used to communicate with comms
	usart_init();

	//Signal that intialisation is complete
	comms_init_complete_flg = true;
}


void comms_config(uint8_t *command, uint8_t *parameter, uint8_t parameter_bits)
{
	
	
}

void comms_update(void)
{
	comms_retrieve_data();

	//Decode if there are new packets present
	if(new_packet_flg)
	{
		// Reset timeout counter
		timeout_counter = 0;
		
		new_packet_flg = false;
		// Set unread data flag (cleared when comms_get_byte is called)
		unread_data_flg = true;
	}
	else
	{
		// Increment timeout counter if no packet arrived
		timeout_counter++;
		// Set flag if timeout counter has reached the limit without being reset by a new packet arriving
		if(timeout_counter == COMMS_TIMEOUT_PERIOD)
		{
			comms_timeout_flg = true;
		} 
	}
}

void comms_retrieve_data()
{
	static enum comms_states_enum comms_state = idle;
	static uint8_t packet_buffer_pos = 0;
	static uint8_t num_of_data_bytes = 0;
	static uint8_t rx_data_byte;

	while(usart_get_byte(&rx_data_byte))
	{
		
		switch(comms_state){
			case idle:
				
				packet_buffer_pos = 0;
				num_of_data_bytes = 0;
				if(rx_data_byte == iden_chars[0])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					comms_state = second_iden_char;
				}
				break;
			case second_iden_char:
				if(rx_data_byte == iden_chars[1])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					comms_state = third_iden_char;
				}
				else
				{
					// Go back to idle state if header not valid
					comms_state = idle;
				}
				break;
			case third_iden_char:
				if(rx_data_byte == iden_chars[2])
				{
					packet_buffer[packet_buffer_pos] = rx_data_byte;
					packet_buffer_pos++;
					comms_state = packet_data_count;
				}
				else
				{
					// Go back to idle state if header not valid
					comms_state = idle;
				}
				break;
			case packet_data_count:
				comms_state = packet_data;
				packet_buffer[packet_buffer_pos] = rx_data_byte;
				num_of_data_bytes = rx_data_byte;
				packet_buffer_pos++;
				break;

			case packet_data:
				
				packet_buffer[packet_buffer_pos] = rx_data_byte;
				packet_buffer_pos++;
				if(packet_buffer_pos >= 4+3) //FIX
				{
					comms_state = packet_complete;
				}
				
				break;
			case receiving_checksum:
				comms_state = packet_complete;
				break;
			case packet_complete:
				// Set new packet flag true so comms decode can be called
				new_packet_flg = true;
				comms_state = idle;
				break;
			default:
				comms_state = idle;
				break;
		}
		
		//packet_buffer_pos++;
		if(packet_buffer_pos > BUFFER_SIZE)					//Resets packet buffer index (shouldn't happen)
		{
			packet_buffer_pos = 0;
			comms_packet_buffer_overrun_flg = true;
		}
	}
}

uint8_t comms_get_byte(uint8_t byte_num)
{
	// Clear unread data flag once at east one byte from the new packet has been read
	unread_data_flg = false;
	return packet_buffer[byte_num];
}

// Function just passes variables onto usart
void comms_send(uint8_t *data, uint8_t num_of_bytes)
{
	usart_send(data, num_of_bytes);
}

// Returns true if comms has timed out because it hasn't received a packet in COMMS_TIMEOUT_PERIOD
uint8_t comms_timeout(void)
{
	// Temp flag variable so comms_timeout flag can be cleared before returning
	uint8_t temp_flg;
	temp_flg = comms_timeout_flg;
	// Clear timeout flag once read
	comms_timeout_flg = false;
	return temp_flg;
}

// Returns true if their is a new packet that hasn't been read
uint8_t comms_is_new_packet(void)
{
	return unread_data_flg;
}
