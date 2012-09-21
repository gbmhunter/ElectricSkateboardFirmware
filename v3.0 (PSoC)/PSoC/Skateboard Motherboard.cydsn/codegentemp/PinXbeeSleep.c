/*******************************************************************************
* File Name: PinXbeeSleep.c  
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
#include "PinXbeeSleep.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PinXbeeSleep__PORT == 15 && (PinXbeeSleep__MASK & 0xC0))

/*******************************************************************************
* Function Name: PinXbeeSleep_Write
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
void PinXbeeSleep_Write(uint8 value) 
{
    uint8 staticBits = PinXbeeSleep_DR & ~PinXbeeSleep_MASK;
    PinXbeeSleep_DR = staticBits | ((value << PinXbeeSleep_SHIFT) & PinXbeeSleep_MASK);
}


/*******************************************************************************
* Function Name: PinXbeeSleep_SetDriveMode
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
void PinXbeeSleep_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PinXbeeSleep_0, mode);
}


/*******************************************************************************
* Function Name: PinXbeeSleep_Read
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
*  Macro PinXbeeSleep_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PinXbeeSleep_Read(void) 
{
    return (PinXbeeSleep_PS & PinXbeeSleep_MASK) >> PinXbeeSleep_SHIFT;
}


/*******************************************************************************
* Function Name: PinXbeeSleep_ReadDataReg
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
uint8 PinXbeeSleep_ReadDataReg(void) 
{
    return (PinXbeeSleep_DR & PinXbeeSleep_MASK) >> PinXbeeSleep_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PinXbeeSleep_INTSTAT) 

    /*******************************************************************************
    * Function Name: PinXbeeSleep_ClearInterrupt
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
    uint8 PinXbeeSleep_ClearInterrupt(void) 
    {
        return (PinXbeeSleep_INTSTAT & PinXbeeSleep_MASK) >> PinXbeeSleep_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
