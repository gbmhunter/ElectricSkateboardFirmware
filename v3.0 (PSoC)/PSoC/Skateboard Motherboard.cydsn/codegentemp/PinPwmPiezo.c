/*******************************************************************************
* File Name: PinPwmPiezo.c  
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
#include "PinPwmPiezo.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinPwmPiezo__PORT == 15 && (PinPwmPiezo__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinPwmPiezo_Write
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
void PinPwmPiezo_Write(uint8 value) 
{
    uint8 staticBits = PinPwmPiezo_DR & ~PinPwmPiezo_MASK;
    PinPwmPiezo_DR = staticBits | ((value << PinPwmPiezo_SHIFT) & PinPwmPiezo_MASK);
}


/*******************************************************************************
* Function Name: PinPwmPiezo_SetDriveMode
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
void PinPwmPiezo_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinPwmPiezo_0, mode);
}


/*******************************************************************************
* Function Name: PinPwmPiezo_Read
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
*  Macro PinPwmPiezo_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinPwmPiezo_Read(void) 
{
    return (PinPwmPiezo_PS & PinPwmPiezo_MASK) >> PinPwmPiezo_SHIFT;
}


/*******************************************************************************
* Function Name: PinPwmPiezo_ReadDataReg
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
uint8 PinPwmPiezo_ReadDataReg(void) 
{
    return (PinPwmPiezo_DR & PinPwmPiezo_MASK) >> PinPwmPiezo_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinPwmPiezo_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinPwmPiezo_ClearInterrupt
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
    uint8 PinPwmPiezo_ClearInterrupt(void) 
    {
        return (PinPwmPiezo_INTSTAT & PinPwmPiezo_MASK) >> PinPwmPiezo_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
