

#include "adc.h"
#include <avr/io.h>

void initADC7(){
    //set reference voltage
    ADMUX |= (1<<REFS0);
    ADMUX &= ~(1<<REFS1);

    //determine left or right justified (ADLAR = 0 RIGHT JUSTIFIED)
    ADMUX &= ~(1<<ADLAR);

    //specify ADC input channel and mode
    //set ADC7 as single-ended input with MUX[5:0] = 0b000111
    ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);
    ADMUX &= ~((1<<MUX4)|(1<<MUX3));
    ADCSRB &= ~(1<<MUX5);

    //set Auto Trigger source selection 
    //use free-running mode ADTS[2:0] = 0b000
    ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));

    //enable ADC and enable auto-triggering
    ADCSRA |= (1<<ADEN)|(1<<ADATE);

    //set the ADC clock frequency. Use a pre-salcer of 128
    //ADC clock frequency is 16Mhz divided by pre-scaler = 125KHz
    //sampling rate is 1/(1/125Khz)*(13 Clock Cycles)) = 9615 Khz
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

    //diable ADC0 pin digital input - pin A0 on board
    DIDR0 |= (1<<ADC7D);

    //start the first ADC conversion
    ADCSRA |= (1<<ADSC);

}