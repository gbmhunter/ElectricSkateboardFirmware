/*******************************************************************************
* File Name: PinLightRear.c  
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
#include "PinLightRear.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightRear__PORT == 15 && (PinLightRear__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLightRear_Write
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
void PinLightRear_Write(uint8 value) 
{
    uint8 staticBits = PinLightRear_DR & ~PinLightRear_MASK;
    PinLightRear_DR = staticBits | ((value << PinLightRear_SHIFT) & PinLightRear_MASK);
}


/*******************************************************************************
* Function Name: PinLightRear_SetDriveMode
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
void PinLightRear_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLightRear_0, mode);
}


/*******************************************************************************
* Function Name: PinLightRear_Read
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
*  Macro PinLightRear_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLightRear_Read(void) 
{
    return (PinLightRear_PS & PinLightRear_MASK) >> PinLightRear_SHIFT;
}


/*******************************************************************************
* Function Name: PinLightRear_ReadDataReg
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
uint8 PinLightRear_ReadDataReg(void) 
{
    return (PinLightRear_DR & PinLightRear_MASK) >> PinLightRear_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLightRear_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLightRear_ClearInterrupt
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
    uint8 PinLightRear_ClearInterrupt(void) 
    {
        return (PinLightRear_INTSTAT & PinLightRear_MASK) >> PinLightRear_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
