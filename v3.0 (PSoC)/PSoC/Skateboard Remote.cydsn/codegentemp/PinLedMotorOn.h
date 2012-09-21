/*******************************************************************************
* File Name: PinLedMotorOn.h  
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

#if !defined(CY_PINS_PinLedMotorOn_H) /* Pins PinLedMotorOn_H */
#define CY_PINS_PinLedMotorOn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedMotorOn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedMotorOn__PORT == 15 && (PinLedMotorOn__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedMotorOn_Write(uint8 value) ;
void    PinLedMotorOn_SetDriveMode(uint8 mode) ;
uint8   PinLedMotorOn_ReadDataReg(void) ;
uint8   PinLedMotorOn_Read(void) ;
uint8   PinLedMotorOn_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedMotorOn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedMotorOn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedMotorOn_DM_RES_UP          PIN_DM_RES_UP
#define PinLedMotorOn_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedMotorOn_DM_OD_LO           PIN_DM_OD_LO
#define PinLedMotorOn_DM_OD_HI           PIN_DM_OD_HI
#define PinLedMotorOn_DM_STRONG          PIN_DM_STRONG
#define PinLedMotorOn_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedMotorOn_MASK               PinLedMotorOn__MASK
#define PinLedMotorOn_SHIFT              PinLedMotorOn__SHIFT
#define PinLedMotorOn_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedMotorOn_PS                     (* (reg8 *) PinLedMotorOn__PS)
/* Data Register */
#define PinLedMotorOn_DR                     (* (reg8 *) PinLedMotorOn__DR)
/* Port Number */
#define PinLedMotorOn_PRT_NUM                (* (reg8 *) PinLedMotorOn__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedMotorOn_AG                     (* (reg8 *) PinLedMotorOn__AG)                       
/* Analog MUX bux enable */
#define PinLedMotorOn_AMUX                   (* (reg8 *) PinLedMotorOn__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedMotorOn_BIE                    (* (reg8 *) PinLedMotorOn__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedMotorOn_BIT_MASK               (* (reg8 *) PinLedMotorOn__BIT_MASK)
/* Bypass Enable */
#define PinLedMotorOn_BYP                    (* (reg8 *) PinLedMotorOn__BYP)
/* Port wide control signals */                                                   
#define PinLedMotorOn_CTL                    (* (reg8 *) PinLedMotorOn__CTL)
/* Drive Modes */
#define PinLedMotorOn_DM0                    (* (reg8 *) PinLedMotorOn__DM0) 
#define PinLedMotorOn_DM1                    (* (reg8 *) PinLedMotorOn__DM1)
#define PinLedMotorOn_DM2                    (* (reg8 *) PinLedMotorOn__DM2) 
/* Input Buffer Disable Override */
#define PinLedMotorOn_INP_DIS                (* (reg8 *) PinLedMotorOn__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedMotorOn_LCD_COM_SEG            (* (reg8 *) PinLedMotorOn__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedMotorOn_LCD_EN                 (* (reg8 *) PinLedMotorOn__LCD_EN)
/* Slew Rate Control */
#define PinLedMotorOn_SLW                    (* (reg8 *) PinLedMotorOn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedMotorOn_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedMotorOn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedMotorOn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedMotorOn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedMotorOn_PRTDSI__OE_SEL0        (* (reg8 *) PinLedMotorOn__PRTDSI__OE_SEL0) 
#define PinLedMotorOn_PRTDSI__OE_SEL1        (* (reg8 *) PinLedMotorOn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedMotorOn_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedMotorOn__PRTDSI__OUT_SEL0) 
#define PinLedMotorOn_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedMotorOn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedMotorOn_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedMotorOn__PRTDSI__SYNC_OUT) 


#if defined(PinLedMotorOn__INTSTAT)  /* Interrupt Registers */

    #define PinLedMotorOn_INTSTAT                (* (reg8 *) PinLedMotorOn__INTSTAT)
    #define PinLedMotorOn_SNAP                   (* (reg8 *) PinLedMotorOn__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedMotorOn_H */

#endif
/* [] END OF FILE */
