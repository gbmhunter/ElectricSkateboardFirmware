//!
//! @file 		Adc.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Driver file for the ADC.
//! @details
//!		<b>Last Modified:			</b> 21/05/2011								\n
//!		<b>Version:					</b> v1.0									\n
//!		<b>Company:					</b> CladLabs								\n
//!		<b>Project:					</b> Electric Skateboard - Skateboard Remote\n
//!		<b>Computer Architecture:	</b> ARM									\n
//!		<b>Compiler:				</b> GCC									\n
//! 	<b>uC Model:				</b> PSoC5									\n
//!		<b>Documentation Format:	</b> Doxygen								\n
//!		
//!		Initializes and receives values from the ADC, as well as controlling the adc input mux
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>
#include <stdio.h>

#include "../common/PublicObjects.h"
#include "Config.h"
#include "Adc.h"

typedef enum
{
	adcInit,
	adcIdle,
	adcGetBattVolt
} adcStates_t;

static double _battVoltage = 0;
static double _throttleVoltage = 0;
static bool_t _enableThrottleVoltMeasFlag = FALSE;


void Adc_Run(void)
{
	static uint32_t stateCounter = 0;
	
	static uint32_t lastBattVoltMeasureCount = 0;
	static uint32_t battVoltMeasurePeriod = (uint32_t)configBATT_MEASURE_PERIOD_MS/configMAIN_TICK_PERIOD_MS;
	
	static bool_t turnOn = TRUE;
	
	static adcStates_t adcState = adcInit;
	static adcStates_t prevAdcState = adcInit;

	switch(adcState)
	{
		case adcInit:
			// Power up the ADC and reset all states
			AdcSar_Start();
			adcState = adcIdle;
			break;
			
		case adcIdle:
			if(prevAdcState != adcState)
			{
				#if(configDEBUG_ADC == 1) 
						UartDebug_PutString("ADC: Entering idle state.\r\n");
				#endif
				prevAdcState = adcState;
			}
				
			if(stateCounter >= lastBattVoltMeasureCount + battVoltMeasurePeriod)
				adcState = adcGetBattVolt;
			
			
			if(turnOn)
			{
				adcState = adcGetBattVolt;
				turnOn = FALSE;
				break;
			}
			break;
			
		case adcGetBattVolt:
			if(prevAdcState != adcState)
			{
				#if(configDEBUG_ADC == 1) 
						UartDebug_PutString("ADC: Entering adcGetBattVolt state.\r\n");
				#endif
				
				// Start ADC conversion
				AdcSar_StartConvert();
				
				lastBattVoltMeasureCount = stateCounter;
				prevAdcState = adcState;
			}

			// Wait for end of conversion
			// Accepts either ADC_WAIT_FOR_RESULT or ADC_RETURN_STATUS
			if(AdcSar_IsEndConversion(AdcSar_RETURN_STATUS))
			{
					// Get and return adc value
				uint16 adcVal = AdcSar_GetResult16();
				
				// Wait for end of conversion
				// Accepts either ADC_WAIT_FOR_RESULT or ADC_RETURN_STATUS
				AdcSar_IsEndConversion(AdcSar_WAIT_FOR_RESULT);
				
				// Get and return adc value
				adcVal = AdcSar_GetResult16();
				
				adcVal = AdcSar_CountsTo_mVolts(adcVal);
				
				double tempVar;
				
				// Convert 16-bit int to double
				tempVar = (double)adcVal;
				
				#if(configDEBUG_ADC == 1)
					char tempBuff1[50];
					snprintf(tempBuff1, sizeof(tempBuff1), "ADC: Adc voltage = %f\r\n", tempVar);
					UartDebug_PutString(tempBuff1);
				#endif
				
				// Scale by resistor divider to find input voltage
				tempVar = ((configBATT_VOLT_R1_KOHM + configBATT_VOLT_R2_KOHM)/configBATT_VOLT_R2_KOHM)*tempVar + configBATT_VOLT_OFFSET_MV;
				//tempVar = tempVar*configBATT_VOLT_R_RATIO;
				// Return battery voltage
				_battVoltage = tempVar;
				
				#if(configDEBUG_ADC == 1)
					char tempBuff2[50];
					snprintf(tempBuff2, sizeof(tempBuff2), "ADC: Batt voltage = %f\r\n", _battVoltage);
					UartDebug_PutString(tempBuff2);
				#endif
				
				// Go back to idle state
				adcState = adcIdle;
				
				break;
			}
			
		
			break;
			
	}
	
	// Increment state counter
	stateCounter++;
}

//! @brief		Enables or disables the throttle voltage measurement. Only needed in the mainMotorOn state
void Adc_EnableThrottleVoltMeas(bool_t enable)
{
		_enableThrottleVoltMeasFlag = enable;
}

//! @brief		Returns the battery voltage
//! @returns 	Battery voltage as double, scaled appropriately due to voltage divider
double Adc_GetBattVolt(void)
{
	return _battVoltage;
}

//! @brief		Returns the throttle voltage
//! @returns 	Throttle voltage as double, scaled appropriately due to voltage divider
double Adc_GetThrottleVolt(void)
{
	return _throttleVoltage;
}	

/* [] END OF FILE */
