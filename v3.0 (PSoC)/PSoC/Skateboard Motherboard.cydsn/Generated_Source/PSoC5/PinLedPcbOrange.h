/*******************************************************************************
* File Name: PinLedPcbOrange.h  
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

#if !defined(CY_PINS_PinLedPcbOrange_H) /* Pins PinLedPcbOrange_H */
#define CY_PINS_PinLedPcbOrange_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedPcbOrange_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedPcbOrange__PORT == 15 && (PinLedPcbOrange__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedPcbOrange_Write(uint8 value) ;
void    PinLedPcbOrange_SetDriveMode(uint8 mode) ;
uint8   PinLedPcbOrange_ReadDataReg(void) ;
uint8   PinLedPcbOrange_Read(void) ;
uint8   PinLedPcbOrange_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedPcbOrange_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedPcbOrange_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedPcbOrange_DM_RES_UP          PIN_DM_RES_UP
#define PinLedPcbOrange_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedPcbOrange_DM_OD_LO           PIN_DM_OD_LO
#define PinLedPcbOrange_DM_OD_HI           PIN_DM_OD_HI
#define PinLedPcbOrange_DM_STRONG          PIN_DM_STRONG
#define PinLedPcbOrange_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedPcbOrange_MASK               PinLedPcbOrange__MASK
#define PinLedPcbOrange_SHIFT              PinLedPcbOrange__SHIFT
#define PinLedPcbOrange_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedPcbOrange_PS                     (* (reg8 *) PinLedPcbOrange__PS)
/* Data Register */
#define PinLedPcbOrange_DR                     (* (reg8 *) PinLedPcbOrange__DR)
/* Port Number */
#define PinLedPcbOrange_PRT_NUM                (* (reg8 *) PinLedPcbOrange__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedPcbOrange_AG                     (* (reg8 *) PinLedPcbOrange__AG)                       
/* Analog MUX bux enable */
#define PinLedPcbOrange_AMUX                   (* (reg8 *) PinLedPcbOrange__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedPcbOrange_BIE                    (* (reg8 *) PinLedPcbOrange__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedPcbOrange_BIT_MASK               (* (reg8 *) PinLedPcbOrange__BIT_MASK)
/* Bypass Enable */
#define PinLedPcbOrange_BYP                    (* (reg8 *) PinLedPcbOrange__BYP)
/* Port wide control signals */                                                   
#define PinLedPcbOrange_CTL                    (* (reg8 *) PinLedPcbOrange__CTL)
/* Drive Modes */
#define PinLedPcbOrange_DM0                    (* (reg8 *) PinLedPcbOrange__DM0) 
#define PinLedPcbOrange_DM1                    (* (reg8 *) PinLedPcbOrange__DM1)
#define PinLedPcbOrange_DM2                    (* (reg8 *) PinLedPcbOrange__DM2) 
/* Input Buffer Disable Override */
#define PinLedPcbOrange_INP_DIS                (* (reg8 *) PinLedPcbOrange__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedPcbOrange_LCD_COM_SEG            (* (reg8 *) PinLedPcbOrange__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedPcbOrange_LCD_EN                 (* (reg8 *) PinLedPcbOrange__LCD_EN)
/* Slew Rate Control */
#define PinLedPcbOrange_SLW                    (* (reg8 *) PinLedPcbOrange__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedPcbOrange_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedPcbOrange__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedPcbOrange_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedPcbOrange__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedPcbOrange_PRTDSI__OE_SEL0        (* (reg8 *) PinLedPcbOrange__PRTDSI__OE_SEL0) 
#define PinLedPcbOrange_PRTDSI__OE_SEL1        (* (reg8 *) PinLedPcbOrange__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedPcbOrange_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedPcbOrange__PRTDSI__OUT_SEL0) 
#define PinLedPcbOrange_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedPcbOrange__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedPcbOrange_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedPcbOrange__PRTDSI__SYNC_OUT) 


#if defined(PinLedPcbOrange__INTSTAT)  /* Interrupt Registers */

    #define PinLedPcbOrange_INTSTAT                (* (reg8 *) PinLedPcbOrange__INTSTAT)
    #define PinLedPcbOrange_SNAP                   (* (reg8 *) PinLedPcbOrange__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedPcbOrange_H */

#endif
/* [] END OF FILE */
