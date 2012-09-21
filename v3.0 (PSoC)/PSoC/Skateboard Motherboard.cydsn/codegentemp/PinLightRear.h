/*******************************************************************************
* File Name: PinLightRear.h  
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

#if !defined(CY_PINS_PinLightRear_H) /* Pins PinLightRear_H */
#define CY_PINS_PinLightRear_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLightRear_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightRear__PORT == 15 && (PinLightRear__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLightRear_Write(uint8 value) ;
void    PinLightRear_SetDriveMode(uint8 mode) ;
uint8   PinLightRear_ReadDataReg(void) ;
uint8   PinLightRear_Read(void) ;
uint8   PinLightRear_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLightRear_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLightRear_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLightRear_DM_RES_UP          PIN_DM_RES_UP
#define PinLightRear_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLightRear_DM_OD_LO           PIN_DM_OD_LO
#define PinLightRear_DM_OD_HI           PIN_DM_OD_HI
#define PinLightRear_DM_STRONG          PIN_DM_STRONG
#define PinLightRear_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLightRear_MASK               PinLightRear__MASK
#define PinLightRear_SHIFT              PinLightRear__SHIFT
#define PinLightRear_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLightRear_PS                     (* (reg8 *) PinLightRear__PS)
/* Data Register */
#define PinLightRear_DR                     (* (reg8 *) PinLightRear__DR)
/* Port Number */
#define PinLightRear_PRT_NUM                (* (reg8 *) PinLightRear__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLightRear_AG                     (* (reg8 *) PinLightRear__AG)                       
/* Analog MUX bux enable */
#define PinLightRear_AMUX                   (* (reg8 *) PinLightRear__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLightRear_BIE                    (* (reg8 *) PinLightRear__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLightRear_BIT_MASK               (* (reg8 *) PinLightRear__BIT_MASK)
/* Bypass Enable */
#define PinLightRear_BYP                    (* (reg8 *) PinLightRear__BYP)
/* Port wide control signals */                                                   
#define PinLightRear_CTL                    (* (reg8 *) PinLightRear__CTL)
/* Drive Modes */
#define PinLightRear_DM0                    (* (reg8 *) PinLightRear__DM0) 
#define PinLightRear_DM1                    (* (reg8 *) PinLightRear__DM1)
#define PinLightRear_DM2                    (* (reg8 *) PinLightRear__DM2) 
/* Input Buffer Disable Override */
#define PinLightRear_INP_DIS                (* (reg8 *) PinLightRear__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLightRear_LCD_COM_SEG            (* (reg8 *) PinLightRear__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLightRear_LCD_EN                 (* (reg8 *) PinLightRear__LCD_EN)
/* Slew Rate Control */
#define PinLightRear_SLW                    (* (reg8 *) PinLightRear__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLightRear_PRTDSI__CAPS_SEL       (* (reg8 *) PinLightRear__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLightRear_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLightRear__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLightRear_PRTDSI__OE_SEL0        (* (reg8 *) PinLightRear__PRTDSI__OE_SEL0) 
#define PinLightRear_PRTDSI__OE_SEL1        (* (reg8 *) PinLightRear__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLightRear_PRTDSI__OUT_SEL0       (* (reg8 *) PinLightRear__PRTDSI__OUT_SEL0) 
#define PinLightRear_PRTDSI__OUT_SEL1       (* (reg8 *) PinLightRear__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLightRear_PRTDSI__SYNC_OUT       (* (reg8 *) PinLightRear__PRTDSI__SYNC_OUT) 


#if defined(PinLightRear__INTSTAT)  /* Interrupt Registers */

    #define PinLightRear_INTSTAT                (* (reg8 *) PinLightRear__INTSTAT)
    #define PinLightRear_SNAP                   (* (reg8 *) PinLightRear__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLightRear_H */

#endif
/* [] END OF FILE */
