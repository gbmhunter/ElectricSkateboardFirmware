/*******************************************************************************
* File Name: PinSpare3.h  
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

#if !defined(CY_PINS_PinSpare3_H) /* Pins PinSpare3_H */
#define CY_PINS_PinSpare3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinSpare3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinSpare3__PORT == 15 && (PinSpare3__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinSpare3_Write(uint8 value) ;
void    PinSpare3_SetDriveMode(uint8 mode) ;
uint8   PinSpare3_ReadDataReg(void) ;
uint8   PinSpare3_Read(void) ;
uint8   PinSpare3_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinSpare3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinSpare3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinSpare3_DM_RES_UP          PIN_DM_RES_UP
#define PinSpare3_DM_RES_DWN         PIN_DM_RES_DWN
#define PinSpare3_DM_OD_LO           PIN_DM_OD_LO
#define PinSpare3_DM_OD_HI           PIN_DM_OD_HI
#define PinSpare3_DM_STRONG          PIN_DM_STRONG
#define PinSpare3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinSpare3_MASK               PinSpare3__MASK
#define PinSpare3_SHIFT              PinSpare3__SHIFT
#define PinSpare3_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinSpare3_PS                     (* (reg8 *) PinSpare3__PS)
/* Data Register */
#define PinSpare3_DR                     (* (reg8 *) PinSpare3__DR)
/* Port Number */
#define PinSpare3_PRT_NUM                (* (reg8 *) PinSpare3__PRT) 
/* Connect to Analog Globals */                                                  
#define PinSpare3_AG                     (* (reg8 *) PinSpare3__AG)                       
/* Analog MUX bux enable */
#define PinSpare3_AMUX                   (* (reg8 *) PinSpare3__AMUX) 
/* Bidirectional Enable */                                                        
#define PinSpare3_BIE                    (* (reg8 *) PinSpare3__BIE)
/* Bit-mask for Aliased Register Access */
#define PinSpare3_BIT_MASK               (* (reg8 *) PinSpare3__BIT_MASK)
/* Bypass Enable */
#define PinSpare3_BYP                    (* (reg8 *) PinSpare3__BYP)
/* Port wide control signals */                                                   
#define PinSpare3_CTL                    (* (reg8 *) PinSpare3__CTL)
/* Drive Modes */
#define PinSpare3_DM0                    (* (reg8 *) PinSpare3__DM0) 
#define PinSpare3_DM1                    (* (reg8 *) PinSpare3__DM1)
#define PinSpare3_DM2                    (* (reg8 *) PinSpare3__DM2) 
/* Input Buffer Disable Override */
#define PinSpare3_INP_DIS                (* (reg8 *) PinSpare3__INP_DIS)
/* LCD Common or Segment Drive */
#define PinSpare3_LCD_COM_SEG            (* (reg8 *) PinSpare3__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinSpare3_LCD_EN                 (* (reg8 *) PinSpare3__LCD_EN)
/* Slew Rate Control */
#define PinSpare3_SLW                    (* (reg8 *) PinSpare3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinSpare3_PRTDSI__CAPS_SEL       (* (reg8 *) PinSpare3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinSpare3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinSpare3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinSpare3_PRTDSI__OE_SEL0        (* (reg8 *) PinSpare3__PRTDSI__OE_SEL0) 
#define PinSpare3_PRTDSI__OE_SEL1        (* (reg8 *) PinSpare3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinSpare3_PRTDSI__OUT_SEL0       (* (reg8 *) PinSpare3__PRTDSI__OUT_SEL0) 
#define PinSpare3_PRTDSI__OUT_SEL1       (* (reg8 *) PinSpare3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinSpare3_PRTDSI__SYNC_OUT       (* (reg8 *) PinSpare3__PRTDSI__SYNC_OUT) 


#if defined(PinSpare3__INTSTAT)  /* Interrupt Registers */

    #define PinSpare3_INTSTAT                (* (reg8 *) PinSpare3__INTSTAT)
    #define PinSpare3_SNAP                   (* (reg8 *) PinSpare3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinSpare3_H */

#endif
/* [] END OF FILE */
