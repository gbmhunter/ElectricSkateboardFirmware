/*******************************************************************************
* File Name: UartDebug.c
* Version 2.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "UartDebug.h"


/***************************************
* Local data allocation
***************************************/

static UartDebug_BACKUP_STRUCT  UartDebug_backup =
{
    /* enableState - disabled */
    0u,
};        



/*******************************************************************************
* Function Name: UartDebug_SaveConfig
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
* Global Variables:
*  UartDebug_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartDebug_SaveConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (CY_PSOC3_ES2 || CY_PSOC5_ES1)

        #if(UartDebug_CONTROL_REG_REMOVED == 0u)
            UartDebug_backup.cr = UartDebug_CONTROL_REG;
        #endif /* End UartDebug_CONTROL_REG_REMOVED */

        #if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
            UartDebug_backup.rx_period = UartDebug_RXBITCTR_PERIOD_REG;
            UartDebug_backup.rx_mask = UartDebug_RXSTATUS_MASK_REG;
            #if (UartDebug_RXHW_ADDRESS_ENABLED)
                UartDebug_backup.rx_addr1 = UartDebug_RXADDRESS1_REG;
                UartDebug_backup.rx_addr2 = UartDebug_RXADDRESS2_REG;
            #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */
        #endif /* End UartDebug_RX_ENABLED | UartDebug_HD_ENABLED*/

        #if(UartDebug_TX_ENABLED)
            #if(UartDebug_TXCLKGEN_DP)
                UartDebug_backup.tx_clk_ctr = UartDebug_TXBITCLKGEN_CTR_REG;
                UartDebug_backup.tx_clk_compl = UartDebug_TXBITCLKTX_COMPLETE_REG;
            #else
                UartDebug_backup.tx_period = UartDebug_TXBITCTR_PERIOD_REG;
            #endif /*End UartDebug_TXCLKGEN_DP */
            UartDebug_backup.tx_mask = UartDebug_TXSTATUS_MASK_REG;
        #endif /*End UartDebug_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (CY_PSOC3_ES3 || CY_PSOC5_ES2)

        #if(UartDebug_CONTROL_REG_REMOVED == 0u)
            UartDebug_backup.cr = UartDebug_CONTROL_REG;
        #endif /* End UartDebug_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: UartDebug_RestoreConfig
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
* Global Variables:
*  UartDebug_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartDebug_RestoreConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (CY_PSOC3_ES2 || CY_PSOC5_ES1)

        #if(UartDebug_CONTROL_REG_REMOVED == 0u)
            UartDebug_CONTROL_REG = UartDebug_backup.cr;
        #endif /* End UartDebug_CONTROL_REG_REMOVED */

        #if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
            UartDebug_RXBITCTR_PERIOD_REG = UartDebug_backup.rx_period;
            UartDebug_RXSTATUS_MASK_REG = UartDebug_backup.rx_mask;
            #if (UartDebug_RXHW_ADDRESS_ENABLED)
                UartDebug_RXADDRESS1_REG = UartDebug_backup.rx_addr1;
                UartDebug_RXADDRESS2_REG = UartDebug_backup.rx_addr2;
            #endif /* End UartDebug_RXHW_ADDRESS_ENABLED */
        #endif  /* End (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */

        #if(UartDebug_TX_ENABLED)
            #if(UartDebug_TXCLKGEN_DP)
                UartDebug_TXBITCLKGEN_CTR_REG = UartDebug_backup.tx_clk_ctr;
                UartDebug_TXBITCLKTX_COMPLETE_REG = UartDebug_backup.tx_clk_compl;
            #else
                UartDebug_TXBITCTR_PERIOD_REG = UartDebug_backup.tx_period;
            #endif /*End UartDebug_TXCLKGEN_DP */
            UartDebug_TXSTATUS_MASK_REG = UartDebug_backup.tx_mask;
        #endif /*End UartDebug_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (CY_PSOC3_ES3 || CY_PSOC5_ES2)

        #if(UartDebug_CONTROL_REG_REMOVED == 0u)
            UartDebug_CONTROL_REG = UartDebug_backup.cr;
        #endif /* End UartDebug_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: UartDebug_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UartDebug_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartDebug_Sleep(void)
{

    #if(UartDebug_RX_ENABLED || UartDebug_HD_ENABLED)
        if((UartDebug_RXSTATUS_ACTL_REG  & UartDebug_INT_ENABLE) != 0u) 
        {
            UartDebug_backup.enableState = 1u;
        }
        else
        {
            UartDebug_backup.enableState = 0u;
        }
    #else
        if((UartDebug_TXSTATUS_ACTL_REG  & UartDebug_INT_ENABLE) !=0u)
        {
            UartDebug_backup.enableState = 1u;
        }
        else
        {
            UartDebug_backup.enableState = 0u;
        }
    #endif /* End UartDebug_RX_ENABLED || UartDebug_HD_ENABLED*/

    UartDebug_Stop();
    UartDebug_SaveConfig();
}


/*******************************************************************************
* Function Name: UartDebug_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UartDebug_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartDebug_Wakeup(void)
{
    UartDebug_RestoreConfig();
    #if( (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) )
        UartDebug_ClearRxBuffer();
    #endif /* End (UartDebug_RX_ENABLED) || (UartDebug_HD_ENABLED) */
    #if(UartDebug_TX_ENABLED || UartDebug_HD_ENABLED)
        UartDebug_ClearTxBuffer();
    #endif /* End UartDebug_TX_ENABLED || UartDebug_HD_ENABLED */

    if(UartDebug_backup.enableState != 0u)
    {
        UartDebug_Enable();
    } 
}


/* [] END OF FILE */
