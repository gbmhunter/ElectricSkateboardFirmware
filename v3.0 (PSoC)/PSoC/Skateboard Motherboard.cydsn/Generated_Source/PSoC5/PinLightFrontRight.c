/*******************************************************************************
* File Name: PinLightFrontRight.c  
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
#include "PinLightFrontRight.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinLightFrontRight__PORT == 15 && (PinLightFrontRight__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinLightFrontRight_Write
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
void PinLightFrontRight_Write(uint8 value) 
{
    uint8 staticBits = PinLightFrontRight_DR & ~PinLightFrontRight_MASK;
    PinLightFrontRight_DR = staticBits | ((value << PinLightFrontRight_SHIFT) & PinLightFrontRight_MASK);
}


/*******************************************************************************
* Function Name: PinLightFrontRight_SetDriveMode
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
void PinLightFrontRight_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinLightFrontRight_0, mode);
}


/*******************************************************************************
* Function Name: PinLightFrontRight_Read
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
*  Macro PinLightFrontRight_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinLightFrontRight_Read(void) 
{
    return (PinLightFrontRight_PS & PinLightFrontRight_MASK) >> PinLightFrontRight_SHIFT;
}


/*******************************************************************************
* Function Name: PinLightFrontRight_ReadDataReg
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
uint8 PinLightFrontRight_ReadDataReg(void) 
{
    return (PinLightFrontRight_DR & PinLightFrontRight_MASK) >> PinLightFrontRight_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinLightFrontRight_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinLightFrontRight_ClearInterrupt
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
    uint8 PinLightFrontRight_ClearInterrupt(void) 
    {
        return (PinLightFrontRight_INTSTAT & PinLightFrontRight_MASK) >> PinLightFrontRight_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
