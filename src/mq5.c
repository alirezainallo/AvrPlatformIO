#include "mq5.h"

uint32_t mq5_ms = 500;
extern menuStat_t get_menuStat(void);

void mq5_init(uint32_t ms){
  //adc_init(200);//init alone
  mq5_ms = ms;
  adc_start(adc_ch4);
}
uint16_t mq5_value(void){
  uint16_t mq5Val = 0;
  mq5Val = get_adc_value(adc_ch4);
  return mq5Val; 
}
static uint32_t nextTick = 0;
static uint32_t currTick = 0;
void mq5_loop(void){
  currTick = get_currentTick();
  if(nextTick < currTick){
    // static char display_LCD[17];
    nextTick = currTick + mq5_ms;
    // LCD_Clear();
    if(get_menuStat() == menu_mainPage_Stat){
      LCD_String_xy(1, 4, "      ");
      sprintf(display_LCD, "%d", mq5_value());
      LCD_String_xy(1, 4, display_LCD);
    }
  }
}