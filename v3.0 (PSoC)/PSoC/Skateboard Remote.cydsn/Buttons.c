//!
//! @file 		Buttons.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Handles the cap sense buttons.
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
//!		Controls the buttons on the board.
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>

#include "../common/PublicObjects.h"

#include "Buttons.h"
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

typedef enum
{
	ST_OFF,
	ST_HALF_ON,
	ST_ON,
	ST_HALF_OFF
} buttonsState_t;

// Button state variables
buttonsState_t motorState = ST_OFF;
buttonsState_t lightsOnOffState = ST_OFF;
buttonsState_t alarmState = ST_OFF;
buttonsState_t lightModeState = ST_OFF;
//=================================================================================================
//=============================== PRIVATE FUNCTION PROTOTYPES =====================================
//=================================================================================================

void Buttons_MotorStateMachine(uint8 motorButtonActive);
void Buttons_LightsOnOffStateMachine(uint8 lightsOnOffButtonActive);
void Buttons_AlarmStateMachine(uint8_t alarmButtonActive);
void Buttons_LightModeStateMachine(uint8_t lightModeButtonActive);

//=================================================================================================
//===================================== PUBLIC FUNCTIONS ==========================================
//=================================================================================================

//! @brief		Initialises cap sense required for buttons
//! @note		Call before calling any other Buttons.c function
void Buttons_Init(void)
{
	CapSense_Start();
	CapSense_InitializeAllBaselines();
	
}

//! @brief		Buttons state machine
//! @note		Call once every tick
void Buttons_Run(void)
{
	CapSense_ScanEnabledWidgets();
	while(CapSense_IsBusy());
	
	uint8 motorButtonActive = 0;
	uint8 lightsButtonActive = 0;
	uint8 alarmButtonActive = 0;
	uint8_t lightModeButtonActive = 0;
	
	// Check buttons states
	
	//============================= MOTOR ON/OFF =======================//
	
	motorButtonActive = CapSense_CheckIsWidgetActive(CapSense_BUTTONMOTORONOFF__BTN);
	
	if(motorButtonActive)
		Buttons_MotorStateMachine(1);
	else
		Buttons_MotorStateMachine(0);
		
	//============================= LIGHTS ON/OFF =======================//
	
	lightsButtonActive = CapSense_CheckIsWidgetActive(CapSense_BUTTONLIGHTSONOFF__BTN);
	
	if(lightsButtonActive)
		Buttons_LightsOnOffStateMachine(1);
	else
		Buttons_LightsOnOffStateMachine(0);
		
	//============================= ALARM ON/OFF =======================//
	
	alarmButtonActive = CapSense_CheckIsWidgetActive(CapSense_BUTTONALARMONOFF__BTN);
	
	if(alarmButtonActive)
	{
		Buttons_AlarmStateMachine(1);
	}
	else
		Buttons_AlarmStateMachine(0);
		
	//============================= LIGHT MODE ON/OFF =======================//
	
	lightModeButtonActive = CapSense_CheckIsWidgetActive(CapSense_BUTTONLIGHTMODE__BTN);
	
	if(lightModeButtonActive)
	{
		Buttons_LightModeStateMachine(1);
	}
	else
		Buttons_LightModeStateMachine(0);
	
	// Update the baselines
	CapSense_UpdateEnabledBaselines();
	
	
	
}


bool_t Buttons_IsMotorButtonPressed(void)
{
	if(motorState == ST_ON || motorState == ST_HALF_OFF)
		return TRUE;
	else
		return FALSE;
	
}

bool_t Buttons_IsLightsOnOffButtonPressed(void)
{
	if(lightsOnOffState == ST_ON || lightsOnOffState == ST_HALF_OFF)
		return TRUE;
	else
		return FALSE;
	
}

bool_t Buttons_IsAlarmButtonPressed(void)
{
	if(alarmState == ST_ON || alarmState == ST_HALF_OFF)
		return TRUE;
	else
		return FALSE;
}

bool_t Buttons_IsLightModeButtonPressed(void)
{
	if(lightModeState == ST_ON || lightModeState == ST_HALF_OFF)
		return TRUE;
	else
		return FALSE;
}

//! @brief		Reset the state of the light mode button
void Buttons_ResetLightModeButtonState(void)
{
	lightModeState = ST_OFF;
}

//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================



void Buttons_MotorStateMachine(uint8 motorButtonActive)
{

	if(motorButtonActive && (motorState == ST_OFF))
	{
		motorState = ST_HALF_ON;
	}
	else if(!motorButtonActive && (motorState == ST_HALF_ON))
	{
		motorState = ST_ON;
	}
	else if(motorButtonActive && (motorState == ST_ON))
	{
		motorState = ST_HALF_OFF;
	}
	else if(!motorButtonActive && (motorState == ST_HALF_OFF))
	{
		motorState = ST_OFF;
	}
}

void Buttons_LightsOnOffStateMachine(uint8 lightsOnOffButtonActive)
{

	if(lightsOnOffButtonActive && (lightsOnOffState == ST_OFF))
	{
		lightsOnOffState = ST_HALF_ON;
	}
	else if(!lightsOnOffButtonActive && (lightsOnOffState == ST_HALF_ON))
	{
		lightsOnOffState = ST_ON;
	}
	else if(lightsOnOffButtonActive && (lightsOnOffState == ST_ON))
	{
		lightsOnOffState = ST_HALF_OFF;
	}
	else if(!lightsOnOffButtonActive && (lightsOnOffState == ST_HALF_OFF))
	{
		lightsOnOffState = ST_OFF;
	}
}

void Buttons_AlarmStateMachine(uint8 alarmButtonActive)
{

	if(alarmButtonActive && (alarmState == ST_OFF))
	{
		alarmState = ST_HALF_ON;
	}
	else if(!alarmButtonActive && (alarmState == ST_HALF_ON))
	{
		alarmState = ST_ON;
	}
	else if(alarmButtonActive && (alarmState == ST_ON))
	{
		alarmState = ST_HALF_OFF;
	}
	else if(!alarmButtonActive && (alarmState == ST_HALF_OFF))
	{
		alarmState = ST_OFF;
	}
}

//! @brief		State machine for the light mode button
void Buttons_LightModeStateMachine(uint8_t lightModeButtonActive)
{

	if(lightModeButtonActive && (lightModeState == ST_OFF))
	{
		lightModeState = ST_HALF_ON;
	}
	else if(!lightModeButtonActive && (lightModeState == ST_HALF_ON))
	{
		lightModeState = ST_ON;
	}
	else if(lightModeButtonActive && (lightModeState == ST_ON))
	{
		lightModeState = ST_HALF_OFF;
	}
	else if(!lightModeButtonActive && (lightModeState == ST_HALF_OFF))
	{
		lightModeState = ST_OFF;
	}
}


//===================================== DRIVER FUNCTIONS ========================================//


//===============================================================================================//
//============================================ ISR's ============================================//
//===============================================================================================//

// none

//===============================================================================================//
//============================================= GRAVEYARD =======================================//
//===============================================================================================//


/* [] END OF FILE */