/*******************************************************************************
* File Name: PinLedInRange.h  
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

#if !defined(CY_PINS_PinLedInRange_H) /* Pins PinLedInRange_H */
#define CY_PINS_PinLedInRange_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedInRange_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedInRange__PORT == 15 && (PinLedInRange__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedInRange_Write(uint8 value) ;
void    PinLedInRange_SetDriveMode(uint8 mode) ;
uint8   PinLedInRange_ReadDataReg(void) ;
uint8   PinLedInRange_Read(void) ;
uint8   PinLedInRange_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedInRange_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedInRange_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedInRange_DM_RES_UP          PIN_DM_RES_UP
#define PinLedInRange_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedInRange_DM_OD_LO           PIN_DM_OD_LO
#define PinLedInRange_DM_OD_HI           PIN_DM_OD_HI
#define PinLedInRange_DM_STRONG          PIN_DM_STRONG
#define PinLedInRange_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedInRange_MASK               PinLedInRange__MASK
#define PinLedInRange_SHIFT              PinLedInRange__SHIFT
#define PinLedInRange_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedInRange_PS                     (* (reg8 *) PinLedInRange__PS)
/* Data Register */
#define PinLedInRange_DR                     (* (reg8 *) PinLedInRange__DR)
/* Port Number */
#define PinLedInRange_PRT_NUM                (* (reg8 *) PinLedInRange__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedInRange_AG                     (* (reg8 *) PinLedInRange__AG)                       
/* Analog MUX bux enable */
#define PinLedInRange_AMUX                   (* (reg8 *) PinLedInRange__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedInRange_BIE                    (* (reg8 *) PinLedInRange__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedInRange_BIT_MASK               (* (reg8 *) PinLedInRange__BIT_MASK)
/* Bypass Enable */
#define PinLedInRange_BYP                    (* (reg8 *) PinLedInRange__BYP)
/* Port wide control signals */                                                   
#define PinLedInRange_CTL                    (* (reg8 *) PinLedInRange__CTL)
/* Drive Modes */
#define PinLedInRange_DM0                    (* (reg8 *) PinLedInRange__DM0) 
#define PinLedInRange_DM1                    (* (reg8 *) PinLedInRange__DM1)
#define PinLedInRange_DM2                    (* (reg8 *) PinLedInRange__DM2) 
/* Input Buffer Disable Override */
#define PinLedInRange_INP_DIS                (* (reg8 *) PinLedInRange__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedInRange_LCD_COM_SEG            (* (reg8 *) PinLedInRange__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedInRange_LCD_EN                 (* (reg8 *) PinLedInRange__LCD_EN)
/* Slew Rate Control */
#define PinLedInRange_SLW                    (* (reg8 *) PinLedInRange__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedInRange_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedInRange__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedInRange_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedInRange__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedInRange_PRTDSI__OE_SEL0        (* (reg8 *) PinLedInRange__PRTDSI__OE_SEL0) 
#define PinLedInRange_PRTDSI__OE_SEL1        (* (reg8 *) PinLedInRange__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedInRange_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedInRange__PRTDSI__OUT_SEL0) 
#define PinLedInRange_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedInRange__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedInRange_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedInRange__PRTDSI__SYNC_OUT) 


#if defined(PinLedInRange__INTSTAT)  /* Interrupt Registers */

    #define PinLedInRange_INTSTAT                (* (reg8 *) PinLedInRange__INTSTAT)
    #define PinLedInRange_SNAP                   (* (reg8 *) PinLedInRange__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedInRange_H */

#endif
/* [] END OF FILE */
