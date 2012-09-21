/*******************************************************************************
* File Name: PinLedBoardBattLevelMed.h  
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

#if !defined(CY_PINS_PinLedBoardBattLevelMed_H) /* Pins PinLedBoardBattLevelMed_H */
#define CY_PINS_PinLedBoardBattLevelMed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedBoardBattLevelMed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedBoardBattLevelMed__PORT == 15 && (PinLedBoardBattLevelMed__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedBoardBattLevelMed_Write(uint8 value) ;
void    PinLedBoardBattLevelMed_SetDriveMode(uint8 mode) ;
uint8   PinLedBoardBattLevelMed_ReadDataReg(void) ;
uint8   PinLedBoardBattLevelMed_Read(void) ;
uint8   PinLedBoardBattLevelMed_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedBoardBattLevelMed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedBoardBattLevelMed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedBoardBattLevelMed_DM_RES_UP          PIN_DM_RES_UP
#define PinLedBoardBattLevelMed_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedBoardBattLevelMed_DM_OD_LO           PIN_DM_OD_LO
#define PinLedBoardBattLevelMed_DM_OD_HI           PIN_DM_OD_HI
#define PinLedBoardBattLevelMed_DM_STRONG          PIN_DM_STRONG
#define PinLedBoardBattLevelMed_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedBoardBattLevelMed_MASK               PinLedBoardBattLevelMed__MASK
#define PinLedBoardBattLevelMed_SHIFT              PinLedBoardBattLevelMed__SHIFT
#define PinLedBoardBattLevelMed_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedBoardBattLevelMed_PS                     (* (reg8 *) PinLedBoardBattLevelMed__PS)
/* Data Register */
#define PinLedBoardBattLevelMed_DR                     (* (reg8 *) PinLedBoardBattLevelMed__DR)
/* Port Number */
#define PinLedBoardBattLevelMed_PRT_NUM                (* (reg8 *) PinLedBoardBattLevelMed__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedBoardBattLevelMed_AG                     (* (reg8 *) PinLedBoardBattLevelMed__AG)                       
/* Analog MUX bux enable */
#define PinLedBoardBattLevelMed_AMUX                   (* (reg8 *) PinLedBoardBattLevelMed__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedBoardBattLevelMed_BIE                    (* (reg8 *) PinLedBoardBattLevelMed__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedBoardBattLevelMed_BIT_MASK               (* (reg8 *) PinLedBoardBattLevelMed__BIT_MASK)
/* Bypass Enable */
#define PinLedBoardBattLevelMed_BYP                    (* (reg8 *) PinLedBoardBattLevelMed__BYP)
/* Port wide control signals */                                                   
#define PinLedBoardBattLevelMed_CTL                    (* (reg8 *) PinLedBoardBattLevelMed__CTL)
/* Drive Modes */
#define PinLedBoardBattLevelMed_DM0                    (* (reg8 *) PinLedBoardBattLevelMed__DM0) 
#define PinLedBoardBattLevelMed_DM1                    (* (reg8 *) PinLedBoardBattLevelMed__DM1)
#define PinLedBoardBattLevelMed_DM2                    (* (reg8 *) PinLedBoardBattLevelMed__DM2) 
/* Input Buffer Disable Override */
#define PinLedBoardBattLevelMed_INP_DIS                (* (reg8 *) PinLedBoardBattLevelMed__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedBoardBattLevelMed_LCD_COM_SEG            (* (reg8 *) PinLedBoardBattLevelMed__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedBoardBattLevelMed_LCD_EN                 (* (reg8 *) PinLedBoardBattLevelMed__LCD_EN)
/* Slew Rate Control */
#define PinLedBoardBattLevelMed_SLW                    (* (reg8 *) PinLedBoardBattLevelMed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedBoardBattLevelMed_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedBoardBattLevelMed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedBoardBattLevelMed_PRTDSI__OE_SEL0        (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__OE_SEL0) 
#define PinLedBoardBattLevelMed_PRTDSI__OE_SEL1        (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedBoardBattLevelMed_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__OUT_SEL0) 
#define PinLedBoardBattLevelMed_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedBoardBattLevelMed_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedBoardBattLevelMed__PRTDSI__SYNC_OUT) 


#if defined(PinLedBoardBattLevelMed__INTSTAT)  /* Interrupt Registers */

    #define PinLedBoardBattLevelMed_INTSTAT                (* (reg8 *) PinLedBoardBattLevelMed__INTSTAT)
    #define PinLedBoardBattLevelMed_SNAP                   (* (reg8 *) PinLedBoardBattLevelMed__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedBoardBattLevelMed_H */

#endif
/* [] END OF FILE */
