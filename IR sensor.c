/*
 * IR sensor
 *
 * Created: 11/13/2020 4:41:01 PM
 * Author : gbece
 */ 

#include <avr/io.h>


int main(void)
	{
	
	PORTD = 0x00;  	// Calling all D ports
	DDRD = 0xC0;  	// set Pin.7 and Pins.6 as outputs 

	   while (1)	// loop to read IR sensors data 
	   {
	        // get input from PinD0 and output to PinD6
			if((PIND & 0x01) != 0)    // read PIND.0
			PORTD &= 0b10111110;      // clear PORTD.6
			else
			PORTD |= 0b01000000;      // set PORTD.6
			
		// get input from PinD1 and output to PinD7
			if((PIND & 0x02) != 0)    // read PIND.1
			PORTD &= 0b01111111;      // clear PORTD.7
			else
			PORTD |= 0b10000000;      // set PORTD.7  

	   }
	}