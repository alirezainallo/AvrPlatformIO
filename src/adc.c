#include "adc.h"

void adc_init(void){
  // AREF, Internal Vref turned off
  DDRA   &= ~(1 << PA4);
  PORTA  &= ~(1 << PA4);
  ADMUX  |=  0x04 | (1 << REFS0); 
  ADCSRA |= (1 << ADEN)|(1 << ADIE);
  ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);//PreScaler 128
  // ADCSRA |= (1 << ADSC);//start adc conv
  // ADCSRA |= (1 << ADCSRA); interrupt flag
  // ADCW: data reg
}
void adc_start(void){
  ADCSRA |= (1 << ADSC);//start adc conv
}
uint16_t adcVal = 0;
// uint16_t count = 0;
ISR(ADC_vect){
  adcVal = ADCW;
  //count++;
  adc_start();
}
uint16_t get_adc_value(void){
  return adcVal;
}