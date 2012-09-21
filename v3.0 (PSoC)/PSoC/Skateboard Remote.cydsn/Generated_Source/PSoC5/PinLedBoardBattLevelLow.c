/*******************************************************************************
* File Name: PinLedBoardBattLevelLow.c  
* Version 1.60
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "PinLedBoardBattLevelLow.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedBoardBattLevelLow__PORT == 15 && (PinLedBoardBattLevelLow__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLedBoardBattLevelLow_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void PinLedBoardBattLevelLow_Write(uint8 value) 
{
    uint8 staticBits = PinLedBoardBattLevelLow_DR & ~PinLedBoardBattLevelLow_MASK;
    PinLedBoardBattLevelLow_DR = staticBits | ((value << PinLedBoardBattLevelLow_SHIFT) & PinLedBoardBattLevelLow_MASK);
}


/*******************************************************************************
* Function Name: PinLedBoardBattLevelLow_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void PinLedBoardBattLevelLow_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLedBoardBattLevelLow_0, mode);
}


/*******************************************************************************
* Function Name: PinLedBoardBattLevelLow_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PinLedBoardBattLevelLow_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLedBoardBattLevelLow_Read(void) 
{
    return (PinLedBoardBattLevelLow_PS & PinLedBoardBattLevelLow_MASK) >> PinLedBoardBattLevelLow_SHIFT;
}


/*******************************************************************************
* Function Name: PinLedBoardBattLevelLow_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PinLedBoardBattLevelLow_ReadDataReg(void) 
{
    return (PinLedBoardBattLevelLow_DR & PinLedBoardBattLevelLow_MASK) >> PinLedBoardBattLevelLow_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLedBoardBattLevelLow_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLedBoardBattLevelLow_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PinLedBoardBattLevelLow_ClearInterrupt(void) 
    {
        return (PinLedBoardBattLevelLow_INTSTAT & PinLedBoardBattLevelLow_MASK) >> PinLedBoardBattLevelLow_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
