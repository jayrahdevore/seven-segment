/*
 Created by legowave440
 */

#include "segments.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <stdint.h>


#define BRIGHTNESS 100 //This is the typical brightness


//Init
void initIO(void) {
    //Initialize the segments for each digit

    DDRD = DDRD | 0b11110000; //Digit output setup
    DDRB = 0b11111111; //Segment output setup
}

void sleep(void) {
    //PORTD = PORTD & 0b00001111; //Turn off the digits
    //PORTB = 0b00000000; //Turn off the segments
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    sleep_enable();
    sleep_bod_disable();
    sei();
    sleep_cpu();
}

/*  -    -   -   -   -   -   -   -   - Main Program -    -   -   -   -   -   -   -   - */


int main(void) {
	initIO();


    //leftScore(0);
    text("LETS");
    flashDisplay();
    text("PLAY");
    flashDisplay();
    text("PING");
    for ( int x = 0; x <= 100; x++) {
        updateDisplay(255);
    }
    for ( int x = 100; x >= 0; x--) {
        updateDisplay(x);
    }
    text("PONG");
    for ( int x = 0; x <= 100; x++) {
        updateDisplay(255);
    }
    for ( int x = 100; x >= 0; x--) {
        updateDisplay(255);
    }

    leftScore(0);
    rightScore(0);

	while (1) {
        slowPulse();
	}
	return 0; // never reached
}





/* From OLD Library:


 void Seg::
 void Seg::colon(boolean input) {
 //Colon = input;
 if (Colon == true) {
 PortB[0] = PortB[0]	| B10000000;
 } else {
 PortB[0] = PortB[0] & B01111111;
 }
 }


 byte Seg::

 */
