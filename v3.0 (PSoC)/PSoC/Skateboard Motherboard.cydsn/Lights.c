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

typedef enum
{
		alwaysOn,
		flashingSlow,
		flashingFast
} lightModeStates_t;
	
//=================================================================================================
//==================================== PRIVATE VARIABLES ==========================================
//=================================================================================================

bool_t _errorFlash = FALSE;
ledMode_t ledModeArray[configNUM_OF_LIGHTS];
double ledFlashRateMsArray[configNUM_OF_LIGHTS];
uint32 ledPrevFlashCountArray[configNUM_OF_LIGHTS] = {0};
lightModeStates_t lightModeState = alwaysOn;
bool_t _highPowerLightsOn = FALSE;

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

	for(x = 0; x < configNUM_OF_LIGHTS; x++)
	{
		Lights_SetLed(x, 0);
	}
}

void Lights_AllOn(void)
{
	uint8 x;

	for(x = 0; x < configNUM_OF_LIGHTS; x++)
	{
		Lights_SetLed(x, 1);
	}
}

void Lights_FlashAllLeds(void)
{
	uint8 x;
	
	for(x = 0; x < configNUM_OF_LIGHTS; x++)
	{
		Lights_SetLed(x, 1);
	}
	
	CyDelay(500);
	
	for(x = 0; x < configNUM_OF_LIGHTS; x++)
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
	
	for(x = 0; x < configNUM_OF_LIGHTS; x++)
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

void Lights_ChangeHighPowerLightMode(void)
{
	switch(lightModeState)
	{
		case alwaysOn:
			lightModeState = flashingSlow;
			break;
		case flashingSlow:
			lightModeState = flashingFast;
			break;
		case flashingFast:
			lightModeState = alwaysOn;
			break;
	}
}

//! @brief		Turns on the high power lights according to the light mode state
void Lights_TurnOnHighPowerLights(void)
{
	_highPowerLightsOn = TRUE;
	switch(lightModeState)
	{
		case alwaysOn:
			Lights_SetLedMode(LIGHT_FRONT, ON, 0);
			Lights_SetLedMode(LIGHT_BACK, ON, 0);
			break;
		case flashingSlow:
			Lights_SetLedMode(LIGHT_FRONT, FLASHING, 1000);
			Lights_SetLedMode(LIGHT_BACK, FLASHING, 1000);
			break;
		case flashingFast:
			Lights_SetLedMode(LIGHT_FRONT, FLASHING, 500);
			Lights_SetLedMode(LIGHT_BACK, FLASHING, 500);
			break;
	}
}

//! @brief		Turns off the high power lights
void Lights_TurnOffHighPowerLights(void)
{
	_highPowerLightsOn = FALSE;
	Lights_SetLedMode(LIGHT_FRONT, OFF, 0);
	Lights_SetLedMode(LIGHT_BACK, OFF, 0);
}

bool_t Lights_IsHighPowerLightsOn(void)
{
	return _highPowerLightsOn;
}

//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================

//===================================== DRIVER FUNCTIONS ========================================//

//! @brief		Controls the actual pin that drives the lights.
//! @note		Some inversion takes place for leds in which the current in sunk. The acutal
//!				'lights' are driven by N-Ch MOSFET's and hence the pin is driven high to turn them on
void Lights_SetLed(uint8 ledNum, uint8 offOn)
{
	switch(ledNum)
	{
		case LED_RED:
				PinLedRed_Write(!offOn);
			break;
		case LED_ORANGE:
				PinLedOrange_Write(!offOn);
			break;
		case LED_GREEN:
				PinLedGreen_Write(!offOn);
			break;
		case LIGHT_FRONT:
				PinLightFront_Write(offOn);
			break;
		case LIGHT_BACK:
				PinLightRear_Write(offOn);
			break;
		case LIGHT_SKIRTING:
				PinLightSkirting_Write(offOn);
			break;
	}
}

void Lights_ToggleLed(uint8 ledNum)
{
	switch(ledNum)
	{
		case LED_RED:
				PinLedRed_Write(!PinLedRed_Read());
			break;
		case LED_ORANGE:
				PinLedOrange_Write(!PinLedOrange_Read());
			break;
		case LED_GREEN:
				PinLedGreen_Write(!PinLedGreen_Read());
			break;
		case LIGHT_FRONT:
				PinLightFront_Write(!PinLightFront_Read());
			break;
		case LIGHT_BACK:
				PinLightRear_Write(!PinLightRear_Read());
			break;
		case LIGHT_SKIRTING:
				PinLightSkirting_Write(!PinLightSkirting_Read());
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