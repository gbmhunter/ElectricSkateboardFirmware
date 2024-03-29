/*******************************************************************************
* File Name: AdcSar_theACLK.h
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

#if !defined(CY_CLOCK_AdcSar_theACLK_H)
#define CY_CLOCK_AdcSar_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void AdcSar_theACLK_Start(void) ;
void AdcSar_theACLK_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void AdcSar_theACLK_StopBlock(void) ;
#endif

void AdcSar_theACLK_StandbyPower(uint8 state) ;
void AdcSar_theACLK_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 AdcSar_theACLK_GetDividerRegister(void) ;
void AdcSar_theACLK_SetModeRegister(uint8 modeBitMask) ;
void AdcSar_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 AdcSar_theACLK_GetModeRegister(void) ;
void AdcSar_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 AdcSar_theACLK_GetSourceRegister(void) ;
#if defined(AdcSar_theACLK__CFG3)
void AdcSar_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 AdcSar_theACLK_GetPhaseRegister(void) ;
#endif

#define AdcSar_theACLK_Enable()                       AdcSar_theACLK_Start()
#define AdcSar_theACLK_Disable()                      AdcSar_theACLK_Stop()
#define AdcSar_theACLK_SetDivider(clkDivider)         AdcSar_theACLK_SetDividerRegister(clkDivider, 1)
#define AdcSar_theACLK_SetDividerValue(clkDivider)    AdcSar_theACLK_SetDividerRegister((clkDivider) - 1, 1)
#define AdcSar_theACLK_SetMode(clkMode)               AdcSar_theACLK_SetModeRegister(clkMode)
#define AdcSar_theACLK_SetSource(clkSource)           AdcSar_theACLK_SetSourceRegister(clkSource)
#if defined(AdcSar_theACLK__CFG3)
#define AdcSar_theACLK_SetPhase(clkPhase)             AdcSar_theACLK_SetPhaseRegister(clkPhase)
#define AdcSar_theACLK_SetPhaseValue(clkPhase)        AdcSar_theACLK_SetPhaseRegister((clkPhase) + 1)
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
#define AdcSar_theACLK_CLKEN              (* (reg8 *) AdcSar_theACLK__PM_ACT_CFG)
#define AdcSar_theACLK_CLKEN_PTR          ((reg8 *) AdcSar_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define AdcSar_theACLK_CLKSTBY            (* (reg8 *) AdcSar_theACLK__PM_STBY_CFG)
#define AdcSar_theACLK_CLKSTBY_PTR        ((reg8 *) AdcSar_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define AdcSar_theACLK_DIV_LSB            (* (reg8 *) AdcSar_theACLK__CFG0)
#define AdcSar_theACLK_DIV_LSB_PTR        ((reg8 *) AdcSar_theACLK__CFG0)
#define AdcSar_theACLK_DIV_PTR            ((reg16 *) AdcSar_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define AdcSar_theACLK_DIV_MSB            (* (reg8 *) AdcSar_theACLK__CFG1)
#define AdcSar_theACLK_DIV_MSB_PTR        ((reg8 *) AdcSar_theACLK__CFG1)

/* Mode and source configuration register */
#define AdcSar_theACLK_MOD_SRC            (* (reg8 *) AdcSar_theACLK__CFG2)
#define AdcSar_theACLK_MOD_SRC_PTR        ((reg8 *) AdcSar_theACLK__CFG2)

#if defined(AdcSar_theACLK__CFG3)
/* Analog clock phase configuration register */
#define AdcSar_theACLK_PHASE              (* (reg8 *) AdcSar_theACLK__CFG3)
#define AdcSar_theACLK_PHASE_PTR          ((reg8 *) AdcSar_theACLK__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define AdcSar_theACLK_CLKEN_MASK         AdcSar_theACLK__PM_ACT_MSK
#define AdcSar_theACLK_CLKSTBY_MASK       AdcSar_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define AdcSar_theACLK_SRC_SEL_MSK        AdcSar_theACLK__CFG2_SRC_SEL_MASK
#define AdcSar_theACLK_MODE_MASK          (~(AdcSar_theACLK_SRC_SEL_MSK))

#if defined(AdcSar_theACLK__CFG3)
/* CFG3 phase mask */
#define AdcSar_theACLK_PHASE_MASK         AdcSar_theACLK__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_AdcSar_theACLK_H */


/* [] END OF FILE */
