/*******************************************************************************
* File Name: PinPwmMotor.h  
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

#if !defined(CY_PINS_PinPwmMotor_H) /* Pins PinPwmMotor_H */
#define CY_PINS_PinPwmMotor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinPwmMotor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinPwmMotor__PORT == 15 && (PinPwmMotor__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinPwmMotor_Write(uint8 value) ;
void    PinPwmMotor_SetDriveMode(uint8 mode) ;
uint8   PinPwmMotor_ReadDataReg(void) ;
uint8   PinPwmMotor_Read(void) ;
uint8   PinPwmMotor_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinPwmMotor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinPwmMotor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinPwmMotor_DM_RES_UP          PIN_DM_RES_UP
#define PinPwmMotor_DM_RES_DWN         PIN_DM_RES_DWN
#define PinPwmMotor_DM_OD_LO           PIN_DM_OD_LO
#define PinPwmMotor_DM_OD_HI           PIN_DM_OD_HI
#define PinPwmMotor_DM_STRONG          PIN_DM_STRONG
#define PinPwmMotor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinPwmMotor_MASK               PinPwmMotor__MASK
#define PinPwmMotor_SHIFT              PinPwmMotor__SHIFT
#define PinPwmMotor_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinPwmMotor_PS                     (* (reg8 *) PinPwmMotor__PS)
/* Data Register */
#define PinPwmMotor_DR                     (* (reg8 *) PinPwmMotor__DR)
/* Port Number */
#define PinPwmMotor_PRT_NUM                (* (reg8 *) PinPwmMotor__PRT) 
/* Connect to Analog Globals */                                                  
#define PinPwmMotor_AG                     (* (reg8 *) PinPwmMotor__AG)                       
/* Analog MUX bux enable */
#define PinPwmMotor_AMUX                   (* (reg8 *) PinPwmMotor__AMUX) 
/* Bidirectional Enable */                                                        
#define PinPwmMotor_BIE                    (* (reg8 *) PinPwmMotor__BIE)
/* Bit-mask for Aliased Register Access */
#define PinPwmMotor_BIT_MASK               (* (reg8 *) PinPwmMotor__BIT_MASK)
/* Bypass Enable */
#define PinPwmMotor_BYP                    (* (reg8 *) PinPwmMotor__BYP)
/* Port wide control signals */                                                   
#define PinPwmMotor_CTL                    (* (reg8 *) PinPwmMotor__CTL)
/* Drive Modes */
#define PinPwmMotor_DM0                    (* (reg8 *) PinPwmMotor__DM0) 
#define PinPwmMotor_DM1                    (* (reg8 *) PinPwmMotor__DM1)
#define PinPwmMotor_DM2                    (* (reg8 *) PinPwmMotor__DM2) 
/* Input Buffer Disable Override */
#define PinPwmMotor_INP_DIS                (* (reg8 *) PinPwmMotor__INP_DIS)
/* LCD Common or Segment Drive */
#define PinPwmMotor_LCD_COM_SEG            (* (reg8 *) PinPwmMotor__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinPwmMotor_LCD_EN                 (* (reg8 *) PinPwmMotor__LCD_EN)
/* Slew Rate Control */
#define PinPwmMotor_SLW                    (* (reg8 *) PinPwmMotor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinPwmMotor_PRTDSI__CAPS_SEL       (* (reg8 *) PinPwmMotor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinPwmMotor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinPwmMotor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinPwmMotor_PRTDSI__OE_SEL0        (* (reg8 *) PinPwmMotor__PRTDSI__OE_SEL0) 
#define PinPwmMotor_PRTDSI__OE_SEL1        (* (reg8 *) PinPwmMotor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinPwmMotor_PRTDSI__OUT_SEL0       (* (reg8 *) PinPwmMotor__PRTDSI__OUT_SEL0) 
#define PinPwmMotor_PRTDSI__OUT_SEL1       (* (reg8 *) PinPwmMotor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinPwmMotor_PRTDSI__SYNC_OUT       (* (reg8 *) PinPwmMotor__PRTDSI__SYNC_OUT) 


#if defined(PinPwmMotor__INTSTAT)  /* Interrupt Registers */

    #define PinPwmMotor_INTSTAT                (* (reg8 *) PinPwmMotor__INTSTAT)
    #define PinPwmMotor_SNAP                   (* (reg8 *) PinPwmMotor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinPwmMotor_H */

#endif
/* [] END OF FILE */
