/***************************************************************
 * Geo's Wireless Skateboard: Common File
 * comms.h 
 * Written By: Geoffrey Hunter
 * Last Modification: 04/01/2012
 *
 ***************************************************************
 */

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _COMMS_H
#define _COMMS_H

// Definitions for remote to skateboard data packets (8 bit)
#define commsSTATUS_BYTE_POS 				(4)
	#define commsON_BIT_POS 					(0)
	#define commsALARM_ON_BIT_POS 				(1)
	#define commsIN_RANGE_BIT_POS 				(2)
	#define commsLIGHTS_ON_BIT_POS 				(3)
	#define commsCHANGE_LIGHT_MODE_BIT_POS		(4)
#define commsMOTOR_HIGH_BYTE_POS 			(5)
#define commsMOTOR_LOW_BYTE_POS 			(6)
#define commsBOARD_BATT_VOLT_HIGH_BYTE_POS 	(7)
#define commsBOARD_BATT_VOLT_LOW_BYTE_POS 	(8)

//===============================================================================================//
//===================================== PUBLIC TYPEDEF's ========================================//
//===============================================================================================//


typedef struct comms{
	uint16_t motorSpeed;				//Range: 
} commsData_t;

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

void 	Comms_Init(uint8_t* idenCharsIn);
void 	Comms_Config(uint8_t *command, uint8_t *parameter, uint8_t parameterBits);
void 	Comms_Run(void);
uint8_t Comms_GetByte(uint8_t byteNum);
void 	Comms_Send(uint8_t *dataArray, uint8_t numOfBytes);
uint8_t Comms_Timeout(void);
bool_t Comms_IsNewPacket(void);

#endif
