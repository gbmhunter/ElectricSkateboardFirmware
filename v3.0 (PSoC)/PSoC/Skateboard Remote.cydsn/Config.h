//!
//! @file 		Config.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Configuration file for project
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

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _CONFIG_H
#define _CONFIG_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

#define config_DEBUG_MAIN			(1)		//!< (bool_t) Set to 1 to enable main debug messages
#define config_DEBUG_COMMS			(0)		//!< (bool_t) Set to 1 to enable comms debug messages
#define config_DEBUG_ADC			(1)		//!< (bool_t) Set to 1 to enable adc debug messages
#define configDEBUG_BATT_MONITOR	(0)		//!< (bool_t) Set to 1 to enable batt monitor debug messages

#define config_DEBUG_COMMS_ERROR	(1)		//!< (bool_t) Set to 1 to enable comms error messages

//=========================================== SYSTEM CONFIG =====================================//

#define configMAIN_TICK_PERIOD_MS (10.0)	//!< (double) Time (in milli-seconds) between main state ticks. This controls the rate at which all control code is executed. 
#define configNUM_OF_LEDS (9)				//!< (uint8) Total number of leds on the remote pcb


//=========================================== ANALOG CONFIG =====================================//

#define configBATT_MEASURE_PERIOD_MS 				(5000.0) 	//!< (double) Time (in ms) between remote battery voltage measurements
#define configTHROTTLE_MEASURE_PERIOD_MS 			(50.0)		//!< (double) Time (in ms) between throttle battery voltage measurments. One of the parameters which determines the response of the throttle.

#define configBATT_VOLT_R1_KOHM 					(100.0)		//!< (double) Resistance in kOhm of the top resistor in the batt voltage divider going into ADC
#define configBATT_VOLT_R2_KOHM 					(19.1)		//!< (double) Resistance in kOhm of the bottom resistor in the batt voltage divider going into ADC
#define configBATT_VOLT_OFFSET_MV 					(-30.0)		//!< (double) Offset of final voltage from battery to account for any error (calibrated value)

#define configREMOTE_BATT_VOLT_LOW_LEVEL_MV			(6000.0)	//!< (double) Maximum level of remote battery 
#define configREMOTE_BATT_VOLT_HIGH_LEVEL_MV		(9500.0)	//!< (double) Minimum level of remote battery
#define configBOARD_BATT_VOLT_LOW_LEVEL_MV			(35000.0)	//!< (double) Maximum level of board battery 
#define configBOARD_BATT_VOLT_HIGH_LEVEL_MV			(58000.0)	//!< (double) Minimum level of board battery

#define configTHROTTLE_LOW_LEVEL_MV					(1250.0)	//!< (double) Voltage (in mV) from the throttle POT to map to 0% motor speed
#define configTHROTTLE_HIGH_LEVEL_MV				(2183.0)	//!< (double) Voltage (in mV) from the throttle POT to map to 100% motor speed

#define configAMUX_CH_BATT_VOLT 					(0)			//!< (uint8) AMUX channel that the battery voltage is connected to 
#define configAMUX_CH_THROTTLE_VOLT 				(1) 		//!< (uint8) AMUX channel that the throttle is connected to

#define configBATT_MONITOR_LOWEST_FLASH_PERIOD_MS 	(50.0)		//!< (double) Fastest flash rate (in ms) of the leds indicating battery condition
#define configBATT_MONITOR_HIGHEST_FLASH_PERIOD_MS 	(1000.0)	//!< (double) Slowest flash rate (in ms) of the leds indicating battery condition

//#define configERROR_FLASH_PERIOD_MS					(250)

//============================================ COMMS CONFIG =====================================//

//#define configCOMM_NUM_OF_PACKET_BUFFERS			(5)			//!< (integer)
#define configCOMM_RX_BUFFER_SIZE 					(50)		//!< (integer)
#define configCOMMS_TIMEOUT_PERIOD_MS 				(100.0)		//!< (double) Time in ms before comms timesout waiting for response from the board. Board should respond as soon as message is sent. Reponse time
														//!				seems to be around 40-50ms
#define configCOMMS_ALLOW_XBEE_SLEEP				(0)			//!< (bool_t) If set to 1, allows XBEE to sleep.
#define configCOMMS_SEND_PERIOD_MS					(100.0)		//!< (double) Send time in ms between each comms packet
#define configXBEE_START_UP_TIME_MS					(10.0)		//!< (double) Start time of the xbee module. Rounded to the nearest #configMAIN_TICK_PERIOD_MS (excluding 0)
#define configCOMMS_MSG_SIZE 						(8)			//!< (uint8_t)

#endif

//[] END OF FILE
