/*******************************************************************************
* File Name: PinLedBoardBattLevelLow.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_PinLedBoardBattLevelLow_H) /* Pins PinLedBoardBattLevelLow_H */
#define CY_PINS_PinLedBoardBattLevelLow_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedBoardBattLevelLow_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedBoardBattLevelLow__PORT == 15 && (PinLedBoardBattLevelLow__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedBoardBattLevelLow_Write(uint8 value) ;
void    PinLedBoardBattLevelLow_SetDriveMode(uint8 mode) ;
uint8   PinLedBoardBattLevelLow_ReadDataReg(void) ;
uint8   PinLedBoardBattLevelLow_Read(void) ;
uint8   PinLedBoardBattLevelLow_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedBoardBattLevelLow_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedBoardBattLevelLow_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedBoardBattLevelLow_DM_RES_UP          PIN_DM_RES_UP
#define PinLedBoardBattLevelLow_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedBoardBattLevelLow_DM_OD_LO           PIN_DM_OD_LO
#define PinLedBoardBattLevelLow_DM_OD_HI           PIN_DM_OD_HI
#define PinLedBoardBattLevelLow_DM_STRONG          PIN_DM_STRONG
#define PinLedBoardBattLevelLow_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedBoardBattLevelLow_MASK               PinLedBoardBattLevelLow__MASK
#define PinLedBoardBattLevelLow_SHIFT              PinLedBoardBattLevelLow__SHIFT
#define PinLedBoardBattLevelLow_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedBoardBattLevelLow_PS                     (* (reg8 *) PinLedBoardBattLevelLow__PS)
/* Data Register */
#define PinLedBoardBattLevelLow_DR                     (* (reg8 *) PinLedBoardBattLevelLow__DR)
/* Port Number */
#define PinLedBoardBattLevelLow_PRT_NUM                (* (reg8 *) PinLedBoardBattLevelLow__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedBoardBattLevelLow_AG                     (* (reg8 *) PinLedBoardBattLevelLow__AG)                       
/* Analog MUX bux enable */
#define PinLedBoardBattLevelLow_AMUX                   (* (reg8 *) PinLedBoardBattLevelLow__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedBoardBattLevelLow_BIE                    (* (reg8 *) PinLedBoardBattLevelLow__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedBoardBattLevelLow_BIT_MASK               (* (reg8 *) PinLedBoardBattLevelLow__BIT_MASK)
/* Bypass Enable */
#define PinLedBoardBattLevelLow_BYP                    (* (reg8 *) PinLedBoardBattLevelLow__BYP)
/* Port wide control signals */                                                   
#define PinLedBoardBattLevelLow_CTL                    (* (reg8 *) PinLedBoardBattLevelLow__CTL)
/* Drive Modes */
#define PinLedBoardBattLevelLow_DM0                    (* (reg8 *) PinLedBoardBattLevelLow__DM0) 
#define PinLedBoardBattLevelLow_DM1                    (* (reg8 *) PinLedBoardBattLevelLow__DM1)
#define PinLedBoardBattLevelLow_DM2                    (* (reg8 *) PinLedBoardBattLevelLow__DM2) 
/* Input Buffer Disable Override */
#define PinLedBoardBattLevelLow_INP_DIS                (* (reg8 *) PinLedBoardBattLevelLow__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedBoardBattLevelLow_LCD_COM_SEG            (* (reg8 *) PinLedBoardBattLevelLow__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedBoardBattLevelLow_LCD_EN                 (* (reg8 *) PinLedBoardBattLevelLow__LCD_EN)
/* Slew Rate Control */
#define PinLedBoardBattLevelLow_SLW                    (* (reg8 *) PinLedBoardBattLevelLow__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedBoardBattLevelLow_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedBoardBattLevelLow_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedBoardBattLevelLow_PRTDSI__OE_SEL0        (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__OE_SEL0) 
#define PinLedBoardBattLevelLow_PRTDSI__OE_SEL1        (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedBoardBattLevelLow_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__OUT_SEL0) 
#define PinLedBoardBattLevelLow_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedBoardBattLevelLow_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedBoardBattLevelLow__PRTDSI__SYNC_OUT) 


#if defined(PinLedBoardBattLevelLow__INTSTAT)  /* Interrupt Registers */

    #define PinLedBoardBattLevelLow_INTSTAT                (* (reg8 *) PinLedBoardBattLevelLow__INTSTAT)
    #define PinLedBoardBattLevelLow_SNAP                   (* (reg8 *) PinLedBoardBattLevelLow__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedBoardBattLevelLow_H */

#endif
/* [] END OF FILE */
