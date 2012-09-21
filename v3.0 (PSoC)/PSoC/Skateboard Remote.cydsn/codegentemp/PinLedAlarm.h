/*******************************************************************************
* File Name: PinLedAlarm.h  
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

#if !defined(CY_PINS_PinLedAlarm_H) /* Pins PinLedAlarm_H */
#define CY_PINS_PinLedAlarm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinLedAlarm_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedAlarm__PORT == 15 && (PinLedAlarm__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinLedAlarm_Write(uint8 value) ;
void    PinLedAlarm_SetDriveMode(uint8 mode) ;
uint8   PinLedAlarm_ReadDataReg(void) ;
uint8   PinLedAlarm_Read(void) ;
uint8   PinLedAlarm_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLedAlarm_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinLedAlarm_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinLedAlarm_DM_RES_UP          PIN_DM_RES_UP
#define PinLedAlarm_DM_RES_DWN         PIN_DM_RES_DWN
#define PinLedAlarm_DM_OD_LO           PIN_DM_OD_LO
#define PinLedAlarm_DM_OD_HI           PIN_DM_OD_HI
#define PinLedAlarm_DM_STRONG          PIN_DM_STRONG
#define PinLedAlarm_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinLedAlarm_MASK               PinLedAlarm__MASK
#define PinLedAlarm_SHIFT              PinLedAlarm__SHIFT
#define PinLedAlarm_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLedAlarm_PS                     (* (reg8 *) PinLedAlarm__PS)
/* Data Register */
#define PinLedAlarm_DR                     (* (reg8 *) PinLedAlarm__DR)
/* Port Number */
#define PinLedAlarm_PRT_NUM                (* (reg8 *) PinLedAlarm__PRT) 
/* Connect to Analog Globals */                                                  
#define PinLedAlarm_AG                     (* (reg8 *) PinLedAlarm__AG)                       
/* Analog MUX bux enable */
#define PinLedAlarm_AMUX                   (* (reg8 *) PinLedAlarm__AMUX) 
/* Bidirectional Enable */                                                        
#define PinLedAlarm_BIE                    (* (reg8 *) PinLedAlarm__BIE)
/* Bit-mask for Aliased Register Access */
#define PinLedAlarm_BIT_MASK               (* (reg8 *) PinLedAlarm__BIT_MASK)
/* Bypass Enable */
#define PinLedAlarm_BYP                    (* (reg8 *) PinLedAlarm__BYP)
/* Port wide control signals */                                                   
#define PinLedAlarm_CTL                    (* (reg8 *) PinLedAlarm__CTL)
/* Drive Modes */
#define PinLedAlarm_DM0                    (* (reg8 *) PinLedAlarm__DM0) 
#define PinLedAlarm_DM1                    (* (reg8 *) PinLedAlarm__DM1)
#define PinLedAlarm_DM2                    (* (reg8 *) PinLedAlarm__DM2) 
/* Input Buffer Disable Override */
#define PinLedAlarm_INP_DIS                (* (reg8 *) PinLedAlarm__INP_DIS)
/* LCD Common or Segment Drive */
#define PinLedAlarm_LCD_COM_SEG            (* (reg8 *) PinLedAlarm__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinLedAlarm_LCD_EN                 (* (reg8 *) PinLedAlarm__LCD_EN)
/* Slew Rate Control */
#define PinLedAlarm_SLW                    (* (reg8 *) PinLedAlarm__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinLedAlarm_PRTDSI__CAPS_SEL       (* (reg8 *) PinLedAlarm__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinLedAlarm_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinLedAlarm__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinLedAlarm_PRTDSI__OE_SEL0        (* (reg8 *) PinLedAlarm__PRTDSI__OE_SEL0) 
#define PinLedAlarm_PRTDSI__OE_SEL1        (* (reg8 *) PinLedAlarm__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinLedAlarm_PRTDSI__OUT_SEL0       (* (reg8 *) PinLedAlarm__PRTDSI__OUT_SEL0) 
#define PinLedAlarm_PRTDSI__OUT_SEL1       (* (reg8 *) PinLedAlarm__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinLedAlarm_PRTDSI__SYNC_OUT       (* (reg8 *) PinLedAlarm__PRTDSI__SYNC_OUT) 


#if defined(PinLedAlarm__INTSTAT)  /* Interrupt Registers */

    #define PinLedAlarm_INTSTAT                (* (reg8 *) PinLedAlarm__INTSTAT)
    #define PinLedAlarm_SNAP                   (* (reg8 *) PinLedAlarm__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinLedAlarm_H */

#endif
/* [] END OF FILE */
