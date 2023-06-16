#include "mq5.h"

void mq5_init(void){
  adc_init();//adc4
  adc_start();
}
uint16_t mq5_value(void){
  return get_adc_value();
}
