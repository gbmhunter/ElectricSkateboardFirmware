#include "crypt.h"
#include "math.h"


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
#define ASSIGNBIT(a,x,v) (v==0)?CLEARBIT(a,x):SETBIT(a,x)
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
void demessage2(buffer_t *inmessage, buffer_t *outmessage, void *key)
{

	long i;
	
	for(i=0; i < inmessage->length; i++)
	{	
		uint8_t chari = inmessage->buffer[i];
		
		/* Decrypt Step 1 */
		uint8_t tempchari = (chari ^ 10);
		uint8_t total = 0;
		uint8_t parity = 0;
		int cnt = 0;
		for(cnt=0; cnt < 8; cnt++)
		{
			total = total + ISSET(tempchari,cnt);
		}
		parity = total % 2;
		if(parity){
		 chari = tempchari;
		}
		
		/* Decrypt Step 2 */
		int bit_4 = ISSET(chari, 4);
		int bit_7 = ISSET(chari, 7);
		chari = ASSIGNBIT(chari,4,bit_7);
		chari = ASSIGNBIT(chari,7,bit_4);

		/* Decrypt Step 3 */
		total = 0;
		uint8_t partialparity = 0;
		cnt = 0;
		for(cnt=0; cnt < 8; cnt++)
		{
			total = total + ISSET(chari,cnt);
		}
		parity = ISSET(chari,7);
		partialparity = (total - ISSET(chari,7)) % 2;

		chari = ASSIGNBIT(chari,7,(parity ^ partialparity));

		/* Putting decrypted character back in message */
		outmessage->buffer[i] = chari;	
	}
}

/* Decoding Message 3 */
void demessage3(buffer_t *inmessage, buffer_t *outmessage, void *key)
{

	long i;
	int word24;
	
	for(i=0; i < inmessage->length; i++)
	{	
		uint8_t chari = inmessage->buffer[i];
		int cnt_3 = (i+1) % 3;



		if(cnt_3 == 0){

			int base=1;
			int e;
			for(e=1;e<=16;e++){
				base = base*2;

			}
			word24 = word24 * base;
			word24 = word24 + chari;
			printf("%u\n", word24);

			int position;
			uint8_t letter1=0;
			uint8_t letter2=0;
			uint8_t letter3=0;
			uint8_t letter4=0;
			for(position=18; position<25; position++){
		
				letter1 = ASSIGNBIT(letter1,(position-18),ISSET(word24,position));
		
			}
			outmessage->buffer[i] = letter1;
			word24 = 0;
		}
		else{
			int base=1;
			int e;
			for(e=1;e<=(8*(cnt_3 - 1));e++){
				base = base*2;

			}
			word24 = word24 * base;
			word24 = word24 + chari;
			printf("%u\n", word24);

		}

		
	}
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

	if (strcmp(encoder_name, "demessage3") == 0)
	{
		return demessage3;
	}
	
	printf("Encoder/Decoder not found\n");
	exit(1);
	return NULL;
}

