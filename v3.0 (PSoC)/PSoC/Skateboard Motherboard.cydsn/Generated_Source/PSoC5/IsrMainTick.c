/*******************************************************************************
* File Name: IsrMainTick.c  
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
#include <IsrMainTick.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START IsrMainTick_intc` */

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
* Function Name: IsrMainTick_Start
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
void IsrMainTick_Start(void)
{
    /* For all we know the interrupt is active. */
    IsrMainTick_Disable();

    /* Set the ISR to point to the IsrMainTick Interrupt. */
    IsrMainTick_SetVector(IsrMainTick_Interrupt);

    /* Set the priority. */
    IsrMainTick_SetPriority(IsrMainTick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrMainTick_Enable();
}

/*******************************************************************************
* Function Name: IsrMainTick_StartEx
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
void IsrMainTick_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    IsrMainTick_Disable();

    /* Set the ISR to point to the IsrMainTick Interrupt. */
    IsrMainTick_SetVector(address);

    /* Set the priority. */
    IsrMainTick_SetPriority(IsrMainTick_INTC_PRIOR_NUMBER);

    /* Enable it. */
    IsrMainTick_Enable();
}

/*******************************************************************************
* Function Name: IsrMainTick_Stop
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
void IsrMainTick_Stop(void) 
{
    /* Disable this interrupt. */
    IsrMainTick_Disable();

    /* Set the ISR to point to the passive one. */
    IsrMainTick_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: IsrMainTick_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for IsrMainTick.
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
CY_ISR(IsrMainTick_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START IsrMainTick_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: IsrMainTick_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling IsrMainTick_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use IsrMainTick_StartEx instead.
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
void IsrMainTick_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + IsrMainTick__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: IsrMainTick_GetVector
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
cyisraddress IsrMainTick_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + IsrMainTick__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: IsrMainTick_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling IsrMainTick_Start
*   or IsrMainTick_StartEx will override any effect this method would have had. 
*	This method should only be called after IsrMainTick_Start or 
*	IsrMainTick_StartEx has been called. To set the initial
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
void IsrMainTick_SetPriority(uint8 priority) 
{
    *IsrMainTick_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: IsrMainTick_GetPriority
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
uint8 IsrMainTick_GetPriority(void) 
{
    uint8 priority;


    priority = *IsrMainTick_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: IsrMainTick_Enable
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
void IsrMainTick_Enable(void) 
{
    /* Enable the general interrupt. */
    *IsrMainTick_INTC_SET_EN = IsrMainTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMainTick_GetState
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
uint8 IsrMainTick_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*IsrMainTick_INTC_SET_EN & IsrMainTick__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: IsrMainTick_Disable
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
void IsrMainTick_Disable(void) 
{
    /* Disable the general interrupt. */
    *IsrMainTick_INTC_CLR_EN = IsrMainTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMainTick_SetPending
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
void IsrMainTick_SetPending(void) 
{
    *IsrMainTick_INTC_SET_PD = IsrMainTick__INTC_MASK;
}

/*******************************************************************************
* Function Name: IsrMainTick_ClearPending
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
void IsrMainTick_ClearPending(void) 
{
    *IsrMainTick_INTC_CLR_PD = IsrMainTick__INTC_MASK;
}
