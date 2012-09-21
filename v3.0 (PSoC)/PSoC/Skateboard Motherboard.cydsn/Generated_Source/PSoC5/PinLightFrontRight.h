/*******************************************************************************
* File Name: PinLightFrontRight.h  
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

#if !defined(CY_PINS_PinLightFrontRight_H) /* Pins PinLightFrontRight_H */
#define CY_PINS_PinLightFrontRight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLightFrontRight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightFrontRight__PORT == 15 && (PinLightFrontRight__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLightFrontRight_Write(uint8 value) ;
void    PinLightFrontRight_SetDriveMode(uint8 mode) ;
uint8   PinLightFrontRight_ReadDataReg(void) ;
uint8   PinLightFrontRight_Read(void) ;
uint8   PinLightFrontRight_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLightFrontRight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLightFrontRight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLightFrontRight_DM_RES_UP          PIN_DM_RES_UP
#define PinLightFrontRight_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLightFrontRight_DM_OD_LO           PIN_DM_OD_LO
#define PinLightFrontRight_DM_OD_HI           PIN_DM_OD_HI
#define PinLightFrontRight_DM_STRONG          PIN_DM_STRONG
#define PinLightFrontRight_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLightFrontRight_MASK               PinLightFrontRight__MASK
#define PinLightFrontRight_SHIFT              PinLightFrontRight__SHIFT
#define PinLightFrontRight_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLightFrontRight_PS                     (* (reg8 *) PinLightFrontRight__PS)
/* Data Register */
#define PinLightFrontRight_DR                     (* (reg8 *) PinLightFrontRight__DR)
/* Port Number */
#define PinLightFrontRight_PRT_NUM                (* (reg8 *) PinLightFrontRight__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLightFrontRight_AG                     (* (reg8 *) PinLightFrontRight__AG)                       
/* Analog MUX bux enable */
#define PinLightFrontRight_AMUX                   (* (reg8 *) PinLightFrontRight__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLightFrontRight_BIE                    (* (reg8 *) PinLightFrontRight__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLightFrontRight_BIT_MASK               (* (reg8 *) PinLightFrontRight__BIT_MASK)
/* Bypass Enable */
#define PinLightFrontRight_BYP                    (* (reg8 *) PinLightFrontRight__BYP)
/* Port wide control signals */                                                   
#define PinLightFrontRight_CTL                    (* (reg8 *) PinLightFrontRight__CTL)
/* Drive Modes */
#define PinLightFrontRight_DM0                    (* (reg8 *) PinLightFrontRight__DM0) 
#define PinLightFrontRight_DM1                    (* (reg8 *) PinLightFrontRight__DM1)
#define PinLightFrontRight_DM2                    (* (reg8 *) PinLightFrontRight__DM2) 
/* Input Buffer Disable Override */
#define PinLightFrontRight_INP_DIS                (* (reg8 *) PinLightFrontRight__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLightFrontRight_LCD_COM_SEG            (* (reg8 *) PinLightFrontRight__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLightFrontRight_LCD_EN                 (* (reg8 *) PinLightFrontRight__LCD_EN)
/* Slew Rate Control */
#define PinLightFrontRight_SLW                    (* (reg8 *) PinLightFrontRight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLightFrontRight_PRTDSI__CAPS_SEL       (* (reg8 *) PinLightFrontRight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLightFrontRight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLightFrontRight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLightFrontRight_PRTDSI__OE_SEL0        (* (reg8 *) PinLightFrontRight__PRTDSI__OE_SEL0) 
#define PinLightFrontRight_PRTDSI__OE_SEL1        (* (reg8 *) PinLightFrontRight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLightFrontRight_PRTDSI__OUT_SEL0       (* (reg8 *) PinLightFrontRight__PRTDSI__OUT_SEL0) 
#define PinLightFrontRight_PRTDSI__OUT_SEL1       (* (reg8 *) PinLightFrontRight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLightFrontRight_PRTDSI__SYNC_OUT       (* (reg8 *) PinLightFrontRight__PRTDSI__SYNC_OUT) 


#if defined(PinLightFrontRight__INTSTAT)  /* Interrupt Registers */

    #define PinLightFrontRight_INTSTAT                (* (reg8 *) PinLightFrontRight__INTSTAT)
    #define PinLightFrontRight_SNAP                   (* (reg8 *) PinLightFrontRight__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLightFrontRight_H */

#endif
/* [] END OF FILE */
