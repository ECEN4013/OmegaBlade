/*
 * File:   main.c
 * Author: Christian Coffield
 * This program is designed to test the ISR component for the
 * Omega Blade project for Senior Design 1. 
 * Created on October 16, 2015, 4:43 PM
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include "xc.h"

void interrupt ISR();
void init_ISR();

#define F_OSC 16000000
#define _XTAL_FREQ 16000000

#define TIMEOUT 2678 //set constant TIMEOUT, = 2.6785ms = 2678 us. 

volatile int HealthPoints = 10;
volatile int stunCount = 0;
volatile int D1cycles=0;
volatile int D2cycles=0;
volatile int Davgcycles=0;
volatile int numPackets=0;

void main(void) 
{
    OSCCON |= 0b01111010; // Configure for 16MHz operation with internal oscillator
    init_ISR(); //initialize the ISR-necessary registers
    
    TRISA = 0b00010000; //set all of PORTA to be outputs except RA4, the IR input
    ANSELA = 0; //configure all of PORTA to be digital, not analog

    //test the lights by blinking three times
    int i = 0;
    while(i < 3) {
    PORTA |= 0b00000111;
    __delay_ms(200);
    PORTA &= 0b11111000; 
    __delay_ms(200);
    i++;
    } 
    //TMR1 = 0;
    while(1) 
    {
        if(HealthPoints < 10) //damage received!
        {
            RA0 = 1; //turn on first light
            __delay_ms(200); //wait 
            RA0 = 0; //turn off first light
            HealthPoints = 10; //return to default condition
        }
        if(HealthPoints > 10) //health received!
        {
            RA1 = 1; //turn on second light
            __delay_ms(200); //wait
            RA1 = 0; //turn off second light
            HealthPoints = 10; //return to default condition
        }
        if(stunCount > 0) //stun received!
        {
            RA2 = 1; //turn on third light
            __delay_ms(200); //wait
            RA2 = 0; //turn off third light
            stunCount = 0; //return to default condition
        }
    }
    return;
}

void init_ISR() {     
//enable global interrupts and also enable interrupt on change
INTCON = 0b11011000;

//set port A, pin 4 to look for rising edges to interrupt
IOCAP = IOCAP | 0b00010000;

//set port A, pin 4 to look for falling edges to interrupt
IOCAN = IOCAN | 0b00010000;

//set timer 1 up with a prescaling of 1:4, on the program clock (FOSC/4),
//synchronized with system clock. Increments every us.
T1CON = 0b00100001;
}

void interrupt ISR() { //note: this logic is inverted! 
    TMR1 = 0; //reset timer
    if (IOCAFbits.IOCAF4)
    {
        IOCAF &= 0b11101111; //clear the flag for an IR interrupt on pin A4
        while(!PORTAbits.RA4) //wait until the start bursts end
        {
            if(TMR1 >= TIMEOUT)
            { 
                return;
            }
        }
            TMR1 = 0; //reset timer
            while(PORTAbits.RA4) //wait until the first data bursts starts
            {
                if(TMR1 >= TIMEOUT) 
                { 
                    return;
                }
            }
            TMR1 = 0; //reset timer
            while(!PORTAbits.RA4) //wait until the first data bursts end
            {
                if(TMR1 >= TIMEOUT) 
                { 
                    return;
                }
            }
            D1cycles = TMR1; //record the length of the first data bursts in number of cycles
            TMR1 = 0; //reset timer
            while(PORTAbits.RA4) //wait until the redundant data bursts starts
            {
                if(TMR1 >= TIMEOUT)
                { 
                    return;
                }
            }
            TMR1 = 0; //reset timer
            while(!PORTAbits.RA4) //wait until the redundant data bursts end
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
                HealthPoints--; //damage received! Decrement HP!
                return;
            } 
            else if(numPackets >= 10000 && numPackets < 12000) 
            {
                HealthPoints++; //heal received! Increment HP!
                return;
            }
            else if(numPackets >= 13000 && numPackets < 15000) 
            {
                stunCount++; //stun received! Increment counter for length of stun in main loop!
                return; 
            }
        return;
    }
}