/*******************************************************************************
* File Name: PinDebug.h  
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

#if !defined(CY_PINS_PinDebug_H) /* Pins PinDebug_H */
#define CY_PINS_PinDebug_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinDebug_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinDebug__PORT == 15 && (PinDebug__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinDebug_Write(uint8 value) ;
void    PinDebug_SetDriveMode(uint8 mode) ;
uint8   PinDebug_ReadDataReg(void) ;
uint8   PinDebug_Read(void) ;
uint8   PinDebug_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinDebug_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinDebug_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinDebug_DM_RES_UP          PIN_DM_RES_UP
#define PinDebug_DM_RES_DWN         PIN_DM_RES_DWN
#define PinDebug_DM_OD_LO           PIN_DM_OD_LO
#define PinDebug_DM_OD_HI           PIN_DM_OD_HI
#define PinDebug_DM_STRONG          PIN_DM_STRONG
#define PinDebug_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinDebug_MASK               PinDebug__MASK
#define PinDebug_SHIFT              PinDebug__SHIFT
#define PinDebug_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinDebug_PS                     (* (reg8 *) PinDebug__PS)
/* Data Register */
#define PinDebug_DR                     (* (reg8 *) PinDebug__DR)
/* Port Number */
#define PinDebug_PRT_NUM                (* (reg8 *) PinDebug__PRT) 
/* Connect to Analog Globals */                                                  
#define PinDebug_AG                     (* (reg8 *) PinDebug__AG)                       
/* Analog MUX bux enable */
#define PinDebug_AMUX                   (* (reg8 *) PinDebug__AMUX) 
/* Bidirectional Enable */                                                        
#define PinDebug_BIE                    (* (reg8 *) PinDebug__BIE)
/* Bit-mask for Aliased Register Access */
#define PinDebug_BIT_MASK               (* (reg8 *) PinDebug__BIT_MASK)
/* Bypass Enable */
#define PinDebug_BYP                    (* (reg8 *) PinDebug__BYP)
/* Port wide control signals */                                                   
#define PinDebug_CTL                    (* (reg8 *) PinDebug__CTL)
/* Drive Modes */
#define PinDebug_DM0                    (* (reg8 *) PinDebug__DM0) 
#define PinDebug_DM1                    (* (reg8 *) PinDebug__DM1)
#define PinDebug_DM2                    (* (reg8 *) PinDebug__DM2) 
/* Input Buffer Disable Override */
#define PinDebug_INP_DIS                (* (reg8 *) PinDebug__INP_DIS)
/* LCD Common or Segment Drive */
#define PinDebug_LCD_COM_SEG            (* (reg8 *) PinDebug__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinDebug_LCD_EN                 (* (reg8 *) PinDebug__LCD_EN)
/* Slew Rate Control */
#define PinDebug_SLW                    (* (reg8 *) PinDebug__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinDebug_PRTDSI__CAPS_SEL       (* (reg8 *) PinDebug__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinDebug_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinDebug__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinDebug_PRTDSI__OE_SEL0        (* (reg8 *) PinDebug__PRTDSI__OE_SEL0) 
#define PinDebug_PRTDSI__OE_SEL1        (* (reg8 *) PinDebug__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinDebug_PRTDSI__OUT_SEL0       (* (reg8 *) PinDebug__PRTDSI__OUT_SEL0) 
#define PinDebug_PRTDSI__OUT_SEL1       (* (reg8 *) PinDebug__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinDebug_PRTDSI__SYNC_OUT       (* (reg8 *) PinDebug__PRTDSI__SYNC_OUT) 


#if defined(PinDebug__INTSTAT)  /* Interrupt Registers */

    #define PinDebug_INTSTAT                (* (reg8 *) PinDebug__INTSTAT)
    #define PinDebug_SNAP                   (* (reg8 *) PinDebug__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinDebug_H */

#endif
/* [] END OF FILE */
