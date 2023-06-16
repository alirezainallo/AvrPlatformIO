#ifndef _UART_H
#define _UART_H

#include "main.h"


#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<PE)
#define DATA_OVERRUN (1<<DOR)

// USART Receiver buffer
#define RX_BUFFER_SIZE 256

// USART Transmitter buffer
#define TX_BUFFER_SIZE 256


void uart_init(void);
void putChar(char c);

#endif //_UART_H
