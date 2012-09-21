#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdlib.h>
#include <math.h>
#include "stdint.h"

/*
 * Function Prototypes
 */
char* binary_string(char result[], uint8_t value);
uint8_t binary_value(char string[]);

/*
 * Define some commonly used bit manipulation MACROS
 */
#define BV(x)		 		(1 << (x))
#define CLEARBIT(a,x)		((a) & ~BV((x)))
#define SETBIT(a,x)			((a) | BV((x)))
#define ASSIGNBIT(a,x,v)	((v) ? SETBIT((a),(x)) : CLEARBIT((a),(x)))
#define ISCLEAR(a,x)		((a) & BV((x)) ? 0 : 1)
#define ISSET(a,x)			((a) & BV((x)) ? 1 : 0)

#endif /*UTILITIES_H_*/
