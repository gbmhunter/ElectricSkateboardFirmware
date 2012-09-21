//!
//! @file 		Motor.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Header file for Motor.c
//! @details
//!		<b>Last Modified:			</b> 29/05/2011										\n
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

#ifndef _MOTOR_H
#define _MOTOR_H

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

void Motor_Run(void);
void Motor_TurnOn(void);
void Motor_TurnOff(void);

#endif
//[] END OF FILE
