/*====================================================================================
File:   uart.c
Author: bjesper

Created on October 17, 2015
====================================================================================*/

#include "main_header.h"

// Set up USART with a baud rate of 9600.
void init_usart()
{
   TRISC6 = 1;
   TRISC7 = 1;
   SPBRG  = 3;
   TXSTA  = 0b00100000;
   RCSTA  = 0b10010000;
}

// ***************************************************************************
// The methods putch(), getch(), and getche() will be automatically used by
// the compiler and other native C methods. It is therefore necessary to
// declare them here in order for the USART module to function.
// ***************************************************************************

// Send one byte via USART.
void putch(unsigned char input)
{
   while(!TXIF)
   {
      continue;
   }
   TXREG = input;
}

// Receive one byte via USART.
unsigned char getch()
{
   while(!RCIF)
   {
      continue;
   }
   return RCREG;
}

// Receive one byte via USART and immediately send it back via USART.
unsigned char getche()
{
   unsigned char c;
   putch(c = getch());
   return c;
}
