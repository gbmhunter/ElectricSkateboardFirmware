/*******************************************************************************
* File Name: PinLedRemoteBattLevelLow.h  
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

#if !defined(CY_PINS_PinLedRemoteBattLevelLow_H) /* Pins PinLedRemoteBattLevelLow_H */
#define CY_PINS_PinLedRemoteBattLevelLow_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedRemoteBattLevelLow_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedRemoteBattLevelLow__PORT == 15 && (PinLedRemoteBattLevelLow__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedRemoteBattLevelLow_Write(uint8 value) ;
void    PinLedRemoteBattLevelLow_SetDriveMode(uint8 mode) ;
uint8   PinLedRemoteBattLevelLow_ReadDataReg(void) ;
uint8   PinLedRemoteBattLevelLow_Read(void) ;
uint8   PinLedRemoteBattLevelLow_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedRemoteBattLevelLow_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedRemoteBattLevelLow_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedRemoteBattLevelLow_DM_RES_UP          PIN_DM_RES_UP
#define PinLedRemoteBattLevelLow_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedRemoteBattLevelLow_DM_OD_LO           PIN_DM_OD_LO
#define PinLedRemoteBattLevelLow_DM_OD_HI           PIN_DM_OD_HI
#define PinLedRemoteBattLevelLow_DM_STRONG          PIN_DM_STRONG
#define PinLedRemoteBattLevelLow_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedRemoteBattLevelLow_MASK               PinLedRemoteBattLevelLow__MASK
#define PinLedRemoteBattLevelLow_SHIFT              PinLedRemoteBattLevelLow__SHIFT
#define PinLedRemoteBattLevelLow_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedRemoteBattLevelLow_PS                     (* (reg8 *) PinLedRemoteBattLevelLow__PS)
/* Data Register */
#define PinLedRemoteBattLevelLow_DR                     (* (reg8 *) PinLedRemoteBattLevelLow__DR)
/* Port Number */
#define PinLedRemoteBattLevelLow_PRT_NUM                (* (reg8 *) PinLedRemoteBattLevelLow__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedRemoteBattLevelLow_AG                     (* (reg8 *) PinLedRemoteBattLevelLow__AG)                       
/* Analog MUX bux enable */
#define PinLedRemoteBattLevelLow_AMUX                   (* (reg8 *) PinLedRemoteBattLevelLow__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedRemoteBattLevelLow_BIE                    (* (reg8 *) PinLedRemoteBattLevelLow__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedRemoteBattLevelLow_BIT_MASK               (* (reg8 *) PinLedRemoteBattLevelLow__BIT_MASK)
/* Bypass Enable */
#define PinLedRemoteBattLevelLow_BYP                    (* (reg8 *) PinLedRemoteBattLevelLow__BYP)
/* Port wide control signals */                                                   
#define PinLedRemoteBattLevelLow_CTL                    (* (reg8 *) PinLedRemoteBattLevelLow__CTL)
/* Drive Modes */
#define PinLedRemoteBattLevelLow_DM0                    (* (reg8 *) PinLedRemoteBattLevelLow__DM0) 
#define PinLedRemoteBattLevelLow_DM1                    (* (reg8 *) PinLedRemoteBattLevelLow__DM1)
#define PinLedRemoteBattLevelLow_DM2                    (* (reg8 *) PinLedRemoteBattLevelLow__DM2) 
/* Input Buffer Disable Override */
#define PinLedRemoteBattLevelLow_INP_DIS                (* (reg8 *) PinLedRemoteBattLevelLow__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedRemoteBattLevelLow_LCD_COM_SEG            (* (reg8 *) PinLedRemoteBattLevelLow__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedRemoteBattLevelLow_LCD_EN                 (* (reg8 *) PinLedRemoteBattLevelLow__LCD_EN)
/* Slew Rate Control */
#define PinLedRemoteBattLevelLow_SLW                    (* (reg8 *) PinLedRemoteBattLevelLow__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedRemoteBattLevelLow_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedRemoteBattLevelLow_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedRemoteBattLevelLow_PRTDSI__OE_SEL0        (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__OE_SEL0) 
#define PinLedRemoteBattLevelLow_PRTDSI__OE_SEL1        (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedRemoteBattLevelLow_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__OUT_SEL0) 
#define PinLedRemoteBattLevelLow_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedRemoteBattLevelLow_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedRemoteBattLevelLow__PRTDSI__SYNC_OUT) 


#if defined(PinLedRemoteBattLevelLow__INTSTAT)  /* Interrupt Registers */

    #define PinLedRemoteBattLevelLow_INTSTAT                (* (reg8 *) PinLedRemoteBattLevelLow__INTSTAT)
    #define PinLedRemoteBattLevelLow_SNAP                   (* (reg8 *) PinLedRemoteBattLevelLow__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedRemoteBattLevelLow_H */

#endif
/* [] END OF FILE */
