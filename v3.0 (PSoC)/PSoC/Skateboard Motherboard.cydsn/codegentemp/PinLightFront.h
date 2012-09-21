/*******************************************************************************
* File Name: PinLightFront.h  
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

#if !defined(CY_PINS_PinLightFront_H) /* Pins PinLightFront_H */
#define CY_PINS_PinLightFront_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLightFront_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightFront__PORT == 15 && (PinLightFront__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLightFront_Write(uint8 value) ;
void    PinLightFront_SetDriveMode(uint8 mode) ;
uint8   PinLightFront_ReadDataReg(void) ;
uint8   PinLightFront_Read(void) ;
uint8   PinLightFront_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLightFront_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLightFront_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLightFront_DM_RES_UP          PIN_DM_RES_UP
#define PinLightFront_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLightFront_DM_OD_LO           PIN_DM_OD_LO
#define PinLightFront_DM_OD_HI           PIN_DM_OD_HI
#define PinLightFront_DM_STRONG          PIN_DM_STRONG
#define PinLightFront_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLightFront_MASK               PinLightFront__MASK
#define PinLightFront_SHIFT              PinLightFront__SHIFT
#define PinLightFront_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLightFront_PS                     (* (reg8 *) PinLightFront__PS)
/* Data Register */
#define PinLightFront_DR                     (* (reg8 *) PinLightFront__DR)
/* Port Number */
#define PinLightFront_PRT_NUM                (* (reg8 *) PinLightFront__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLightFront_AG                     (* (reg8 *) PinLightFront__AG)                       
/* Analog MUX bux enable */
#define PinLightFront_AMUX                   (* (reg8 *) PinLightFront__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLightFront_BIE                    (* (reg8 *) PinLightFront__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLightFront_BIT_MASK               (* (reg8 *) PinLightFront__BIT_MASK)
/* Bypass Enable */
#define PinLightFront_BYP                    (* (reg8 *) PinLightFront__BYP)
/* Port wide control signals */                                                   
#define PinLightFront_CTL                    (* (reg8 *) PinLightFront__CTL)
/* Drive Modes */
#define PinLightFront_DM0                    (* (reg8 *) PinLightFront__DM0) 
#define PinLightFront_DM1                    (* (reg8 *) PinLightFront__DM1)
#define PinLightFront_DM2                    (* (reg8 *) PinLightFront__DM2) 
/* Input Buffer Disable Override */
#define PinLightFront_INP_DIS                (* (reg8 *) PinLightFront__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLightFront_LCD_COM_SEG            (* (reg8 *) PinLightFront__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLightFront_LCD_EN                 (* (reg8 *) PinLightFront__LCD_EN)
/* Slew Rate Control */
#define PinLightFront_SLW                    (* (reg8 *) PinLightFront__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLightFront_PRTDSI__CAPS_SEL       (* (reg8 *) PinLightFront__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLightFront_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLightFront__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLightFront_PRTDSI__OE_SEL0        (* (reg8 *) PinLightFront__PRTDSI__OE_SEL0) 
#define PinLightFront_PRTDSI__OE_SEL1        (* (reg8 *) PinLightFront__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLightFront_PRTDSI__OUT_SEL0       (* (reg8 *) PinLightFront__PRTDSI__OUT_SEL0) 
#define PinLightFront_PRTDSI__OUT_SEL1       (* (reg8 *) PinLightFront__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLightFront_PRTDSI__SYNC_OUT       (* (reg8 *) PinLightFront__PRTDSI__SYNC_OUT) 


#if defined(PinLightFront__INTSTAT)  /* Interrupt Registers */

    #define PinLightFront_INTSTAT                (* (reg8 *) PinLightFront__INTSTAT)
    #define PinLightFront_SNAP                   (* (reg8 *) PinLightFront__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLightFront_H */

#endif
/* [] END OF FILE */
