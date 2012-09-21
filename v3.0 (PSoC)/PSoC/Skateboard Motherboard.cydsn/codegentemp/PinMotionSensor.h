/*******************************************************************************
* File Name: PinMotionSensor.h  
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

#if !defined(CY_PINS_PinMotionSensor_H) /* Pins PinMotionSensor_H */
#define CY_PINS_PinMotionSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinMotionSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinMotionSensor__PORT == 15 && (PinMotionSensor__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinMotionSensor_Write(uint8 value) ;
void    PinMotionSensor_SetDriveMode(uint8 mode) ;
uint8   PinMotionSensor_ReadDataReg(void) ;
uint8   PinMotionSensor_Read(void) ;
uint8   PinMotionSensor_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinMotionSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinMotionSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinMotionSensor_DM_RES_UP          PIN_DM_RES_UP
#define PinMotionSensor_DM_RES_DWN         PIN_DM_RES_DWN
#define PinMotionSensor_DM_OD_LO           PIN_DM_OD_LO
#define PinMotionSensor_DM_OD_HI           PIN_DM_OD_HI
#define PinMotionSensor_DM_STRONG          PIN_DM_STRONG
#define PinMotionSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinMotionSensor_MASK               PinMotionSensor__MASK
#define PinMotionSensor_SHIFT              PinMotionSensor__SHIFT
#define PinMotionSensor_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinMotionSensor_PS                     (* (reg8 *) PinMotionSensor__PS)
/* Data Register */
#define PinMotionSensor_DR                     (* (reg8 *) PinMotionSensor__DR)
/* Port Number */
#define PinMotionSensor_PRT_NUM                (* (reg8 *) PinMotionSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define PinMotionSensor_AG                     (* (reg8 *) PinMotionSensor__AG)                       
/* Analog MUX bux enable */
#define PinMotionSensor_AMUX                   (* (reg8 *) PinMotionSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define PinMotionSensor_BIE                    (* (reg8 *) PinMotionSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define PinMotionSensor_BIT_MASK               (* (reg8 *) PinMotionSensor__BIT_MASK)
/* Bypass Enable */
#define PinMotionSensor_BYP                    (* (reg8 *) PinMotionSensor__BYP)
/* Port wide control signals */                                                   
#define PinMotionSensor_CTL                    (* (reg8 *) PinMotionSensor__CTL)
/* Drive Modes */
#define PinMotionSensor_DM0                    (* (reg8 *) PinMotionSensor__DM0) 
#define PinMotionSensor_DM1                    (* (reg8 *) PinMotionSensor__DM1)
#define PinMotionSensor_DM2                    (* (reg8 *) PinMotionSensor__DM2) 
/* Input Buffer Disable Override */
#define PinMotionSensor_INP_DIS                (* (reg8 *) PinMotionSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define PinMotionSensor_LCD_COM_SEG            (* (reg8 *) PinMotionSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinMotionSensor_LCD_EN                 (* (reg8 *) PinMotionSensor__LCD_EN)
/* Slew Rate Control */
#define PinMotionSensor_SLW                    (* (reg8 *) PinMotionSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinMotionSensor_PRTDSI__CAPS_SEL       (* (reg8 *) PinMotionSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinMotionSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinMotionSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinMotionSensor_PRTDSI__OE_SEL0        (* (reg8 *) PinMotionSensor__PRTDSI__OE_SEL0) 
#define PinMotionSensor_PRTDSI__OE_SEL1        (* (reg8 *) PinMotionSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinMotionSensor_PRTDSI__OUT_SEL0       (* (reg8 *) PinMotionSensor__PRTDSI__OUT_SEL0) 
#define PinMotionSensor_PRTDSI__OUT_SEL1       (* (reg8 *) PinMotionSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinMotionSensor_PRTDSI__SYNC_OUT       (* (reg8 *) PinMotionSensor__PRTDSI__SYNC_OUT) 


#if defined(PinMotionSensor__INTSTAT)  /* Interrupt Registers */

    #define PinMotionSensor_INTSTAT                (* (reg8 *) PinMotionSensor__INTSTAT)
    #define PinMotionSensor_SNAP                   (* (reg8 *) PinMotionSensor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinMotionSensor_H */

#endif
/* [] END OF FILE */
