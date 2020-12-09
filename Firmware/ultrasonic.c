/*
 * ultrasonic.c
 *
 * Created: 11/20/2020
 * Author: Alan Gonzalez
 */ 
#define _NOP() do { __asm__ __volatile__ ("nop"); } while(0)
#define F_CPU 1000000UL

#include <avr/io.h>
#include "capt_timer.h"

int tick_count = 0;								// to count how many times the timer has ran
int t1_ticks = 0;								// to count how many ticks the echo pin was high for

void init_input_capt_timer() {
	TIMSK1 |= (1 << ICIE1);						// enable input capture interrupts on timer1
	TCCR1B |= (1 << ICES1) | (1 << ICNC1) | (1 << CS12);
	/* enable rising edge detection
	 * noise cancellation
	 * clock pre-scaler 256
	 */
	edge.current_edge = RISING;
	edge.next_edge = RISING;
}

void init_timer2() {
	OCR2A = (uint8_t) OCR2A_VALUE;				// set the timer2 to generate interrupt every 20us
	TIFR2 |= (1 << OCF2A);						// clear the output compare match flag
	TCCR2A |= (1 << WGM21);						// set timer2 to CTC mode
	TIMSK2 |= (1 << OCIE2A);					// enable timer2 compare match interrupts
	TCCR2B |= (1 << CS21);						// set timer2 clock prescaler to 8 and start timer
}

int main(void)
{
    DDRB &= ~(1 << PB0);						// Set PB0 (pin 14) to input for Echo
    DDRB |= (1 << PB1);							// Set PB1 (pin 15) to output for Trigger
	DDRD |= (1 << PD2);							// Set PD2 (pin 4) to output for LED
	
	t1_ticks = 0;								// to count how many ticks the echo pin was high for
	
	init_input_capt_timer();					// initialize timer1
	init_timer2();								// initialize timer2
	
	sei();										// enable interrupts
	
    while (1) 
    {
		_NOP();
    }
}

ISR(TIMER1_CAPT_vect)
{
	cli();										// disable interrupts
	
	switch(edge.next_edge) {
	case RISING: {
		TCNT1 = 0;								// start the timer1 counter at 0
		TCCR1B &= ~(1 << ICES1);				// next interrupt on falling edge
		edge.current_edge = RISING;
		edge.next_edge = FALLING;
	}
		break;
	
	case FALLING: {
		t1_ticks = (uint16_t) ICR1L;
		t1_ticks |= (uint16_t) (ICR1H << 8);		// store number of ticks between rising and falling edge
		TCCR1B |= (1 << ICES1);						// next interrupt on rising edge
		edge.current_edge = FALLING;
		edge.next_edge = RISING;
		if(t1_ticks > 0 && t1_ticks < 8) {
			//////////////////////////////////////////////////////
			// what will it do when it gets too close to obstacle?
			
			PORTD |= (1 << PORTD2);					// turn LED on TEST
			//////////////////////////////////////////////////////
		}
	}
		break;
		
	default:
		break;
	}
	sei();										// enable interrupts
}

ISR(TIMER2_COMPA_vect) {
	cli();										// disable interrupts
	tick_count++;
	
	if (tick_count == 1) {
		PORTB |= (1 << PB1);					// set Trigger pin to HIGH
	}
	
	if (tick_count == 2) {
		PORTB &= ~(1 << PB1);					// clear Trigger pin to LOW
	}
	
	if (tick_count == 1500) {
		tick_count = 0;							// reset the timer to set the trigger pin again
		PORTD &= ~(1 << PORTD2);				// turn LED off TEST
	}
	
	sei();
}
	
