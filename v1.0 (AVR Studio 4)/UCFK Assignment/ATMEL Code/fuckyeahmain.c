#include <avr/io.h>
#include <stdint.h>
#include <font.h>

#define BV(x) (1 << (x))
#define CLEARBIT(a,x) ((a) & (~BV(x)))
#define SETBIT(a,x) ((a) | (BV(x)))
#define ASSIGNBIT(a,x,v) (v==0)?CLEARBIT(a,x):SETBIT(a,x)
#define ISCLEAR(a,x) ((((a) & (BV(x))) == BV(x))?(0):(1))
#define ISSET(a,x) ((((a) & (BV(x))) == BV(x))?(1):(0))
#define adcstart 0xC7
#define adsccheck 6




// Global Variables
uint8_t messagearray[50][6];
char custom_message[50];
char preset_message[] = "GEO AND ALEX"; //"HAPPY :-) SAD :-( HUNGRY :-O DEAD X-( KISS :-X RICH $-)";
uint8_t stringlength;
uint8_t messagelength;
uint8_t button_count = 0;

 // Defining Functions
void messagecreator(uint8_t preset_or_custom);
void collumn(uint8_t x);
uint8_t getbutton(uint8_t button_num);

void make_custom_message(){
	uint8_t col_on;
	uint8_t fontnum = 1;
	uint8_t letternum = 0;
	uint8_t count;
	messagelength = 1;

	while(1){
		
		if(count == 20){
			count = 0;
			fontnum = fontnum + getbutton(1);
			if(getbutton(1) && getbutton(2)){ //Compiles entered message and breaks loop
				messagecreator(0);
				break;
			}
			if(getbutton(2)){
				custom_message[letternum] = (fontnum + 64);
				fontnum = 1;
				letternum ++;
				messagelength++;
			}
			
		}

		for(col_on = 1; col_on < 6; ++col_on)
		{
			PORTD = ~font[((fontnum + 32)*5)+(col_on-1)];	
			collumn(col_on);
				
			TCNT1 = 0;
			while (TCNT1 < 2) // controls resolution and partially speed
   				continue;
				collumn(0);
				
		}
		count++;
		
	}
}

void button_check(){
	uint8_t button1 = getbutton(1);
	uint8_t button2 = getbutton(2);
	if(button1 && button2){
		button_count++;
		switch(button_count % 2){
		case 0:
			make_custom_message();
		break;
		case 1:
			messagecreator(1);
		break;
		
		}
	}
}

void delay(uint8_t time)
{
	TCNT1 = 0;
	while(TCNT1 < time)
	continue;
}

uint8_t getbutton(uint8_t button_num)
{
	uint8_t pin;
	switch(button_num){
		case 1:
			pin = 3;
		break;
		case 2:
			pin = 5;
		break;
	}
		
	uint8_t pinbyte = PINB;
	uint8_t buttonstate;
	if(ISCLEAR(pinbyte,pin)){
		delay(10);
		buttonstate = 1;
	}
	else{
		buttonstate = 0;
	}
	return buttonstate;
}


	
	

void messagecreator(uint8_t preset_or_custom)
{

	uint8_t fontcode;
	uint8_t i;
	uint8_t j;

	char message_to_compile[100];

	if(preset_or_custom){	// Decides to use custom or preset message
		stringlength = sizeof(preset_message);
		for(i=0; i<=stringlength; i++){
				message_to_compile[i] = preset_message[i];
		}
	}
	else{
		stringlength = messagelength;
		for(i=0; i<=stringlength; i++){
				message_to_compile[i] = custom_message[i];
		}
	}

	for(j=0; j<6; j++)		//Adding spaces at message beginning and end for continuous scrolling
	{
		messagearray[0][j] = ~0x00;
		messagearray[stringlength][j] = ~0x00;
	}

	for(i=0; i<(stringlength-1); i++) // Creating the right bytes from ASCII code to turn on LED's
	{
		for(j=0; j<5; j++)
		{
			fontcode = message_to_compile[i] - 32;
			messagearray[i+1][j] = ~font[fontcode*5+j];
		}
		messagearray[i+1][5] = ~0x00;
	}

}	

uint8_t getspeed()
{
	uint16_t adcvalue;
	uint8_t speed;
	ADCSRA = adcstart;
	while(ISSET(ADCSRA,adsccheck)){
		continue;
	}
	adcvalue = ADC;
	speed = (((adcvalue*30) / 1023) + 5);
	return speed;
	
		
}

void collumn(uint8_t x) // This is spelt wrongly!?!
{
	switch(x)
	{
		case 0:
			PORTB = SETBIT(PORTB,0);		//PORTB = ~0;
			PORTB = SETBIT(PORTB,1);
			PORTB = SETBIT(PORTB,2);
			PORTC = SETBIT(PORTC,2);
			PORTC = SETBIT(PORTC,3);
		break;
		case 1: 
			PORTB = CLEARBIT(PORTB,0);		//PORTB = ~1;
			PORTB = SETBIT(PORTB,1);
			PORTB = SETBIT(PORTB,2);
			PORTC = SETBIT(PORTC,2);
			PORTC = SETBIT(PORTC,3);
		break;
		case 2: 
			PORTB = SETBIT(PORTB,0);		//PORTB = ~2;
			PORTB = CLEARBIT(PORTB,1);
			PORTB = SETBIT(PORTB,2);
			PORTC = SETBIT(PORTC,2);
			PORTC = SETBIT(PORTC,3);
		break;
		case 3: 
			PORTB = SETBIT(PORTB,0);		//PORTB = ~4;
			PORTB = SETBIT(PORTB,1);
			PORTB = CLEARBIT(PORTB,2);
			PORTC = SETBIT(PORTC,2);
			PORTC = SETBIT(PORTC,3);
		break;
		case 4: 
			PORTB = SETBIT(PORTB,0);		//PORTC = ~4;
			PORTB = SETBIT(PORTB,1);
			PORTB = SETBIT(PORTB,2);
			PORTC = CLEARBIT(PORTC,2);
			PORTC = SETBIT(PORTC,3);
		break;
		case 5: 
			PORTB = SETBIT(PORTB,0);		//PORTB = ~8;
			PORTB = SETBIT(PORTB,1);
			PORTB = SETBIT(PORTB,2);
			PORTC = SETBIT(PORTC,2);
			PORTC = CLEARBIT(PORTC,3);
		break;
	}
}

int main(void)
{

	messagecreator(1);

	DDRB = 0x07;
	DDRC = 0x0C;
	DDRD = 0xFE;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	TCCR1A = 0x00;
	TCCR1B = 0x05;

	PORTD = ~0x00;
	PORTB = ~0x00;
	PORTC = ~0x00;

	uint8_t char_start = 0;
	uint8_t char_actual = 0;
	uint8_t col_num = 0;
	uint8_t col_on = 0;
	uint8_t position = 0;
	uint8_t count = 0;
	uint8_t speed = 100;

	while(1){
	
		count = count + 1;
		


		if(count == speed){ // controls Speed of scrolling
			
			button_check();
			speed = getspeed();
			position = position + 1; //Moves the display once over every 6 times
			count = 0;
			if(position == 7){ // Increments starting character once 1st one has fully moved off screen
				char_start = char_start + 1;
				position = 1;
			}
			if(char_start >= (stringlength)){
				char_start = 0;
			}
		}
		col_num = position;	

		for(col_on = 1; col_on < 6; ++col_on)
		{
				

				if (col_num >= 6){ // Shows the start of the next letter
					char_actual = char_start + 1;
					PORTD = messagearray[char_actual][(col_num-6)];
				}
				else{
					char_actual = char_start;
					PORTD = messagearray[char_actual][(col_num)];
				}
				col_num = col_num + 1;
				collumn(col_on);
				
				TCNT1 = 0;

			while (TCNT1 < 2) // controls resolution and partially speed
   				continue;
				collumn(0);
				
		}
		
		
	}
	//return(0);
}
