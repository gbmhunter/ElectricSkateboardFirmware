/*******************************************************************************
* File Name: PinXbeeIsSleep.c  
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
#include "PinXbeeIsSleep.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinXbeeIsSleep__PORT == 15 && (PinXbeeIsSleep__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinXbeeIsSleep_Write
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
void PinXbeeIsSleep_Write(uint8 value) 
{
    uint8 staticBits = PinXbeeIsSleep_DR & ~PinXbeeIsSleep_MASK;
    PinXbeeIsSleep_DR = staticBits | ((value << PinXbeeIsSleep_SHIFT) & PinXbeeIsSleep_MASK);
}


/*******************************************************************************
* Function Name: PinXbeeIsSleep_SetDriveMode
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
void PinXbeeIsSleep_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinXbeeIsSleep_0, mode);
}


/*******************************************************************************
* Function Name: PinXbeeIsSleep_Read
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
*  Macro PinXbeeIsSleep_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinXbeeIsSleep_Read(void) 
{
    return (PinXbeeIsSleep_PS & PinXbeeIsSleep_MASK) >> PinXbeeIsSleep_SHIFT;
}


/*******************************************************************************
* Function Name: PinXbeeIsSleep_ReadDataReg
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
uint8 PinXbeeIsSleep_ReadDataReg(void) 
{
    return (PinXbeeIsSleep_DR & PinXbeeIsSleep_MASK) >> PinXbeeIsSleep_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinXbeeIsSleep_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinXbeeIsSleep_ClearInterrupt
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
    uint8 PinXbeeIsSleep_ClearInterrupt(void) 
    {
        return (PinXbeeIsSleep_INTSTAT & PinXbeeIsSleep_MASK) >> PinXbeeIsSleep_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
