/*******************************************************************************
* File Name: PinXbeeIsSleep.h  
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

#if !defined(CY_PINS_PinXbeeIsSleep_H) /* Pins PinXbeeIsSleep_H */
#define CY_PINS_PinXbeeIsSleep_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinXbeeIsSleep_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinXbeeIsSleep__PORT == 15 && (PinXbeeIsSleep__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinXbeeIsSleep_Write(uint8 value) ;
void    PinXbeeIsSleep_SetDriveMode(uint8 mode) ;
uint8   PinXbeeIsSleep_ReadDataReg(void) ;
uint8   PinXbeeIsSleep_Read(void) ;
uint8   PinXbeeIsSleep_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinXbeeIsSleep_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinXbeeIsSleep_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinXbeeIsSleep_DM_RES_UP          PIN_DM_RES_UP
#define PinXbeeIsSleep_DM_RES_DWN         PIN_DM_RES_DWN
#define PinXbeeIsSleep_DM_OD_LO           PIN_DM_OD_LO
#define PinXbeeIsSleep_DM_OD_HI           PIN_DM_OD_HI
#define PinXbeeIsSleep_DM_STRONG          PIN_DM_STRONG
#define PinXbeeIsSleep_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinXbeeIsSleep_MASK               PinXbeeIsSleep__MASK
#define PinXbeeIsSleep_SHIFT              PinXbeeIsSleep__SHIFT
#define PinXbeeIsSleep_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinXbeeIsSleep_PS                     (* (reg8 *) PinXbeeIsSleep__PS)
/* Data Register */
#define PinXbeeIsSleep_DR                     (* (reg8 *) PinXbeeIsSleep__DR)
/* Port Number */
#define PinXbeeIsSleep_PRT_NUM                (* (reg8 *) PinXbeeIsSleep__PRT) 
/* Connect to Analog Globals */                                                  
#define PinXbeeIsSleep_AG                     (* (reg8 *) PinXbeeIsSleep__AG)                       
/* Analog MUX bux enable */
#define PinXbeeIsSleep_AMUX                   (* (reg8 *) PinXbeeIsSleep__AMUX) 
/* Bidirectional Enable */                                                        
#define PinXbeeIsSleep_BIE                    (* (reg8 *) PinXbeeIsSleep__BIE)
/* Bit-mask for Aliased Register Access */
#define PinXbeeIsSleep_BIT_MASK               (* (reg8 *) PinXbeeIsSleep__BIT_MASK)
/* Bypass Enable */
#define PinXbeeIsSleep_BYP                    (* (reg8 *) PinXbeeIsSleep__BYP)
/* Port wide control signals */                                                   
#define PinXbeeIsSleep_CTL                    (* (reg8 *) PinXbeeIsSleep__CTL)
/* Drive Modes */
#define PinXbeeIsSleep_DM0                    (* (reg8 *) PinXbeeIsSleep__DM0) 
#define PinXbeeIsSleep_DM1                    (* (reg8 *) PinXbeeIsSleep__DM1)
#define PinXbeeIsSleep_DM2                    (* (reg8 *) PinXbeeIsSleep__DM2) 
/* Input Buffer Disable Override */
#define PinXbeeIsSleep_INP_DIS                (* (reg8 *) PinXbeeIsSleep__INP_DIS)
/* LCD Common or Segment Drive */
#define PinXbeeIsSleep_LCD_COM_SEG            (* (reg8 *) PinXbeeIsSleep__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinXbeeIsSleep_LCD_EN                 (* (reg8 *) PinXbeeIsSleep__LCD_EN)
/* Slew Rate Control */
#define PinXbeeIsSleep_SLW                    (* (reg8 *) PinXbeeIsSleep__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinXbeeIsSleep_PRTDSI__CAPS_SEL       (* (reg8 *) PinXbeeIsSleep__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinXbeeIsSleep_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinXbeeIsSleep__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinXbeeIsSleep_PRTDSI__OE_SEL0        (* (reg8 *) PinXbeeIsSleep__PRTDSI__OE_SEL0) 
#define PinXbeeIsSleep_PRTDSI__OE_SEL1        (* (reg8 *) PinXbeeIsSleep__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinXbeeIsSleep_PRTDSI__OUT_SEL0       (* (reg8 *) PinXbeeIsSleep__PRTDSI__OUT_SEL0) 
#define PinXbeeIsSleep_PRTDSI__OUT_SEL1       (* (reg8 *) PinXbeeIsSleep__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinXbeeIsSleep_PRTDSI__SYNC_OUT       (* (reg8 *) PinXbeeIsSleep__PRTDSI__SYNC_OUT) 


#if defined(PinXbeeIsSleep__INTSTAT)  /* Interrupt Registers */

    #define PinXbeeIsSleep_INTSTAT                (* (reg8 *) PinXbeeIsSleep__INTSTAT)
    #define PinXbeeIsSleep_SNAP                   (* (reg8 *) PinXbeeIsSleep__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinXbeeIsSleep_H */

#endif
/* [] END OF FILE */
