/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/
#define _XTAL_FREQ 32000000 
#include "main_header.h"
//void main_loop_individual();
//void main_loop_omega();
//init_ir();
char stun_counter = 0;
char health = 50;
char omega_mode = 0;
char blade = 0;

    

int main()
{
    init_pic();
    init_ir();
    
    while(1){
        output_ir(0,100);
        __delay_ms(250);
        output_ir(1,100);
        __delay_ms(250);
        output_ir(2,100);
        __delay_ms(250);
        
        
    }
  
}

// Initialize TRISX registers and set oscillator frequency
void init_pic(){
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111000;
    
    // Set pin RB3 to output
    TRISCbits.TRISC3 = 0;
    
    // Enable interrupts
    GIE = 0;
}
