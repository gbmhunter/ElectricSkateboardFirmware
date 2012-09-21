//!
//! @file 		Lights.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Header file for Lights.c
//! @details
//!		<b>Last Modified:			</b> 24/05/2011										\n
//!		<b>Version:					</b> v1.0											\n
//!		<b>Company:					</b> CladLabs										\n
//!		<b>Project:					</b> Electric Skateboard - Skateboard Motherboard	\n
//!		<b>Computer Architecture:	</b> ARM											\n
//!		<b>Compiler:				</b> GCC											\n
//! 	<b>uC Model:				</b> PSoC5											\n
//!		<b>Documentation Format:	</b> Doxygen										\n
//!

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _LIGHTS_H
#define _LIGHTS_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

// none

//===============================================================================================//
//===================================== PUBLIC TYPEDEF's ========================================//
//===============================================================================================//

//! @note 	Order is important!
typedef enum
{
	LED_RED,
	LED_ORANGE,
	LED_GREEN,
	LIGHT_FRONT,
	LIGHT_BACK,
	LIGHT_SKIRTING
} led_t;

typedef enum
{
	OFF,
	ON,
	FLASHING
} ledMode_t;

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// See Lights.c for function descriptions
void Lights_Run(void);

void Lights_AllOn(void);
void Lights_AllOff(void);

void Lights_TurnOnHighPowerLights(void);
void Lights_TurnOffHighPowerLights(void);
void Lights_ChangeHighPowerLightMode(void);
bool_t Lights_IsHighPowerLightsOn(void);

void Lights_SetLedMode(led_t led, ledMode_t ledMode, double ledFlashRate);


//===============================================================================================//
//======================================= PUBLIC VARIABLES ======================================//
//===============================================================================================//

// End of header guard
#endif

//[] END OF FILE