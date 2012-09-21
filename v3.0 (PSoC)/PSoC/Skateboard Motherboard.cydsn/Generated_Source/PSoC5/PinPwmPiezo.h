/*******************************************************************************
* File Name: PinPwmPiezo.h  
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

#if !defined(CY_PINS_PinPwmPiezo_H) /* Pins PinPwmPiezo_H */
#define CY_PINS_PinPwmPiezo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinPwmPiezo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinPwmPiezo__PORT == 15 && (PinPwmPiezo__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    PinPwmPiezo_Write(uint8 value) ;
void    PinPwmPiezo_SetDriveMode(uint8 mode) ;
uint8   PinPwmPiezo_ReadDataReg(void) ;
uint8   PinPwmPiezo_Read(void) ;
uint8   PinPwmPiezo_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinPwmPiezo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PinPwmPiezo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PinPwmPiezo_DM_RES_UP          PIN_DM_RES_UP
#define PinPwmPiezo_DM_RES_DWN         PIN_DM_RES_DWN
#define PinPwmPiezo_DM_OD_LO           PIN_DM_OD_LO
#define PinPwmPiezo_DM_OD_HI           PIN_DM_OD_HI
#define PinPwmPiezo_DM_STRONG          PIN_DM_STRONG
#define PinPwmPiezo_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PinPwmPiezo_MASK               PinPwmPiezo__MASK
#define PinPwmPiezo_SHIFT              PinPwmPiezo__SHIFT
#define PinPwmPiezo_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinPwmPiezo_PS                     (* (reg8 *) PinPwmPiezo__PS)
/* Data Register */
#define PinPwmPiezo_DR                     (* (reg8 *) PinPwmPiezo__DR)
/* Port Number */
#define PinPwmPiezo_PRT_NUM                (* (reg8 *) PinPwmPiezo__PRT) 
/* Connect to Analog Globals */                                                  
#define PinPwmPiezo_AG                     (* (reg8 *) PinPwmPiezo__AG)                       
/* Analog MUX bux enable */
#define PinPwmPiezo_AMUX                   (* (reg8 *) PinPwmPiezo__AMUX) 
/* Bidirectional Enable */                                                        
#define PinPwmPiezo_BIE                    (* (reg8 *) PinPwmPiezo__BIE)
/* Bit-mask for Aliased Register Access */
#define PinPwmPiezo_BIT_MASK               (* (reg8 *) PinPwmPiezo__BIT_MASK)
/* Bypass Enable */
#define PinPwmPiezo_BYP                    (* (reg8 *) PinPwmPiezo__BYP)
/* Port wide control signals */                                                   
#define PinPwmPiezo_CTL                    (* (reg8 *) PinPwmPiezo__CTL)
/* Drive Modes */
#define PinPwmPiezo_DM0                    (* (reg8 *) PinPwmPiezo__DM0) 
#define PinPwmPiezo_DM1                    (* (reg8 *) PinPwmPiezo__DM1)
#define PinPwmPiezo_DM2                    (* (reg8 *) PinPwmPiezo__DM2) 
/* Input Buffer Disable Override */
#define PinPwmPiezo_INP_DIS                (* (reg8 *) PinPwmPiezo__INP_DIS)
/* LCD Common or Segment Drive */
#define PinPwmPiezo_LCD_COM_SEG            (* (reg8 *) PinPwmPiezo__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinPwmPiezo_LCD_EN                 (* (reg8 *) PinPwmPiezo__LCD_EN)
/* Slew Rate Control */
#define PinPwmPiezo_SLW                    (* (reg8 *) PinPwmPiezo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinPwmPiezo_PRTDSI__CAPS_SEL       (* (reg8 *) PinPwmPiezo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinPwmPiezo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinPwmPiezo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinPwmPiezo_PRTDSI__OE_SEL0        (* (reg8 *) PinPwmPiezo__PRTDSI__OE_SEL0) 
#define PinPwmPiezo_PRTDSI__OE_SEL1        (* (reg8 *) PinPwmPiezo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinPwmPiezo_PRTDSI__OUT_SEL0       (* (reg8 *) PinPwmPiezo__PRTDSI__OUT_SEL0) 
#define PinPwmPiezo_PRTDSI__OUT_SEL1       (* (reg8 *) PinPwmPiezo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinPwmPiezo_PRTDSI__SYNC_OUT       (* (reg8 *) PinPwmPiezo__PRTDSI__SYNC_OUT) 


#if defined(PinPwmPiezo__INTSTAT)  /* Interrupt Registers */

    #define PinPwmPiezo_INTSTAT                (* (reg8 *) PinPwmPiezo__INTSTAT)
    #define PinPwmPiezo_SNAP                   (* (reg8 *) PinPwmPiezo__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PinPwmPiezo_H */

#endif
/* [] END OF FILE */
