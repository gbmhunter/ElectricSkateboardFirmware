/*******************************************************************************
* File Name: IsrMotionSensor.h
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
#if !defined(__IsrMotionSensor_INTC_H__)
#define __IsrMotionSensor_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IsrMotionSensor_Start(void);
void IsrMotionSensor_StartEx(cyisraddress address);
void IsrMotionSensor_Stop(void) ;

CY_ISR_PROTO(IsrMotionSensor_Interrupt);

void IsrMotionSensor_SetVector(cyisraddress address) ;
cyisraddress IsrMotionSensor_GetVector(void) ;

void IsrMotionSensor_SetPriority(uint8 priority) ;
uint8 IsrMotionSensor_GetPriority(void) ;

void IsrMotionSensor_Enable(void) ;
uint8 IsrMotionSensor_GetState(void) ;
void IsrMotionSensor_Disable(void) ;

void IsrMotionSensor_SetPending(void) ;
void IsrMotionSensor_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IsrMotionSensor ISR. */
#define IsrMotionSensor_INTC_VECTOR            ((reg32 *) IsrMotionSensor__INTC_VECT)

/* Address of the IsrMotionSensor ISR priority. */
#define IsrMotionSensor_INTC_PRIOR             ((reg8 *) IsrMotionSensor__INTC_PRIOR_REG)

/* Priority of the IsrMotionSensor interrupt. */
#define IsrMotionSensor_INTC_PRIOR_NUMBER      IsrMotionSensor__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IsrMotionSensor interrupt. */
#define IsrMotionSensor_INTC_SET_EN            ((reg32 *) IsrMotionSensor__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IsrMotionSensor interrupt. */
#define IsrMotionSensor_INTC_CLR_EN            ((reg32 *) IsrMotionSensor__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IsrMotionSensor interrupt state to pending. */
#define IsrMotionSensor_INTC_SET_PD            ((reg32 *) IsrMotionSensor__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IsrMotionSensor interrupt. */
#define IsrMotionSensor_INTC_CLR_PD            ((reg32 *) IsrMotionSensor__INTC_CLR_PD_REG)



/* __IsrMotionSensor_INTC_H__ */
#endif
