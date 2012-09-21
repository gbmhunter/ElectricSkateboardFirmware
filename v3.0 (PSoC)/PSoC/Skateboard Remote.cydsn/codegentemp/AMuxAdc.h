/*******************************************************************************
* File Name: AMuxAdc.h
* Version 1.50
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMuxAdc_H)
#define CY_AMUX_AMuxAdc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMuxAdc_Start(void);
void AMuxAdc_Init(void);
void AMuxAdc_Stop(void);
void AMuxAdc_Select(uint8 channel) ;
void AMuxAdc_FastSelect(uint8 channel) ;
void AMuxAdc_DisconnectAll(void) ;
/* The Connect and Disconnect functions are declared elsewhere */
/* void AMuxAdc_Connect(uint8 channel); */
/* void AMuxAdc_Disconnect(uint8 channel); */


/***************************************
*     Initial Parameter Constants
***************************************/

#define AMuxAdc_CHANNELS  2
#define AMuxAdc_MUXTYPE   1


/***************************************
*             API Constants
***************************************/

#define AMuxAdc_NULL_CHANNEL  0xFFu
#define AMuxAdc_MUX_SINGLE   1
#define AMuxAdc_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMuxAdc_MUXTYPE == AMuxAdc_MUX_SINGLE
# define AMuxAdc_Connect(channel) AMuxAdc_Set(channel)
# define AMuxAdc_Disconnect(channel) AMuxAdc_Unset(channel)
#else
void AMuxAdc_Connect(uint8 channel) ;
void AMuxAdc_Disconnect(uint8 channel) ;
#endif

#endif /* CY_AMUX_AMuxAdc_H */


/* [] END OF FILE */
