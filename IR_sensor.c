/*
 * IR sensor
 *
 * Created: 11/13/2020 4:41:01 PM
 * Author : gbece
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
	{
	   PORTB = 0b00000000;
	   DDRB  = 0b00000001; // Portb.0 = output
	   PORTD = 0b00000000;
	   DDRD  = 0b10000000; // Portd.7 = output
	   while (1)
	   {
		   ////if(0!= (PORTB & 0x02 ))
		   
		   if((PINB & 0b00000010) != 0)    // read PINB.1
		   
		   PORTB &= 0b11111110;  // clear PORTB.0
		   else
		   PORTB |= 0b00000001;    // set PORTB.0

	        
		   
		   if((PINB & 0b00000100) != 0)    // read PINB.2
		   
		   PORTD &= 0b01111111;  // clear PORTD.7
		   else
		   PORTD |= 0b10000000;    // set PORTD.7
			
		   
	   }
	}

