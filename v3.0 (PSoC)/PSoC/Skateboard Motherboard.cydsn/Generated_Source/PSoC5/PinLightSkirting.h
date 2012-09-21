/*******************************************************************************
* File Name: PinLightSkirting.h  
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

#if !defined(CY_PINS_PinLightSkirting_H) /* Pins PinLightSkirting_H */
#define CY_PINS_PinLightSkirting_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLightSkirting_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightSkirting__PORT == 15 && (PinLightSkirting__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLightSkirting_Write(uint8 value) ;
void    PinLightSkirting_SetDriveMode(uint8 mode) ;
uint8   PinLightSkirting_ReadDataReg(void) ;
uint8   PinLightSkirting_Read(void) ;
uint8   PinLightSkirting_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLightSkirting_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLightSkirting_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLightSkirting_DM_RES_UP          PIN_DM_RES_UP
#define PinLightSkirting_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLightSkirting_DM_OD_LO           PIN_DM_OD_LO
#define PinLightSkirting_DM_OD_HI           PIN_DM_OD_HI
#define PinLightSkirting_DM_STRONG          PIN_DM_STRONG
#define PinLightSkirting_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLightSkirting_MASK               PinLightSkirting__MASK
#define PinLightSkirting_SHIFT              PinLightSkirting__SHIFT
#define PinLightSkirting_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLightSkirting_PS                     (* (reg8 *) PinLightSkirting__PS)
/* Data Register */
#define PinLightSkirting_DR                     (* (reg8 *) PinLightSkirting__DR)
/* Port Number */
#define PinLightSkirting_PRT_NUM                (* (reg8 *) PinLightSkirting__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLightSkirting_AG                     (* (reg8 *) PinLightSkirting__AG)                       
/* Analog MUX bux enable */
#define PinLightSkirting_AMUX                   (* (reg8 *) PinLightSkirting__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLightSkirting_BIE                    (* (reg8 *) PinLightSkirting__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLightSkirting_BIT_MASK               (* (reg8 *) PinLightSkirting__BIT_MASK)
/* Bypass Enable */
#define PinLightSkirting_BYP                    (* (reg8 *) PinLightSkirting__BYP)
/* Port wide control signals */                                                   
#define PinLightSkirting_CTL                    (* (reg8 *) PinLightSkirting__CTL)
/* Drive Modes */
#define PinLightSkirting_DM0                    (* (reg8 *) PinLightSkirting__DM0) 
#define PinLightSkirting_DM1                    (* (reg8 *) PinLightSkirting__DM1)
#define PinLightSkirting_DM2                    (* (reg8 *) PinLightSkirting__DM2) 
/* Input Buffer Disable Override */
#define PinLightSkirting_INP_DIS                (* (reg8 *) PinLightSkirting__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLightSkirting_LCD_COM_SEG            (* (reg8 *) PinLightSkirting__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLightSkirting_LCD_EN                 (* (reg8 *) PinLightSkirting__LCD_EN)
/* Slew Rate Control */
#define PinLightSkirting_SLW                    (* (reg8 *) PinLightSkirting__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLightSkirting_PRTDSI__CAPS_SEL       (* (reg8 *) PinLightSkirting__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLightSkirting_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLightSkirting__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLightSkirting_PRTDSI__OE_SEL0        (* (reg8 *) PinLightSkirting__PRTDSI__OE_SEL0) 
#define PinLightSkirting_PRTDSI__OE_SEL1        (* (reg8 *) PinLightSkirting__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLightSkirting_PRTDSI__OUT_SEL0       (* (reg8 *) PinLightSkirting__PRTDSI__OUT_SEL0) 
#define PinLightSkirting_PRTDSI__OUT_SEL1       (* (reg8 *) PinLightSkirting__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLightSkirting_PRTDSI__SYNC_OUT       (* (reg8 *) PinLightSkirting__PRTDSI__SYNC_OUT) 


#if defined(PinLightSkirting__INTSTAT)  /* Interrupt Registers */

    #define PinLightSkirting_INTSTAT                (* (reg8 *) PinLightSkirting__INTSTAT)
    #define PinLightSkirting_SNAP                   (* (reg8 *) PinLightSkirting__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLightSkirting_H */

#endif
/* [] END OF FILE */
