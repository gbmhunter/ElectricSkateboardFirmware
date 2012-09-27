//!
//! @file 		Comms.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		22/12/2010
//! @brief 		Controls the comms between board and remote. Common to both platforms.
//! @details
//!		<b>Last Modified:			</b> 24/05/2011								\n
//!		<b>Version:					</b> v1.0									\n
//!		<b>Company:					</b> CladLabs								\n
//!		<b>Project:					</b> Electric Skateboard - Board			\n
//!		<b>Computer Architecture:	</b> ARM									\n
//!		<b>Compiler:				</b> GCC									\n
//! 	<b>uC Model:				</b> PSoC5									\n
//!		<b>Documentation Format:	</b> Doxygen								\n
//!		
//!		
//!

//===============================================================================================//
//======================================= FILE INCLUSIONS =======================================//
//===============================================================================================//

#include <device.h>
#include "../common/PublicObjects.h"
#include "Config.h"
#include "Comms.h"


// Bit positions of data in rx packet

#define MS1_BP 5	// Higher byte of motor speed
#define MS0_BP 6	// Lower byte of motor speed

typedef enum {
	idle,
	secondIdenChar,
	thirdIdenChar,
	packetDataCount,
	packetData,
	receivingChecksum,
	packetComplete
} commsStates_t;

typedef enum {
	xbeeInit,
	xbeeOn
} xbeeStates_t;

//===============================================================================================//
//=============================== PRIVATE FUNCTION PROTOTYPES ===================================//
//===============================================================================================//

void Comms_RetrieveData();
uint8 Comms_DecodePacket();

//===============================================================================================//
//==================================== PRIVATE VARIABLES ========================================//
//===============================================================================================//

//flags
static bool_t _newPacketFlag = FALSE;
// Set when a byte has not been read from a new data packet
static bool_t _unreadDataFlag = FALSE;
static bool_t _commsPacketBufferOverrunFlag = FALSE;
static bool_t _commsInitCompleteFlag = FALSE;
static bool_t _commsTimeoutFlag = FALSE;

//rx variables
//static commsData_t _commsData;
static uint8_t _packetBuffer[configCOMM_BUFFER_SIZE];
static uint8_t* _idenChars;

// counter for comms timeout
static uint16_t _timeoutCounter = 0;

/***Function Definitions***/

void Comms_Init(uint8_t* idenCharsIn)
{
	//led_on(0);
	_idenChars = idenCharsIn;
	
	// Intialise uart used to communicate with comms
	UartXbee_Start();
	
	// Wake-up Xbee
	//PinXbeeSleep_Write(1);

	//Signal that intialisation is complete
	_commsInitCompleteFlag = TRUE;
}

//! @brief		State machine for comms to remote control.
//! @note		Call once per main loop tick
void Comms_Run(void)
{
	
	static xbeeStates_t xbeeState = xbeeInit;
	static xbeeStates_t prevxbeeState = xbeeInit;
	
	switch(xbeeState)
	{
		case xbeeInit:
			#if(configDEBUG_COMMS == 1) 
				UartDebug_PutString("COMMS: Entering xbeeInit state.\r\n");
			#endif
			// Intialise uart used to communicate with comms
			UartXbee_Start();
			// Go to on state
			xbeeState = xbeeOn;
			break;
		case xbeeOn:
			if(prevxbeeState != xbeeState)
			{
				#if(configDEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeOn state.\r\n");
				#endif
				prevxbeeState = xbeeState;
			}
			// Check for data
			Comms_RetrieveData();
			
			//Decode if their are new packets present
			if(_newPacketFlag)
			{
				// Reset timeout counter
				_timeoutCounter = 0;
				// Set timeout flag to false when new packet arrives
				_commsTimeoutFlag = FALSE;
				_newPacketFlag = FALSE;
				// Set unread data flag (cleared when comms_get_byte is called)
				_unreadDataFlag = TRUE;
			}
			else
			{
				// Increment timeout counter if no packet arrived
				_timeoutCounter++;
				// Set flag if timeout counter has reached the limit without being reset by a new packet arriving
				if(_timeoutCounter >= configCOMMS_TIMEOUT_PERIOD_MS/configMAIN_TICK_PERIOD_MS)
				{
					_commsTimeoutFlag = TRUE;
				} 
			}
			
			break;
	}
}

//! @brief		Checks the rx uart buffer and decodes if data present
void Comms_RetrieveData()
{
	static commsStates_t commsState = idle;
	static uint8_t packetBufferPos = 0;
	static uint8_t numOfDataBytes = 0;
	static uint8_t rxDataByte;

	while(UartXbee_GetRxBufferSize() != 0)
	{
		rxDataByte = UartXbee_GetChar();
		
		switch(commsState){
			case idle:
				
				packetBufferPos = 0;
				numOfDataBytes = 0;
				if(rxDataByte == _idenChars[0])
				{
					_packetBuffer[packetBufferPos] = rxDataByte;
					packetBufferPos++;
					commsState = secondIdenChar;
				}
				break;
			case secondIdenChar:
				if(rxDataByte == _idenChars[1])
				{
					_packetBuffer[packetBufferPos] = rxDataByte;
					packetBufferPos++;
					commsState = thirdIdenChar;
				}
				else
				{
					// Go back to idle state if header not valid
					commsState = idle;
				}
				break;
			case thirdIdenChar:
				if(rxDataByte == _idenChars[2])
				{
					_packetBuffer[packetBufferPos] = rxDataByte;
					packetBufferPos++;
					commsState = packetDataCount;
				}
				else
				{
					// Go back to idle state if header not valid
					commsState = idle;
				}
				break;
			case packetDataCount:
				commsState = packetData;
				_packetBuffer[packetBufferPos] = rxDataByte;
				numOfDataBytes = rxDataByte;
				packetBufferPos++;
				break;

			case packetData:
				
				_packetBuffer[packetBufferPos] = rxDataByte;
				packetBufferPos++;
				if(packetBufferPos >= configCOMMS_RX_MSG_LENGTH	- 1) //! @todo Fix
				{
					commsState = packetComplete;
				}
				
				break;
			case receivingChecksum:
				commsState = packetComplete;
				break;
			case packetComplete:
				// Set new packet flag true so comms decode can be called
				_newPacketFlag = TRUE;
				commsState = idle;
				break;
			default:
				commsState = idle;
				break;
		}
		
		//packetBufferPos++;
		if(packetBufferPos > configCOMM_BUFFER_SIZE)					//Resets packet buffer index (shouldn't happen)
		{
			#if(configDEBUG_COMMS_ERRORS == 1)
				UartDebug_PutString("COMMS: Error - Packet buffer overrun before message was dound\r\n");
			#endif
			packetBufferPos = 0;
			_commsPacketBufferOverrunFlag = TRUE;
			PinLedGreen_Write(0);
		}
	}
}

uint8_t Comms_GetByte(uint8_t byteNum)
{
	// Return requested byter
	return _packetBuffer[byteNum];
}

//! @brief 		Function passes variables onto usart
void Comms_Send(uint8_t *dataArray, uint8_t numOfBytes)
{
	UartXbee_PutArray(dataArray, numOfBytes);
}

// Returns true if comms has timeout because it has received a packet in COMMS_TIMEOUT_PERIOD
uint8_t Comms_Timeout(void)
{
	return _commsTimeoutFlag;
}

//! @brief 		Returns true if there is a new packet that hasn't been read
bool_t Comms_IsNewPacket(void)
{
	bool_t tempVar = _unreadDataFlag;
	_unreadDataFlag = FALSE;
	return tempVar;
}
