#include "crypt.h"


/*
 * An encrypting function - all encrypting and decrypting functions follow
 * this template:
 *    inbuffer :: 		the input message
 *    outbuffer ::		the output encoded/decoded message
 *    key ::			a generic pointer to an object that is the encoding key
 * 
 * This function is used to encrypt a message using Caesar's shift algorithm.
 */
#define BV(x) (1 << (x))
#define CLEARBIT(a,x) ((a) & (~BV(x)))
#define SETBIT(a,x) ((a) | (BV(x)))
#define ASSIGNBIT(a,v,x) (v==0)?CLEARBIT(a,x):SETBIT(a,x)
#define ISCLEAR(a,x) ((((a) & (BV(x))) == BV(x))?(0):(1))
#define ISSET(a,x) ((((a) & (BV(x))) == BV(x))?(1):(0))

void caesar(buffer_t *inmessage, buffer_t *outmessage, void *key)
{
	long i;
	int offset = *((uint8_t*)key) - 'a';
	
	for(i=0; i < inmessage->length; i++)
	{
		outmessage->buffer[i] = (inmessage->buffer[i] + offset) % ASCII_TABLE_SIZE;
	}
}

/*
 * Start here - replace me with a useful comment
 */
void decaesar(buffer_t *inmessage, buffer_t *outmessage, void *key)
{
	long i;
	int offset = *((uint8_t*)key) - 'a';
	
	for(i=0; i < inmessage->length; i++)
	{
		outmessage->buffer[i] = (inmessage->buffer[i] - offset) % ASCII_TABLE_SIZE;
	}
}

/* Decoding Message 2 */
void demessage2(buffer_t *inmessage, buffer_t *outmessage, void *key){

	printf("hello");
	/* Testing Code!!!
	uint8_t result1 = BV(3);
	printf("%u\n", result1);
	
	uint8_t result2 = CLEARBIT(255,3);
	printf("%u\n", result2);

	uint8_t result3 = SETBIT(127,7);
	printf("%u\n", result3);

	uint8_t result4 = ASSIGNBIT(255,0,7);
	printf("%u\n", result4);

	uint8_t result5 = ISCLEAR(127,6);
	printf("%u\n", result5);

	uint8_t result6 = ISSET(127,6);
	printf("%u\n", result6);
	*/

	long i;
		
	for(i=0; i < inmessage->length; i++){

		int total;
		int parity;
		int counter;
		uint8_t chari = inmessage->buffer[i];

		/* Finding parity */
		for(counter=0; counter<8; counter++){
			
			total = total + ISSET(chari,counter);
		}
		parity = total%2;
		chari = ASSIGNBIT(chari, parity, 7);

		/* Swapping bits 4 and 7 */
		int bit7;
		int bit4;
		if (ISSET(chari,7)){
			bit7 = 1;
		}
		else{
			bit7 = 0;
		}
		if(ISSET(chari,4)){
			bit4 = 1;
		}
		else{
			bit4 = 0;
		}
		chari = ASSIGNBIT(chari, bit7, 4);
		chari = ASSIGNBIT(chari, bit4, 7);

		/* Key Transormation */
		if (parity){
			chari = (10 ^ chari);
		}

		/* Storing Converted Character Back Into Array */
		outmessage->buffer[i] = chari;
		printf("%u\n", chari);
		printf("hello");

	}
	printf("hello");
}

/* A function to find the encoding/decoding function from a command-line text string */
encoder_function_t get_encoder(char* encoder_name) 
{
	if (strcmp(encoder_name, "caesar") == 0)
	{
		return caesar;
	}

	if (strcmp(encoder_name, "decaesar") == 0)
	{
		return decaesar;
	}

	if (strcmp(encoder_name, "demessage2") == 0)
	{
		return demessage2;
	}


	
	printf("Encoder/Decoder not found\n");
	exit(1);
	return NULL;
}

