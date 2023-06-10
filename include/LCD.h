#ifndef _LCD_H
#define _LCD_H

#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */

#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define RW signal pin */
#define EN PB2 				/* Define Enable signal pin */

void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();


// int main()
// {
// 	LCD_Init();			/* Initialization of LCD*/

// 	LCD_String("ElectronicWINGS");	/* Write string on 1st line of LCD*/
// 	LCD_Command(0xC0);		/* Go to 2nd line*/
// 	LCD_String("Hello World");	/* Write string on 2nd line*/
// 	while(1);
// }

#endif //_LCD_H
