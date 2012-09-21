/*******************************************************************************
* File Name: PinLightFrontLeft.c  
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
#include "PinLightFrontLeft.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightFrontLeft__PORT == 15 && (PinLightFrontLeft__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLightFrontLeft_Write
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
void PinLightFrontLeft_Write(uint8 value) 
{
    uint8 staticBits = PinLightFrontLeft_DR & ~PinLightFrontLeft_MASK;
    PinLightFrontLeft_DR = staticBits | ((value << PinLightFrontLeft_SHIFT) & PinLightFrontLeft_MASK);
}


/*******************************************************************************
* Function Name: PinLightFrontLeft_SetDriveMode
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
void PinLightFrontLeft_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLightFrontLeft_0, mode);
}


/*******************************************************************************
* Function Name: PinLightFrontLeft_Read
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
*  Macro PinLightFrontLeft_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLightFrontLeft_Read(void) 
{
    return (PinLightFrontLeft_PS & PinLightFrontLeft_MASK) >> PinLightFrontLeft_SHIFT;
}


/*******************************************************************************
* Function Name: PinLightFrontLeft_ReadDataReg
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
uint8 PinLightFrontLeft_ReadDataReg(void) 
{
    return (PinLightFrontLeft_DR & PinLightFrontLeft_MASK) >> PinLightFrontLeft_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLightFrontLeft_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLightFrontLeft_ClearInterrupt
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
    uint8 PinLightFrontLeft_ClearInterrupt(void) 
    {
        return (PinLightFrontLeft_INTSTAT & PinLightFrontLeft_MASK) >> PinLightFrontLeft_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
