/*******************************************************************************
* File Name: PIN_PWM.c  
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
#include "PIN_PWM.h"

/* APIs are not generated for P15[7:6] */
#if !(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 &&\
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_PRODUCTION &&\
	 PIN_PWM__PORT == 15 && (PIN_PWM__MASK & 0xC0))

/*******************************************************************************
* Function Name: PIN_PWM_Write
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
void PIN_PWM_Write(uint8 value) 
{
    uint8 staticBits = PIN_PWM_DR & ~PIN_PWM_MASK;
    PIN_PWM_DR = staticBits | ((value << PIN_PWM_SHIFT) & PIN_PWM_MASK);
}


/*******************************************************************************
* Function Name: PIN_PWM_SetDriveMode
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
void PIN_PWM_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PIN_PWM_0, mode);
}


/*******************************************************************************
* Function Name: PIN_PWM_Read
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
*  Macro PIN_PWM_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PIN_PWM_Read(void) 
{
    return (PIN_PWM_PS & PIN_PWM_MASK) >> PIN_PWM_SHIFT;
}


/*******************************************************************************
* Function Name: PIN_PWM_ReadDataReg
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
uint8 PIN_PWM_ReadDataReg(void) 
{
    return (PIN_PWM_DR & PIN_PWM_MASK) >> PIN_PWM_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PIN_PWM_INTSTAT) 

    /*******************************************************************************
    * Function Name: PIN_PWM_ClearInterrupt
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
    uint8 PIN_PWM_ClearInterrupt(void) 
    {
        return (PIN_PWM_INTSTAT & PIN_PWM_MASK) >> PIN_PWM_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
