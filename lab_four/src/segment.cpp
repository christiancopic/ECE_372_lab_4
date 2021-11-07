#include <Arduino.h>
#include <avr/io.h>
#include "segment.h"
#include "timer.h"
const unsigned z = 50; // delay
void initSegment(){
      DDRC |= (1<<DDC0) | (1<<DDC2) | (1<<DDC4);    // Set PORTC as output  pin number (37 clock    , 35 latch    ,33  data )   
}
void displayNum(unsigned int y){
      switch(y){
            case 0: 
                  dataIN(0);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  latch();
                  break;
            case 1: 
                  dataIN(0);
                  dataIN(0);
                  dataIN(0);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(0);
                  latch();
                  break;
            case 2: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  latch();
                  break;
            case 3: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  latch();
                  break;
            case 4: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(0);
                  latch();
                  break;
            case 5: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  latch();
                  break;
            case 6: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  latch();
                  break;
            case 7: 
                  dataIN(0);
                  dataIN(0);
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(0);
                  latch();
                  break;
            case 8: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  latch();
                  break;
            case 9: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  latch();
                  break;
            case 10: 
                  dataIN(0);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(1);
                  dataIN(0);
                  dataIN(1);
                  latch();
                  break;
            
             default:
                  break;
      }
}
void dataIN(unsigned int bit){
            if(bit == 1){
                  PORTC |= (1<<PORTC4);
                  PORTC |= (1<<PORTC0);
                  delayMs(z);
                  PORTC &= ~(1<<PORTC0);
                  delayMs(z);
                  PORTC &= ~(1<<PORTC4);
            }else if(bit == 0){
                  PORTC &= ~(1<<PORTC4);
                  PORTC |= (1<<PORTC0);
                  delayMs(z);
                  PORTC &= ~(1<<PORTC0);
                  delayMs(z);
                  PORTC &= ~(1<<PORTC4);
            }
}

void latch(){
      PORTC |= (1<<PORTC2);
      delayMs(z);
      PORTC &= ~(1<<PORTC2);
      delayMs(z);
}


