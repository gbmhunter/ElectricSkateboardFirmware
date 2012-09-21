/*******************************************************************************
* File Name: PinLedRemoteBattLevelMed.h  
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

#if !defined(CY_PINS_PinLedRemoteBattLevelMed_H) /* Pins PinLedRemoteBattLevelMed_H */
#define CY_PINS_PinLedRemoteBattLevelMed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedRemoteBattLevelMed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedRemoteBattLevelMed__PORT == 15 && (PinLedRemoteBattLevelMed__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedRemoteBattLevelMed_Write(uint8 value) ;
void    PinLedRemoteBattLevelMed_SetDriveMode(uint8 mode) ;
uint8   PinLedRemoteBattLevelMed_ReadDataReg(void) ;
uint8   PinLedRemoteBattLevelMed_Read(void) ;
uint8   PinLedRemoteBattLevelMed_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedRemoteBattLevelMed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedRemoteBattLevelMed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedRemoteBattLevelMed_DM_RES_UP          PIN_DM_RES_UP
#define PinLedRemoteBattLevelMed_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedRemoteBattLevelMed_DM_OD_LO           PIN_DM_OD_LO
#define PinLedRemoteBattLevelMed_DM_OD_HI           PIN_DM_OD_HI
#define PinLedRemoteBattLevelMed_DM_STRONG          PIN_DM_STRONG
#define PinLedRemoteBattLevelMed_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedRemoteBattLevelMed_MASK               PinLedRemoteBattLevelMed__MASK
#define PinLedRemoteBattLevelMed_SHIFT              PinLedRemoteBattLevelMed__SHIFT
#define PinLedRemoteBattLevelMed_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedRemoteBattLevelMed_PS                     (* (reg8 *) PinLedRemoteBattLevelMed__PS)
/* Data Register */
#define PinLedRemoteBattLevelMed_DR                     (* (reg8 *) PinLedRemoteBattLevelMed__DR)
/* Port Number */
#define PinLedRemoteBattLevelMed_PRT_NUM                (* (reg8 *) PinLedRemoteBattLevelMed__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedRemoteBattLevelMed_AG                     (* (reg8 *) PinLedRemoteBattLevelMed__AG)                       
/* Analog MUX bux enable */
#define PinLedRemoteBattLevelMed_AMUX                   (* (reg8 *) PinLedRemoteBattLevelMed__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedRemoteBattLevelMed_BIE                    (* (reg8 *) PinLedRemoteBattLevelMed__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedRemoteBattLevelMed_BIT_MASK               (* (reg8 *) PinLedRemoteBattLevelMed__BIT_MASK)
/* Bypass Enable */
#define PinLedRemoteBattLevelMed_BYP                    (* (reg8 *) PinLedRemoteBattLevelMed__BYP)
/* Port wide control signals */                                                   
#define PinLedRemoteBattLevelMed_CTL                    (* (reg8 *) PinLedRemoteBattLevelMed__CTL)
/* Drive Modes */
#define PinLedRemoteBattLevelMed_DM0                    (* (reg8 *) PinLedRemoteBattLevelMed__DM0) 
#define PinLedRemoteBattLevelMed_DM1                    (* (reg8 *) PinLedRemoteBattLevelMed__DM1)
#define PinLedRemoteBattLevelMed_DM2                    (* (reg8 *) PinLedRemoteBattLevelMed__DM2) 
/* Input Buffer Disable Override */
#define PinLedRemoteBattLevelMed_INP_DIS                (* (reg8 *) PinLedRemoteBattLevelMed__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedRemoteBattLevelMed_LCD_COM_SEG            (* (reg8 *) PinLedRemoteBattLevelMed__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedRemoteBattLevelMed_LCD_EN                 (* (reg8 *) PinLedRemoteBattLevelMed__LCD_EN)
/* Slew Rate Control */
#define PinLedRemoteBattLevelMed_SLW                    (* (reg8 *) PinLedRemoteBattLevelMed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedRemoteBattLevelMed_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedRemoteBattLevelMed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedRemoteBattLevelMed_PRTDSI__OE_SEL0        (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__OE_SEL0) 
#define PinLedRemoteBattLevelMed_PRTDSI__OE_SEL1        (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedRemoteBattLevelMed_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__OUT_SEL0) 
#define PinLedRemoteBattLevelMed_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedRemoteBattLevelMed_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedRemoteBattLevelMed__PRTDSI__SYNC_OUT) 


#if defined(PinLedRemoteBattLevelMed__INTSTAT)  /* Interrupt Registers */

    #define PinLedRemoteBattLevelMed_INTSTAT                (* (reg8 *) PinLedRemoteBattLevelMed__INTSTAT)
    #define PinLedRemoteBattLevelMed_SNAP                   (* (reg8 *) PinLedRemoteBattLevelMed__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedRemoteBattLevelMed_H */

#endif
/* [] END OF FILE */
