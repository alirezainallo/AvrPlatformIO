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

  uart_init();
  _delay_ms(100);
  putChar('A');
  _delay_ms(100);
  putChar('B');
  _delay_ms(100);
  putChar('C');

  // timeOut(100);
  while(1){
    heart_beat();


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
    nextTick = currTick + ms;
    togglePin();
  }
}
