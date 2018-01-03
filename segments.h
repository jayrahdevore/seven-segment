#ifndef SEGMENTS_H
#define WHATEVER_H_INCLUDED
#include <stdint.h>

#define F_CPU 8000000 //8 MHz

/*
 Created by legowave440
 */

uint8_t PortB[4]; //These are the segment controls for digits 0-4

/*  -   -   -   -   -   Display -   -   -   -   -   -   */

//Returns the segment code for a letter or number.
//This will not work with the letters 'K', 'Q', 'R', 'V', 'W', or 'X'.
uint8_t chartodigit(char input);

//This replaces the numbers with text.  Only works with ALL CAPS
void text(char input[4]);
//This function updates the display
void updateDisplay(uint8_t brightness);
//This function updates the display AND sets individual brightnesses for each side
void updateDigitDisplay(uint8_t brightness_l, uint8_t brightness_r);
uint8_t inttodig(int input);
//This sets the score of the 2 righmost digits
void rightScore(int input);
//This sets the score of the 2 leftmost digits
void leftScore(int input);

//VisualEffects ----------------
void flashDisplay(void);

void slowPulse(void);
void flashLeftDigit(void);

void flashRightDigit(void);

#endif
