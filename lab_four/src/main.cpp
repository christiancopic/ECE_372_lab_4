#include <Arduino.h>

#include <avr/io.h>
#include "pwm.h"
#include "adc.h"
#include "timer.h"
//#include "switch.h"
#include <avr/interrupt.h>

/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum stateEnum{
    wait_press,
    bounce_low,
    wait_release,
    bounce_high
  } stateType;

// Initialize states.  Remember to use volatile 
volatile stateType state = wait_press;
unsigned int result = 0;

int main(){
  initTimer0();
  initTimer1();
  initPWMTimer3();
  initPWMTimer4();
  initADC7();
  //init switch
  //init 7-segment display

  sei();
  

	while(1){
    //read potentiometer & change speed/direction accordingly
    result = ADCL;
    result += ((unsigned int)ADCH)<<8;
    changeDutyCycle(result);

    switch(state){
      case wait_press:
         break;
      case bounce_low:
        delayMs(1);
        state = wait_release;
        break;
      case wait_release:
        break;
      case bounce_high:
        delayMs(1);
        state = wait_press;
        break;
    }
	}


  ISR(INT0_vect){
    if(state == wait_press){
      state = bounce_low;
    }
    else if (state == wait_release){
      cli();   //disable interrupt
      changeDutyCycle(0b0100000000); //input 512 to Turn motor Off
      for(int i=9; i>=0; i++){
        delayS(1);
        //Display i on 7-segment display 
      }
      changeDutyCycle(result);   //Restart motor at current voltage
      sei();   //enable interrupt
      state = bounce_high;
    }

  }
}
