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


//"AT+CMGS="09035683914"/r/n"
//"AT+CNMI=1,2,0,0,0/r/n"
int main(void){
  // DDRD  |= (1 << PD3);
  // PORTD |= (1 << PD3);
  
  sei(); //enable global interrupt
  tim1_init();
  heart_beat_init(500);
  

  keypad_init(FALLING_EDGE);

  LCD_Init();
  // _delay_ms(50);
  LCD_Clear();
  LCD_String_xy(0,0,"Starting...");
  _delay_ms(1000);
  LCD_Clear();

  mq5_init();

  uart_init();
  _delay_ms(100);
  // putChar('A');
  txSendDataLen("Alirezainallo\n", 14);
  // timeOut(100);
  while(1){
    heart_beat();
    keypad_process();
    // timeOut(2000);

    if(rx_lineReady){
      rx_buffer[rx_len] = 0;
      LCD_String_xy(0,0,rx_buffer);
      // UDR = 'a';
      // send_ch('a');
      rx_lineReady = 0;
      // sei();
      // static char i = 0;
      // i++;
      // if(i == 1){
      //   putChar('B');
      // }else if(i == 2){
      //   putChar('C');
      // }
    }

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
