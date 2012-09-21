/*******************************************************************************
* File Name: PIN_PIEZO_PWM1.h  
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

#if !defined(CY_PINS_PIN_PIEZO_PWM1_H) /* Pins PIN_PIEZO_PWM1_H */
#define CY_PINS_PIN_PIEZO_PWM1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PIN_PIEZO_PWM1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PIN_PIEZO_PWM1__PORT == 15 && (PIN_PIEZO_PWM1__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_PIEZO_PWM1_Write(uint8 value) ;
void    PIN_PIEZO_PWM1_SetDriveMode(uint8 mode) ;
uint8   PIN_PIEZO_PWM1_ReadDataReg(void) ;
uint8   PIN_PIEZO_PWM1_Read(void) ;
uint8   PIN_PIEZO_PWM1_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_PIEZO_PWM1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PIN_PIEZO_PWM1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PIN_PIEZO_PWM1_DM_RES_UP          PIN_DM_RES_UP
#define PIN_PIEZO_PWM1_DM_RES_DWN         PIN_DM_RES_DWN
#define PIN_PIEZO_PWM1_DM_OD_LO           PIN_DM_OD_LO
#define PIN_PIEZO_PWM1_DM_OD_HI           PIN_DM_OD_HI
#define PIN_PIEZO_PWM1_DM_STRONG          PIN_DM_STRONG
#define PIN_PIEZO_PWM1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PIN_PIEZO_PWM1_MASK               PIN_PIEZO_PWM1__MASK
#define PIN_PIEZO_PWM1_SHIFT              PIN_PIEZO_PWM1__SHIFT
#define PIN_PIEZO_PWM1_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_PIEZO_PWM1_PS                     (* (reg8 *) PIN_PIEZO_PWM1__PS)
/* Data Register */
#define PIN_PIEZO_PWM1_DR                     (* (reg8 *) PIN_PIEZO_PWM1__DR)
/* Port Number */
#define PIN_PIEZO_PWM1_PRT_NUM                (* (reg8 *) PIN_PIEZO_PWM1__PRT) 
/* Connect to Analog Globals */                                                  
#define PIN_PIEZO_PWM1_AG                     (* (reg8 *) PIN_PIEZO_PWM1__AG)                       
/* Analog MUX bux enable */
#define PIN_PIEZO_PWM1_AMUX                   (* (reg8 *) PIN_PIEZO_PWM1__AMUX) 
/* Bidirectional Enable */                                                        
#define PIN_PIEZO_PWM1_BIE                    (* (reg8 *) PIN_PIEZO_PWM1__BIE)
/* Bit-mask for Aliased Register Access */
#define PIN_PIEZO_PWM1_BIT_MASK               (* (reg8 *) PIN_PIEZO_PWM1__BIT_MASK)
/* Bypass Enable */
#define PIN_PIEZO_PWM1_BYP                    (* (reg8 *) PIN_PIEZO_PWM1__BYP)
/* Port wide control signals */                                                   
#define PIN_PIEZO_PWM1_CTL                    (* (reg8 *) PIN_PIEZO_PWM1__CTL)
/* Drive Modes */
#define PIN_PIEZO_PWM1_DM0                    (* (reg8 *) PIN_PIEZO_PWM1__DM0) 
#define PIN_PIEZO_PWM1_DM1                    (* (reg8 *) PIN_PIEZO_PWM1__DM1)
#define PIN_PIEZO_PWM1_DM2                    (* (reg8 *) PIN_PIEZO_PWM1__DM2) 
/* Input Buffer Disable Override */
#define PIN_PIEZO_PWM1_INP_DIS                (* (reg8 *) PIN_PIEZO_PWM1__INP_DIS)
/* LCD Common or Segment Drive */
#define PIN_PIEZO_PWM1_LCD_COM_SEG            (* (reg8 *) PIN_PIEZO_PWM1__LCD_COM_SEG)
/* Enable Segment LCD */
#define PIN_PIEZO_PWM1_LCD_EN                 (* (reg8 *) PIN_PIEZO_PWM1__LCD_EN)
/* Slew Rate Control */
#define PIN_PIEZO_PWM1_SLW                    (* (reg8 *) PIN_PIEZO_PWM1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PIN_PIEZO_PWM1_PRTDSI__CAPS_SEL       (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PIN_PIEZO_PWM1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PIN_PIEZO_PWM1_PRTDSI__OE_SEL0        (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__OE_SEL0) 
#define PIN_PIEZO_PWM1_PRTDSI__OE_SEL1        (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PIN_PIEZO_PWM1_PRTDSI__OUT_SEL0       (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__OUT_SEL0) 
#define PIN_PIEZO_PWM1_PRTDSI__OUT_SEL1       (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PIN_PIEZO_PWM1_PRTDSI__SYNC_OUT       (* (reg8 *) PIN_PIEZO_PWM1__PRTDSI__SYNC_OUT) 


#if defined(PIN_PIEZO_PWM1__INTSTAT)  /* Interrupt Registers */

    #define PIN_PIEZO_PWM1_INTSTAT                (* (reg8 *) PIN_PIEZO_PWM1__INTSTAT)
    #define PIN_PIEZO_PWM1_SNAP                   (* (reg8 *) PIN_PIEZO_PWM1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PIN_PIEZO_PWM1_H */

#endif
/* [] END OF FILE */
