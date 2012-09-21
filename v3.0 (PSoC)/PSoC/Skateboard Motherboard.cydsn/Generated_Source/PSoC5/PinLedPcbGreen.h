/*******************************************************************************
* File Name: PinLedPcbGreen.h  
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

#if !defined(CY_PINS_PinLedPcbGreen_H) /* Pins PinLedPcbGreen_H */
#define CY_PINS_PinLedPcbGreen_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedPcbGreen_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedPcbGreen__PORT == 15 && (PinLedPcbGreen__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedPcbGreen_Write(uint8 value) ;
void    PinLedPcbGreen_SetDriveMode(uint8 mode) ;
uint8   PinLedPcbGreen_ReadDataReg(void) ;
uint8   PinLedPcbGreen_Read(void) ;
uint8   PinLedPcbGreen_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedPcbGreen_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedPcbGreen_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedPcbGreen_DM_RES_UP          PIN_DM_RES_UP
#define PinLedPcbGreen_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedPcbGreen_DM_OD_LO           PIN_DM_OD_LO
#define PinLedPcbGreen_DM_OD_HI           PIN_DM_OD_HI
#define PinLedPcbGreen_DM_STRONG          PIN_DM_STRONG
#define PinLedPcbGreen_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedPcbGreen_MASK               PinLedPcbGreen__MASK
#define PinLedPcbGreen_SHIFT              PinLedPcbGreen__SHIFT
#define PinLedPcbGreen_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedPcbGreen_PS                     (* (reg8 *) PinLedPcbGreen__PS)
/* Data Register */
#define PinLedPcbGreen_DR                     (* (reg8 *) PinLedPcbGreen__DR)
/* Port Number */
#define PinLedPcbGreen_PRT_NUM                (* (reg8 *) PinLedPcbGreen__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedPcbGreen_AG                     (* (reg8 *) PinLedPcbGreen__AG)                       
/* Analog MUX bux enable */
#define PinLedPcbGreen_AMUX                   (* (reg8 *) PinLedPcbGreen__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedPcbGreen_BIE                    (* (reg8 *) PinLedPcbGreen__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedPcbGreen_BIT_MASK               (* (reg8 *) PinLedPcbGreen__BIT_MASK)
/* Bypass Enable */
#define PinLedPcbGreen_BYP                    (* (reg8 *) PinLedPcbGreen__BYP)
/* Port wide control signals */                                                   
#define PinLedPcbGreen_CTL                    (* (reg8 *) PinLedPcbGreen__CTL)
/* Drive Modes */
#define PinLedPcbGreen_DM0                    (* (reg8 *) PinLedPcbGreen__DM0) 
#define PinLedPcbGreen_DM1                    (* (reg8 *) PinLedPcbGreen__DM1)
#define PinLedPcbGreen_DM2                    (* (reg8 *) PinLedPcbGreen__DM2) 
/* Input Buffer Disable Override */
#define PinLedPcbGreen_INP_DIS                (* (reg8 *) PinLedPcbGreen__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedPcbGreen_LCD_COM_SEG            (* (reg8 *) PinLedPcbGreen__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedPcbGreen_LCD_EN                 (* (reg8 *) PinLedPcbGreen__LCD_EN)
/* Slew Rate Control */
#define PinLedPcbGreen_SLW                    (* (reg8 *) PinLedPcbGreen__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedPcbGreen_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedPcbGreen__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedPcbGreen_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedPcbGreen__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedPcbGreen_PRTDSI__OE_SEL0        (* (reg8 *) PinLedPcbGreen__PRTDSI__OE_SEL0) 
#define PinLedPcbGreen_PRTDSI__OE_SEL1        (* (reg8 *) PinLedPcbGreen__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedPcbGreen_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedPcbGreen__PRTDSI__OUT_SEL0) 
#define PinLedPcbGreen_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedPcbGreen__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedPcbGreen_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedPcbGreen__PRTDSI__SYNC_OUT) 


#if defined(PinLedPcbGreen__INTSTAT)  /* Interrupt Registers */

    #define PinLedPcbGreen_INTSTAT                (* (reg8 *) PinLedPcbGreen__INTSTAT)
    #define PinLedPcbGreen_SNAP                   (* (reg8 *) PinLedPcbGreen__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedPcbGreen_H */

#endif
/* [] END OF FILE */
