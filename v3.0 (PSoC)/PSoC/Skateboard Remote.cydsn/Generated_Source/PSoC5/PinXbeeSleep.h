/*******************************************************************************
* File Name: PinXbeeSleep.h  
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

#if !defined(CY_PINS_PinXbeeSleep_H) /* Pins PinXbeeSleep_H */
#define CY_PINS_PinXbeeSleep_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinXbeeSleep_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinXbeeSleep__PORT == 15 && (PinXbeeSleep__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinXbeeSleep_Write(uint8 value) ;
void    PinXbeeSleep_SetDriveMode(uint8 mode) ;
uint8   PinXbeeSleep_ReadDataReg(void) ;
uint8   PinXbeeSleep_Read(void) ;
uint8   PinXbeeSleep_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinXbeeSleep_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinXbeeSleep_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinXbeeSleep_DM_RES_UP          PIN_DM_RES_UP
#define PinXbeeSleep_DM_RES_DWN         PIN_DM_RES_DWN
#define PinXbeeSleep_DM_OD_LO           PIN_DM_OD_LO
#define PinXbeeSleep_DM_OD_HI           PIN_DM_OD_HI
#define PinXbeeSleep_DM_STRONG          PIN_DM_STRONG
#define PinXbeeSleep_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinXbeeSleep_MASK               PinXbeeSleep__MASK
#define PinXbeeSleep_SHIFT              PinXbeeSleep__SHIFT
#define PinXbeeSleep_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinXbeeSleep_PS                     (* (reg8 *) PinXbeeSleep__PS)
/* Data Register */
#define PinXbeeSleep_DR                     (* (reg8 *) PinXbeeSleep__DR)
/* Port Number */
#define PinXbeeSleep_PRT_NUM                (* (reg8 *) PinXbeeSleep__PRT) 
/* Connect to Analog Globals */                                                  
#define PinXbeeSleep_AG                     (* (reg8 *) PinXbeeSleep__AG)                       
/* Analog MUX bux enable */
#define PinXbeeSleep_AMUX                   (* (reg8 *) PinXbeeSleep__AMUX) 
/* Bidirectional Enable */                                                        
#define PinXbeeSleep_BIE                    (* (reg8 *) PinXbeeSleep__BIE)
/* Bit-mask for Aliased Register Access */
#define PinXbeeSleep_BIT_MASK               (* (reg8 *) PinXbeeSleep__BIT_MASK)
/* Bypass Enable */
#define PinXbeeSleep_BYP                    (* (reg8 *) PinXbeeSleep__BYP)
/* Port wide control signals */                                                   
#define PinXbeeSleep_CTL                    (* (reg8 *) PinXbeeSleep__CTL)
/* Drive Modes */
#define PinXbeeSleep_DM0                    (* (reg8 *) PinXbeeSleep__DM0) 
#define PinXbeeSleep_DM1                    (* (reg8 *) PinXbeeSleep__DM1)
#define PinXbeeSleep_DM2                    (* (reg8 *) PinXbeeSleep__DM2) 
/* Input Buffer Disable Override */
#define PinXbeeSleep_INP_DIS                (* (reg8 *) PinXbeeSleep__INP_DIS)
/* LCD Common or Segment Drive */
#define PinXbeeSleep_LCD_COM_SEG            (* (reg8 *) PinXbeeSleep__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinXbeeSleep_LCD_EN                 (* (reg8 *) PinXbeeSleep__LCD_EN)
/* Slew Rate Control */
#define PinXbeeSleep_SLW                    (* (reg8 *) PinXbeeSleep__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinXbeeSleep_PRTDSI__CAPS_SEL       (* (reg8 *) PinXbeeSleep__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinXbeeSleep_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinXbeeSleep__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinXbeeSleep_PRTDSI__OE_SEL0        (* (reg8 *) PinXbeeSleep__PRTDSI__OE_SEL0) 
#define PinXbeeSleep_PRTDSI__OE_SEL1        (* (reg8 *) PinXbeeSleep__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinXbeeSleep_PRTDSI__OUT_SEL0       (* (reg8 *) PinXbeeSleep__PRTDSI__OUT_SEL0) 
#define PinXbeeSleep_PRTDSI__OUT_SEL1       (* (reg8 *) PinXbeeSleep__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinXbeeSleep_PRTDSI__SYNC_OUT       (* (reg8 *) PinXbeeSleep__PRTDSI__SYNC_OUT) 


#if defined(PinXbeeSleep__INTSTAT)  /* Interrupt Registers */

    #define PinXbeeSleep_INTSTAT                (* (reg8 *) PinXbeeSleep__INTSTAT)
    #define PinXbeeSleep_SNAP                   (* (reg8 *) PinXbeeSleep__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinXbeeSleep_H */

#endif
/* [] END OF FILE */
