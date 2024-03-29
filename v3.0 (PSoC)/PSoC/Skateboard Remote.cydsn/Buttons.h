//!
//! @file 		Buttons.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Header file for Lights.c
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

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _BUTTONS_H
#define _BUTTONS_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

// none

//===============================================================================================//
//===================================== PUBLIC TYPEDEF's ========================================//
//===============================================================================================//

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// See Buttons.c for function descriptions

void Buttons_Init(void);
void Buttons_Run(void);
bool_t Buttons_IsMotorButtonPressed(void);
bool_t Buttons_IsLightsOnOffButtonPressed(void);
bool_t Buttons_IsAlarmButtonPressed(void);
bool_t Buttons_IsLightModeButtonPressed(void);
void Buttons_ResetLightModeButtonState(void);

//===============================================================================================//
//======================================= PUBLIC VARIABLES ======================================//
//===============================================================================================//

// End of header guard
#endif

//[] END OF FILE