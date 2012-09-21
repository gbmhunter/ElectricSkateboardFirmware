//!
//! @file 		Comms.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		22/12/2010
//! @brief 		Controls the comms between board and remote. Common to both platforms.
//! @details
//!		<b>Last Modified:			</b> 24/05/2011								\n
//!		<b>Version:					</b> v1.0									\n
//!		<b>Company:					</b> CladLabs								\n
//!		<b>Project:					</b> Electric Skateboard - Skateboard Remote\n
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
#include <stdio.h>

#include "../common/PublicObjects.h"
#include "Config.h"
#include "Comms.h"
#include "Lights.h"




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
	xbeeOff,
	xbeeTurningOn,
	xbeeOnStable,
	xbeeSending,
	xbeeWaitingForResponse
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


static uint8_t* _idenChars;

static uint8_t _txDataBuffer[configCOMMS_MSG_SIZE];
static uint8_t _rxDataBuffer[configCOMM_RX_BUFFER_SIZE];

static bool_t _turnOffXbeeFlag = FALSE;
static bool_t _turnOnXbeeFlag = FALSE;
static bool_t _toSendFlag = FALSE;

/***Function Definitions***/

void Comms_Init(uint8_t* idenCharsIn)
{
	//led_on(0);
	_idenChars = idenCharsIn;
	
	//Signal that intialisation is complete
	_commsInitCompleteFlag = TRUE;
}

//! @brief		Call once per main loop tick
void Comms_Run(void)
{
	static uint32_t counter = 0;
	
	static xbeeStates_t xbeeState = xbeeInit;
	static xbeeStates_t prevxbeeState = xbeeInit;
	static uint32_t	xbeeTurnOnTime = 0;
	static uint32_t waitingForResponseCount = 0;
	
	
	switch(xbeeState)
	{
		case xbeeInit:
			// Intialise uart used to communicate with comms
			UartXbee_Start();
			// Sleep Xbee
			PinXbeeSleep_Write(1);
			xbeeState = xbeeOff;
			break;
		case xbeeOff:
			if(prevxbeeState != xbeeOff)
			{
				#if(config_DEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeOff state.\r\n");
				#endif
				// Put xbee to sleep
				PinXbeeSleep_Write(1);
				prevxbeeState = xbeeOff;
			}
			
			if(_turnOffXbeeFlag == TRUE)
				_turnOffXbeeFlag = FALSE;
			
			// Check if xbee needs to be turned on
			if(_turnOnXbeeFlag == TRUE)
			{
				xbeeState = xbeeTurningOn;
				// Reset flag
				_turnOnXbeeFlag = FALSE;
			}

			break;
		case xbeeTurningOn:
			if(prevxbeeState != xbeeTurningOn)
			{
				#if(config_DEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeTurningOn state.\r\n");
				#endif
				// Turn on xbee
				PinXbeeSleep_Write(0);
				// Assign turn on time
				xbeeTurnOnTime = counter;
				prevxbeeState = xbeeTurningOn;
			}
			// Increment counter to wait for xbee to start up
			if(counter >= xbeeTurnOnTime + configXBEE_START_UP_TIME_MS/configMAIN_TICK_PERIOD_MS)
				xbeeState = xbeeOnStable;
			break;
		case xbeeOnStable:
			if(prevxbeeState != xbeeOnStable)
			{
				#if(config_DEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeOnStable state.\r\n");
				#endif
				prevxbeeState = xbeeOnStable;
			}
			
			// Clear flag as we don't need to do anything
			if(_turnOnXbeeFlag == TRUE)
				_turnOnXbeeFlag = FALSE;
			
			if(_toSendFlag == TRUE)
			{
				xbeeState = xbeeSending;
			}
			
			// Check if xbee needs to be turned off
			if(_turnOffXbeeFlag == TRUE)
			{
				#if(configCOMMS_ALLOW_XBEE_SLEEP == 1)
					xbeeState = xbeeOff;
				#endif
				// Reset flag
				_turnOffXbeeFlag = FALSE;
			}
			break;
		case xbeeSending:
			if(prevxbeeState != xbeeSending)
			{
				#if(config_DEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeSending state.\r\n");
				#endif
				// Send data to the uart
				UartXbee_PutArray(_txDataBuffer, configCOMMS_MSG_SIZE);
				prevxbeeState = xbeeSending;
			}
			
			// Check is message has been sent
			if(UartDebug_ReadTxStatus() && UartXbee_TX_STS_FIFO_EMPTY)
			{
				_toSendFlag = FALSE;
				xbeeState = xbeeWaitingForResponse;
			}

			break;
			
		case xbeeWaitingForResponse:
			if(prevxbeeState != xbeeWaitingForResponse)
			{
				#if(config_DEBUG_COMMS == 1) 
					UartDebug_PutString("COMMS: Entering xbeeWaitingForResponse state.\r\n");
				#endif
				waitingForResponseCount = counter;
				prevxbeeState = xbeeWaitingForResponse;
			}
			
			Comms_RetrieveData();
			
			//Decode if their are new packets present
			if(_newPacketFlag)
			{
				#if(config_DEBUG_COMMS == 1)
					char tempBuff[50];
					snprintf(tempBuff, sizeof(tempBuff), "COMMS: Board reponsed. Reponse time: %fms\r\n", (double)(counter - waitingForResponseCount)*configMAIN_TICK_PERIOD_MS);
					UartDebug_PutString(tempBuff);
				#endif
				_newPacketFlag = FALSE;
				// Set unread data flag (cleared when comms_get_byte is called)
				_unreadDataFlag = TRUE;
				xbeeState = xbeeOnStable;
			}
			
			// Check for timeout
			if(counter >= waitingForResponseCount + configCOMMS_TIMEOUT_PERIOD_MS/configMAIN_TICK_PERIOD_MS)
			{
				#if(config_DEBUG_COMMS_ERROR == 1) 
					char tempBuff[100];
					snprintf(tempBuff, sizeof(tempBuff), "COMMS: Xbee timeout. Time since send: %fms\r\n", (double)(counter - waitingForResponseCount)*configMAIN_TICK_PERIOD_MS);
					UartDebug_PutString(tempBuff);
				#endif
				_commsTimeoutFlag = TRUE;
				xbeeState = xbeeOnStable;
			}
			break;
	}
	
	// Increment state counter
	counter++;
}

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
					_rxDataBuffer[packetBufferPos] = rxDataByte;
					packetBufferPos++;
					commsState = secondIdenChar;
				}
				break;
			case secondIdenChar:
				if(rxDataByte == _idenChars[1])
				{
					_rxDataBuffer[packetBufferPos] = rxDataByte;
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
					_rxDataBuffer[packetBufferPos] = rxDataByte;
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
				_rxDataBuffer[packetBufferPos] = rxDataByte;
				numOfDataBytes = rxDataByte;
				packetBufferPos++;
				break;

			case packetData:
				
				_rxDataBuffer[packetBufferPos] = rxDataByte;
				packetBufferPos++;
				if(packetBufferPos >= 4+5) //! @todo Fix
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
		if(packetBufferPos > configCOMM_RX_BUFFER_SIZE )					//Resets packet buffer index (shouldn't happen)
		{
			#if(config_DEBUG_COMMS_ERROR == 1) 
					UartDebug_PutString("COMMS: ***Error***. Buffer overrun.\r\n");
			#endif
			packetBufferPos = 0;
			_commsPacketBufferOverrunFlag = TRUE;
		}
	}
}

void Comms_TurnOn(void)
{
	_turnOnXbeeFlag = TRUE;
}

void Comms_TurnOff(void)
{
	_turnOffXbeeFlag = TRUE;
}

uint8_t Comms_GetByte(uint8_t byteNum)
{
	// Clear unread data flag once at east one byte from the new packet has been read
	return _rxDataBuffer[byteNum];
}

//! @brief 		Call to send data to the comms
void Comms_Send(uint8_t* dataArray)
{
	memcpy(_txDataBuffer, dataArray, configCOMMS_MSG_SIZE);
	_toSendFlag = TRUE;
}

//! @brief 		Returns true if comms has timeout because it has received a packet in COMMS_TIMEOUT_PERIOD
bool_t Comms_IsTimeout(void)
{
	// Reset flag
	bool_t tempVar = _commsTimeoutFlag;
	_commsTimeoutFlag = FALSE;
	return tempVar;
}

// Returns true if their is a new packet that hasn't been read
uint8_t Comms_IsNewPacket(void)
{
	bool_t tempVar = _unreadDataFlag;
	_unreadDataFlag = FALSE;
	return tempVar;
}
