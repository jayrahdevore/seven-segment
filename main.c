/*
 Created by legowave440
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define BRIGHTNESS 100 //This is the typical brightness

int8_t PortB[4]; //These are the segment controls for digits 0-4

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

/*  -   -   -   -   -   Display -   -   -   -   -   -   */

//Returns the segment code for a letter or number.
//This will not work with the letters 'K', 'Q', 'R', 'V', 'W', or 'X'.
uint8_t chartodigit(char input) {
    uint8_t x;
    //As-is, CAPS only.
    switch (input) {
        case '0':
            x = 0b11000000;
            break;
        case '1':
            x = 0b11111001;
            break;
        case '2':
            x = 0b10100100;
            break;
        case '3':
            x = 0b10110000;
            break;
        case '4':
            x = 0b10011001;
            break;
        case '5':
            x = 0b10010010;
            break;
        case '6':
            x = 0b10000010;
            break;
        case '7':
            x = 0b11111000;
            break;
        case '8':
            x = 0b10000000;
            break;
        case '9':
            x = 0b10010000;
            break;
        case 'A':
            x = 0b10001000;
            break;
        case 'B':
            x = 0b10000011;
            break;
        case 'C':
            x = 0b11000110;
            break;
        case 'D':
            x = 0b10100001;
            break;
        case 'E':
            x = 0b10000110;
            break;
        case 'F':
            x = 0b10001110;
            break;
        case 'G':
            x = 0b10010000;
            break;
        case 'H':
            x = 0b10001001;
            break;
        case 'I':
            x = 0b11001111;
            break;
        case 'J':
            x = 0b01100001;//fixed
            break;
            //NO K
        case 'L':
            x = 0b11000111;
            break;
            //NO M
        case 'N':
            x = 0b10101011;
            break;
        case 'O':
            x = 0b10100011;
            break;
        case 'P':
            x = 0b10001100;
            break;
            //NO Q OR R
        case 'S'://SAME AS 5
            x = 0b10010010;
            break;
        case 'T'://same as 7
            x = 0b10000111;
            break;
        case 'U':
            x = 0b11000001;
            break;
            //NO V, W, OR X
        case 'Y':
            x = 0b10010001;
            break;
        case 'Z'://SAME AS 2
            x = 0b10100010;
            break;
        case ' ':
            x = 0b11111111;
            break;
        default:
            x = 0b10111111;
            break;
    }
    return x;
}

//This replaces the numbers with text.  Only works with ALL CAPS
void text(char input[4]) {
    //colon(false);  //IMPLEMENT WHEN COLON IS USED
    
    for (int x = 0; x <= 4; x++) {
        PortB[x] = chartodigit(input[x]);
    }
}



//This function updates the display
void updateDisplay(uint8_t brightness) {
    
    for ( uint8_t x = 0; x < 4; x++ ) { //Run through each digit (Digits 0 - 3)
        
        //Be careful not to burn out the display!
        
        PORTD = PORTD | ( 0b00010000 << x ); //Set the digit
        
        PORTB = PortB[x]; //Turn on segments by setting LOW
        
        //This changes the time each digit spends on
        for (uint8_t y = 0; y < brightness; y++) {
            _delay_us(1);
        }
        
        PORTD = PORTD & 0b00001111; //Turn off the digit
        
        PORTB = 0b11111111;  //Turn off segments by setting HIGH
        
        _delay_us(500);
        
    }
    
}

//This function updates the display AND sets individual brightnesses for each side
void updateDigitDisplay(uint8_t brightness_l, uint8_t brightness_r) {
    
    for ( uint8_t x = 0; x < 4; x++ ) { //Run through each digit (Digits 0 - 3)
        
        //Be careful not to burn out the display!
        
        PORTD = PORTD | ( 0b00010000 << x ); //Set the digit
        
        PORTB = PortB[x]; //Turn on segments by setting LOW
        if (x < 2) {
            //This changes the time each digit spends on
            for (uint8_t y = 0; y < brightness_l; y++) {
                _delay_us(1);
            }
        }  else {
            //This changes the time each digit spends on
            for (uint8_t y = 0; y < brightness_r; y++) {
                _delay_us(1);
            }
        }
        
        PORTD = PORTD & 0b00001111; //Turn off the digit
        
        PORTB = 0b11111111;  //Turn off segments by setting HIGH
        
        _delay_us(500);
        
    }
    
}

uint8_t inttodig(int input) {
    uint8_t x;
    switch (input) {
        case 0:
            x = 0b11000000;
            break;
        case 1:
            x = 0b11111001;
            break;
        case 2:
            x = 0b10100100;
            break;
        case 3:
            x = 0b10110000;
            break;
        case 4:
            x = 0b10011001;
            break;
        case 5:
            x = 0b10010010;
            break;
        case 6:
            x = 0b10000010;
            break;
        case 7:
            x = 0b11111000;
            break;
        case 8:
            x = 0b10000000;
            break;
        case 9:
            x = 0b10010000;
            break;
        default:
            x = 0b10111111;
            break;
    }
    return x;
    
}

//This sets the score of the 2 righmost digits
void rightScore(int input){
    int input2 = (input % 10);
    input = input - input2;
    input = input/10;
    PortB[2] = inttodig(input);
    PortB[3] = inttodig(input2);
}

//This sets the score of the 2 leftmost digits
void leftScore(int input){
    int input2 = (input % 10);
    input = input - input2;
    input = input/10;
    PortB[0] = inttodig(input);
    PortB[1] = inttodig(input2);
}


//VisualEffects ----------------
void flashDisplay(void) {
    for ( int x = 0; x <= 255; x++) {
        updateDisplay(x);
    }
    for ( int x = 255; x >= 0; x--) {
        updateDisplay(x);
    }
}

void slowPulse(void) {
    for ( int x = 0; x <= 255; x++) {
        updateDisplay(x);
    }
    for ( int x = 0; x <= 255; x++) {
        updateDisplay(255);
    }
    for ( int x = 255; x >= 0; x--) {
        updateDisplay(x);
    }
}

void flashLeftDigit(void) {
#define BRIGHTNESS 100
    for ( int x = 0; x <= 255; x++) {
        updateDigitDisplay(x, BRIGHTNESS);
    }
    for ( int x = 255; x >= 0; x--) {
        updateDigitDisplay(x, BRIGHTNESS);
    }
}

void flashRightDigit(void) {
    for ( int x = 0; x <= 255; x++) {
        updateDigitDisplay(BRIGHTNESS, x);
    }
    for ( int x = 255; x >= 0; x--) {
        updateDigitDisplay(BRIGHTNESS, x);
    }
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
