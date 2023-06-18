#include "main.h"
#include "adc.h"
#include "mq5.h"
#include "gsm.h"
#include "RTC.h"
#include "menu.h"
#include "uart.h"
#include "DHT11.h"
#include "timTick.h"
#include "time_out.h"
#include "keypad_4x4.h"
#include "heart_beat.h"


int main(void){
  
  sei(); //enable global interrupt
  
  tim1_init();

  menu_init();

  // uart_init();

  while(1){

    menu_loop();
    heart_beat();
    keypad_process();

    dht11_loop();
    mq5_loop();
    
    GSM_loop();

  }
}




