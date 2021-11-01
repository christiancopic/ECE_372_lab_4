

#include <avr/io.h>

//non-inverting
void initPWMTimer3(){
    //Set Pin number 5 to output
    DDRE |= (1<<DDE3);

    //WGM = 0111
    TCCR3A |= (1<<COM3A1)|(1<<WGM31)|(1<<WGM30);
    TCCR3B |= (1<<WGM32);

    //duty cycle to 25%
    OCR3A = 255;
    
}

//inverting
void initPWMTimer4(){
    //Set pin numner 6 to output
    DDRH |= (1<<DDH3);
    //WGM = 0111
    TCCR4A |= (1<<COM4A1)|(1<<COM4A0)|(1<<WGM41)|(1<<WGM40);
    TCCR4B |= (1<<WGM42);
    //duty cycle to 25%
    OCR4A = 255;
}
