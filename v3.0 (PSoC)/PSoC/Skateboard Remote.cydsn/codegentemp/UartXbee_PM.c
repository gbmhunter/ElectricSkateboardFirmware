/*******************************************************************************
* File Name: UartXbee.c
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

#include "UartXbee.h"


/***************************************
* Local data allocation
***************************************/

static UartXbee_BACKUP_STRUCT  UartXbee_backup =
{
    /* enableState - disabled */
    0u,
};        



/*******************************************************************************
* Function Name: UartXbee_SaveConfig
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
*  UartXbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartXbee_SaveConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (CY_PSOC3_ES2 || CY_PSOC5_ES1)

        #if(UartXbee_CONTROL_REG_REMOVED == 0u)
            UartXbee_backup.cr = UartXbee_CONTROL_REG;
        #endif /* End UartXbee_CONTROL_REG_REMOVED */

        #if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
            UartXbee_backup.rx_period = UartXbee_RXBITCTR_PERIOD_REG;
            UartXbee_backup.rx_mask = UartXbee_RXSTATUS_MASK_REG;
            #if (UartXbee_RXHW_ADDRESS_ENABLED)
                UartXbee_backup.rx_addr1 = UartXbee_RXADDRESS1_REG;
                UartXbee_backup.rx_addr2 = UartXbee_RXADDRESS2_REG;
            #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */
        #endif /* End UartXbee_RX_ENABLED | UartXbee_HD_ENABLED*/

        #if(UartXbee_TX_ENABLED)
            #if(UartXbee_TXCLKGEN_DP)
                UartXbee_backup.tx_clk_ctr = UartXbee_TXBITCLKGEN_CTR_REG;
                UartXbee_backup.tx_clk_compl = UartXbee_TXBITCLKTX_COMPLETE_REG;
            #else
                UartXbee_backup.tx_period = UartXbee_TXBITCTR_PERIOD_REG;
            #endif /*End UartXbee_TXCLKGEN_DP */
            UartXbee_backup.tx_mask = UartXbee_TXSTATUS_MASK_REG;
        #endif /*End UartXbee_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (CY_PSOC3_ES3 || CY_PSOC5_ES2)

        #if(UartXbee_CONTROL_REG_REMOVED == 0u)
            UartXbee_backup.cr = UartXbee_CONTROL_REG;
        #endif /* End UartXbee_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: UartXbee_RestoreConfig
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
*  UartXbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartXbee_RestoreConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (CY_PSOC3_ES2 || CY_PSOC5_ES1)

        #if(UartXbee_CONTROL_REG_REMOVED == 0u)
            UartXbee_CONTROL_REG = UartXbee_backup.cr;
        #endif /* End UartXbee_CONTROL_REG_REMOVED */

        #if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
            UartXbee_RXBITCTR_PERIOD_REG = UartXbee_backup.rx_period;
            UartXbee_RXSTATUS_MASK_REG = UartXbee_backup.rx_mask;
            #if (UartXbee_RXHW_ADDRESS_ENABLED)
                UartXbee_RXADDRESS1_REG = UartXbee_backup.rx_addr1;
                UartXbee_RXADDRESS2_REG = UartXbee_backup.rx_addr2;
            #endif /* End UartXbee_RXHW_ADDRESS_ENABLED */
        #endif  /* End (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */

        #if(UartXbee_TX_ENABLED)
            #if(UartXbee_TXCLKGEN_DP)
                UartXbee_TXBITCLKGEN_CTR_REG = UartXbee_backup.tx_clk_ctr;
                UartXbee_TXBITCLKTX_COMPLETE_REG = UartXbee_backup.tx_clk_compl;
            #else
                UartXbee_TXBITCTR_PERIOD_REG = UartXbee_backup.tx_period;
            #endif /*End UartXbee_TXCLKGEN_DP */
            UartXbee_TXSTATUS_MASK_REG = UartXbee_backup.tx_mask;
        #endif /*End UartXbee_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (CY_PSOC3_ES3 || CY_PSOC5_ES2)

        #if(UartXbee_CONTROL_REG_REMOVED == 0u)
            UartXbee_CONTROL_REG = UartXbee_backup.cr;
        #endif /* End UartXbee_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: UartXbee_Sleep
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
*  UartXbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartXbee_Sleep(void)
{

    #if(UartXbee_RX_ENABLED || UartXbee_HD_ENABLED)
        if((UartXbee_RXSTATUS_ACTL_REG  & UartXbee_INT_ENABLE) != 0u) 
        {
            UartXbee_backup.enableState = 1u;
        }
        else
        {
            UartXbee_backup.enableState = 0u;
        }
    #else
        if((UartXbee_TXSTATUS_ACTL_REG  & UartXbee_INT_ENABLE) !=0u)
        {
            UartXbee_backup.enableState = 1u;
        }
        else
        {
            UartXbee_backup.enableState = 0u;
        }
    #endif /* End UartXbee_RX_ENABLED || UartXbee_HD_ENABLED*/

    UartXbee_Stop();
    UartXbee_SaveConfig();
}


/*******************************************************************************
* Function Name: UartXbee_Wakeup
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
*  UartXbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UartXbee_Wakeup(void)
{
    UartXbee_RestoreConfig();
    #if( (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) )
        UartXbee_ClearRxBuffer();
    #endif /* End (UartXbee_RX_ENABLED) || (UartXbee_HD_ENABLED) */
    #if(UartXbee_TX_ENABLED || UartXbee_HD_ENABLED)
        UartXbee_ClearTxBuffer();
    #endif /* End UartXbee_TX_ENABLED || UartXbee_HD_ENABLED */

    if(UartXbee_backup.enableState != 0u)
    {
        UartXbee_Enable();
    } 
}


/* [] END OF FILE */
