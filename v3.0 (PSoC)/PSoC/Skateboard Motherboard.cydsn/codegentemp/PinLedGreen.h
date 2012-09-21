/*******************************************************************************
* File Name: PinLedGreen.h  
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

#if !defined(CY_PINS_PinLedGreen_H) /* Pins PinLedGreen_H */
#define CY_PINS_PinLedGreen_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedGreen_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedGreen__PORT == 15 && (PinLedGreen__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedGreen_Write(uint8 value) ;
void    PinLedGreen_SetDriveMode(uint8 mode) ;
uint8   PinLedGreen_ReadDataReg(void) ;
uint8   PinLedGreen_Read(void) ;
uint8   PinLedGreen_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedGreen_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedGreen_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedGreen_DM_RES_UP          PIN_DM_RES_UP
#define PinLedGreen_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedGreen_DM_OD_LO           PIN_DM_OD_LO
#define PinLedGreen_DM_OD_HI           PIN_DM_OD_HI
#define PinLedGreen_DM_STRONG          PIN_DM_STRONG
#define PinLedGreen_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedGreen_MASK               PinLedGreen__MASK
#define PinLedGreen_SHIFT              PinLedGreen__SHIFT
#define PinLedGreen_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedGreen_PS                     (* (reg8 *) PinLedGreen__PS)
/* Data Register */
#define PinLedGreen_DR                     (* (reg8 *) PinLedGreen__DR)
/* Port Number */
#define PinLedGreen_PRT_NUM                (* (reg8 *) PinLedGreen__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedGreen_AG                     (* (reg8 *) PinLedGreen__AG)                       
/* Analog MUX bux enable */
#define PinLedGreen_AMUX                   (* (reg8 *) PinLedGreen__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedGreen_BIE                    (* (reg8 *) PinLedGreen__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedGreen_BIT_MASK               (* (reg8 *) PinLedGreen__BIT_MASK)
/* Bypass Enable */
#define PinLedGreen_BYP                    (* (reg8 *) PinLedGreen__BYP)
/* Port wide control signals */                                                   
#define PinLedGreen_CTL                    (* (reg8 *) PinLedGreen__CTL)
/* Drive Modes */
#define PinLedGreen_DM0                    (* (reg8 *) PinLedGreen__DM0) 
#define PinLedGreen_DM1                    (* (reg8 *) PinLedGreen__DM1)
#define PinLedGreen_DM2                    (* (reg8 *) PinLedGreen__DM2) 
/* Input Buffer Disable Override */
#define PinLedGreen_INP_DIS                (* (reg8 *) PinLedGreen__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedGreen_LCD_COM_SEG            (* (reg8 *) PinLedGreen__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedGreen_LCD_EN                 (* (reg8 *) PinLedGreen__LCD_EN)
/* Slew Rate Control */
#define PinLedGreen_SLW                    (* (reg8 *) PinLedGreen__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedGreen_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedGreen__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedGreen_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedGreen__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedGreen_PRTDSI__OE_SEL0        (* (reg8 *) PinLedGreen__PRTDSI__OE_SEL0) 
#define PinLedGreen_PRTDSI__OE_SEL1        (* (reg8 *) PinLedGreen__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedGreen_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedGreen__PRTDSI__OUT_SEL0) 
#define PinLedGreen_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedGreen__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedGreen_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedGreen__PRTDSI__SYNC_OUT) 


#if defined(PinLedGreen__INTSTAT)  /* Interrupt Registers */

    #define PinLedGreen_INTSTAT                (* (reg8 *) PinLedGreen__INTSTAT)
    #define PinLedGreen_SNAP                   (* (reg8 *) PinLedGreen__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedGreen_H */

#endif
/* [] END OF FILE */
