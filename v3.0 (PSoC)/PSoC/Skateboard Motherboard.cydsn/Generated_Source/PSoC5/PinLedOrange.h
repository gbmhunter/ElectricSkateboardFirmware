/*******************************************************************************
* File Name: PinLedOrange.h  
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

#if !defined(CY_PINS_PinLedOrange_H) /* Pins PinLedOrange_H */
#define CY_PINS_PinLedOrange_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedOrange_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedOrange__PORT == 15 && (PinLedOrange__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedOrange_Write(uint8 value) ;
void    PinLedOrange_SetDriveMode(uint8 mode) ;
uint8   PinLedOrange_ReadDataReg(void) ;
uint8   PinLedOrange_Read(void) ;
uint8   PinLedOrange_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedOrange_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedOrange_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedOrange_DM_RES_UP          PIN_DM_RES_UP
#define PinLedOrange_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedOrange_DM_OD_LO           PIN_DM_OD_LO
#define PinLedOrange_DM_OD_HI           PIN_DM_OD_HI
#define PinLedOrange_DM_STRONG          PIN_DM_STRONG
#define PinLedOrange_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedOrange_MASK               PinLedOrange__MASK
#define PinLedOrange_SHIFT              PinLedOrange__SHIFT
#define PinLedOrange_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedOrange_PS                     (* (reg8 *) PinLedOrange__PS)
/* Data Register */
#define PinLedOrange_DR                     (* (reg8 *) PinLedOrange__DR)
/* Port Number */
#define PinLedOrange_PRT_NUM                (* (reg8 *) PinLedOrange__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedOrange_AG                     (* (reg8 *) PinLedOrange__AG)                       
/* Analog MUX bux enable */
#define PinLedOrange_AMUX                   (* (reg8 *) PinLedOrange__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedOrange_BIE                    (* (reg8 *) PinLedOrange__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedOrange_BIT_MASK               (* (reg8 *) PinLedOrange__BIT_MASK)
/* Bypass Enable */
#define PinLedOrange_BYP                    (* (reg8 *) PinLedOrange__BYP)
/* Port wide control signals */                                                   
#define PinLedOrange_CTL                    (* (reg8 *) PinLedOrange__CTL)
/* Drive Modes */
#define PinLedOrange_DM0                    (* (reg8 *) PinLedOrange__DM0) 
#define PinLedOrange_DM1                    (* (reg8 *) PinLedOrange__DM1)
#define PinLedOrange_DM2                    (* (reg8 *) PinLedOrange__DM2) 
/* Input Buffer Disable Override */
#define PinLedOrange_INP_DIS                (* (reg8 *) PinLedOrange__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedOrange_LCD_COM_SEG            (* (reg8 *) PinLedOrange__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedOrange_LCD_EN                 (* (reg8 *) PinLedOrange__LCD_EN)
/* Slew Rate Control */
#define PinLedOrange_SLW                    (* (reg8 *) PinLedOrange__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedOrange_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedOrange__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedOrange_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedOrange__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedOrange_PRTDSI__OE_SEL0        (* (reg8 *) PinLedOrange__PRTDSI__OE_SEL0) 
#define PinLedOrange_PRTDSI__OE_SEL1        (* (reg8 *) PinLedOrange__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedOrange_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedOrange__PRTDSI__OUT_SEL0) 
#define PinLedOrange_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedOrange__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedOrange_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedOrange__PRTDSI__SYNC_OUT) 


#if defined(PinLedOrange__INTSTAT)  /* Interrupt Registers */

    #define PinLedOrange_INTSTAT                (* (reg8 *) PinLedOrange__INTSTAT)
    #define PinLedOrange_SNAP                   (* (reg8 *) PinLedOrange__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedOrange_H */

#endif
/* [] END OF FILE */
