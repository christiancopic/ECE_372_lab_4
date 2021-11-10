#include <Arduino.h>
#include <avr/io.h>
#include "pwm.h"
#include "adc.h"
#include "timer.h"
#include "switch.h"
#include "segment.h"
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
int result = 0;
volatile int segment_state = 1;  // not segment state counting 
int main(){
  initTimer0();
  initTimer1();
  initPWMTimer3();
  initPWMTimer4();
  initADC7();
  initSwitchPD0();  // initialized switch for external interrupt
  initSegment(); // initialized segment controller ports

  Serial.begin(9600);
  Serial.flush();

  sei();
	while(1){
    //read potentiometer & change speed/direction accordingly
    result = ADCL;
    result += ((unsigned int)ADCH)<<8;
    changeDutyCycle(result);
    
    if(segment_state == 2){
            for(int i = 9; i >= 0; i--){
             displayNum(i);
             }
        //code for motor to stop 
  
        segment_state = 1;
    }else{
    sei();   //enable global interrupt

        //motor forward and backward 

   }


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

 
}

 ISR(INT0_vect){  // External interrrupt 
    if(state == wait_press){
      state = bounce_low;
    }
    else if (state == wait_release){
      cli();   //disable interrupt
      changeDutyCycle(512); //input 512 to Turn motor Off
      if(segment_state == 1){  // check for the blinking state
            segment_state = 2;
          }
          else{
            segment_state = 1;
          }
      changeDutyCycle(result);   //Restart motor at current voltage
      
      state = bounce_high;
    }

  }
