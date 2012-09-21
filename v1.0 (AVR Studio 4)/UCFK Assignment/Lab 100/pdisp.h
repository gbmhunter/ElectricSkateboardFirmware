#ifndef PDISP_H_
#define PDISP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif
	void *thread_main1( void *ptr );
	void *thread_main2( void *ptr );
	void *thread_main3( void *ptr );
#ifdef __cplusplus
}
#endif

extern volatile uint8_t PORTB;
extern volatile uint8_t PORTC;
extern volatile uint8_t PORTD;
extern volatile uint8_t TCNT0;
extern volatile uint16_t TCNT1;
extern volatile uint8_t TCNT2;

typedef struct thread_command_line {
	int argc;
	char **argv;
	void *userdata;
}  thread_command_line_t;

#endif /*PDISP_H_*/
