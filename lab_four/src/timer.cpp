// Author: Megan Mickey
// Net ID: meganfaithmickey
// Date:
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
	//set waveform generation bits for CTC mode
    //      WGM13 = 0; WGM12 = 0; WGM11 = 1; WGM10 = 0;
    TCCR1A &= ~(1<<WGM10);
    TCCR1B &= ~(1<<WGM12);
    TCCR1A |= (1<<WGM11);

    // //set the prescaler to 1024
    // //CS12 = 1, CS11 = 0, CS10 = 1;
    TCCR1B &= ~(1<<CS11);
    TCCR1B |= (1<<CS12)|(1<<CS10);

    //count needed given the prescaler
    OCR1A = 15625;
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayS(unsigned int delay){
    unsigned int delayCnt = 0;

    TCNT1 = 0;
    TIFR1 |= (1<<OCF1A);

    while(delayCnt<delay){
        if (TIFR1 & (1<<OCF1A)){
            delayCnt++;
            TIFR1 |= (1<<OCF1A);
        }
    }
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    //set waveform generation bits for CTC mode
    //      WGM03 = 0; WGM02 = 0; WGM01 = 1; WGM00 = 0;
    TCCR0A &= ~(1<<WGM00);
    TCCR0B &= ~(1<<WGM02);
    TCCR0A |= (1<<WGM01);

    // //set the prescaler to 64
    // //CS12 = 0, CS11 = 1, CS10 = 1;
    TCCR0B &= ~(1<<CS02);
    TCCR0B |= (1<<CS01)|(1<<CS00);

    OCR0A = 250;
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    unsigned int delayCnt = 0;

    TCNT0 = 0;
    TIFR0 |= (1<<OCF0A);

    while(delayCnt<delay){
        if (TIFR0 & (1<<OCF0A)){
            delayCnt++;
            TIFR0 |= (1<<OCF0A);
        }
    }
   
}