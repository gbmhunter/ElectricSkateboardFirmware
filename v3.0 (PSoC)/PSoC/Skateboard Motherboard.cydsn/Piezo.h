//!
//! @file 		Piezo.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Header file for Piezo.c
//! @details
//!		<b>Last Modified:			</b> 14/05/2011			\n
//!		<b>Version:					</b> v1.0				\n
//!		<b>Company:					</b> CladLabs			\n
//!		<b>Project:					</b> Electric Skateboard\n
//!		<b>Computer Architecture:	</b> ARM				\n
//!		<b>Compiler:				</b> GCC				\n
//! 	<b>uC Model:				</b> PSoC5				\n
//!		<b>Documentation Format:	</b> Doxygen			\n
//!

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _PIEZO_H
#define _PIEZO_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

// none

//===============================================================================================//
//===================================== PUBLIC TYPEDEF's ========================================//
//===============================================================================================//

typedef enum
{
	up,
	down
} motorOnSoundDirection_t;

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// See Led.c for function descriptions
void Piezo_Run(void);
void Piezo_AlarmEnable(bool_t enable);
void Piezo_EmitBeep(void);
void Piezo_EmitMotorOnSound(motorOnSoundDirection_t motorOnSoundDirection);
void Piezo_AlarmActivatedSound(void);

//===============================================================================================//
//======================================= PUBLIC VARIABLES ======================================//
//===============================================================================================//

// End of header guard
#endif

//[] END OF FILE