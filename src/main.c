#include "LCD.h"
#include "DHT11.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


uint16_t temperature_int = 0;
uint16_t humidity_int = 0;
void LCD_print(uint16_t temp, unsigned char cur_count);

#define BLINK_DDR  DDRA
#define BLINK_PORT PORTA
#define BLINK_PINS ((1 << PA0)|(1 << PA2)|(1 << PA4)|(1 << PA6))

int main(void){

  LCD_Init();
  LCD_Clear();
  
  BLINK_DDR  = 0xFF;
  BLINK_PORT = 0x00;

  LCD_String_xy(1,0,"slm");
  LCD_String("slm");
  LCD_String("slm");

  // char* template = "Temp:   . C     Rh:   . %";
	// char* error = "Error";
  // LCD_String_xy(0, 0, template);
  _delay_ms(1000);

  while(1){
    //call DHT sensor function defined in DHT.c
		// if(dht_GetTempUtil(&temperature_int, &humidity_int) != -1){
		// 	LCD_print(temperature_int, 7);
		// 	LCD_print(humidity_int, 21);
		// }
		// else{
    //   LCD_Command(CMD_ForceCursorToTheBeginning1);
    //   LCD_String_xy (1, 0, error);
    //   // LCD_Command(CMD_ForceCursorToTheBeginning1);
    // }
		// _delay_ms(1500);

    // LCD_String_xy(1, 0, "                ");
		
    // BLINK_PORT |=  BLINK_PINS;
    // _delay_ms(500);
    // BLINK_PORT &= ~BLINK_PINS;
    // _delay_ms(500);
  }
}

//function to convert number values into characters
void LCD_print(uint16_t temp, unsigned char cur_count){
	
	unsigned char ten_count = 0;
	unsigned char hun_count = 0;
	while( temp >= 100 ) {
		hun_count++;
		temp -= 100;
	}	
	
  LCD_Command(CMD_ReturnHome);
  for(int i = 0; i < cur_count; i++){
    LCD_Command(CMD_IncrementCursor);
  }
  LCD_Char(hun_count + '0');
	// LCD_Cursor(cur_count);
	// LCD_WriteData(hun_count + '0');
	// cur_count++;
	// LCD_Cursor(cur_count);
  LCD_Command(CMD_IncrementCursor);
	while( temp >= 10 ) {
		ten_count++;
		temp -= 10;
	}
	
	LCD_Char(ten_count + '0');
	// cur_count++;
	// LCD_Cursor(cur_count);
  LCD_Command(CMD_IncrementCursor);
	
	// LCD_WriteData('.');
	// cur_count++;
	// LCD_Cursor(cur_count);
  LCD_Char('.');
  LCD_Command(CMD_IncrementCursor);
	
	LCD_Char((unsigned char) temp + '0');
	
	// LCD_Cursor(0);
  LCD_Command(CMD_ReturnHome);
}