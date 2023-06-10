#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DDR  DDRA
#define BLINK_PORT PORTA
#define BLINK_PINS ((1 << PA0)|(1 << PA2)|(1 << PA4)|(1 << PA6))

int main(void){

  BLINK_DDR  = 0xFF;
  BLINK_PORT = 0x00;

  while(1){
    BLINK_PORT |= BLINK_PINS;
    _delay_ms(500);
    BLINK_PORT &= ~BLINK_PINS;
    _delay_ms(500);
  }
}