/*******************************************************************************
* File Name: PinLedRemoteBattLevelHigh.h  
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

#if !defined(CY_PINS_PinLedRemoteBattLevelHigh_H) /* Pins PinLedRemoteBattLevelHigh_H */
#define CY_PINS_PinLedRemoteBattLevelHigh_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedRemoteBattLevelHigh_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedRemoteBattLevelHigh__PORT == 15 && (PinLedRemoteBattLevelHigh__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedRemoteBattLevelHigh_Write(uint8 value) ;
void    PinLedRemoteBattLevelHigh_SetDriveMode(uint8 mode) ;
uint8   PinLedRemoteBattLevelHigh_ReadDataReg(void) ;
uint8   PinLedRemoteBattLevelHigh_Read(void) ;
uint8   PinLedRemoteBattLevelHigh_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedRemoteBattLevelHigh_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedRemoteBattLevelHigh_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedRemoteBattLevelHigh_DM_RES_UP          PIN_DM_RES_UP
#define PinLedRemoteBattLevelHigh_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedRemoteBattLevelHigh_DM_OD_LO           PIN_DM_OD_LO
#define PinLedRemoteBattLevelHigh_DM_OD_HI           PIN_DM_OD_HI
#define PinLedRemoteBattLevelHigh_DM_STRONG          PIN_DM_STRONG
#define PinLedRemoteBattLevelHigh_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedRemoteBattLevelHigh_MASK               PinLedRemoteBattLevelHigh__MASK
#define PinLedRemoteBattLevelHigh_SHIFT              PinLedRemoteBattLevelHigh__SHIFT
#define PinLedRemoteBattLevelHigh_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedRemoteBattLevelHigh_PS                     (* (reg8 *) PinLedRemoteBattLevelHigh__PS)
/* Data Register */
#define PinLedRemoteBattLevelHigh_DR                     (* (reg8 *) PinLedRemoteBattLevelHigh__DR)
/* Port Number */
#define PinLedRemoteBattLevelHigh_PRT_NUM                (* (reg8 *) PinLedRemoteBattLevelHigh__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedRemoteBattLevelHigh_AG                     (* (reg8 *) PinLedRemoteBattLevelHigh__AG)                       
/* Analog MUX bux enable */
#define PinLedRemoteBattLevelHigh_AMUX                   (* (reg8 *) PinLedRemoteBattLevelHigh__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedRemoteBattLevelHigh_BIE                    (* (reg8 *) PinLedRemoteBattLevelHigh__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedRemoteBattLevelHigh_BIT_MASK               (* (reg8 *) PinLedRemoteBattLevelHigh__BIT_MASK)
/* Bypass Enable */
#define PinLedRemoteBattLevelHigh_BYP                    (* (reg8 *) PinLedRemoteBattLevelHigh__BYP)
/* Port wide control signals */                                                   
#define PinLedRemoteBattLevelHigh_CTL                    (* (reg8 *) PinLedRemoteBattLevelHigh__CTL)
/* Drive Modes */
#define PinLedRemoteBattLevelHigh_DM0                    (* (reg8 *) PinLedRemoteBattLevelHigh__DM0) 
#define PinLedRemoteBattLevelHigh_DM1                    (* (reg8 *) PinLedRemoteBattLevelHigh__DM1)
#define PinLedRemoteBattLevelHigh_DM2                    (* (reg8 *) PinLedRemoteBattLevelHigh__DM2) 
/* Input Buffer Disable Override */
#define PinLedRemoteBattLevelHigh_INP_DIS                (* (reg8 *) PinLedRemoteBattLevelHigh__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedRemoteBattLevelHigh_LCD_COM_SEG            (* (reg8 *) PinLedRemoteBattLevelHigh__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedRemoteBattLevelHigh_LCD_EN                 (* (reg8 *) PinLedRemoteBattLevelHigh__LCD_EN)
/* Slew Rate Control */
#define PinLedRemoteBattLevelHigh_SLW                    (* (reg8 *) PinLedRemoteBattLevelHigh__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedRemoteBattLevelHigh_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedRemoteBattLevelHigh_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedRemoteBattLevelHigh_PRTDSI__OE_SEL0        (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__OE_SEL0) 
#define PinLedRemoteBattLevelHigh_PRTDSI__OE_SEL1        (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedRemoteBattLevelHigh_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__OUT_SEL0) 
#define PinLedRemoteBattLevelHigh_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedRemoteBattLevelHigh_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedRemoteBattLevelHigh__PRTDSI__SYNC_OUT) 


#if defined(PinLedRemoteBattLevelHigh__INTSTAT)  /* Interrupt Registers */

    #define PinLedRemoteBattLevelHigh_INTSTAT                (* (reg8 *) PinLedRemoteBattLevelHigh__INTSTAT)
    #define PinLedRemoteBattLevelHigh_SNAP                   (* (reg8 *) PinLedRemoteBattLevelHigh__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedRemoteBattLevelHigh_H */

#endif
/* [] END OF FILE */
