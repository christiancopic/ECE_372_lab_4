#include <avr/io.h>
#include <math.h>
#include <Arduino.h>

//non-inverting
void initPWMTimer3(){
    //Set Pin number 5 to output
    DDRE |= (1<<DDE3);

    //WGM = 0111
    TCCR3A |= (1<<COM3A1)|(1<<WGM31)|(1<<WGM30);
    TCCR3B |= (1<<WGM32)|(1<<CS30);

    //duty cycle to 25%
    OCR3A = 255;
    
}

//inverting
void initPWMTimer4(){
    //Set pin numner 6 to output
    DDRH |= (1<<DDH3);
    //WGM = 0111
    TCCR4A |= (1<<COM4A1)|(1<<COM4A0)|(1<<WGM41)|(1<<WGM40);
    TCCR4B |= (1<<WGM42)|(1<<CS40);
    //duty cycle to 25%
    OCR4A = 1023;
}


void changeDutyCycle(int tenBits){
    float v_k = (5.0/1024.0) * tenBits;
    
    Serial.println(v_k, 2);
    Serial.flush();

    if(v_k > 2.5){
        OCR4A = (1-(v_k-2.5)/2.5) * 1023;
        OCR3A = 0;
        Serial.println("1");
    }
    else if (fabs(v_k - 2.5) < 0.0001){      
        OCR3A = 0;
        OCR4A = 0;
        Serial.println("2");
    }
    else{
        OCR3A = (1-(v_k/2.5)) * 1023;
        OCR4A = 1023;
        Serial.println("3");
    }
}

