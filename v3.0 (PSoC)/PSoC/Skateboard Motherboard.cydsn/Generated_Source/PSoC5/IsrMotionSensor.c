/*******************************************************************************
* File Name: IsrMotionSensor.c  
* Version 1.50
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <IsrMotionSensor.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START IsrMotionSensor_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE	16
#endif
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);

/*******************************************************************************
* Function Name: IsrMotionSensor_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void IsrMotionSensor_Start(void)
{
    /* For all we know the interrupt is active. */
    IsrMotionSensor_Disable();

    /* Set the ISR to point to the IsrMotionSensor Interrupt. */
    IsrMotionSensor_SetVector(IsrMotionSensor_Interrupt);

    /* Set the priority. */
    IsrMotionSensor_SetPriority(IsrMotionSensor_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrMotionSensor_Enable();
}

/*******************************************************************************
* Function Name: IsrMotionSensor_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void IsrMotionSensor_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    IsrMotionSensor_Disable();

    /* Set the ISR to point to the IsrMotionSensor Interrupt. */
    IsrMotionSensor_SetVector(address);

    /* Set the priority. */
    IsrMotionSensor_SetPriority(IsrMotionSensor_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrMotionSensor_Enable();
}

/*******************************************************************************
* Function Name: IsrMotionSensor_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void IsrMotionSensor_Stop(void) 
{
    /* Disable this interrupt. */
    IsrMotionSensor_Disable();

    /* Set the ISR to point to the passive one. */
    IsrMotionSensor_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: IsrMotionSensor_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for IsrMotionSensor.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(IsrMotionSensor_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START IsrMotionSensor_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: IsrMotionSensor_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling IsrMotionSensor_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use IsrMotionSensor_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + IsrMotionSensor__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress IsrMotionSensor_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + IsrMotionSensor__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: IsrMotionSensor_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling IsrMotionSensor_Start
*   or IsrMotionSensor_StartEx will override any effect this method would have had. 
*	This method should only be called after IsrMotionSensor_Start or 
*	IsrMotionSensor_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_SetPriority(uint8 priority) 
{
    *IsrMotionSensor_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 IsrMotionSensor_GetPriority(void) 
{
    uint8 priority;


    priority = *IsrMotionSensor_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_Enable(void) 
{
    /* Enable the general interrupt. */
    *IsrMotionSensor_INTC_SET_EN = IsrMotionSensor__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 IsrMotionSensor_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*IsrMotionSensor_INTC_SET_EN & IsrMotionSensor__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_Disable(void) 
{
    /* Disable the general interrupt. */
    *IsrMotionSensor_INTC_CLR_EN = IsrMotionSensor__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_SetPending(void) 
{
    *IsrMotionSensor_INTC_SET_PD = IsrMotionSensor__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMotionSensor_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void IsrMotionSensor_ClearPending(void) 
{
    *IsrMotionSensor_INTC_CLR_PD = IsrMotionSensor__INTC_MASK;
}
