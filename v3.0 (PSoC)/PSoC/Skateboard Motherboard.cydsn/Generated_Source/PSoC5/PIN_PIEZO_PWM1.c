/*******************************************************************************
* File Name: PIN_PIEZO_PWM1.c  
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
#include "PIN_PIEZO_PWM1.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PIN_PIEZO_PWM1__PORT == 15 && (PIN_PIEZO_PWM1__MASK & 0xC0))

/*******************************************************************************
* Function Name: PIN_PIEZO_PWM1_Write
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
void PIN_PIEZO_PWM1_Write(uint8 value) 
{
    uint8 staticBits = PIN_PIEZO_PWM1_DR & ~PIN_PIEZO_PWM1_MASK;
    PIN_PIEZO_PWM1_DR = staticBits | ((value << PIN_PIEZO_PWM1_SHIFT) & PIN_PIEZO_PWM1_MASK);
}


/*******************************************************************************
* Function Name: PIN_PIEZO_PWM1_SetDriveMode
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
void PIN_PIEZO_PWM1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PIN_PIEZO_PWM1_0, mode);
}


/*******************************************************************************
* Function Name: PIN_PIEZO_PWM1_Read
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
*  Macro PIN_PIEZO_PWM1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PIN_PIEZO_PWM1_Read(void) 
{
    return (PIN_PIEZO_PWM1_PS & PIN_PIEZO_PWM1_MASK) >> PIN_PIEZO_PWM1_SHIFT;
}


/*******************************************************************************
* Function Name: PIN_PIEZO_PWM1_ReadDataReg
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
uint8 PIN_PIEZO_PWM1_ReadDataReg(void) 
{
    return (PIN_PIEZO_PWM1_DR & PIN_PIEZO_PWM1_MASK) >> PIN_PIEZO_PWM1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PIN_PIEZO_PWM1_INTSTAT) 

    /*******************************************************************************
    * Function Name: PIN_PIEZO_PWM1_ClearInterrupt
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
    uint8 PIN_PIEZO_PWM1_ClearInterrupt(void) 
    {
        return (PIN_PIEZO_PWM1_INTSTAT & PIN_PIEZO_PWM1_MASK) >> PIN_PIEZO_PWM1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
