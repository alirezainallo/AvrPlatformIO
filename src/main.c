#include "main.h"
#include "adc.h"
#include "mq5.h"
#include "RTC.h"
#include "menu.h"
#include "uart.h"
#include "DHT11.h"
#include "timTick.h"
#include "time_out.h"
#include "keypad_4x4.h"
#include "heart_beat.h"

// void LCD_print(uint16_t temp, unsigned char cur_count);

extern void togglePin(void);

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
  
  tim1_init();

  // txSendDataLen("Alireza\n", 8);
  
  // char buffer[20];
	// char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  

  menu_init();

  // timeOut(100);
  while(1){

    menu_loop();
    heart_beat();
    keypad_process();
    // dht11_loop();
    // mq5_loop();
    
    


    // MQ5
    // timeOut(2000);

    // uart_loop();

    //RTC
    /*
        RTC_Read_Clock(0);	// Read clock with second add. i.e location is 0
    if (hour & TimeFormat12)	
    {
      sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
      if(IsItPM(hour)){
        strcat(buffer, "PM");
      }
      else{
        strcat(buffer, "AM");
      }
      // lcd_print_xy(0,0,buffer);
      LCD_String_xy(0,0,buffer);
    }
    else
    {
      sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
      // lcd_print_xy(0,0,buffer);
      LCD_String_xy(0,0,buffer);
    }
    RTC_Read_Calendar(3);	// Read calendar with day address i.e location is 3 
    sprintf(buffer, "%02x/%02x/%02x %3s ", date, month, year,days[day-1]);
    // lcd_print_xy(1,0,buffer);
    LCD_String_xy(1,0,buffer);
    */

    //DHT sensor
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




