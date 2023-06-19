#include "adc.h"


adc_channels_t currChannel = adc_ch_Idle;

uint32_t adc_ms = 200;

void adc_init(uint32_t ms){
  adc_ms = ms;
  // AREF, Internal Vref turned off
  DDRA   &= ~(1 << PA4);
  PORTA  &= ~(1 << PA4);
  ADMUX  |=  (1 << REFS0); 
  ADCSRA |= (1 << ADEN)|(1 << ADIE);
  ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);//PreScaler 128
  // ADCSRA |= (1 << ADSC);//start adc conv
  // ADCSRA |= (1 << ADCSRA); interrupt flag
  // ADCW: data reg
}
void adc_start(adc_channels_t ch){
  while (currChannel != adc_ch_Idle){
  }
  currChannel = ch;
  
  ADMUX = (ADMUX & 0xE0) | ch;  
  ADCSRA |= (1 << ADSC);//start adc conv
}
uint16_t adcVal[2] = {0};
ISR(ADC_vect){
  if(currChannel == adc_ch4){
    adcVal[0] = ADCW;
  }
  else if(currChannel == adc_ch5){
    adcVal[1] = ADCW;
  }
  currChannel = adc_ch_Idle;
  
}
uint16_t get_adc_value(adc_channels_t ch){
  uint8_t retInd = 0;
  if(ch == adc_ch4){
    retInd = 0;
  }
  else if(ch == adc_ch5){
    retInd = 1;
  }
  else{
    return 0;
  }
  return adcVal[retInd];
}
void adc_loop(void){
  static uint32_t nextTick = 0;
  static uint32_t currTick = 0;
  static bool change_ch = false; 
  currTick = get_currentTick();
  if(nextTick < currTick){
    nextTick = currTick + adc_ms;

    if(change_ch){
      adc_start(adc_ch4);
    }
    else{
      adc_start(adc_ch5);
    }
    change_ch =! change_ch;
  }

}