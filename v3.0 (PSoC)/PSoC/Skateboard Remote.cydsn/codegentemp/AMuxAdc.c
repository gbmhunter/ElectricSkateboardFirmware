/*******************************************************************************
* File Name: AMuxAdc.c
* Version 1.50
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AMuxAdc.h"

uint8 AMuxAdc_initVar = 0u;
uint8 AMuxAdc_lastChannel = AMuxAdc_NULL_CHANNEL;


/*******************************************************************************
* Function Name: AMuxAdc_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Start(void)
{
    AMuxAdc_DisconnectAll();
    AMuxAdc_initVar = 1u;
}


/*******************************************************************************
* Function Name: AMuxAdc_Init
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Init(void)
{
    AMuxAdc_DisconnectAll();
}


/*******************************************************************************
* Function Name: AMuxAdc_Stop
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Stop(void)
{
    AMuxAdc_DisconnectAll();
}


/*******************************************************************************
* Function Name: AMuxAdc_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Select(uint8 channel) 
{
    AMuxAdc_DisconnectAll();        /* Disconnect all previous connections */
    AMuxAdc_Connect(channel);       /* Make the given selection */
    AMuxAdc_lastChannel = channel;  /* Update last channel */
}


/*******************************************************************************
* Function Name: AMuxAdc_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( AMuxAdc_lastChannel != AMuxAdc_NULL_CHANNEL)   /* Update last channel */
    {
        AMuxAdc_Disconnect(AMuxAdc_lastChannel);
    }

    /* Make the new channel connection */
    AMuxAdc_Connect(channel);
    AMuxAdc_lastChannel = channel;   /* Update last channel */
}


#if(AMuxAdc_MUXTYPE == AMuxAdc_MUX_DIFF)
/*******************************************************************************
* Function Name: AMuxAdc_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Connect(uint8 channel) 
{
    AMuxAdc_CYAMUXSIDE_A_Set(channel);
    AMuxAdc_CYAMUXSIDE_B_Set(channel);
}


/*******************************************************************************
* Function Name: AMuxAdc_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_Disconnect(uint8 channel) 
{
    AMuxAdc_CYAMUXSIDE_A_Unset(channel);
    AMuxAdc_CYAMUXSIDE_B_Unset(channel);
}
#endif


/*******************************************************************************
* Function Name: AMuxAdc_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMuxAdc_DisconnectAll(void) 
{
    uint8 chan;

#if(AMuxAdc_MUXTYPE == AMuxAdc_MUX_SINGLE)
    for(chan = 0; chan < AMuxAdc_CHANNELS ; chan++)
    {
        AMuxAdc_Unset(chan);
    }
#else
    for(chan = 0; chan < AMuxAdc_CHANNELS ; chan++)
    {
        AMuxAdc_CYAMUXSIDE_A_Unset(chan);
        AMuxAdc_CYAMUXSIDE_B_Unset(chan);
    }
#endif
}


/* [] END OF FILE */
