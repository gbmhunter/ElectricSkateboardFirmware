//!
//! @file 		Config.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Contains configuration settings
//! @details
//!		<b>Last Modified:			</b> 24/05/2011			\n
//!		<b>Version:					</b> v1.0				\n
//!		<b>Company:					</b> CladLabs			\n
//!		<b>Project:					</b> Electric Skateboard - Board\n
//!		<b>Computer Architecture:	</b> ARM				\n
//!		<b>Compiler:				</b> GCC				\n
//! 	<b>uC Model:				</b> PSoC5				\n
//!		<b>Documentation Format:	</b> Doxygen			\n
//!

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _CONFIG_H
#define _CONFIG_H

//===============================================================================================//
//======================================= PUBLIC DEFINES ========================================//
//===============================================================================================//

//===================================== DEBUG SWITCHES ==========================================//

#define configDEBUG_ENABLE_BUFFER	(1)

#define configDEBUG_MAIN			(1)
#define configDEBUG_PIEZO			(0)
#define configDEBUG_ADC				(0)
#define configDEBUG_MOTOR			(0)
#define configDEBUG_COMMS			(0)
#define configDEBUG_MOTOR_VERBOSE	(0)

#define configDEBUG_COMMS_ERRORS	(1)

#if(configDEBUG_ENABLE_BUFFER == 1)
	char debugBuff[200];
#endif

//======================================= SYSTEM CONFIG =========================================//

#define configMAIN_TICK_PERIOD_MS	(10)				//!< (double) Time (in milli-seconds) between main state ticks. This controls the rate at which all control code is executed. 

//======================================== PIEZO CONFIG =========================================//

#define configPWM_PIEZO_CLOCK_FREQ_MHZ 					(24.0) 		//!< (double) Frequency in MHz of the clock the PWM module is running from.

#define configALARM_TRIGGER_TIME_MSEC
#define configALARM_SIREN_ON_TIME_SEC

#define configALARM_TONE_1_HZ							(3500.0)	//!< (double) Frequency in hertz of the first tone in the alarm sound.
#define configALARM_TONE_2_HZ							(4000.0)	//!< (double) Frequency in hertz of the second tone in the alarm sound.
#define configALARM_TONE_PERIOD_MS 						(500)		//!< (uint16) Period in ms of the alarm sound.

#define configON_TONE_1_HZ								(2000.0)
#define configON_TONE_2_HZ								(2300.0)
#define configON_TONE_3_HZ								(2600.0)

#define configBEEP_TONE_1_HZ 							(3500.0)	//!< (double) Frequency in Hertz  of the first tone in the beep sound.
#define configBEEP_TONE_2_HZ 							(4000.0)	//!< (double) Frequency in Hertz  of the second tone in the beep sound.

#define configALARM_NUMBER_OF_WARNING_BEEPS				(2)			//!< (uint8_t)
#define configALARM_TIME_TO_REMAIN_TRIGGERED_SEC		(10.0)		//!< (double)

#define configALARM_TONE_1_PERIOD_MS					(250.0)		//!< (double) Time in milliseconds of the fiirst tone in the alarm sound.
#define configALARM_TONE_2_PERIOD_MS					(250.0)		//!< (double) Time in milliseconds of the second tone in the alarm sound.

#define configALARM_ACTIVATED_SOUND_1_PERIOD_MS			(400.0)		//!< (double) Time (in ms) of the first tone in the alarm
#define configALARM_ACTIVATED_SOUND_2_PERIOD_MS			(200.0)		//!< (double) Time (in ms) of the silence between the first and second tones
#define configALARM_ACTIVATED_SOUND_3_PERIOD_MS			(400.0)		//!< (double) Time (in ms) of the second tone in the alarm

#define configBEEP_PERIOD_MS							(100.0)		//!< (double) Time (in ms) of the beep
#define configMOTOR_ON_TONE_PERIOD_MS 					(50.0)
#define configMOTOR_ON_NUM_TONES 						(10)
#define configPIEZO_MOTOR_ON_START_FREQ_HZ				(3000.0)
#define configPIEZO_MOTOR_ON_JUMP_COUNTS				(200.0)

//======================================= LIGHTS CONFIG =========================================//

#define configNUM_OF_LIGHTS								(6)


//========================================== ADC CONFIG =========================================//

#define configBATT_MEASURE_PERIOD_MS					(500.0)
#define configBATT_VOLT_R1_KOHM							(750.0)
#define configBATT_VOLT_R2_KOHM							(12.0)
#define configBATT_VOLT_OFFSET_MV						(-500.0)

//============================================ COMMS CONFIG =====================================//

#define configCOMM_BUFFER_SIZE							(100)		//!< (integer)
#define configCOMMS_TIMEOUT_PERIOD_MS 					(350.0)		//!< (double) Time in ms before comms has time out if no packet has arrived. Make sure this is greater than configCOMMS_SEND_PERIOD_MS on the remote. 
#define configCOMMS_TX_MSG_LENGTH						(10)		//!< (uint8_t) Length in bytes of message sent of comms
#define configCOMMS_RX_MSG_LENGTH						(8)			//!< (uint8_t) Length in bytes of message sent of comms

//========================================== MOTOR CONFIG =======================================//

#define configMOTOR_MAX_THROTTLE						(100.0)		//!< (double) Maximum duty cycle (%) of motor pwm
#define configMOTOR_MIN_THROTTLE						(0.0)		//!< (double Minimum duty cycle (%) of motor pwm

#define configMOTOR_PWM_PERIOD_COUNTS					(1091.0)	//!< (double) The number of counts per PWM period
							
#define configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2	(70.0)		//!< 60 (double) The maximum acceleration (in percentage/second^2) of the motor
#define configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3		(6000.0)	//!< 8000 (double) The maximum jerk (in percentage speed/second^3) of the motor

// End of header guard
#endif

//[] END OF FILE
