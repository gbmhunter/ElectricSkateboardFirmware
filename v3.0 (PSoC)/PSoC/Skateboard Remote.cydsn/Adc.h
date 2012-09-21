//!
//! @file 		Lights.h
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

#ifndef _ADC_H
#define _ADC_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

void Adc_Init(void);
void Adc_Run(void);
double Adc_GetBattVolt(void);
double Adc_GetThrottleVolt(void);
void Adc_EnableThrottleVoltMeas(bool_t enable);

#endif

//[] END OF FILE
