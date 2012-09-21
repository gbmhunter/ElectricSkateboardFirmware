/*******************************************************************************
* File Name: IsrMainTick.h
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
#if !defined(__IsrMainTick_INTC_H__)
#define __IsrMainTick_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IsrMainTick_Start(void);
void IsrMainTick_StartEx(cyisraddress address);
void IsrMainTick_Stop(void) ;

CY_ISR_PROTO(IsrMainTick_Interrupt);

void IsrMainTick_SetVector(cyisraddress address) ;
cyisraddress IsrMainTick_GetVector(void) ;

void IsrMainTick_SetPriority(uint8 priority) ;
uint8 IsrMainTick_GetPriority(void) ;

void IsrMainTick_Enable(void) ;
uint8 IsrMainTick_GetState(void) ;
void IsrMainTick_Disable(void) ;

void IsrMainTick_SetPending(void) ;
void IsrMainTick_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IsrMainTick ISR. */
#define IsrMainTick_INTC_VECTOR            ((reg32 *) IsrMainTick__INTC_VECT)

/* Address of the IsrMainTick ISR priority. */
#define IsrMainTick_INTC_PRIOR             ((reg8 *) IsrMainTick__INTC_PRIOR_REG)

/* Priority of the IsrMainTick interrupt. */
#define IsrMainTick_INTC_PRIOR_NUMBER      IsrMainTick__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IsrMainTick interrupt. */
#define IsrMainTick_INTC_SET_EN            ((reg32 *) IsrMainTick__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IsrMainTick interrupt. */
#define IsrMainTick_INTC_CLR_EN            ((reg32 *) IsrMainTick__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IsrMainTick interrupt state to pending. */
#define IsrMainTick_INTC_SET_PD            ((reg32 *) IsrMainTick__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IsrMainTick interrupt. */
#define IsrMainTick_INTC_CLR_PD            ((reg32 *) IsrMainTick__INTC_CLR_PD_REG)



/* __IsrMainTick_INTC_H__ */
#endif
