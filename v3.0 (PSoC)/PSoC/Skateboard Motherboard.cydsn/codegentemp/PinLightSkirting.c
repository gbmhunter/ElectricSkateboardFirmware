/*******************************************************************************
* File Name: PinLightSkirting.c  
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
#include "PinLightSkirting.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightSkirting__PORT == 15 && (PinLightSkirting__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLightSkirting_Write
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
void PinLightSkirting_Write(uint8 value) 
{
    uint8 staticBits = PinLightSkirting_DR & ~PinLightSkirting_MASK;
    PinLightSkirting_DR = staticBits | ((value << PinLightSkirting_SHIFT) & PinLightSkirting_MASK);
}


/*******************************************************************************
* Function Name: PinLightSkirting_SetDriveMode
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
void PinLightSkirting_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLightSkirting_0, mode);
}


/*******************************************************************************
* Function Name: PinLightSkirting_Read
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
*  Macro PinLightSkirting_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLightSkirting_Read(void) 
{
    return (PinLightSkirting_PS & PinLightSkirting_MASK) >> PinLightSkirting_SHIFT;
}


/*******************************************************************************
* Function Name: PinLightSkirting_ReadDataReg
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
uint8 PinLightSkirting_ReadDataReg(void) 
{
    return (PinLightSkirting_DR & PinLightSkirting_MASK) >> PinLightSkirting_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLightSkirting_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLightSkirting_ClearInterrupt
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
    uint8 PinLightSkirting_ClearInterrupt(void) 
    {
        return (PinLightSkirting_INTSTAT & PinLightSkirting_MASK) >> PinLightSkirting_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
