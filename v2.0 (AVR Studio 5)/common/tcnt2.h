/*
***************************************************************
* Geo's Wireless Skateboard
* tcnt2.h
* Written By: Geoffrey Hunter
* Last Modification: 05/01/2011
*
***************************************************************
*/

//***Header Guard***
#ifndef _TCNT2_H
#define _TCNT2_H

//***File Inclusions***
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*** Function Declarations ***/
void tcnt2_init(void);
void tcnt2_set_limit(uint8_t limit);
void tcnt2_enable(void);
void tcnt2_disable(void);

#endif
