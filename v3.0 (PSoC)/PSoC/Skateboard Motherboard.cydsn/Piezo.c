//!
//! @file 		Piezo.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		14/05/2011
//! @brief 		Controls the piezo functions on the skateboard.
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
//!		Controls the led's on the board
//!

//=================================================================================================
//============================================ INFO ===============================================
//=================================================================================================

//=================================================================================================
//======================================= FILE INCLUSIONS =========================================
//=================================================================================================

#include <device.h>
#include "../common/PublicObjects.h"
#include "Piezo.h"
#include "Config.h"

//===============================================================================================//
//=================================== PRECOMPILER CHECKS ========================================//
//===============================================================================================//

//=================================================================================================
//========================================== DEFINES ==============================================
//=================================================================================================

//=================================================================================================
//========================================== TYPEDEF's ============================================
//=================================================================================================

typedef enum
{
	piezoInit,
	piezoOff,
	piezoAlarmSound1,
	piezoAlarmSound2,
	piezoBeeping,
	piezoMotorOnSound,
	alarmActivatedSound1,
	alarmActivatedSound2,
	alarmActivatedSound3
} piezoStates_t;

//=================================================================================================
//==================================== PRIVATE VARIABLES ==========================================
//=================================================================================================


static motorOnSoundDirection_t _motorOnSoundDirection = up;

bool_t _emitMotorSoundFlag = FALSE;
bool_t _alarmEnableFlag = FALSE;
bool_t _alarmActivatedSoundFlag = FALSE;
uint8_t _piezoBeepCount = 0;

//=================================================================================================
//=============================== PRIVATE FUNCTION PROTOTYPES =====================================
//=================================================================================================

//=================================================================================================
//===================================== PUBLIC FUNCTIONS ==========================================
//=================================================================================================

void Piezo_Run(void)
{
	static uint32_t counter = 0;
	
	static uint32_t piezoLastChangeCount = 0;

	// Calculate run times in counts
	static uint32_t piezoAlarmSound1RunTimeCounts = (uint32_t)(configALARM_TONE_1_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t piezoAlarmSound2RunTimeCounts = (uint32_t)(configALARM_TONE_2_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t	beepRunTimeCounts = (uint32_t)(configBEEP_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t	motorOnToneTimeCounts = (uint32_t)(configMOTOR_ON_TONE_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t piezoActivatedSound1RunTimeCounts = (uint32_t)(configALARM_ACTIVATED_SOUND_1_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t piezoActivatedSound2RunTimeCounts = (uint32_t)(configALARM_ACTIVATED_SOUND_2_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	static uint32_t piezoActivatedSound3RunTimeCounts = (uint32_t)(configALARM_ACTIVATED_SOUND_3_PERIOD_MS/configMAIN_TICK_PERIOD_MS);
	
	static uint16_t currentToneCounts = 0;
	static uint16_t toneCount = 0;

	static piezoStates_t prevPiezoState = piezoInit;
	static piezoStates_t piezoState = piezoInit;
	
	switch(piezoState)
	{
		case piezoInit:
			piezoState = piezoOff;
			break;
		case piezoOff:
			if(prevPiezoState != piezoOff)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering piezoOff state.\r\n");
				#endif
				PwmPiezo_Stop();
				prevPiezoState = piezoOff;
			}
			
			if(_emitMotorSoundFlag)
			{
				piezoState = piezoMotorOnSound;
				_emitMotorSoundFlag = FALSE;
				break;
			}
			
			if(_alarmEnableFlag)
			{
				piezoState = piezoAlarmSound1;
				break;
			}
			
			if(_piezoBeepCount != 0)
			{
				piezoState = piezoBeeping;
				_piezoBeepCount--;
				break;
			}
			
			if(_alarmActivatedSoundFlag)
			{
				piezoState = alarmActivatedSound1;
				_alarmActivatedSoundFlag = FALSE;
				break;
			}
		
			break;
			
		case piezoAlarmSound1:
			if(prevPiezoState != piezoAlarmSound1)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering piezoAlarmSound1 state.\r\n");
				#endif
				PwmPiezo_Start();
				PwmPiezo_WritePeriod(6000);
				PwmPiezo_WriteCompare(3000);
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = piezoAlarmSound1;
			}
			
			if(_alarmEnableFlag == FALSE)
			{
				piezoState = piezoOff;
				break;
			}
			
			if(counter >= piezoLastChangeCount + piezoAlarmSound1RunTimeCounts)
			{
				piezoState = piezoAlarmSound2;
				break;
			}
			break;
			
		case piezoAlarmSound2:
			if(prevPiezoState != piezoAlarmSound2)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering piezoAlarmSound2 state.\r\n");
				#endif
				PwmPiezo_WritePeriod(6500);
				PwmPiezo_WriteCompare(3250);
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = piezoAlarmSound2;
			}
			
			if(_alarmEnableFlag == FALSE)
			{
				piezoState = piezoOff;
				break;
			}
			
			if(counter >= piezoLastChangeCount + piezoAlarmSound2RunTimeCounts)
			{
				piezoState = piezoAlarmSound1;
				break;
			}
			
			break;
		case piezoBeeping:
		
			if(prevPiezoState != piezoBeeping)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering piezoBeeping state.\r\n");
				#endif
				PwmPiezo_WritePeriod(6000);
				PwmPiezo_WriteCompare(3000);
				PwmPiezo_Start();
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = piezoBeeping;
			}
			
			if(counter >= piezoLastChangeCount + beepRunTimeCounts)
			{
				piezoState = piezoOff;
				break;
			}
			
			break;
			
		case piezoMotorOnSound:
		
			if(prevPiezoState != piezoMotorOnSound)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering piezoMotorOnSound state.\r\n");
				#endif
				currentToneCounts = (configPWM_PIEZO_CLOCK_FREQ_MHZ*1000000.0)/configPIEZO_MOTOR_ON_START_FREQ_HZ;
				PwmPiezo_WritePeriod(currentToneCounts);
				PwmPiezo_WriteCompare(currentToneCounts/2);
				PwmPiezo_Start();
				toneCount = 0;
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = piezoMotorOnSound;
			}
			
			if(counter >= piezoLastChangeCount + motorOnToneTimeCounts)
			{
				toneCount++;
				if(toneCount >= configMOTOR_ON_NUM_TONES)
				{
					piezoState = piezoOff;
					break;
				}
				if(_motorOnSoundDirection == up)
					currentToneCounts = currentToneCounts - configPIEZO_MOTOR_ON_JUMP_COUNTS;
				else
					// Must be down
					currentToneCounts = currentToneCounts + configPIEZO_MOTOR_ON_JUMP_COUNTS;
					
				PwmPiezo_WritePeriod(currentToneCounts);
				PwmPiezo_WriteCompare(currentToneCounts/2);
				piezoLastChangeCount = counter;
			}
			
			break;
		case alarmActivatedSound1:
			if(prevPiezoState != alarmActivatedSound1)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering alarmActivatedSound1 state.\r\n");
				#endif
				PwmPiezo_Start();
				PwmPiezo_WritePeriod(6000);
				PwmPiezo_WriteCompare(3000);
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = alarmActivatedSound1;
			}
			
			if(counter >= piezoLastChangeCount + piezoActivatedSound1RunTimeCounts)
			{
				piezoState = alarmActivatedSound2;
				break;
			}
			break;
			
		case alarmActivatedSound2:
			if(prevPiezoState != alarmActivatedSound2)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering alarmActivatedSound2 state.\r\n");
				#endif
				PwmPiezo_WritePeriod(6500);
				PwmPiezo_WriteCompare(0);
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = alarmActivatedSound2;
			}
			
			if(counter >= piezoLastChangeCount + piezoActivatedSound2RunTimeCounts)
			{
				piezoState = alarmActivatedSound3;
				break;
			}
			
			break;
		case alarmActivatedSound3:
			if(prevPiezoState != alarmActivatedSound3)
			{
				#if(configDEBUG_PIEZO == 1)
					UartDebug_PutString("PIEZO: Entering alarmActivatedSound3 state.\r\n");
				#endif
				PwmPiezo_WritePeriod(6000);
				PwmPiezo_WriteCompare(3000);
				
				piezoLastChangeCount = counter;
				
				prevPiezoState = alarmActivatedSound3;
			}
			
			if(counter >= piezoLastChangeCount + piezoActivatedSound3RunTimeCounts)
			{
				piezoState = piezoOff;
				break;
			}
			
			break;
	}
	
	// Increment state machine loop counter
	counter++;
}


void Piezo_AlarmEnable(bool_t enable)
{
	_alarmEnableFlag = enable;
}


void Piezo_EmitBeep(void)
{
	_piezoBeepCount++;
}

void Piezo_EmitMotorOnSound(motorOnSoundDirection_t motorOnSoundDirection)
{
	_motorOnSoundDirection = motorOnSoundDirection;
	// Set flag for state machine to enter motor piezo sound
	_emitMotorSoundFlag = TRUE;
}

void Piezo_AlarmActivatedSound(void)
{
	_alarmActivatedSoundFlag = TRUE;
}


//=================================================================================================
//==================================== PRIVATE FUNCTIONS ==========================================
//=================================================================================================

//===============================================================================================//
//============================================ ISR's ============================================//
//===============================================================================================//

// none

//===============================================================================================//
//============================================= GRAVEYARD =======================================//
//===============================================================================================//


/* [] END OF FILE */
