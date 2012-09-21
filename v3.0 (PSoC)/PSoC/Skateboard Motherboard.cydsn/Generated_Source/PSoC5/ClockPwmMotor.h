/*******************************************************************************
* File Name: ClockPwmMotor.h
* Version 1.60
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_ClockPwmMotor_H)
#define CY_CLOCK_ClockPwmMotor_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void ClockPwmMotor_Start(void) ;
void ClockPwmMotor_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void ClockPwmMotor_StopBlock(void) ;
#endif

void ClockPwmMotor_StandbyPower(uint8 state) ;
void ClockPwmMotor_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 ClockPwmMotor_GetDividerRegister(void) ;
void ClockPwmMotor_SetModeRegister(uint8 modeBitMask) ;
void ClockPwmMotor_ClearModeRegister(uint8 modeBitMask) ;
uint8 ClockPwmMotor_GetModeRegister(void) ;
void ClockPwmMotor_SetSourceRegister(uint8 clkSource) ;
uint8 ClockPwmMotor_GetSourceRegister(void) ;
#if defined(ClockPwmMotor__CFG3)
void ClockPwmMotor_SetPhaseRegister(uint8 clkPhase) ;
uint8 ClockPwmMotor_GetPhaseRegister(void) ;
#endif

#define ClockPwmMotor_Enable()                       ClockPwmMotor_Start()
#define ClockPwmMotor_Disable()                      ClockPwmMotor_Stop()
#define ClockPwmMotor_SetDivider(clkDivider)         ClockPwmMotor_SetDividerRegister(clkDivider, 1)
#define ClockPwmMotor_SetDividerValue(clkDivider)    ClockPwmMotor_SetDividerRegister((clkDivider) - 1, 1)
#define ClockPwmMotor_SetMode(clkMode)               ClockPwmMotor_SetModeRegister(clkMode)
#define ClockPwmMotor_SetSource(clkSource)           ClockPwmMotor_SetSourceRegister(clkSource)
#if defined(ClockPwmMotor__CFG3)
#define ClockPwmMotor_SetPhase(clkPhase)             ClockPwmMotor_SetPhaseRegister(clkPhase)
#define ClockPwmMotor_SetPhaseValue(clkPhase)        ClockPwmMotor_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*           API Constants
***************************************/

/* Constants SetPhase(), clkPhase parameter. Only valid for PSoC 3 ES2 and earlier. See datasheet for details. */
#if CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
   (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 || \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
#define CYCLK_2_5NS             0x01 /* 2.5 ns delay. */
#define CYCLK_3_5NS             0x02 /* 3.5 ns delay. */
#define CYCLK_4_5NS             0x03 /* 4.5 ns delay. */
#define CYCLK_5_5NS             0x04 /* 5.5 ns delay. */
#define CYCLK_6_5NS             0x05 /* 6.5 ns delay. */
#define CYCLK_7_5NS             0x06 /* 7.5 ns delay. */
#define CYCLK_8_5NS             0x07 /* 8.5 ns delay. */
#define CYCLK_9_5NS             0x08 /* 9.5 ns delay. */
#define CYCLK_10_5NS            0x09 /* 10.5 ns delay. */
#define CYCLK_11_5NS            0x0A /* 11.5 ns delay. */
#define CYCLK_12_5NS            0x0B /* 12.5 ns delay. */
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ClockPwmMotor_CLKEN              (* (reg8 *) ClockPwmMotor__PM_ACT_CFG)
#define ClockPwmMotor_CLKEN_PTR          ((reg8 *) ClockPwmMotor__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ClockPwmMotor_CLKSTBY            (* (reg8 *) ClockPwmMotor__PM_STBY_CFG)
#define ClockPwmMotor_CLKSTBY_PTR        ((reg8 *) ClockPwmMotor__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ClockPwmMotor_DIV_LSB            (* (reg8 *) ClockPwmMotor__CFG0)
#define ClockPwmMotor_DIV_LSB_PTR        ((reg8 *) ClockPwmMotor__CFG0)
#define ClockPwmMotor_DIV_PTR            ((reg16 *) ClockPwmMotor__CFG0)

/* Clock MSB divider configuration register. */
#define ClockPwmMotor_DIV_MSB            (* (reg8 *) ClockPwmMotor__CFG1)
#define ClockPwmMotor_DIV_MSB_PTR        ((reg8 *) ClockPwmMotor__CFG1)

/* Mode and source configuration register */
#define ClockPwmMotor_MOD_SRC            (* (reg8 *) ClockPwmMotor__CFG2)
#define ClockPwmMotor_MOD_SRC_PTR        ((reg8 *) ClockPwmMotor__CFG2)

#if defined(ClockPwmMotor__CFG3)
/* Analog clock phase configuration register */
#define ClockPwmMotor_PHASE              (* (reg8 *) ClockPwmMotor__CFG3)
#define ClockPwmMotor_PHASE_PTR          ((reg8 *) ClockPwmMotor__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ClockPwmMotor_CLKEN_MASK         ClockPwmMotor__PM_ACT_MSK
#define ClockPwmMotor_CLKSTBY_MASK       ClockPwmMotor__PM_STBY_MSK

/* CFG2 field masks */
#define ClockPwmMotor_SRC_SEL_MSK        ClockPwmMotor__CFG2_SRC_SEL_MASK
#define ClockPwmMotor_MODE_MASK          (~(ClockPwmMotor_SRC_SEL_MSK))

#if defined(ClockPwmMotor__CFG3)
/* CFG3 phase mask */
#define ClockPwmMotor_PHASE_MASK         ClockPwmMotor__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_ClockPwmMotor_H */


/* [] END OF FILE */
