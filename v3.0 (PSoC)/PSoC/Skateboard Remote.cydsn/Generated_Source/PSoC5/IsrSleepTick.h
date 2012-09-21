/*******************************************************************************
* File Name: IsrSleepTick.h
* Version 1.50
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__IsrSleepTick_INTC_H__)
#define __IsrSleepTick_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IsrSleepTick_Start(void);
void IsrSleepTick_StartEx(cyisraddress address);
void IsrSleepTick_Stop(void) ;

CY_ISR_PROTO(IsrSleepTick_Interrupt);

void IsrSleepTick_SetVector(cyisraddress address) ;
cyisraddress IsrSleepTick_GetVector(void) ;

void IsrSleepTick_SetPriority(uint8 priority) ;
uint8 IsrSleepTick_GetPriority(void) ;

void IsrSleepTick_Enable(void) ;
uint8 IsrSleepTick_GetState(void) ;
void IsrSleepTick_Disable(void) ;

void IsrSleepTick_SetPending(void) ;
void IsrSleepTick_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IsrSleepTick ISR. */
#define IsrSleepTick_INTC_VECTOR            ((reg32 *) IsrSleepTick__INTC_VECT)

/* Address of the IsrSleepTick ISR priority. */
#define IsrSleepTick_INTC_PRIOR             ((reg8 *) IsrSleepTick__INTC_PRIOR_REG)

/* Priority of the IsrSleepTick interrupt. */
#define IsrSleepTick_INTC_PRIOR_NUMBER      IsrSleepTick__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IsrSleepTick interrupt. */
#define IsrSleepTick_INTC_SET_EN            ((reg32 *) IsrSleepTick__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IsrSleepTick interrupt. */
#define IsrSleepTick_INTC_CLR_EN            ((reg32 *) IsrSleepTick__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IsrSleepTick interrupt state to pending. */
#define IsrSleepTick_INTC_SET_PD            ((reg32 *) IsrSleepTick__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IsrSleepTick interrupt. */
#define IsrSleepTick_INTC_CLR_PD            ((reg32 *) IsrSleepTick__INTC_CLR_PD_REG)



/* __IsrSleepTick_INTC_H__ */
#endif
