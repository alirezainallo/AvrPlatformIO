#include "main.h"
#include "adc.h"
#include "mq5.h"
#include "uart.h"
#include "DHT11.h"
#include "timTick.h"
#include "time_out.h"
#include "keypad_4x4.h"
#include "heart_beat.h"

uint16_t temperature_int = 0;
uint16_t humidity_int = 0;
// void LCD_print(uint16_t temp, unsigned char cur_count);

extern void togglePin(void);
void timeOut(uint32_t ms);

char rxUart_debug = 0;

/*void setPin(volatile uint8_t* Port, uint8_t Pin, bool level){
	if(level){
		*Port |=  (1 << Pin);
	}
	else{
		*Port &= ~(1 << Pin);
	}
}
// PinState PinRead(volatile uint8_t* PIN, uint8_t Pin){
// 	return (*PIN & (1 << Pin));
// }
void send_ch(char ch){
  _delay_us(104);
  _delay_us(104);
  for(uint8_t i = 0; i < 8; i++){
    setPin(&PORTD, i, ((ch & (1 << i)) != 0));
    _delay_us(104);
  }
  _delay_us(104);
}*/


//"AT+CNMI=1,2,0,0,0/r/n"
//"AT+CMGS="09035683914"/r/n"
//Res//"+cmt: "+989217791093","","23/06/16,17:29:29+14""
int main(void){
  DDRA  |= (1 << PA3);
  PORTA |= (1 << PA3);
  
  sei(); //enable global interrupt
  LCD_Init();
  LCD_Clear();
  _delay_ms(50);
  LCD_String_xy(0, 0, "Starting...");
  _delay_ms(2000);
  LCD_Clear();

  tim1_init();

  heart_beat_init(500);

  keypad_init(FALLING_EDGE);

  mq5_init();

  uart_init();
  _delay_ms(100);
  
  txSendDataLen("Alireza\n", 8);

  // timeOut(100);
  while(1){
    heart_beat();
    keypad_process();
    // timeOut(2000);

    uart_loop();

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
    sprintf(display, "MQ5:%d  %d  ", mq5_value(), count);
    LCD_Clear();
    LCD_String_xy(1,0,display);
  }
}
