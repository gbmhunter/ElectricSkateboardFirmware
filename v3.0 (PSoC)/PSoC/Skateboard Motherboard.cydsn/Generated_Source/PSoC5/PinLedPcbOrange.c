/*******************************************************************************
* File Name: PinLedPcbOrange.c  
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
#include "PinLedPcbOrange.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLedPcbOrange__PORT == 15 && (PinLedPcbOrange__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLedPcbOrange_Write
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
void PinLedPcbOrange_Write(uint8 value) 
{
    uint8 staticBits = PinLedPcbOrange_DR & ~PinLedPcbOrange_MASK;
    PinLedPcbOrange_DR = staticBits | ((value << PinLedPcbOrange_SHIFT) & PinLedPcbOrange_MASK);
}


/*******************************************************************************
* Function Name: PinLedPcbOrange_SetDriveMode
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
void PinLedPcbOrange_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLedPcbOrange_0, mode);
}


/*******************************************************************************
* Function Name: PinLedPcbOrange_Read
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
*  Macro PinLedPcbOrange_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLedPcbOrange_Read(void) 
{
    return (PinLedPcbOrange_PS & PinLedPcbOrange_MASK) >> PinLedPcbOrange_SHIFT;
}


/*******************************************************************************
* Function Name: PinLedPcbOrange_ReadDataReg
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
uint8 PinLedPcbOrange_ReadDataReg(void) 
{
    return (PinLedPcbOrange_DR & PinLedPcbOrange_MASK) >> PinLedPcbOrange_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLedPcbOrange_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLedPcbOrange_ClearInterrupt
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
    uint8 PinLedPcbOrange_ClearInterrupt(void) 
    {
        return (PinLedPcbOrange_INTSTAT & PinLedPcbOrange_MASK) >> PinLedPcbOrange_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
