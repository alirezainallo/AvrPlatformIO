#include "main.h"
#include "uart.h"
#include "timTick.h"
#include "time_out.h"
#include "heart_beat.h"
#include "DHT11.h"

uint16_t temperature_int = 0;
uint16_t humidity_int = 0;
// void LCD_print(uint16_t temp, unsigned char cur_count);

extern void togglePin(void);
void timeOut(uint32_t ms);

void adc_init(void){
  // AREF, Internal Vref turned off
  DDRA  &= ~(1 << PA4);
  PORTA &= ~(1 << PA4);
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
uint16_t count = 0;
ISR(ADC_vect){
  adcVal = ADCW;
  count++;
  adc_start();
}
uint16_t get_adc_value(void){
  return adcVal;
}

int main(void){

  
  sei(); //enable global interrupt
  tim1_init();
  heart_beat_init(500);
  heart_beat();


  LCD_Init();
  // _delay_ms(50);
  LCD_Clear();
  

  LCD_String_xy(0,0,"Starting...");
  _delay_ms(1000);
  LCD_Clear();

  adc_init();//adc4
  adc_start();

  uart_init();
  _delay_ms(100);
  putChar('A');
  _delay_ms(100);
  putChar('B');
  _delay_ms(100);
  putChar('C');

  timeOut(100);
  while(1){
    heart_beat();

    timeOut(2000);

    /*
    //call DHT sensor function defined in DHT.c
		if(dht_GetTempUtil(&temperature_int, &humidity_int) != -1){
      char display[16];
      LCD_Clear();
      sprintf(display, "Temp: %d C", temperature_int);
      LCD_String_xy(0, 0, display);
      sprintf(display, "Rh: %d %c", humidity_int, 0x25);
      LCD_String_xy(1, 0, display);
		}
		else{
      // LCD_String_xy (1, 0, error);
    }
		_delay_ms(1500);*/
  }
}



void timeOut(uint32_t ms){
  static uint32_t nextTick = 0;
  static uint32_t currTick = 0;
  currTick = get_currentTick();
  if(nextTick < currTick){
    static char display[16];
    nextTick = currTick + ms;
    sprintf(display, "MQ5:%d  %d  ", get_adc_value(), count);
    count = 0;
    LCD_Clear();
    LCD_String_xy(1,0,display);
  }
}
