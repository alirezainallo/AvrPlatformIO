#include "timTick.h"

uint32_t currentTick = 0;
uint32_t get_currentTick(void){
  return currentTick;
}
void tim1_init(void){
  //cpu clock: 8MHz
  // WGM12:1, WGM13:0 //CTC TOP is OCR
  TCCR1A = 0;
  //preScaler: 64
  TCCR1B = (1 << WGM12)|(1 << CS11)|(1 << CS10);
  // OCR1A = (8000000/2*256*1000) - 1
  // OCR1A = 15624
  OCR1A  = (int8_t)(((int32_t)8000000/((int32_t)64 * (int32_t)1000))-(int32_t)1);
  TIMSK |= (1 << OCIE1A);// enable timer interrupt
  TIFR  |= (1 << OCF1A); // for flag clear
  TCNT1  = 0;
}
ISR (TIMER1_COMPA_vect){
  // TIFR |= (1 << OCF1A);
  currentTick++;
}
