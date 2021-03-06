/*
 * File:   main.c
 * Author: Christian Coffield
 * This program is designed to test the ISR component for the
 * Omega Blade project for Senior Design 1. 
 * Created on October 16, 2015, 4:43 PM
 */

#include "main_header.h"

#define TIMEOUT 2678 //set constant TIMEOUT, = 2.6785ms = 2678 us. 

volatile int D1cycles=0;
volatile int D2cycles=0;
volatile int Davgcycles=0;
volatile int numPackets=0;


void init_isr() {    
    //enable global interrupts and also enable interrupt on change
    INTCON = 0b11011000;

    //set port A, pins 1 and 4 to look for rising edges to interrupt
    IOCAP = IOCAP | 0b00010010;

    //set port A, pin 4 to look for falling edges to interrupt
    IOCAN = IOCAN | 0b00010000;

    //set timer 1 up with a prescaling of 1:8, on the program clock (FOSC/4),
    //synchronized with system clock. Increments every us.
    T1CON = 0b00110001;

    //set pin RA4 to be an input for IR reception
    TRISA |= 0b00010000;
}

void interrupt isr() { //note: this logic is inverted! 
    
    TMR1 = 0; //reset timer
    
    // Check to see if interrupt was on pin RA1 (sword RX))
    if (IOCAF1)
    {
        // Clear interrupt flag
        IOCAF1 = 0;
        
        __delay_us(100);
        if(!determine_omega_mode_active())
        {
            return;
        }
        
        health = 50;
        display_health();
        display_blade_lights(_LIGHT_MODE_CONNECT);
    }
    // Check to see if interrupt was on pin RA4 (IR input))
    else if (IOCAFbits.IOCAF4)
    {
        IOCAF &= 0b11101111; //clear the flag for an IR interrupt on pin A4
#if !_BETA_BLADE
        while(PORTAbits.RA4) //wait until the start bursts end
        {
            if(TMR1 >= TIMEOUT)
            { 
                return;
            }
        }
            TMR1 = 0; //reset timer
            while(!PORTAbits.RA4) //wait until the first data bursts starts
            {
                if(TMR1 >= TIMEOUT) 
                { 
                    return;
                }
            }
            TMR1 = 0; //reset timer
            while(PORTAbits.RA4) //wait until the first data bursts end
            {
                if(TMR1 >= TIMEOUT) 
                { 
                    return;
                }
            }
            D1cycles = TMR1; //record the length of the first data bursts in number of cycles
            TMR1 = 0; //reset timer
            while(!PORTAbits.RA4) //wait until the redundant data bursts starts
            {
                if(TMR1 >= TIMEOUT)
                { 
                    return;
                }
            }
            TMR1 = 0; //reset timer
            while(PORTAbits.RA4) //wait until the redundant data bursts end
            {
                    if(TMR1 >= TIMEOUT)
                    { 
                        return;
                    }
            }
            
            D2cycles = TMR1;//record the length of the redundant data bursts in number of cycles
            
            //now both lengths have been recorded, assuming no timeouts have occurred
            //check to see if the two data lengths are reasonably close to each other in length
            if((D1cycles > (D2cycles * 1.1)) || (D2cycles > (D1cycles * 1.1))) 
            { 
                return; //if the two lengths are not within 10% of each other, discard
            }
            
             Davgcycles = (D1cycles + D2cycles) / 2; //if this point has been reached, the two data lengths have been recovered successfully. Average the two lengths. 
             numPackets = Davgcycles * 17.85; //Convert the average lengths of the data bursts in clock cyles into number of on-pulses

            if(numPackets >= 6000 && numPackets <7500) 
            {
                if( (health > 0) && (!determine_omega_mode_active()) )
                {
                    health--; //damage received! Decrement HP!
                    damage_received = 1;
                }
                return;
            } 
            else if(numPackets >= 10000 && numPackets < 12000) 
            {
                if(health < 50)
                {
                    health++; //heal received! Increment HP!
                }
                return;
            }
            else if(numPackets >= 13000 && numPackets < 15000) 
            {
                stun_counter++; //stun received! Increment counter for length of stun in main loop!
                return; 
            }
        return;
#endif
    }
}