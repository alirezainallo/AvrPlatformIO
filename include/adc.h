#ifndef _ADC_H
#define _ADC_H

#include "main.h"

void adc_init(void);
void adc_start(void);
uint16_t get_adc_value(void);

#endif //_ADC_H
