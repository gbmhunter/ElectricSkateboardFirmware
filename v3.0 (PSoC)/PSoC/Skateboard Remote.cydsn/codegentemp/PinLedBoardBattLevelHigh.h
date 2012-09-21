/*******************************************************************************
* File Name: PinLedBoardBattLevelHigh.h  
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

#if !defined(CY_PINS_PinLedBoardBattLevelHigh_H) /* Pins PinLedBoardBattLevelHigh_H */
#define CY_PINS_PinLedBoardBattLevelHigh_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedBoardBattLevelHigh_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedBoardBattLevelHigh__PORT == 15 && (PinLedBoardBattLevelHigh__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedBoardBattLevelHigh_Write(uint8 value) ;
void    PinLedBoardBattLevelHigh_SetDriveMode(uint8 mode) ;
uint8   PinLedBoardBattLevelHigh_ReadDataReg(void) ;
uint8   PinLedBoardBattLevelHigh_Read(void) ;
uint8   PinLedBoardBattLevelHigh_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedBoardBattLevelHigh_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedBoardBattLevelHigh_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedBoardBattLevelHigh_DM_RES_UP          PIN_DM_RES_UP
#define PinLedBoardBattLevelHigh_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedBoardBattLevelHigh_DM_OD_LO           PIN_DM_OD_LO
#define PinLedBoardBattLevelHigh_DM_OD_HI           PIN_DM_OD_HI
#define PinLedBoardBattLevelHigh_DM_STRONG          PIN_DM_STRONG
#define PinLedBoardBattLevelHigh_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedBoardBattLevelHigh_MASK               PinLedBoardBattLevelHigh__MASK
#define PinLedBoardBattLevelHigh_SHIFT              PinLedBoardBattLevelHigh__SHIFT
#define PinLedBoardBattLevelHigh_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedBoardBattLevelHigh_PS                     (* (reg8 *) PinLedBoardBattLevelHigh__PS)
/* Data Register */
#define PinLedBoardBattLevelHigh_DR                     (* (reg8 *) PinLedBoardBattLevelHigh__DR)
/* Port Number */
#define PinLedBoardBattLevelHigh_PRT_NUM                (* (reg8 *) PinLedBoardBattLevelHigh__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedBoardBattLevelHigh_AG                     (* (reg8 *) PinLedBoardBattLevelHigh__AG)                       
/* Analog MUX bux enable */
#define PinLedBoardBattLevelHigh_AMUX                   (* (reg8 *) PinLedBoardBattLevelHigh__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedBoardBattLevelHigh_BIE                    (* (reg8 *) PinLedBoardBattLevelHigh__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedBoardBattLevelHigh_BIT_MASK               (* (reg8 *) PinLedBoardBattLevelHigh__BIT_MASK)
/* Bypass Enable */
#define PinLedBoardBattLevelHigh_BYP                    (* (reg8 *) PinLedBoardBattLevelHigh__BYP)
/* Port wide control signals */                                                   
#define PinLedBoardBattLevelHigh_CTL                    (* (reg8 *) PinLedBoardBattLevelHigh__CTL)
/* Drive Modes */
#define PinLedBoardBattLevelHigh_DM0                    (* (reg8 *) PinLedBoardBattLevelHigh__DM0) 
#define PinLedBoardBattLevelHigh_DM1                    (* (reg8 *) PinLedBoardBattLevelHigh__DM1)
#define PinLedBoardBattLevelHigh_DM2                    (* (reg8 *) PinLedBoardBattLevelHigh__DM2) 
/* Input Buffer Disable Override */
#define PinLedBoardBattLevelHigh_INP_DIS                (* (reg8 *) PinLedBoardBattLevelHigh__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedBoardBattLevelHigh_LCD_COM_SEG            (* (reg8 *) PinLedBoardBattLevelHigh__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedBoardBattLevelHigh_LCD_EN                 (* (reg8 *) PinLedBoardBattLevelHigh__LCD_EN)
/* Slew Rate Control */
#define PinLedBoardBattLevelHigh_SLW                    (* (reg8 *) PinLedBoardBattLevelHigh__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedBoardBattLevelHigh_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedBoardBattLevelHigh_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedBoardBattLevelHigh_PRTDSI__OE_SEL0        (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__OE_SEL0) 
#define PinLedBoardBattLevelHigh_PRTDSI__OE_SEL1        (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedBoardBattLevelHigh_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__OUT_SEL0) 
#define PinLedBoardBattLevelHigh_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedBoardBattLevelHigh_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedBoardBattLevelHigh__PRTDSI__SYNC_OUT) 


#if defined(PinLedBoardBattLevelHigh__INTSTAT)  /* Interrupt Registers */

    #define PinLedBoardBattLevelHigh_INTSTAT                (* (reg8 *) PinLedBoardBattLevelHigh__INTSTAT)
    #define PinLedBoardBattLevelHigh_SNAP                   (* (reg8 *) PinLedBoardBattLevelHigh__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedBoardBattLevelHigh_H */

#endif
/* [] END OF FILE */
