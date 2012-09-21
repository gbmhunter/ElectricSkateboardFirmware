//!
//! @file 		Motor.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Motor control functions
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
//!		Controls the motor speed and states
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>						// PSoC creator files
#include <stdio.h>						// Used for snprintf() function
#include <stdlib.h>						// Used for abs() function
#include "../common/PublicObjects.h"
#include "Comms.h"

#include "Config.h"
#include "Motor.h"

typedef enum
{
	motorInit,
	motorOff,
	motorOn
} motorStates_t;

//=================================================================================================
//==================================== PRIVATE VARIABLES ==========================================
//=================================================================================================

static bool_t _turnOnMotorFlag = FALSE;
static bool_t _turnOffMotorFlag = FALSE;

//static double _motorSetValue = 0.0;
//static double _motorCurrentValue = 0.0;
static double _motorSetSpeed = 0.0;

//=================================================================================================
//=============================== PRIVATE FUNCTION PROTOTYPES =====================================
//=================================================================================================

double Motor_Convert16BitSpeedToPercentage(uint16_t speed);
void Motor_ControlMotorSpeed(uint32_t currentStateCount);

//=================================================================================================
//===================================== PUBLIC FUNCTIONS ==========================================
//=================================================================================================

//! @brief		Updates the motor speed from the current value retrieved by the comms
void Motor_Run(void)
{
	static uint32_t stateCounter = 0;
	
	static uint16_t motorSetSpeed16Bit = 0;
	
	static motorStates_t motorState = motorInit;
	static motorStates_t prevMotorState = motorInit;
	
	switch(motorState)
	{
		case motorInit:
			#if(configDEBUG_MOTOR == 1)
				UartDebug_PutString("MOTOR: Entering motorInit state.\r\n");
			#endif
			PwmMotor_Start();
			// Init finished, go to motorOff state
			motorState = motorOff;
			break;
		case motorOff:
			if(prevMotorState != motorState)
			{
				#if(configDEBUG_MOTOR == 1)
					UartDebug_PutString("MOTOR: Entering motorOff state.\r\n");
				#endif
				prevMotorState = motorState;
			}
			
			if(_turnOnMotorFlag)
			{
				motorState = motorOn;
				_turnOnMotorFlag = FALSE;
			}
			break;
		case motorOn:
			if(prevMotorState != motorState)
			{
				#if(configDEBUG_MOTOR == 1)
					UartDebug_PutString("MOTOR: Entering motorOn state.\r\n");
				#endif
				// Start the PWM peripheral
				//PwmMotor_Start();
				prevMotorState = motorState;
			}
			
			// Get motor set speed from comms
			motorSetSpeed16Bit = ((Comms_GetByte(commsMOTOR_HIGH_BYTE_POS)<<8) | (Comms_GetByte(commsMOTOR_LOW_BYTE_POS)));
			
			_motorSetSpeed = Motor_Convert16BitSpeedToPercentage(motorSetSpeed16Bit);
			
			// Controlling of motor is done after switch statement
			//Motor_ControlMotorSpeed(stateCounter);
			
			if(_turnOffMotorFlag)
			{
				// Turn of command to motor
				_motorSetSpeed = 0.0;
				//Motor_SetSpeed(0);
				// Stop the PWM peripheral
				//PwmMotor_Stop();
				motorState = motorOff;
				_turnOffMotorFlag = FALSE;
				break;
			}
			break;
	}
	
	// No matter what, call ControlMotorSpeed
	Motor_ControlMotorSpeed(stateCounter);
	
	stateCounter++;
}


//! @brief		Sets the motor speed.
//! @note		Accepts value from 0 to 65535
double Motor_Convert16BitSpeedToPercentage(uint16_t speed)
{
	// Using 32-bit values so overflows do not occur
	double difference = configMOTOR_MAX_THROTTLE - configMOTOR_MIN_THROTTLE;
	double adjustedSpeed = ((double)speed/65535.0)*difference + configMOTOR_MIN_THROTTLE;
	
	return adjustedSpeed;

}

//! @brief		Controls the actual motor speed based on the set speed sent from the remote
//! @note		Call as fast as possible for the best control (e.g. every state cycle (10ms))
void Motor_ControlMotorSpeed(uint32_t currentStateCount)
{
	static double lastMotorSpeed = 0;
	static double lastMotorAccel = 0;			//!< Units speed percent per second^2
	static double lastStateCount = 0;
	
	// Calculate the change in time since the last call
	double changeInTime = (currentStateCount - lastStateCount)*configMAIN_TICK_PERIOD_MS/1000.0;
	
	double changeInSpeed = _motorSetSpeed - lastMotorSpeed;
	
	//============================== ACCELERATION LIMITING =========================================//
	
	// Calculate the requested acceleration
	double acceleration = (_motorSetSpeed - lastMotorSpeed)/changeInTime;
	
	//Limit the maximum acceleration of the motor
	double motorSpeedAccelLimited = 0.0;
	if(acceleration > configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2)
	{
		motorSpeedAccelLimited = lastMotorSpeed + configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2*changeInTime;
		#if(configDEBUG_MOTOR == 1)
			UartDebug_PutString("MOTOR: Requested speed is acceleration limited (positive).\r\n");
		#endif
	}
	else if(acceleration < -configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2)
	{
		motorSpeedAccelLimited = lastMotorSpeed - configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2*changeInTime;
		#if(configDEBUG_MOTOR == 1)
			UartDebug_PutString("MOTOR: Requested speed is acceleration limited (negative).\r\n");
		#endif
	}
	else
	// No limmiting neccessary for acceleration
		motorSpeedAccelLimited = _motorSetSpeed;
		
	//========================================= JERK LIMITING ======================================//	
	
	// Calculate the requested jerk
	double jerk = (acceleration - lastMotorAccel)/changeInTime;
	
	//Limit the maximum acceleration of the motor
	double motorSpeedJerkLimited = 0.0;
	if(jerk > configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3)
	{
		motorSpeedJerkLimited = lastMotorSpeed + configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3*changeInTime*changeInTime;
		#if(configDEBUG_MOTOR == 1)
			UartDebug_PutString("MOTOR: Requested speed is jerk limited (positive).\r\n");
		#endif
	}
	else if(jerk < -configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3)
	{
		motorSpeedJerkLimited = lastMotorSpeed - configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3*changeInTime*changeInTime;
		#if(configDEBUG_MOTOR == 1)
			UartDebug_PutString("MOTOR: Requested speed is jerk limited (negative).\r\n");
		#endif
	}
	else
	// No limmiting neccessary for jerk
		motorSpeedJerkLimited = _motorSetSpeed;
		
	if(changeInSpeed != 0)
	{
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Change in time = %fs\r\n", 
					changeInTime);
			UartDebug_PutString(debugBuff);
		#endif
		
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Set speed = %fp/s\r\n", 
					_motorSetSpeed);
			UartDebug_PutString(debugBuff);
		#endif
		
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Last speed = %fp/s\r\n", 
					lastMotorSpeed);
			UartDebug_PutString(debugBuff);
		#endif
		
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Change in set speed to actual = %fp/s\r\n", 
					changeInSpeed);
			UartDebug_PutString(debugBuff);
		#endif
		
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Motor acceleration = %fp/s^2\r\n", 
				acceleration);
			UartDebug_PutString(debugBuff);
		#endif
		
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Motor jerk = %fp/s^3\r\n", 
					jerk);
			UartDebug_PutString(debugBuff);
		#endif
	}
	
	//========================================= OUTPUT ======================================//	
	double newMotorSpeed = 0;
	
	// Find the smallest change in speed from the two options (accel or jerk limited)
	if((abs(motorSpeedAccelLimited) - abs(lastMotorSpeed)) < (abs(motorSpeedJerkLimited) - abs(lastMotorSpeed)))
	{
		newMotorSpeed = motorSpeedAccelLimited;
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			UartDebug_PutString("MOTOR: Motor is limited by acceleration.\r\n");
		#endif
	}
	else if((abs(motorSpeedJerkLimited) - abs(lastMotorSpeed)) > (abs(motorSpeedJerkLimited) - abs(lastMotorSpeed)))
	{
		newMotorSpeed = motorSpeedJerkLimited;
		#if(configDEBUG_MOTOR_VERBOSE == 1)
			UartDebug_PutString("MOTOR: Motor is limited by jerk.\r\n");
		#endif
	}
	else
	{
		// Doesn't matter which is assigned, both are the same
		newMotorSpeed = motorSpeedAccelLimited;
	}
	
	double numOfCounts = (newMotorSpeed/100.0)*configMOTOR_PWM_PERIOD_COUNTS;
	// Sets the PWM
	PwmMotor_WriteCompare((uint16_t)numOfCounts);
	
	#if(configDEBUG_MOTOR == 1)
		static uint32_t debugCounter = 0;
		if(debugCounter >= 50)
		{
			snprintf(debugBuff, sizeof(debugBuff), "MOTOR: Motor set speed = %fp/s, Motor speed = %fp/s, Motor accel = %fp/s^2, Motor jerk = %fp/s^3, Change in time = %fs\r\n", 
				_motorSetSpeed, newMotorSpeed, acceleration, jerk,  changeInTime);
			UartDebug_PutString(debugBuff);
				if(abs(acceleration) > configMOTOR_MAX_ACCEL_PERCENT_SPEED_PER_SEC2)
					UartDebug_PutString("MOTOR: Motor speed is acceleration limited.\r\n");
				if(abs(jerk) > configMOTOR_MAX_JERK_PERCENT_SPEED_PER_SEC3)
					UartDebug_PutString("MOTOR: Motor speed is jerk limited.\r\n");
			debugCounter = 0;
		}
		debugCounter++;
	#endif
	
	// Remember current values for next time
	lastMotorSpeed = newMotorSpeed;
	lastMotorAccel = acceleration;
	lastStateCount = currentStateCount;
}

//! @brief 		Enables motor
void Motor_TurnOn(void)
{
	_turnOnMotorFlag = TRUE;
}

//! @brief 	Disables motor
void Motor_TurnOff(void)
{
	_turnOffMotorFlag = TRUE;
}

//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================

/* [] END OF FILE */
