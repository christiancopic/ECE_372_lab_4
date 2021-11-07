#ifndef SEGMENT_H
#define SEGMENT_H
#include <avr/io.h>
void initSegment();
void dataIN(unsigned int bit);
void displayNum(unsigned int y);
void latch();
#endif