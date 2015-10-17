/*====================================================================================
File:   uart.c
Author: bjesper

Created on October 17, 2015
====================================================================================*/

#include "main_header.h"

// Set up USART with a baud rate of 9600.
void init_uart()
{
    // Set RC6(TX) to output)
    TRISC &= 10111111;
    
    // Set RC7(RX) to input)
    TRISC |= 10000000;
    
    // Set baud rate to 9600
    SPBRG  = 51;
    BRGH = 0;
    BRG16 = 0;
    
    // Enable TX and RX
    //TXSTA  = 0b00100000;
    //RCSTA  = 0b10010000;
    SYNC = 0;
    SPEN = 1;
    TXEN = 1;
    CREN = 1;
    RCIE = 1;
}

// ***************************************************************************
// The methods putch(), getch(), and getche() will be automatically used by
// the compiler and other native C methods. It is therefore necessary to
// declare them here in order for the USART module to function.
// ***************************************************************************

// Send one byte via USART.
void putch(unsigned char input)
{
   while(!TRMT)
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
