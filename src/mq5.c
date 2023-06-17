#include "mq5.h"

uint32_t mq5_ms = 0;

extern menuStat_t get_menuStat(void);

void mq5_init(uint32_t ms){
  mq5_ms = ms;
  adc_init();//adc4
  adc_start();
}
uint16_t mq5_value(void){
  uint16_t mq5Val = 0;
  mq5Val = get_adc_value();
  adc_start();
  return mq5Val; 
}
static uint32_t nextTick = 0;
static uint32_t currTick = 0;
void mq5_loop(void){
  currTick = get_currentTick();
  if(nextTick < currTick){
    static char display[16];
    nextTick = currTick + mq5_ms;
    // LCD_Clear();
    if(get_menuStat() == menu_mainPage_Stat){
      LCD_String_xy(1, 4, "      ");
      sprintf(display, "%d", mq5_value());
      LCD_String_xy(1, 4, display);
    }
  }
}