/*******************************************************************************
* File Name: AdcSar_PM.c
* Version 1.71
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "AdcSar.h"


/***************************************
* Local data allocation
***************************************/

static AdcSar_BACKUP_STRUCT  AdcSar_backup =
{
    AdcSar_DISABLED
};
    

/*******************************************************************************
* Function Name: AdcSar_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void AdcSar_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: AdcSar_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void AdcSar_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: AdcSar_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  AdcSar_backup - modified.
*
*******************************************************************************/
void AdcSar_Sleep(void)
{
    if((AdcSar_PWRMGR_SAR_REG  & AdcSar_ACT_PWR_SAR_EN) != 0u) 
    {
        AdcSar_backup.enableState = AdcSar_ENABLED;
        if((AdcSar_SAR_CSR0_REG & AdcSar_SAR_SOF_START_CONV) != 0u)
        {
            AdcSar_backup.enableState |= AdcSar_STARTED;
        }
        AdcSar_Stop();
    }
    else
    {
        AdcSar_backup.enableState = AdcSar_DISABLED;
    }
    /*AdcSar_SaveConfig();*/
}


/*******************************************************************************
* Function Name: AdcSar_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  AdcSar_backup - used. 
*
*******************************************************************************/
void AdcSar_Wakeup(void)
{
    /*AdcSar_RestoreConfig();*/
    if(AdcSar_backup.enableState != AdcSar_DISABLED)
    {
        AdcSar_Enable();
        if((AdcSar_backup.enableState & AdcSar_STARTED) != 0u)
        {
            AdcSar_StartConvert();
        }
    } 
}


/* [] END OF FILE */
