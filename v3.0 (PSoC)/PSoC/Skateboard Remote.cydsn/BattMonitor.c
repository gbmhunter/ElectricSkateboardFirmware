//!
//! @file 		BattMonitor.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Performs actions relating to the battery voltage.
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
//!		
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>
#include "Config.h"
#include "BattMonitor.h"
#include "Lights.h"


static double _remoteBattVoltMin;
static double _remoteBattVoltMax;
static double _remoteBattVoltThreshold1;
static double _remoteBattVoltThreshold2;
static double _remoteBattVoltBetweenThresholds;

static double _boardBattVoltMin;
static double _boardBattVoltMax;
static double _boardBattVoltThreshold1;
static double _boardBattVoltThreshold2;
static double _boardBattVoltBetweenThresholds;

double BattMonitor_CalculateFlashRate(double voltage, double voltageBetweenThresholds);

//! @brief 		Initializes battery monitor variables
//! @details	Call before calling any other battery monitor function.
void BattMonitor_Init()
{
	// Store values into globals
	_remoteBattVoltMin = configREMOTE_BATT_VOLT_LOW_LEVEL_MV;
	_remoteBattVoltThreshold1 = (configREMOTE_BATT_VOLT_HIGH_LEVEL_MV - configREMOTE_BATT_VOLT_LOW_LEVEL_MV)*(1.0/3.0) + configREMOTE_BATT_VOLT_LOW_LEVEL_MV;
	_remoteBattVoltThreshold2 = (configREMOTE_BATT_VOLT_HIGH_LEVEL_MV - configREMOTE_BATT_VOLT_LOW_LEVEL_MV)*(2.0/3.0) + configREMOTE_BATT_VOLT_LOW_LEVEL_MV;
	_remoteBattVoltMax = configREMOTE_BATT_VOLT_HIGH_LEVEL_MV;
	
	// Calculate voltage interval between thresholds
	_remoteBattVoltBetweenThresholds = (configREMOTE_BATT_VOLT_HIGH_LEVEL_MV - configREMOTE_BATT_VOLT_LOW_LEVEL_MV)/3;
	
	// Store values into globals
	_boardBattVoltMin = configBOARD_BATT_VOLT_LOW_LEVEL_MV;
	_boardBattVoltThreshold1 = (configBOARD_BATT_VOLT_HIGH_LEVEL_MV - configBOARD_BATT_VOLT_LOW_LEVEL_MV)*(1.0/3.0) + configBOARD_BATT_VOLT_LOW_LEVEL_MV;
	_boardBattVoltThreshold2 = (configBOARD_BATT_VOLT_HIGH_LEVEL_MV - configBOARD_BATT_VOLT_LOW_LEVEL_MV)*(2.0/3.0) + configBOARD_BATT_VOLT_LOW_LEVEL_MV;
	_boardBattVoltMax = configBOARD_BATT_VOLT_HIGH_LEVEL_MV;
	
	// Calculate voltage interval between thresholds
	_boardBattVoltBetweenThresholds = (configBOARD_BATT_VOLT_HIGH_LEVEL_MV - configBOARD_BATT_VOLT_LOW_LEVEL_MV)/3;
}

//! @brief		Call from main loop once per tick
void BattMonitor_Run(double remoteBattVoltage, double boardBattVoltage)
{
	static uint32 counter = 0;
	
	#if(configDEBUG_BATT_MONITOR == 1)
		char tempBuff[100];
		snprintf(tempBuff, sizeof(tempBuff), "BATT: Remote Batt Voltage = %f, Board Batt Voltage = %f\r\n", remoteBattVoltage, boardBattVoltage);
		UartDebug_PutString(tempBuff);
	#endif
	
	//=========================================== REMOTE BATT LEDS =================================//
	
	// Control the battery level leds
	if(remoteBattVoltage < _remoteBattVoltThreshold1)
	{
		// Voltage is in lower third or below min
		double flashRate = BattMonitor_CalculateFlashRate(remoteBattVoltage - _remoteBattVoltMin, _remoteBattVoltBetweenThresholds);
		// Only flash lower led, others off
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_BOT, FLASHING, flashRate);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_MID, OFF, 0);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_TOP, OFF, 0);
		
	}
	if(remoteBattVoltage >= _remoteBattVoltThreshold1 && remoteBattVoltage < _remoteBattVoltThreshold2)
	{
		// Voltage is in middle third
		double flashRate = BattMonitor_CalculateFlashRate(remoteBattVoltage - _remoteBattVoltThreshold1, _remoteBattVoltBetweenThresholds);
		// Turn bottom led on, and flash middle led
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_BOT, ON, 0);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_MID, FLASHING, flashRate);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_TOP, OFF, 0);

	}
	if(remoteBattVoltage >= _remoteBattVoltThreshold2)
	{
		// Voltage is in top third or above max
		double flashRate = BattMonitor_CalculateFlashRate(remoteBattVoltage - _remoteBattVoltThreshold2, _remoteBattVoltBetweenThresholds);
		// Turn bottom two led's on, and flash top led
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_BOT, ON, 0);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_MID, ON, 0);
		Lights_SetLedMode(LED_REMOTE_BATT_LVL_TOP, FLASHING, flashRate);
	}
	
	//=========================================== BOARD BATT LEDS =================================//
	// Control the boardbattery level leds
	if(boardBattVoltage < _boardBattVoltThreshold1)
	{
		// Voltage is in lower third or below min
		double flashRate = BattMonitor_CalculateFlashRate(boardBattVoltage - _boardBattVoltMin, _boardBattVoltBetweenThresholds);
		// Only flash lower led, others off
		Lights_SetLedMode(LED_BOARD_BATT_LVL_BOT, FLASHING, flashRate);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_MID, OFF, 0);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_TOP, OFF, 0);
		
	}
	if(boardBattVoltage >= _boardBattVoltThreshold1 && boardBattVoltage < _boardBattVoltThreshold2)
	{
		// Voltage is in middle third
		double flashRate = BattMonitor_CalculateFlashRate(boardBattVoltage - _boardBattVoltThreshold1, _boardBattVoltBetweenThresholds);
		// Turn bottom led on, and flash middle led
		Lights_SetLedMode(LED_BOARD_BATT_LVL_BOT, ON, 0);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_MID, FLASHING, flashRate);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_TOP, OFF, 0);

	}
	if(boardBattVoltage >= _boardBattVoltThreshold2)
	{
		// Voltage is in top third or above max
		double flashRate = BattMonitor_CalculateFlashRate(boardBattVoltage - _boardBattVoltThreshold2, _boardBattVoltBetweenThresholds);
		// Turn bottom two led's on, and flash top led
		Lights_SetLedMode(LED_BOARD_BATT_LVL_BOT, ON, 0);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_MID, ON, 0);
		Lights_SetLedMode(LED_BOARD_BATT_LVL_TOP, FLASHING, flashRate);
	}
	
	// Increment counter
	counter++;
		
}

//! @brief 		Calculates the flash rate of a led given a voltage
//! @details	The voltage has to range from 0 to the maximum between two voltage thresholds
double BattMonitor_CalculateFlashRate(double voltage, double voltageBetweenThresholds)
{
	// If voltage happens to be negative (as with the case if it was below voltMin, set to 0
	if(voltage < 0)
		voltage = 0;
	
	// Should always be between 0 and 1. Ratio goes down as battery voltage drops.
	double voltRatio = voltage/voltageBetweenThresholds;
	
	double flashInterval = (configBATT_MONITOR_HIGHEST_FLASH_PERIOD_MS - configBATT_MONITOR_LOWEST_FLASH_PERIOD_MS);
	
	// Want led to flash faster as battery voltage drops, so flashPeriod needs to decrease and ratio decreses
	double flashPeriod = flashInterval*voltRatio + configBATT_MONITOR_LOWEST_FLASH_PERIOD_MS;
	
	return flashPeriod;
}

/* [] END OF FILE */
