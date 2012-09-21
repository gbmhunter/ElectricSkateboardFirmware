/*******************************************************************************
* File Name: PinLightFrontLeft.h  
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

#if !defined(CY_PINS_PinLightFrontLeft_H) /* Pins PinLightFrontLeft_H */
#define CY_PINS_PinLightFrontLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLightFrontLeft_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightFrontLeft__PORT == 15 && (PinLightFrontLeft__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLightFrontLeft_Write(uint8 value) ;
void    PinLightFrontLeft_SetDriveMode(uint8 mode) ;
uint8   PinLightFrontLeft_ReadDataReg(void) ;
uint8   PinLightFrontLeft_Read(void) ;
uint8   PinLightFrontLeft_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLightFrontLeft_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLightFrontLeft_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLightFrontLeft_DM_RES_UP          PIN_DM_RES_UP
#define PinLightFrontLeft_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLightFrontLeft_DM_OD_LO           PIN_DM_OD_LO
#define PinLightFrontLeft_DM_OD_HI           PIN_DM_OD_HI
#define PinLightFrontLeft_DM_STRONG          PIN_DM_STRONG
#define PinLightFrontLeft_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLightFrontLeft_MASK               PinLightFrontLeft__MASK
#define PinLightFrontLeft_SHIFT              PinLightFrontLeft__SHIFT
#define PinLightFrontLeft_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLightFrontLeft_PS                     (* (reg8 *) PinLightFrontLeft__PS)
/* Data Register */
#define PinLightFrontLeft_DR                     (* (reg8 *) PinLightFrontLeft__DR)
/* Port Number */
#define PinLightFrontLeft_PRT_NUM                (* (reg8 *) PinLightFrontLeft__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLightFrontLeft_AG                     (* (reg8 *) PinLightFrontLeft__AG)                       
/* Analog MUX bux enable */
#define PinLightFrontLeft_AMUX                   (* (reg8 *) PinLightFrontLeft__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLightFrontLeft_BIE                    (* (reg8 *) PinLightFrontLeft__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLightFrontLeft_BIT_MASK               (* (reg8 *) PinLightFrontLeft__BIT_MASK)
/* Bypass Enable */
#define PinLightFrontLeft_BYP                    (* (reg8 *) PinLightFrontLeft__BYP)
/* Port wide control signals */                                                   
#define PinLightFrontLeft_CTL                    (* (reg8 *) PinLightFrontLeft__CTL)
/* Drive Modes */
#define PinLightFrontLeft_DM0                    (* (reg8 *) PinLightFrontLeft__DM0) 
#define PinLightFrontLeft_DM1                    (* (reg8 *) PinLightFrontLeft__DM1)
#define PinLightFrontLeft_DM2                    (* (reg8 *) PinLightFrontLeft__DM2) 
/* Input Buffer Disable Override */
#define PinLightFrontLeft_INP_DIS                (* (reg8 *) PinLightFrontLeft__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLightFrontLeft_LCD_COM_SEG            (* (reg8 *) PinLightFrontLeft__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLightFrontLeft_LCD_EN                 (* (reg8 *) PinLightFrontLeft__LCD_EN)
/* Slew Rate Control */
#define PinLightFrontLeft_SLW                    (* (reg8 *) PinLightFrontLeft__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLightFrontLeft_PRTDSI__CAPS_SEL       (* (reg8 *) PinLightFrontLeft__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLightFrontLeft_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLightFrontLeft__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLightFrontLeft_PRTDSI__OE_SEL0        (* (reg8 *) PinLightFrontLeft__PRTDSI__OE_SEL0) 
#define PinLightFrontLeft_PRTDSI__OE_SEL1        (* (reg8 *) PinLightFrontLeft__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLightFrontLeft_PRTDSI__OUT_SEL0       (* (reg8 *) PinLightFrontLeft__PRTDSI__OUT_SEL0) 
#define PinLightFrontLeft_PRTDSI__OUT_SEL1       (* (reg8 *) PinLightFrontLeft__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLightFrontLeft_PRTDSI__SYNC_OUT       (* (reg8 *) PinLightFrontLeft__PRTDSI__SYNC_OUT) 


#if defined(PinLightFrontLeft__INTSTAT)  /* Interrupt Registers */

    #define PinLightFrontLeft_INTSTAT                (* (reg8 *) PinLightFrontLeft__INTSTAT)
    #define PinLightFrontLeft_SNAP                   (* (reg8 *) PinLightFrontLeft__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLightFrontLeft_H */

#endif
/* [] END OF FILE */
