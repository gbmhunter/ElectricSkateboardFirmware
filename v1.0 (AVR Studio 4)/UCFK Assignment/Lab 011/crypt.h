#ifndef CRYPT_H_
#define CRYPT_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>


/*
 * Define a memory structure for handling message objects
 *   _length :: 		length of the message
 *   _buffer_size ::	size of the memory (buffer) _length < _buffer_szie
 *   _buffer ::			message array data is here
 */ 
typedef struct {
	long length;
	long buffer_size;
	uint8_t *buffer;
} buffer_t;

/*
 * Define a union of key types
 */
typedef union {
	char charkey;
	long hexkey;
} key2_t;
enum {CHARKEY, HEXKEY};

/*
 * Define a structure for holding the command line parameters
 */
typedef struct {
	char* methodname;
	char* input;
	char* output;
    int   keytype;
    key2_t key;
} cl_parameters;


/*
 * Define a type that is a function pointer
 *    function returns void
 *    function parameters are
 *       buffer_t *input_message
 *       buffer_t *output_message
 *       void *key_object
 * 
 * If you understand this bit of code and can use it, then you are a very able programmer -
 * have a chat to the TAs and lecturers, we're always keen to identify people in this category
 */
typedef void (*encoder_function_t)(buffer_t*, buffer_t*, void*); 


/*
 * Define some constants for a reduced 6-bit ASCII table
 */
#define ASCII_PRINTABLE_START ' '
#define ASCII_PRINTABLE_STOP  '^'
#define ASCII_PRINTABLE_TABLE_SIZE ((ASCII_PRINTABLE_STOP - ASCII_PRINTABLE_START + 2))
#define ASCII_TABLE_SIZE 256

/*
 * Define function prototypes in main.c
 */
buffer_t* new_buffer(long length);

void delete_buffer(buffer_t *buffer);
long filesize(char filename[]);
buffer_t* read_message(char filename[], buffer_t *outbuffer);
void write_message(char filename[], buffer_t *inbuffer);
cl_parameters parse_cl(int argc, char *argv[]);


/*
 * Define function prototypes in crypt.c
 */
encoder_function_t get_encoder(char* encoder_name);


#endif /*CRYPT_H_*/

