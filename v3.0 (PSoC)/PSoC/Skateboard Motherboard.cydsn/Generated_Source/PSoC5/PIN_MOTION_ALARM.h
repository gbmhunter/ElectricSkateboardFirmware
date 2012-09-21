/*******************************************************************************
* File Name: PIN_MOTION_ALARM.h  
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

#if !defined(CY_PINS_PIN_MOTION_ALARM_H) /* Pins PIN_MOTION_ALARM_H */
#define CY_PINS_PIN_MOTION_ALARM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PIN_MOTION_ALARM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PIN_MOTION_ALARM__PORT == 15 && (PIN_MOTION_ALARM__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_MOTION_ALARM_Write(uint8 value) ;
void    PIN_MOTION_ALARM_SetDriveMode(uint8 mode) ;
uint8   PIN_MOTION_ALARM_ReadDataReg(void) ;
uint8   PIN_MOTION_ALARM_Read(void) ;
uint8   PIN_MOTION_ALARM_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_MOTION_ALARM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PIN_MOTION_ALARM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PIN_MOTION_ALARM_DM_RES_UP          PIN_DM_RES_UP
#define PIN_MOTION_ALARM_DM_RES_DWN         PIN_DM_RES_DWN
#define PIN_MOTION_ALARM_DM_OD_LO           PIN_DM_OD_LO
#define PIN_MOTION_ALARM_DM_OD_HI           PIN_DM_OD_HI
#define PIN_MOTION_ALARM_DM_STRONG          PIN_DM_STRONG
#define PIN_MOTION_ALARM_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PIN_MOTION_ALARM_MASK               PIN_MOTION_ALARM__MASK
#define PIN_MOTION_ALARM_SHIFT              PIN_MOTION_ALARM__SHIFT
#define PIN_MOTION_ALARM_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_MOTION_ALARM_PS                     (* (reg8 *) PIN_MOTION_ALARM__PS)
/* Data Register */
#define PIN_MOTION_ALARM_DR                     (* (reg8 *) PIN_MOTION_ALARM__DR)
/* Port Number */
#define PIN_MOTION_ALARM_PRT_NUM                (* (reg8 *) PIN_MOTION_ALARM__PRT) 
/* Connect to Analog Globals */                                                  
#define PIN_MOTION_ALARM_AG                     (* (reg8 *) PIN_MOTION_ALARM__AG)                       
/* Analog MUX bux enable */
#define PIN_MOTION_ALARM_AMUX                   (* (reg8 *) PIN_MOTION_ALARM__AMUX) 
/* Bidirectional Enable */                                                        
#define PIN_MOTION_ALARM_BIE                    (* (reg8 *) PIN_MOTION_ALARM__BIE)
/* Bit-mask for Aliased Register Access */
#define PIN_MOTION_ALARM_BIT_MASK               (* (reg8 *) PIN_MOTION_ALARM__BIT_MASK)
/* Bypass Enable */
#define PIN_MOTION_ALARM_BYP                    (* (reg8 *) PIN_MOTION_ALARM__BYP)
/* Port wide control signals */                                                   
#define PIN_MOTION_ALARM_CTL                    (* (reg8 *) PIN_MOTION_ALARM__CTL)
/* Drive Modes */
#define PIN_MOTION_ALARM_DM0                    (* (reg8 *) PIN_MOTION_ALARM__DM0) 
#define PIN_MOTION_ALARM_DM1                    (* (reg8 *) PIN_MOTION_ALARM__DM1)
#define PIN_MOTION_ALARM_DM2                    (* (reg8 *) PIN_MOTION_ALARM__DM2) 
/* Input Buffer Disable Override */
#define PIN_MOTION_ALARM_INP_DIS                (* (reg8 *) PIN_MOTION_ALARM__INP_DIS)
/* LCD Common or Segment Drive */
#define PIN_MOTION_ALARM_LCD_COM_SEG            (* (reg8 *) PIN_MOTION_ALARM__LCD_COM_SEG)
/* Enable Segment LCD */
#define PIN_MOTION_ALARM_LCD_EN                 (* (reg8 *) PIN_MOTION_ALARM__LCD_EN)
/* Slew Rate Control */
#define PIN_MOTION_ALARM_SLW                    (* (reg8 *) PIN_MOTION_ALARM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PIN_MOTION_ALARM_PRTDSI__CAPS_SEL       (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PIN_MOTION_ALARM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PIN_MOTION_ALARM_PRTDSI__OE_SEL0        (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__OE_SEL0) 
#define PIN_MOTION_ALARM_PRTDSI__OE_SEL1        (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PIN_MOTION_ALARM_PRTDSI__OUT_SEL0       (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__OUT_SEL0) 
#define PIN_MOTION_ALARM_PRTDSI__OUT_SEL1       (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PIN_MOTION_ALARM_PRTDSI__SYNC_OUT       (* (reg8 *) PIN_MOTION_ALARM__PRTDSI__SYNC_OUT) 


#if defined(PIN_MOTION_ALARM__INTSTAT)  /* Interrupt Registers */

    #define PIN_MOTION_ALARM_INTSTAT                (* (reg8 *) PIN_MOTION_ALARM__INTSTAT)
    #define PIN_MOTION_ALARM_SNAP                   (* (reg8 *) PIN_MOTION_ALARM__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PIN_MOTION_ALARM_H */

#endif
/* [] END OF FILE */
