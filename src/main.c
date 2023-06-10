#include "LCD.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
// #include <hd44780.h>

#define BLINK_DDR  DDRA
#define BLINK_PORT PORTA
#define BLINK_PINS ((1 << PA0)|(1 << PA2)|(1 << PA4)|(1 << PA6))

int main(void){

  LCD_Init();
  LCD_Clear();
  LCD_String_xy(0, 0, "Hello");
  
  BLINK_DDR  = 0xFF;
  BLINK_PORT = 0x00;

  while(1){
    BLINK_PORT |=  BLINK_PINS;
    _delay_ms(500);
    BLINK_PORT &= ~BLINK_PINS;
    _delay_ms(500);
  }
}