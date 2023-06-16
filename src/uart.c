#include "uart.h"


char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 64
unsigned char rx_wr_index=0,rx_rd_index=0;
#else
unsigned int rx_wr_index=0,rx_rd_index=0;
#endif

#if RX_BUFFER_SIZE < 256
unsigned char rx_counter=0;
#else
unsigned int rx_counter=0;
#endif

// This flag is set on USART Receiver buffer overflow
bool rx_buffer_overflow;

// USART Receiver interrupt service routine
ISR(USART_RXC_vect)
{
char status,data;
status=UCSRA;
data=UDR;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer[rx_wr_index++]=data;
#if RX_BUFFER_SIZE == 256
   // special case for receiver buffer size=256
   if (++rx_counter == 0) rx_buffer_overflow=1;
#else
   if (rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   if (++rx_counter == RX_BUFFER_SIZE)
      {
      rx_counter=0;
      rx_buffer_overflow=1;
      }
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
char getChar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index++];
#if RX_BUFFER_SIZE != 256
if (rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#endif
cli();
--rx_counter;
sei();
return data;
}

#endif


// --------------------------------------------------------

char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
unsigned char tx_wr_index=0,tx_rd_index=0;
#else
unsigned int tx_wr_index=0,tx_rd_index=0;
#endif

#if TX_BUFFER_SIZE < 256
unsigned char tx_counter=0;
#else
unsigned int tx_counter=0;
#endif

// USART Transmitter interrupt service routine
ISR(USART_TXC_vect)
{
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index++];
#if TX_BUFFER_SIZE != 256
   if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
void putChar(char c)
{
while (tx_counter == TX_BUFFER_SIZE);
cli();
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer[tx_wr_index++]=c;
#if TX_BUFFER_SIZE != 256
   if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
#endif
   ++tx_counter;
   }
else
   UDR=c;
sei();
}
#endif

void uart_init(void){
  DDRD &= ~(1 << PD0);
  DDRD |=  (1 << PD1);
  /*
  // // UDR reg for send and receive
  // // UCSRA for flag
  // //    UDRE: USART Data Register Empty
  
  // // UCSRB
  // //    RXCIE: RX Complete Interrupt Enable
  // //    TXCIE: TX Complete Interrupt Enable
  // //    RXEN: Receiver Enable
  // //    TXEN: Receiver Enable
  // UCSRB = (1 << RXCIE)|(1 << TXCIE)|(1 << RXEN)|(1 << TXEN);
  // // UCSRC 
  // //    URSEL: Register Select //1:when read//1:when we write
  // //    UMSEL: USART Mode Select //0:UMSEL: USART Mode Select
  // //    USBS: Stop Bit Select //1:2bit stop bit
  // //    UCSZ0:1/UCSZ1:1 //for 8bit data
  // uint8_t UCSRC_tmp = (1 << URSEL)|(1 << UCSZ0)|(1 << UCSZ1);//|(1 << USBS)
  // UCSRC_tmp &= ~(1 << UMSEL);
  // UCSRC = UCSRC_tmp;
  // // UBRRL and UBRRH
  // //    URSEL: Register Select //0:when read//0:when we write
  // //    Bit 14:12: must be zero when we write reg
  // //    UBRR11:0: USART Baud Rate Register : 51 for (U2X = 0)
  // uint8_t UBRRH_tmp = (1 << URSEL)|(1 << 4)|(1 << 5)|(1 << 6)|(0x0F);
  // UBRRH = ~UBRRH_tmp;
  // UBRRL = 51;
  */
  UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<PE) | (1<<U2X) | (0<<MPCM);
  UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
  UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
  UBRRH=0x00;
  UBRRL=0x67;
}
/*
// char uart_send_buff[50];
// size_t uart_send_ind = 0;
// uint8_t rxCom = 0;
// void uart_send_ch(char data){
//   UDR = data;
// }
// void uart_send_data(const char*data, size_t len){
//   memcpy(uart_send_buff, data, len);
// }
// ISR(USART_RXC_vect){

// }
// ISR(USART_TXC_vect){
//   rxCom = 1;
// }
// void putChar(char c)
// {
//   // cli();
//   if (((UCSRA & (1<<UDRE))==0))
//   UDR=c;
//   // sei();
// }*/
