/*******************************************************************************
* File Name: ClockPwmPiezo.h
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

#if !defined(CY_CLOCK_ClockPwmPiezo_H)
#define CY_CLOCK_ClockPwmPiezo_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void ClockPwmPiezo_Start(void) ;
void ClockPwmPiezo_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void ClockPwmPiezo_StopBlock(void) ;
#endif

void ClockPwmPiezo_StandbyPower(uint8 state) ;
void ClockPwmPiezo_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 ClockPwmPiezo_GetDividerRegister(void) ;
void ClockPwmPiezo_SetModeRegister(uint8 modeBitMask) ;
void ClockPwmPiezo_ClearModeRegister(uint8 modeBitMask) ;
uint8 ClockPwmPiezo_GetModeRegister(void) ;
void ClockPwmPiezo_SetSourceRegister(uint8 clkSource) ;
uint8 ClockPwmPiezo_GetSourceRegister(void) ;
#if defined(ClockPwmPiezo__CFG3)
void ClockPwmPiezo_SetPhaseRegister(uint8 clkPhase) ;
uint8 ClockPwmPiezo_GetPhaseRegister(void) ;
#endif

#define ClockPwmPiezo_Enable()                       ClockPwmPiezo_Start()
#define ClockPwmPiezo_Disable()                      ClockPwmPiezo_Stop()
#define ClockPwmPiezo_SetDivider(clkDivider)         ClockPwmPiezo_SetDividerRegister(clkDivider, 1)
#define ClockPwmPiezo_SetDividerValue(clkDivider)    ClockPwmPiezo_SetDividerRegister((clkDivider) - 1, 1)
#define ClockPwmPiezo_SetMode(clkMode)               ClockPwmPiezo_SetModeRegister(clkMode)
#define ClockPwmPiezo_SetSource(clkSource)           ClockPwmPiezo_SetSourceRegister(clkSource)
#if defined(ClockPwmPiezo__CFG3)
#define ClockPwmPiezo_SetPhase(clkPhase)             ClockPwmPiezo_SetPhaseRegister(clkPhase)
#define ClockPwmPiezo_SetPhaseValue(clkPhase)        ClockPwmPiezo_SetPhaseRegister((clkPhase) + 1)
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
#define ClockPwmPiezo_CLKEN              (* (reg8 *) ClockPwmPiezo__PM_ACT_CFG)
#define ClockPwmPiezo_CLKEN_PTR          ((reg8 *) ClockPwmPiezo__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ClockPwmPiezo_CLKSTBY            (* (reg8 *) ClockPwmPiezo__PM_STBY_CFG)
#define ClockPwmPiezo_CLKSTBY_PTR        ((reg8 *) ClockPwmPiezo__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ClockPwmPiezo_DIV_LSB            (* (reg8 *) ClockPwmPiezo__CFG0)
#define ClockPwmPiezo_DIV_LSB_PTR        ((reg8 *) ClockPwmPiezo__CFG0)
#define ClockPwmPiezo_DIV_PTR            ((reg16 *) ClockPwmPiezo__CFG0)

/* Clock MSB divider configuration register. */
#define ClockPwmPiezo_DIV_MSB            (* (reg8 *) ClockPwmPiezo__CFG1)
#define ClockPwmPiezo_DIV_MSB_PTR        ((reg8 *) ClockPwmPiezo__CFG1)

/* Mode and source configuration register */
#define ClockPwmPiezo_MOD_SRC            (* (reg8 *) ClockPwmPiezo__CFG2)
#define ClockPwmPiezo_MOD_SRC_PTR        ((reg8 *) ClockPwmPiezo__CFG2)

#if defined(ClockPwmPiezo__CFG3)
/* Analog clock phase configuration register */
#define ClockPwmPiezo_PHASE              (* (reg8 *) ClockPwmPiezo__CFG3)
#define ClockPwmPiezo_PHASE_PTR          ((reg8 *) ClockPwmPiezo__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ClockPwmPiezo_CLKEN_MASK         ClockPwmPiezo__PM_ACT_MSK
#define ClockPwmPiezo_CLKSTBY_MASK       ClockPwmPiezo__PM_STBY_MSK

/* CFG2 field masks */
#define ClockPwmPiezo_SRC_SEL_MSK        ClockPwmPiezo__CFG2_SRC_SEL_MASK
#define ClockPwmPiezo_MODE_MASK          (~(ClockPwmPiezo_SRC_SEL_MSK))

#if defined(ClockPwmPiezo__CFG3)
/* CFG3 phase mask */
#define ClockPwmPiezo_PHASE_MASK         ClockPwmPiezo__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_ClockPwmPiezo_H */


/* [] END OF FILE */
