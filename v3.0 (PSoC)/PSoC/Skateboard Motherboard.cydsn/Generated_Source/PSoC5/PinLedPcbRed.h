/*******************************************************************************
* File Name: PinLedPcbRed.h  
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

#if !defined(CY_PINS_PinLedPcbRed_H) /* Pins PinLedPcbRed_H */
#define CY_PINS_PinLedPcbRed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedPcbRed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedPcbRed__PORT == 15 && (PinLedPcbRed__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedPcbRed_Write(uint8 value) ;
void    PinLedPcbRed_SetDriveMode(uint8 mode) ;
uint8   PinLedPcbRed_ReadDataReg(void) ;
uint8   PinLedPcbRed_Read(void) ;
uint8   PinLedPcbRed_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedPcbRed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedPcbRed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedPcbRed_DM_RES_UP          PIN_DM_RES_UP
#define PinLedPcbRed_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedPcbRed_DM_OD_LO           PIN_DM_OD_LO
#define PinLedPcbRed_DM_OD_HI           PIN_DM_OD_HI
#define PinLedPcbRed_DM_STRONG          PIN_DM_STRONG
#define PinLedPcbRed_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedPcbRed_MASK               PinLedPcbRed__MASK
#define PinLedPcbRed_SHIFT              PinLedPcbRed__SHIFT
#define PinLedPcbRed_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedPcbRed_PS                     (* (reg8 *) PinLedPcbRed__PS)
/* Data Register */
#define PinLedPcbRed_DR                     (* (reg8 *) PinLedPcbRed__DR)
/* Port Number */
#define PinLedPcbRed_PRT_NUM                (* (reg8 *) PinLedPcbRed__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedPcbRed_AG                     (* (reg8 *) PinLedPcbRed__AG)                       
/* Analog MUX bux enable */
#define PinLedPcbRed_AMUX                   (* (reg8 *) PinLedPcbRed__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedPcbRed_BIE                    (* (reg8 *) PinLedPcbRed__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedPcbRed_BIT_MASK               (* (reg8 *) PinLedPcbRed__BIT_MASK)
/* Bypass Enable */
#define PinLedPcbRed_BYP                    (* (reg8 *) PinLedPcbRed__BYP)
/* Port wide control signals */                                                   
#define PinLedPcbRed_CTL                    (* (reg8 *) PinLedPcbRed__CTL)
/* Drive Modes */
#define PinLedPcbRed_DM0                    (* (reg8 *) PinLedPcbRed__DM0) 
#define PinLedPcbRed_DM1                    (* (reg8 *) PinLedPcbRed__DM1)
#define PinLedPcbRed_DM2                    (* (reg8 *) PinLedPcbRed__DM2) 
/* Input Buffer Disable Override */
#define PinLedPcbRed_INP_DIS                (* (reg8 *) PinLedPcbRed__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedPcbRed_LCD_COM_SEG            (* (reg8 *) PinLedPcbRed__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedPcbRed_LCD_EN                 (* (reg8 *) PinLedPcbRed__LCD_EN)
/* Slew Rate Control */
#define PinLedPcbRed_SLW                    (* (reg8 *) PinLedPcbRed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedPcbRed_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedPcbRed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedPcbRed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedPcbRed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedPcbRed_PRTDSI__OE_SEL0        (* (reg8 *) PinLedPcbRed__PRTDSI__OE_SEL0) 
#define PinLedPcbRed_PRTDSI__OE_SEL1        (* (reg8 *) PinLedPcbRed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedPcbRed_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedPcbRed__PRTDSI__OUT_SEL0) 
#define PinLedPcbRed_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedPcbRed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedPcbRed_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedPcbRed__PRTDSI__SYNC_OUT) 


#if defined(PinLedPcbRed__INTSTAT)  /* Interrupt Registers */

    #define PinLedPcbRed_INTSTAT                (* (reg8 *) PinLedPcbRed__INTSTAT)
    #define PinLedPcbRed_SNAP                   (* (reg8 *) PinLedPcbRed__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedPcbRed_H */

#endif
/* [] END OF FILE */
