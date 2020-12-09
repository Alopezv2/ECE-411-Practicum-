/*
 * capt_timer.h
 * 
 * Created on: Nov 26, 2020
 * Author: Alan Gonzalez
 */

#ifndef INPUTCAPTURE_TIMER_H_
#define INPUTCAPTURE_TIMER_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#define FOSC      16000000UL
#define F_OC2A    50000L		// for 20us
#define OC2A_PRESCALER 8L

#define OCR2A_VALUE  (float)((FOSC/(2*OC2A_PRESCALER*F_OC2A)) -1)

volatile typedef enum edge_state_t{RISING, FALLING}edge_state;

volatile typedef struct {
	edge_state current_edge;
	edge_state next_edge;
}edge_t;

volatile edge_t edge;			// to be used in main program

// Function prototypes
void init_input_capt_timer();
void init_timer2();

#endif
