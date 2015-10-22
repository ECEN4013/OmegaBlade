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

// Send one byte via UART.
void putch(unsigned char input)
{
   while(!TRMT)
   {
      continue;
   }
   TXREG = input;
}

// Receive one byte via UART.
unsigned char getch()
{
    unsigned char counter = 0;
    
    while( !RCIF )
    {
        continue;
        //if(counter > 200)
        //{
        //    return ' ';
        //}
        //++counter;
    }
    return RCREG;
}

// Receive one byte via UART and immediately send it back via UART.
unsigned char getche()
{
   unsigned char c;
   putch(c = getch());
   return c;
}

// Wait for a byte to arrive on UART, then return it
unsigned char waitch()
{
    while(!RCIF)
    {
        continue;
    }
    return RCREG;
}


// Run a simple routine to test UART communication
void uart_test()
{
    char userInput = 0;
    
    while(1)
    {
        printf("\n\rMain Loop Individual\n\r");
        printf("Please enter the character A: ");

        userInput = getch();
        if(userInput == 'A')
        {
            printf("\n\rGood job. You know how to read instructions.\n\n");
        }
        else
        {
            printf("\n\rWrong key. Try again.\n\r");
        }
        RB3 = 1;
        __delay_ms(500);
        RB3 = 0;
        __delay_ms(500);
    }
}