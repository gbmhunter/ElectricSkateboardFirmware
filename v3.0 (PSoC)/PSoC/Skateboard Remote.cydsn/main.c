//!
//! @file 		main.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Contains the entry point and main loop.
//! @details
//!		<b>Last Modified:			</b> 28/09/2012								\n
//!		<b>Version:					</b> v1.0									\n
//!		<b>Company:					</b> CladLabs								\n
//!		<b>Project:					</b> Electric Skateboard - Skateboard Remote\n
//!		<b>Computer Architecture:	</b> ARM									\n
//!		<b>Compiler:				</b> GCC									\n
//! 	<b>uC Model:				</b> PSoC5									\n
//!		<b>Documentation Format:	</b> Doxygen								\n
//!		
//!		Main entry point and loop
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//===============================================================================================//
//======================================= FILE INCLUSIONS =======================================//
//===============================================================================================//

// PSoC
#include <device.h>

// GCC
#include <stdio.h>

// User
#include "../common/PublicObjects.h"
#include "Config.h"
#include "Buttons.h"
#include "BattMonitor.h"
#include "Lights.h"
#include "Adc.h"
#include "Comms.h"

//===============================================================================================//
//========================================== TYPEDEF's ==========================================//
//===============================================================================================//

typedef enum{
	mainInit,
	mainOff,
	mainInRange,
	mainMotorOn,
	mainAlarmOn
} mainState_t;

//===============================================================================================//
//==================================== PRIVATE VARIABLES ========================================//
//===============================================================================================//

static uint32 _mainTickCounter = 0;	//!< Main tick counter, incremented by timer interrupt and used to run main loop at a regular interval


static uint8_t _msg[8];
// Status byte
static uint8_t statusByte = 0x00;

//! @debug
static char tempBuff[100] = {0};

//===============================================================================================//
//=============================== PRIVATE FUNCTION PROTOTYPES ===================================//
//===============================================================================================//

void Main_BuildMsg(uint8_t *msg, mainState_t mainState);
CY_ISR_PROTO(Main_MainTickIsr);

//===============================================================================================//
//===================================== PUBLIC FUNCTIONS ========================================//
//===============================================================================================//

void main()
{

	// Enables global interrupts. Required for CapSense.
    CyGlobalIntEnable;
	
	//========================================= INITIALIZATION CODE ================================//
	Buttons_Init();
	
	static uint8_t iden_chars[3];
	iden_chars[0] = 'r';
	iden_chars[1] = 'm';
	iden_chars[2] = 't';
	
	Comms_Init(iden_chars);
	BattMonitor_Init();
	// Enable timer that triggers interrupt to increment tick
	TimerMainTick_Start();
	//SleepTimer_Start();
	
	#if(config_DEBUG_MAIN == 1)
		UartDebug_Start();
		UartDebug_PutString("Running...");
	#endif
	
	// Start main tick ISR and pass in interrupt handler function
	//IsrSleepTick_StartEx(Main_MainTickIsr);
	IsrMainTick_StartEx(Main_MainTickIsr);
	
	uint16 count = 0;
	uint32 currentTick = 0;
	
	// Main state variable
	mainState_t prevMainState = mainInit;		//!< Assign reset, only valid for first time running through the state machine after reset
	mainState_t mainState = mainInit;		//!< Default state is off
	
	uint32_t commsSendCountInterval = (uint32_t)(configCOMMS_SEND_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	uint32_t commsLastSendCount = 0;
	

	// Flash leds as O.K
	Lights_AllOn();
	CyDelay(500);
	Lights_AllOff();
	CyDelay(500);

	
	//! @todo	Make sure tick variables do not overflow
	
	
	//========================================= MAIN LOOP ==========================================//
    for(;;)
    {
			
		// Update the current tick
		currentTick = _mainTickCounter;
		
		// Run state machines
		Comms_Run();
		Adc_Run();
		static uint16_t boardBattVoltage = 0;
		boardBattVoltage = ((Comms_GetByte(commsBOARD_BATT_VOLT_HIGH_BYTE_POS)<<8) | (Comms_GetByte(commsBOARD_BATT_VOLT_LOW_BYTE_POS)));
		BattMonitor_Run(Adc_GetBattVolt(), (double)boardBattVoltage);
		Lights_Run();
		Buttons_Run();
		
		//! @debug
		count++;
		
		
	
		
		// Main state machine
		switch(mainState)
		{
			case mainInit:
				mainState = mainOff;
				break;
			case mainOff:
				if(prevMainState != mainOff)
				{
					#if(config_DEBUG_MAIN == 1) 
						UartDebug_PutString("MAIN: Entering mainOff state.\r\n");
					#endif
					// Clears on bit in status byte
					statusByte &= ((1 << commsON_BIT_POS)^0xFF);
					prevMainState = mainOff;
				}
				
				// Flash first LED
				Lights_SetLedMode(LED_IN_RANGE, FLASHING, 500);
				
				// Determines speed of packages
				if(currentTick >= commsLastSendCount + commsSendCountInterval)
				{
					// Send message to skateboard
					Main_BuildMsg(_msg, mainState);
					Comms_TurnOn();
					Comms_Send(_msg);
					commsLastSendCount = currentTick;
				}
				
				if(Comms_IsTimeout())
				{
					// Do nothing, connection has not been established yet
					// No power save mode while searching for skateboard
				}
				
				// Check for new packet
				if(Comms_IsNewPacket())
				{
					Comms_TurnOff();
					// True if skateboard has received msg from remote and replied with o.k.
					if((Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsIN_RANGE_BIT_POS)) != 0x00)
					{
						mainState = mainInRange;
						Lights_SetLedMode(LED_IN_RANGE, OFF, 0);
						break;
					}
				}
				
				break;
				
			case mainInRange:
				if(prevMainState != mainInRange)
				{
					#if(config_DEBUG_MAIN == 1) 
						UartDebug_PutString("MAIN: Entering mainInRange state.\r\n");
					#endif
					Lights_SetLedMode(LED_IN_RANGE, ON, 0);
					Lights_SetLedMode(LED_ALARM_ON, OFF, 0);
					Lights_SetLedMode(LED_MOTOR_ON, OFF, 0);
					prevMainState = mainInRange;
				}
				
				// Check for comms timeout. Comms has been dropped (out of range), so go back to off state.
				if(Comms_IsTimeout())
				{
					mainState = mainOff;
					break;
				}
				
				// Check if user has pressed on button, set on bit if true
				if(Buttons_IsMotorButtonPressed())
				{
					// Set on bit in status byte
					statusByte |= (1 << commsON_BIT_POS);
					
				}
				// Buttons presses are mutually exclusive (else if)
				else if(Buttons_IsAlarmButtonPressed())
				{
					statusByte |= (1<< commsALARM_ON_BIT_POS);
				}
				
				// Check if use has pressed the lights on button, set bit if true
				if(Buttons_IsLightsOnOffButtonPressed())
					statusByte |= (1 << commsLIGHTS_ON_BIT_POS);
				else
					statusByte &= ((1 << commsLIGHTS_ON_BIT_POS)^0xFF);
				
				// Check for light mode being pressed. This needs to be reset after message sent.
				if(Buttons_IsLightModeButtonPressed())
					statusByte |= (1 << commsCHANGE_LIGHT_MODE_BIT_POS);
				else
					statusByte &= ((1 << commsCHANGE_LIGHT_MODE_BIT_POS)^0xFF);
					
				// Send packet to skateboard
				if(currentTick >= commsLastSendCount + commsSendCountInterval)
				{
					// Reset button light mode state once info has been sent
					Buttons_ResetLightModeButtonState();
					// Send message to skateboard
					Main_BuildMsg(_msg, mainState);
					
					Comms_TurnOn();	
					Comms_Send(_msg);
					// Reset counter
					commsLastSendCount = currentTick;
				}

				if(Comms_IsNewPacket())
				{
					Comms_TurnOff();
					// True is skateboard has received msg from remote and replied with on
					if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsON_BIT_POS))
					{	
						PinXbeeSleep_Write(0);
						mainState = mainMotorOn;
						Lights_SetLedMode(LED_IN_RANGE, OFF, 0);
						break;
					}
					// True is skateboard has received msg from remote and replied alarm on
					else if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsALARM_ON_BIT_POS))
					{	
						PinXbeeSleep_Write(0);
						mainState = mainAlarmOn;
						break;
					}
				}
				
				break;
			

			//===================================== MOTOR ON STATE =======================================//
			case mainMotorOn:
				
				if(prevMainState != mainMotorOn)
				{
					#if(config_DEBUG_MAIN == 1) 
						UartDebug_PutString("MAIN: Entering motorOn state.\r\n");
					#endif
					// Set on bit in status byte
					statusByte |= (1 << commsON_BIT_POS);
					// Flash third LED
					Lights_SetLedMode(LED_MOTOR_ON, ON, 0);
					
					// Enable throttle voltage measurements. ADC state machine measures throttle every configADC_THROTTLE_VOLT_MEAS_PERIOD_MS
					Adc_EnableThrottleVoltMeas(TRUE);
					prevMainState = mainMotorOn;
				}
				
				// Check for comms timeout. If comms has been dropped, go to off state
				if(Comms_IsTimeout())
				{
					mainState = mainOff;
					Lights_SetLedMode(LED_MOTOR_ON, OFF, 0);
					Adc_EnableThrottleVoltMeas(FALSE);
					break;
				}
				
				// Check if user has pressed on button, clear on bit if true (to turn off)
				if(!Buttons_IsMotorButtonPressed())
				{
					// Clear on bit in status byte
					statusByte &= ((1 << commsON_BIT_POS)^0xFF);
					//nextMainState = off;
					//Lights_SetLedMode(LED_MOTOR_ON, OFF, 0);
				}
				
				// Check if user has pressed the lights on button, set bit if true
				if(Buttons_IsLightsOnOffButtonPressed())
					statusByte |= (1 << commsLIGHTS_ON_BIT_POS);
				else
					statusByte &= ((1 << commsLIGHTS_ON_BIT_POS)^0xFF);
				
				// Check for light mode being pressed. This needs to be reset after message sent.
				if(Buttons_IsLightModeButtonPressed())
					statusByte |= (1 << commsCHANGE_LIGHT_MODE_BIT_POS);
				else
					statusByte &= ((1 << commsCHANGE_LIGHT_MODE_BIT_POS)^0xFF);
				
				
				// Send a new packet to skateboard periodically
				if(currentTick >= commsLastSendCount + commsSendCountInterval)
				{
					Buttons_ResetLightModeButtonState();
					// Send message to skateboard
					Main_BuildMsg(_msg, mainState);
					Comms_TurnOn();
					Comms_Send(_msg);
			
					// Reset counter
					commsLastSendCount = currentTick;
				}
				
				if(Comms_IsNewPacket())
				{
					Comms_TurnOff();
					// True is skateboard has received msg from remote and replied with off
					if(!(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsON_BIT_POS)))
					{	
						mainState = mainInRange;
						Adc_EnableThrottleVoltMeas(FALSE);
						break;
					}
				}
				
				break;
			
			//===================================== ALARM ACTIVATED STATE ================================//
			// Alarm on state. From here you can only go back to the in range by turning off the alarm.
			// Allows lights to be turned on/off, light mode to be changed
			case mainAlarmOn:
				if(prevMainState != mainAlarmOn)
				{
					#if(config_DEBUG_MAIN == 1) 
						UartDebug_PutString("MAIN: Entering alarmOn state.\r\n");
					#endif
					Lights_SetLedMode(LED_ALARM_ON, ON, 0);
					prevMainState = mainAlarmOn;
				}
				
				// Check if user turns alarm off
				if(Buttons_IsAlarmButtonPressed())
					statusByte |= (1<< commsALARM_ON_BIT_POS);
				else
					statusByte &= ((1 << commsALARM_ON_BIT_POS)^0xFF);
				
				// Check if user has pressed the lights on button, set bit if true
				if(Buttons_IsLightsOnOffButtonPressed())
					statusByte |= (1 << commsLIGHTS_ON_BIT_POS);
				else
					statusByte &= ((1 << commsLIGHTS_ON_BIT_POS)^0xFF);
				
				// Send a new packet to skateboard periodically
				if(currentTick >= commsLastSendCount + commsSendCountInterval)
				{
						// Send message to skateboard
						Main_BuildMsg(_msg, mainState);
						Comms_TurnOn();
						Comms_Send(_msg);
						// Reset counter
						commsLastSendCount = currentTick;
				}
				

				if(Comms_IsNewPacket())
				{
					Comms_TurnOff();
					// True is skateboard has replied with alarm off
					if(!(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsALARM_ON_BIT_POS)))
					{	
						mainState = mainInRange;
						break;
					}
				}
				
				break;
			
		}
		
		PinDebug_Write(1);
		
		
		// Wait for next tick from interrupt
		if(currentTick == _mainTickCounter)
			// Normal operation, wait for next tick
			while(currentTick == _mainTickCounter);
		else
		{
			//! @todo Add error checking
		}
		
		PinDebug_Write(0);
		
    }
}

void Main_BuildMsg(uint8_t *msg, mainState_t mainState)
{

	static uint32_t count = 0;
	
	count++;

	// 3 header chars indentifing message
	msg[0] = 's';
	msg[1] = 'k';
	msg[2] = 't';
	// Number of data bytes following...
	msg[3] = 0x03;
	// Status byte
	msg[commsSTATUS_BYTE_POS] = statusByte;
	
	if(mainState == mainMotorOn)
	{
		// Motor speed value (16-bit) (make 0 when off)
		double throttleVolt = Adc_GetThrottleVolt();
		// Scale to use full resolution
		double throttleVal = 65535.0*((throttleVolt - configTHROTTLE_LOW_LEVEL_MV))/(configTHROTTLE_HIGH_LEVEL_MV - configTHROTTLE_LOW_LEVEL_MV);
		
		if(throttleVal < 0)
			throttleVal = 0;
			
		if(throttleVal > 65535)
			throttleVal = 65535;
			
		// Convert to 16-bit
		uint16_t throttleVal16Bit = (uint16_t)throttleVal;
		msg[commsMOTOR_HIGH_BYTE_POS] = (uint8_t)(throttleVal16Bit >> 8);
		msg[commsMOTOR_LOW_BYTE_POS] = (uint8_t)(throttleVal16Bit >> 0);
	}
	else
	{
		msg[commsMOTOR_HIGH_BYTE_POS] = 0;
		msg[commsMOTOR_LOW_BYTE_POS] = 0;
	}
	
	msg[7] = '\0';
	
	/*
	if(count >= 5)
	{
			snprintf(tempBuff, sizeof(tempBuff), "Voltage = %u %u\r\n", msg[commsMOTOR_HIGH_BYTE_POS], msg[commsMOTOR_LOW_BYTE_POS]);
			UartDebug_PutString(tempBuff);
			count = 0;
	}
	*/
	
}

//! @brief 		ISR to handle the main tick
CY_ISR(Main_MainTickIsr)
{	
	
	// Increment the tick counter. This will cause the main loop to execute once
	_mainTickCounter++;
}

/* [] END OF FILE */
