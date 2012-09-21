/*******************************************************************************
* File Name: ISR_MOTION_ALARM.c  
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
#include <ISR_MOTION_ALARM.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_MOTION_ALARM_intc` */

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
* Function Name: ISR_MOTION_ALARM_Start
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
void ISR_MOTION_ALARM_Start(void)
{
    /* For all we know the interrupt is active. */
    ISR_MOTION_ALARM_Disable();

    /* Set the ISR to point to the ISR_MOTION_ALARM Interrupt. */
    ISR_MOTION_ALARM_SetVector(ISR_MOTION_ALARM_Interrupt);

    /* Set the priority. */
    ISR_MOTION_ALARM_SetPriority(ISR_MOTION_ALARM_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_MOTION_ALARM_Enable();
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_StartEx
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
void ISR_MOTION_ALARM_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ISR_MOTION_ALARM_Disable();

    /* Set the ISR to point to the ISR_MOTION_ALARM Interrupt. */
    ISR_MOTION_ALARM_SetVector(address);

    /* Set the priority. */
    ISR_MOTION_ALARM_SetPriority(ISR_MOTION_ALARM_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_MOTION_ALARM_Enable();
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_Stop
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
void ISR_MOTION_ALARM_Stop(void) 
{
    /* Disable this interrupt. */
    ISR_MOTION_ALARM_Disable();

    /* Set the ISR to point to the passive one. */
    ISR_MOTION_ALARM_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ISR_MOTION_ALARM.
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
CY_ISR(ISR_MOTION_ALARM_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ISR_MOTION_ALARM_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ISR_MOTION_ALARM_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use ISR_MOTION_ALARM_StartEx instead.
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
void ISR_MOTION_ALARM_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + ISR_MOTION_ALARM__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_GetVector
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
cyisraddress ISR_MOTION_ALARM_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + ISR_MOTION_ALARM__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling ISR_MOTION_ALARM_Start
*   or ISR_MOTION_ALARM_StartEx will override any effect this method would have had. 
*	This method should only be called after ISR_MOTION_ALARM_Start or 
*	ISR_MOTION_ALARM_StartEx has been called. To set the initial
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
void ISR_MOTION_ALARM_SetPriority(uint8 priority) 
{
    *ISR_MOTION_ALARM_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_GetPriority
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
uint8 ISR_MOTION_ALARM_GetPriority(void) 
{
    uint8 priority;


    priority = *ISR_MOTION_ALARM_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_Enable
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
void ISR_MOTION_ALARM_Enable(void) 
{
    /* Enable the general interrupt. */
    *ISR_MOTION_ALARM_INTC_SET_EN = ISR_MOTION_ALARM__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_GetState
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
uint8 ISR_MOTION_ALARM_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*ISR_MOTION_ALARM_INTC_SET_EN & ISR_MOTION_ALARM__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_Disable
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
void ISR_MOTION_ALARM_Disable(void) 
{
    /* Disable the general interrupt. */
    *ISR_MOTION_ALARM_INTC_CLR_EN = ISR_MOTION_ALARM__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_SetPending
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
void ISR_MOTION_ALARM_SetPending(void) 
{
    *ISR_MOTION_ALARM_INTC_SET_PD = ISR_MOTION_ALARM__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_MOTION_ALARM_ClearPending
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
void ISR_MOTION_ALARM_ClearPending(void) 
{
    *ISR_MOTION_ALARM_INTC_CLR_PD = ISR_MOTION_ALARM__INTC_MASK;
}
