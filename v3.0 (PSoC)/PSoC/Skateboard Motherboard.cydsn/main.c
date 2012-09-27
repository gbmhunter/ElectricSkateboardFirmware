//!
//! @file 		main.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Contains the entry point and main loop.
//! @details
//!		<b>Last Modified:			</b> 28/09/2012					\n
//!		<b>Version:					</b> v1.0						\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Electric Skateboard - Board\n
//!		<b>Computer Architecture:	</b> ARM						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		
//!		Contains main entrant function.
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

// PSoC
#include <device.h>

// GCC
#include <stdio.h>

// User
#include "../common/PublicObjects.h"

#include "Comms.h"

#include "Config.h"
#include "Lights.h"
#include "Piezo.h"
#include "Motor.h"
#include "Adc.h"

//===============================================================================================//
//=================================== PRECOMPILER CHECKS ========================================//
//===============================================================================================//

//===============================================================================================//
//========================================== DEFINES ============================================//
//===============================================================================================//



//===============================================================================================//
//========================================== TYPEDEF's ==========================================//
//===============================================================================================//

typedef enum{
	init,
	off,
	inRange,
	motorOn,
	alarmArmed,
	alarmTriggered
} mainStates_t;

//=================================================================================================
//==================================== PRIVATE VARIABLES ==========================================
//=================================================================================================

static uint8_t _msg[configCOMMS_TX_MSG_LENGTH];
// Status byte (shared with remote, both units can change bits, as set in definitions.h)
static uint8_t boardStatusByte;

static mainStates_t mainState = off;

static uint32_t _mainTickCounter = 0;

static bool_t motionSensorTriggered = FALSE;

//=================================================================================================
//=============================== PRIVATE FUNCTION PROTOTYPES =====================================
//=================================================================================================

bool_t Main_CheckForAlarmOnOffPressed(void);
void Main_CheckForLedOnOffPressed(void);
void Main_CheckForChangeLedMode(void);
void Main_BuildMsg(uint8_t *msg);

CY_ISR_PROTO(Main_MainTickIsr);
CY_ISR_PROTO(Main_MotionSensorIsr);

//=================================================================================================
//===================================== PUBLIC FUNCTIONS ==========================================
//=================================================================================================

void main()
{

	CyGlobalIntEnable;
	
	// Start main tick interrupt and pass in ISR
	IsrMainTick_StartEx(Main_MainTickIsr);
	
	TimerMainTick_Start();
	
	static uint8_t iden_chars[3];
	iden_chars[0] = 's';
	iden_chars[1] = 'k';
	iden_chars[2] = 't';
	
	Comms_Init(iden_chars);
	
	UartDebug_Start();
	
	#if(configDEBUG_MAIN == 1)
		UartDebug_PutString("MAIN: Running...\r\n");
	#endif

	
	// Start motion sensor interrupt and pass in ISR
	IsrMotionSensor_StartEx(Main_MotionSensorIsr);
	IsrMotionSensor_ClearPending();
	
	static mainStates_t prevMainState = init;
	
	// Flash lights as start-up O.K.
    Lights_AllOn();
	CyDelay(500);
	Lights_AllOff();
	CyDelay(250);
	
	//PinXbeeSleep_Write(0);
	// Lights_SetLedMode(LIGHT_FRONT_LEFT, OFF, 0);
	// Lights_SetLedMode(LIGHT_FRONT_RIGHT, OFF, 500);

	uint32_t currentTick = 0;
	static uint8_t alarmTriggerCount = 0;
	static uint32_t alarmTriggeredStartCount = 0;
    
    for(;;)
    {
		
		// Update the current tick
		currentTick = _mainTickCounter;
       
	   //===================================== CALL SUB-STATE MACHINES =============================//
	   
	   // Inputs
	   Lights_Run();
	   Adc_Run();
	   Comms_Run();
	   
	   // Outputs
	   Motor_Run();
	   Piezo_Run();
	   
	   //======================================== MAIN STATE MACHINE ===============================//
		switch(mainState)
		{
			
			case off:
				if(prevMainState != off)
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Entering mainOff state.\r\n");
					#endif
					// Clear on bit in status byte
					boardStatusByte &= ( (1 << commsON_BIT_POS)^0xFF );
					// Clear in range bit
					boardStatusByte &= ( (1 << commsIN_RANGE_BIT_POS)^0xFF );
					
					// Flash orange LED
					Lights_SetLedMode(LED_ORANGE, FLASHING, 500);
					Lights_SetLedMode(LED_RED, OFF, 0);
					Lights_SetLedMode(LED_GREEN, OFF, 0);
					
					// Turn off skirting light
					Lights_SetLedMode(LIGHT_SKIRTING, OFF, 0);
					
					Piezo_EmitBeep();
					Piezo_EmitBeep();
					
					prevMainState = off;
				}
					
				// Check if new packet has arrived from remote
				if(Comms_IsNewPacket())
				{
					
					Main_BuildMsg(_msg);
					Comms_Send(_msg, configCOMMS_TX_MSG_LENGTH);
					mainState = inRange;
					break;
				}
				
				break;
			//=========================================== IN RANGE STATE =================================//
			// Skateboard is in range of remote, but not turned on yet
			// Only state that you can go to alarm state from
			case inRange:
				if(prevMainState != inRange)
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Entering mainInRange state.\r\n");
					#endif
					
					// Set in-range bit in status byte
					boardStatusByte |= (1 << commsIN_RANGE_BIT_POS);
					
					// Solid on orange LED
					Lights_SetLedMode(LED_ORANGE, ON, 0);
					Lights_SetLedMode(LED_RED, OFF, 0);
					Lights_SetLedMode(LED_GREEN, OFF, 0);
					
					// Turn off skirting light
					Lights_SetLedMode(LIGHT_SKIRTING, OFF, 0);
					
					// Emit beep if arriving from any other state than motorOn
					if(prevMainState != motorOn)
						Piezo_EmitBeep();
					
					prevMainState = inRange;
				}
				
				if(Comms_IsNewPacket())
				{
					if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsON_BIT_POS))
					{
						mainState = motorOn;
					}
					
					Main_CheckForLedOnOffPressed();
					Main_CheckForChangeLedMode();
						
					if(Main_CheckForAlarmOnOffPressed())
					{
						mainState = alarmArmed;
						// Set on bit in status byte before sending message
						boardStatusByte |= (1 << commsALARM_ON_BIT_POS);
					}
					
					Main_BuildMsg(_msg);
					Comms_Send(_msg, configCOMMS_TX_MSG_LENGTH);
				}
				
				if(Comms_Timeout())
				{
					// Turn off skateboard if communication lost with remote
					mainState = off;
					break;
				}
				
				break;
			//=========================================== MOTOR ON =======================================//
			// Skateboard is on, and motor can be controlled
			// Cannot enter alarm state from here (have to turn motor off first)
			case motorOn:
				if(prevMainState != motorOn)
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Entering mainMotorOn state.\r\n");
					#endif
					// Set on bit in status byte
					boardStatusByte |= (1 << commsON_BIT_POS);
					
					// Solid on orange LED
					Lights_SetLedMode(LED_ORANGE, ON, 0);
					Lights_SetLedMode(LED_RED, OFF, 0);
					Lights_SetLedMode(LED_GREEN, ON, 0);
					
					// Turn on skirting light
					Lights_SetLedMode(LIGHT_SKIRTING, ON, 0);
					
					Piezo_EmitMotorOnSound(up);
				
					// Enable motor
					Motor_TurnOn();
					
					prevMainState = motorOn;
				}
				
				if(Comms_IsNewPacket())
				{
					
					// Check if off button on remote has been pressed
					if(!(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsON_BIT_POS)))
					{
						#if(configDEBUG_MAIN == 1)
							UartDebug_PutString("MAIN: Remote has turned off motor.\r\n");
						#endif
						// Clear on bit in status byte
						boardStatusByte &= ((1 << commsON_BIT_POS)^0xFF);
						// Turn off motor (user has lost all speed control)
						Piezo_EmitMotorOnSound(down);
						Motor_TurnOff();
						mainState = inRange;
					}
					
					Main_CheckForLedOnOffPressed();
					Main_CheckForChangeLedMode();

					Main_BuildMsg(_msg);
					Comms_Send(_msg, configCOMMS_TX_MSG_LENGTH);
				}

				// Check if comms has timed out (no packet received in limit set by COMMS_TIMEOUT_PERIOD)
				if(Comms_Timeout())
				{
					// Clear on bit in status byte
					boardStatusByte &= ((1 << commsON_BIT_POS)^0xFF);
					// Turn off motor (user has lost all speed control)
					Motor_TurnOff();
					Piezo_EmitMotorOnSound(down);
					// Turn off skateboard if communication lost with remote
					mainState = off;
					break;
				}

				break;
			//=========================================== ALARM ARMED STATE =================================//
			// Allows lights to be turned on/off. No comms timeout in this state, so user can turn remote off
			case alarmArmed:
				if(prevMainState != alarmArmed)
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Entering mainAlarmArmed state.\r\n");
					#endif
					PinMotionSensor_ClearInterrupt();
					IsrMotionSensor_ClearPending();
					IsrMotionSensor_Enable();
					// Solid on orange LED
					Lights_SetLedMode(LED_ORANGE, OFF, 0);
					Lights_SetLedMode(LED_RED, ON, 0);
					Lights_SetLedMode(LED_GREEN, OFF, 0);
					
					Piezo_AlarmActivatedSound();
					
					// Turn off skirting light
					Lights_SetLedMode(LIGHT_SKIRTING, OFF, 0);
					
					// Reset trigger count
					alarmTriggerCount = 0;
					
					prevMainState = alarmArmed;
				}
				
				
				// Turn alarm on if motion sensor is triggered
				if(motionSensorTriggered)
				{
					// Reset triggered flag for next time around
					motionSensorTriggered = FALSE;
					// Increment trigger counter
					alarmTriggerCount++;
					PinMotionSensor_ClearInterrupt();
					IsrMotionSensor_ClearPending();
					IsrMotionSensor_Enable();
					if(alarmTriggerCount > configALARM_NUMBER_OF_WARNING_BEEPS)
						// Go to triggered state (activate piezo, flashes lights)
						mainState = alarmTriggered;
					else
						// Give warning
						Piezo_EmitBeep();
				}
				
				if(Comms_IsNewPacket())
				{	
					Main_CheckForLedOnOffPressed();
					Main_CheckForChangeLedMode();
					
					// Check for alarm being turned off
					if(!Main_CheckForAlarmOnOffPressed())
					{
						Piezo_AlarmEnable(FALSE);
						// Clear status byte of alarm set bit
						boardStatusByte &= ((1 << commsALARM_ON_BIT_POS)^0xFF);
						mainState = inRange;
					}
					
					Main_BuildMsg(_msg);
					Comms_Send(_msg, configCOMMS_TX_MSG_LENGTH);
				}
					
				break;
			//===================================== ALARM TRIGGERED STATE ================================//
			// No timeout for this state (user can set alarm and then turn of remote)
			case alarmTriggered:
				if(prevMainState != mainState)
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Entering mainAlarmTriggered state.\r\n");
					#endif
					// Turn the alarm on
					Piezo_AlarmEnable(TRUE);
					
					// Turn on skirting light, flash all other high-power lights
					Lights_SetLedMode(LIGHT_SKIRTING, ON, 0);
					Lights_SetLedMode(LIGHT_FRONT, FLASHING, 200);
					Lights_SetLedMode(LIGHT_BACK, FLASHING, 200);
					
					// Remeber the count at which this state was entered
					alarmTriggeredStartCount = _mainTickCounter;
					
					prevMainState = mainState;
				}
					#if(configDEBUG_MAIN == 1)
						snprintf(debugBuff, sizeof(debugBuff), "MAIN: Trigger Count = %f, Main State Count = %lu\r\n", 
							alarmTriggeredStartCount + configALARM_TIME_TO_REMAIN_TRIGGERED_SEC*1000.0/configMAIN_TICK_PERIOD_MS, _mainTickCounter);
						UartDebug_PutString(debugBuff);
					#endif
				
				
				if(Comms_IsNewPacket())
				{
					
					Main_CheckForLedOnOffPressed();
					Main_CheckForChangeLedMode();
					
					// Check for alarm being turned off
					if(!Main_CheckForAlarmOnOffPressed())
					{
						Piezo_AlarmEnable(FALSE);
						// Clear status byte of alarm set bit
						boardStatusByte &= ((1 << commsALARM_ON_BIT_POS)^0xFF);
						Lights_TurnOffHighPowerLights();
						mainState = inRange;
					}
					
					Main_BuildMsg(_msg);
					Comms_Send(_msg, configCOMMS_TX_MSG_LENGTH);
				}
				
				if(_mainTickCounter >= (uint32_t)(alarmTriggeredStartCount + configALARM_TIME_TO_REMAIN_TRIGGERED_SEC*1000.0/configMAIN_TICK_PERIOD_MS))
				{
					#if(configDEBUG_MAIN == 1)
						UartDebug_PutString("MAIN: Alarm triggered time elasped.\r\n");
					#endif
					// Disable alarm sound and go back to alarm armed state
					Piezo_AlarmEnable(FALSE);
					Lights_TurnOffHighPowerLights();
					mainState = alarmArmed;
				}
				
				break;
				
			default:
				break;
		}
		
		
		// Wait for next tick from interrupt
		if(currentTick == _mainTickCounter)
			// Normal operation, wait for next tick
			while(currentTick == _mainTickCounter);
		else
		{
			// Tick has incremented before main loop has finished executing, code is running too slow
			//! @todo Add error checking
		}
	   
    }
}

//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================

//! @brief		Checks the status byte to see if the leds have been turned on
void Main_CheckForLedOnOffPressed(void)
{
	// Check for light on/off button being pressed on remote
	if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsLIGHTS_ON_BIT_POS))
	{
		if(Lights_IsHighPowerLightsOn() == FALSE)
		{
			Lights_TurnOnHighPowerLights();
			Piezo_EmitBeep();
		}
	}
	else
	{
		if(Lights_IsHighPowerLightsOn() == TRUE)
		{
			Lights_TurnOffHighPowerLights();
			Piezo_EmitBeep();
		}
	}
}

//! @brief		Checks wether user has pressed the light mode button on remote
void Main_CheckForChangeLedMode(void)
{
	// Check for light on/off button being pressed on remote
	if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsCHANGE_LIGHT_MODE_BIT_POS))
	{
		Piezo_EmitBeep();
		Lights_ChangeHighPowerLightMode();
		Lights_TurnOnHighPowerLights();
	}
}

//! @brief 		Checks for light on/off button being pressed on remote
bool_t Main_CheckForAlarmOnOffPressed(void)
{
	// Check for light on/off button being pressed on remote
	if(Comms_GetByte(commsSTATUS_BYTE_POS) & (1 << commsALARM_ON_BIT_POS))
		return TRUE;
	else
		return FALSE;
}

//! @brief		Builds message to send over comms
void Main_BuildMsg(uint8_t *msg)
{
	msg[0] = 'r';
	msg[1] = 'm';
	msg[2] = 't';
	msg[3] = 0x03;
	msg[commsSTATUS_BYTE_POS] = boardStatusByte;
	msg[5] = Comms_GetByte(commsMOTOR_HIGH_BYTE_POS);
	msg[6] = Comms_GetByte(commsMOTOR_LOW_BYTE_POS);
	
	uint16_t throttleVal16Bit = (uint16_t)Adc_GetBattVolt();
	msg[commsBOARD_BATT_VOLT_HIGH_BYTE_POS] = (uint8_t)(throttleVal16Bit >> 8);
	msg[commsBOARD_BATT_VOLT_LOW_BYTE_POS] = (uint8_t)(throttleVal16Bit >> 0);

	msg[9] = '\0';
	
}

//===============================================================================================//
//============================================ ISR's ============================================//
//===============================================================================================//


CY_ISR(Main_MotionSensorIsr)
{
	motionSensorTriggered = TRUE;
	IsrMotionSensor_Disable();
}

//! @brief 		ISR to handle the main tick
CY_ISR(Main_MainTickIsr)
{
	// Increment the tick counter. This will cause the main loop to execute once
	_mainTickCounter++;
}

//===============================================================================================//
//============================================= GRAVEYARD =======================================//
//===============================================================================================//





/* [] END OF FILE */
