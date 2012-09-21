//!
//! @file 		Lights.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Main GPRS task and supporting functions.
//! @details
//!		<b>Last Modified:			</b> 14/05/2011								\n
//!		<b>Version:					</b> v1.0									\n
//!		<b>Company:					</b> CladLabs								\n
//!		<b>Project:					</b> Electric Skateboard - Skateboard Remote\n
//!		<b>Computer Architecture:	</b> ARM									\n
//!		<b>Compiler:				</b> GCC									\n
//! 	<b>uC Model:				</b> PSoC5									\n
//!		<b>Documentation Format:	</b> Doxygen								\n
//!		
//!		Controls the led's on the board
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>

#include "Config.h"
#include "../common/PublicObjects.h"
#include "Lights.h"

//===============================================================================================//
//=================================== PRECOMPILER CHECKS ========================================//
//===============================================================================================//

//=================================================================================================
//========================================== DEFINES ==============================================
//=================================================================================================

//=================================================================================================
//========================================== TYPEDEF's ============================================
//=================================================================================================



//=================================================================================================
//==================================== PRIVATE VARIABLES ==========================================
//=================================================================================================

ledMode_t ledModeArray[configNUM_OF_LEDS];
double ledFlashRateMsArray[configNUM_OF_LEDS];
uint32 ledPrevFlashCountArray[configNUM_OF_LEDS] = {0};

//=================================================================================================
//=============================== PRIVATE FUNCTION PROTOTYPES =====================================
//=================================================================================================

void Lights_SetLed(uint8 ledNum, uint8 offOn);
void Lights_ToggleLed(uint8 ledNum);

//=================================================================================================
//===================================== PUBLIC FUNCTIONS ==========================================
//=================================================================================================

void Lights_AllOff(void)
{
	uint8 x;

	for(x = 0; x < configNUM_OF_LEDS; x++)
	{
		Lights_SetLed(x, 0);
	}
}

void Lights_AllOn(void)
{
	uint8 x;

	for(x = 0; x < configNUM_OF_LEDS; x++)
	{
		Lights_SetLed(x, 1);
	}
}

void Lights_FlashAllLeds(void)
{
	uint8 x;
	
	for(x = 0; x < configNUM_OF_LEDS; x++)
	{
		Lights_SetLed(x, 1);
	}
	
	CyDelay(500);
	
	for(x = 0; x < configNUM_OF_LEDS; x++)
	{
		Lights_SetLed(x, 0);
	}

	CyDelay(500);
}

//! @brief		Main code loop
void Lights_Run(void)
{
	// Counter for main led state machine
	static uint32 counter = 0;
	
	uint8 x;
	
	for(x = 0; x < configNUM_OF_LEDS; x++)
	{
		if(ledModeArray[x] == OFF)
			Lights_SetLed(x, 0);
		if(ledModeArray[x] == ON)
			Lights_SetLed(x, 1);
		if(ledModeArray[x] == FLASHING)
		{
			uint32 numberOfCounts = (uint32)(ledFlashRateMsArray[x]/(2*configMAIN_TICK_PERIOD_MS));
			if(counter > ledPrevFlashCountArray[x] + numberOfCounts)
			{
				Lights_ToggleLed(x);
				ledPrevFlashCountArray[x] = counter;
			}
		}
	}

	
	// Increment counter
	counter++;
}



void Lights_SetLedMode(led_t led, ledMode_t ledMode, double ledFlashRate)
{
	ledModeArray[led] = ledMode;
	ledFlashRateMsArray[led] = ledFlashRate;
}

//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================

void Lights_SetLed(uint8 ledNum, uint8 offOn)
{
	switch(ledNum)
	{
		case LED_IN_RANGE:
				PinLedInRange_Write(offOn);
			break;
		case LED_MOTOR_ON:
				PinLedMotorOn_Write(offOn);
			break;
		case LED_ALARM_ON:
				PinLedAlarm_Write(offOn);
			break;
		case LED_BOARD_BATT_LVL_TOP:
				PinLedBoardBattLevelHigh_Write(offOn);
			break;
		case LED_BOARD_BATT_LVL_MID:
				PinLedBoardBattLevelMed_Write(offOn);
			break;
		case LED_BOARD_BATT_LVL_BOT:
				PinLedBoardBattLevelLow_Write(offOn);
			break;
		case LED_REMOTE_BATT_LVL_TOP:
				PinLedRemoteBattLevelHigh_Write(offOn);
			break;
		case LED_REMOTE_BATT_LVL_MID:
				PinLedRemoteBattLevelMed_Write(offOn);
			break;
		case LED_REMOTE_BATT_LVL_BOT:
				PinLedRemoteBattLevelLow_Write(offOn);
			break;
	}
}

void Lights_ToggleLed(uint8 ledNum)
{
	switch(ledNum)
	{
		case LED_IN_RANGE:
				PinLedInRange_Write(!PinLedInRange_Read());
			break;
		case LED_MOTOR_ON:
				PinLedMotorOn_Write(!PinLedMotorOn_Read());
			break;
		case LED_ALARM_ON:
				PinLedAlarm_Write(!PinLedAlarm_Read());
			break;
		case LED_BOARD_BATT_LVL_TOP:
				PinLedBoardBattLevelHigh_Write(!PinLedBoardBattLevelHigh_Read());
			break;
		case LED_BOARD_BATT_LVL_MID:
				PinLedBoardBattLevelMed_Write(!PinLedBoardBattLevelMed_Read());
			break;
		case LED_BOARD_BATT_LVL_BOT:
				PinLedBoardBattLevelLow_Write(!PinLedBoardBattLevelLow_Read());
			break;
		case LED_REMOTE_BATT_LVL_TOP:
				PinLedRemoteBattLevelHigh_Write(!PinLedRemoteBattLevelHigh_Read());
			break;
		case LED_REMOTE_BATT_LVL_MID:
				PinLedRemoteBattLevelMed_Write(!PinLedRemoteBattLevelMed_Read());
			break;
		case LED_REMOTE_BATT_LVL_BOT:
				PinLedRemoteBattLevelLow_Write(!PinLedRemoteBattLevelLow_Read());
			break;
	}
}



//===============================================================================================//
//============================================ ISR's ============================================//
//===============================================================================================//

// none

//===============================================================================================//
//============================================= GRAVEYARD =======================================//
//===============================================================================================//


/* [] END OF FILE */