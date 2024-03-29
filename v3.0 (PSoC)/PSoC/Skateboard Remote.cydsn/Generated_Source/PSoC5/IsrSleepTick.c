/*******************************************************************************
* File Name: IsrSleepTick.c  
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
#include <IsrSleepTick.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START IsrSleepTick_intc` */

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
* Function Name: IsrSleepTick_Start
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
void IsrSleepTick_Start(void)
{
    /* For all we know the interrupt is active. */
    IsrSleepTick_Disable();

    /* Set the ISR to point to the IsrSleepTick Interrupt. */
    IsrSleepTick_SetVector(IsrSleepTick_Interrupt);

    /* Set the priority. */
    IsrSleepTick_SetPriority(IsrSleepTick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrSleepTick_Enable();
}

/*******************************************************************************
* Function Name: IsrSleepTick_StartEx
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
void IsrSleepTick_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    IsrSleepTick_Disable();

    /* Set the ISR to point to the IsrSleepTick Interrupt. */
    IsrSleepTick_SetVector(address);

    /* Set the priority. */
    IsrSleepTick_SetPriority(IsrSleepTick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrSleepTick_Enable();
}

/*******************************************************************************
* Function Name: IsrSleepTick_Stop
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
void IsrSleepTick_Stop(void) 
{
    /* Disable this interrupt. */
    IsrSleepTick_Disable();

    /* Set the ISR to point to the passive one. */
    IsrSleepTick_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: IsrSleepTick_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for IsrSleepTick.
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
CY_ISR(IsrSleepTick_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START IsrSleepTick_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: IsrSleepTick_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling IsrSleepTick_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use IsrSleepTick_StartEx instead.
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
void IsrSleepTick_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + IsrSleepTick__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: IsrSleepTick_GetVector
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
cyisraddress IsrSleepTick_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + IsrSleepTick__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: IsrSleepTick_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling IsrSleepTick_Start
*   or IsrSleepTick_StartEx will override any effect this method would have had. 
*	This method should only be called after IsrSleepTick_Start or 
*	IsrSleepTick_StartEx has been called. To set the initial
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
void IsrSleepTick_SetPriority(uint8 priority) 
{
    *IsrSleepTick_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: IsrSleepTick_GetPriority
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
uint8 IsrSleepTick_GetPriority(void) 
{
    uint8 priority;


    priority = *IsrSleepTick_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: IsrSleepTick_Enable
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
void IsrSleepTick_Enable(void) 
{
    /* Enable the general interrupt. */
    *IsrSleepTick_INTC_SET_EN = IsrSleepTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrSleepTick_GetState
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
uint8 IsrSleepTick_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*IsrSleepTick_INTC_SET_EN & IsrSleepTick__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: IsrSleepTick_Disable
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
void IsrSleepTick_Disable(void) 
{
    /* Disable the general interrupt. */
    *IsrSleepTick_INTC_CLR_EN = IsrSleepTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrSleepTick_SetPending
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
void IsrSleepTick_SetPending(void) 
{
    *IsrSleepTick_INTC_SET_PD = IsrSleepTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrSleepTick_ClearPending
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
void IsrSleepTick_ClearPending(void) 
{
    *IsrSleepTick_INTC_CLR_PD = IsrSleepTick__INTC_MASK;
}
