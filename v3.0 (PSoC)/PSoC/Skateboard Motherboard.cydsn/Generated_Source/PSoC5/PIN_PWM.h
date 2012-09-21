/*******************************************************************************
* File Name: PIN_PWM.h  
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

#if !defined(CY_PINS_PIN_PWM_H) /* Pins PIN_PWM_H */
#define CY_PINS_PIN_PWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PIN_PWM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PIN_PWM__PORT == 15 && (PIN_PWM__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PIN_PWM_Write(uint8 value) ;
void    PIN_PWM_SetDriveMode(uint8 mode) ;
uint8   PIN_PWM_ReadDataReg(void) ;
uint8   PIN_PWM_Read(void) ;
uint8   PIN_PWM_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN_PWM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PIN_PWM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PIN_PWM_DM_RES_UP          PIN_DM_RES_UP
#define PIN_PWM_DM_RES_DWN         PIN_DM_RES_DWN
#define PIN_PWM_DM_OD_LO           PIN_DM_OD_LO
#define PIN_PWM_DM_OD_HI           PIN_DM_OD_HI
#define PIN_PWM_DM_STRONG          PIN_DM_STRONG
#define PIN_PWM_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PIN_PWM_MASK               PIN_PWM__MASK
#define PIN_PWM_SHIFT              PIN_PWM__SHIFT
#define PIN_PWM_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN_PWM_PS                     (* (reg8 *) PIN_PWM__PS)
/* Data Register */
#define PIN_PWM_DR                     (* (reg8 *) PIN_PWM__DR)
/* Port Number */
#define PIN_PWM_PRT_NUM                (* (reg8 *) PIN_PWM__PRT) 
/* Connect to Analog Globals */                                                  
#define PIN_PWM_AG                     (* (reg8 *) PIN_PWM__AG)                       
/* Analog MUX bux enable */
#define PIN_PWM_AMUX                   (* (reg8 *) PIN_PWM__AMUX) 
/* Bidirectional Enable */                                                        
#define PIN_PWM_BIE                    (* (reg8 *) PIN_PWM__BIE)
/* Bit-mask for Aliased Register Access */
#define PIN_PWM_BIT_MASK               (* (reg8 *) PIN_PWM__BIT_MASK)
/* Bypass Enable */
#define PIN_PWM_BYP                    (* (reg8 *) PIN_PWM__BYP)
/* Port wide control signals */                                                   
#define PIN_PWM_CTL                    (* (reg8 *) PIN_PWM__CTL)
/* Drive Modes */
#define PIN_PWM_DM0                    (* (reg8 *) PIN_PWM__DM0) 
#define PIN_PWM_DM1                    (* (reg8 *) PIN_PWM__DM1)
#define PIN_PWM_DM2                    (* (reg8 *) PIN_PWM__DM2) 
/* Input Buffer Disable Override */
#define PIN_PWM_INP_DIS                (* (reg8 *) PIN_PWM__INP_DIS)
/* LCD Common or Segment Drive */
#define PIN_PWM_LCD_COM_SEG            (* (reg8 *) PIN_PWM__LCD_COM_SEG)
/* Enable Segment LCD */
#define PIN_PWM_LCD_EN                 (* (reg8 *) PIN_PWM__LCD_EN)
/* Slew Rate Control */
#define PIN_PWM_SLW                    (* (reg8 *) PIN_PWM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PIN_PWM_PRTDSI__CAPS_SEL       (* (reg8 *) PIN_PWM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PIN_PWM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PIN_PWM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PIN_PWM_PRTDSI__OE_SEL0        (* (reg8 *) PIN_PWM__PRTDSI__OE_SEL0) 
#define PIN_PWM_PRTDSI__OE_SEL1        (* (reg8 *) PIN_PWM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PIN_PWM_PRTDSI__OUT_SEL0       (* (reg8 *) PIN_PWM__PRTDSI__OUT_SEL0) 
#define PIN_PWM_PRTDSI__OUT_SEL1       (* (reg8 *) PIN_PWM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PIN_PWM_PRTDSI__SYNC_OUT       (* (reg8 *) PIN_PWM__PRTDSI__SYNC_OUT) 


#if defined(PIN_PWM__INTSTAT)  /* Interrupt Registers */

    #define PIN_PWM_INTSTAT                (* (reg8 *) PIN_PWM__INTSTAT)
    #define PIN_PWM_SNAP                   (* (reg8 *) PIN_PWM__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PIN_PWM_H */

#endif
/* [] END OF FILE */
