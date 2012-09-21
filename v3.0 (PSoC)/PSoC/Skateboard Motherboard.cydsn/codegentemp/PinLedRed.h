/*******************************************************************************
* File Name: PinLedRed.h  
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

#if !defined(CY_PINS_PinLedRed_H) /* Pins PinLedRed_H */
#define CY_PINS_PinLedRed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedRed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedRed__PORT == 15 && (PinLedRed__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedRed_Write(uint8 value) ;
void    PinLedRed_SetDriveMode(uint8 mode) ;
uint8   PinLedRed_ReadDataReg(void) ;
uint8   PinLedRed_Read(void) ;
uint8   PinLedRed_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedRed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedRed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedRed_DM_RES_UP          PIN_DM_RES_UP
#define PinLedRed_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedRed_DM_OD_LO           PIN_DM_OD_LO
#define PinLedRed_DM_OD_HI           PIN_DM_OD_HI
#define PinLedRed_DM_STRONG          PIN_DM_STRONG
#define PinLedRed_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedRed_MASK               PinLedRed__MASK
#define PinLedRed_SHIFT              PinLedRed__SHIFT
#define PinLedRed_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedRed_PS                     (* (reg8 *) PinLedRed__PS)
/* Data Register */
#define PinLedRed_DR                     (* (reg8 *) PinLedRed__DR)
/* Port Number */
#define PinLedRed_PRT_NUM                (* (reg8 *) PinLedRed__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedRed_AG                     (* (reg8 *) PinLedRed__AG)                       
/* Analog MUX bux enable */
#define PinLedRed_AMUX                   (* (reg8 *) PinLedRed__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedRed_BIE                    (* (reg8 *) PinLedRed__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedRed_BIT_MASK               (* (reg8 *) PinLedRed__BIT_MASK)
/* Bypass Enable */
#define PinLedRed_BYP                    (* (reg8 *) PinLedRed__BYP)
/* Port wide control signals */                                                   
#define PinLedRed_CTL                    (* (reg8 *) PinLedRed__CTL)
/* Drive Modes */
#define PinLedRed_DM0                    (* (reg8 *) PinLedRed__DM0) 
#define PinLedRed_DM1                    (* (reg8 *) PinLedRed__DM1)
#define PinLedRed_DM2                    (* (reg8 *) PinLedRed__DM2) 
/* Input Buffer Disable Override */
#define PinLedRed_INP_DIS                (* (reg8 *) PinLedRed__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedRed_LCD_COM_SEG            (* (reg8 *) PinLedRed__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedRed_LCD_EN                 (* (reg8 *) PinLedRed__LCD_EN)
/* Slew Rate Control */
#define PinLedRed_SLW                    (* (reg8 *) PinLedRed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedRed_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedRed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedRed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedRed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedRed_PRTDSI__OE_SEL0        (* (reg8 *) PinLedRed__PRTDSI__OE_SEL0) 
#define PinLedRed_PRTDSI__OE_SEL1        (* (reg8 *) PinLedRed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedRed_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedRed__PRTDSI__OUT_SEL0) 
#define PinLedRed_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedRed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedRed_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedRed__PRTDSI__SYNC_OUT) 


#if defined(PinLedRed__INTSTAT)  /* Interrupt Registers */

    #define PinLedRed_INTSTAT                (* (reg8 *) PinLedRed__INTSTAT)
    #define PinLedRed_SNAP                   (* (reg8 *) PinLedRed__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedRed_H */

#endif
/* [] END OF FILE */
