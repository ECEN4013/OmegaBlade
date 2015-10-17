/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void main_loop_individual();
void main_loop_omega();

int main()
{
    // Initialize team members' blocks
    init_pic();
    init_ir();
    init_accel();
    init_leds();
    init_isr();

    // main loop
    while(1)
    {
        main_loop_individual();
        /*
        // select omega mode loop or individual blade loop
        if(determine_omega_mode_active() <= 0)
        {
            main_loop_individual();
        }
        else
        {
            main_loop_omega();
        }
        */ 
    }
}

// Single iteration of main loop for an individual blade
void main_loop_individual()
{
    //printf("Main Loop Individual    ");
    RB3 = 1;
    __delay_ms(500);
    RB3 = 0;
    __delay_ms(500);
#if _ALPHA_BLADE
    return;
#elif _BETA_BLADE
    return;
#elif _DELTA_BLADE
    return;
#elif _GAMMA_BLADE
    return;
#endif
}

// Single iteration of main loop for the omega blade
void main_loop_omega()
{
    printf("Main Loop Omega    ");
#if _ALPHA_BLADE
    return;
#elif _BETA_BLADE
    return;
#elif _DELTA_BLADE
    return;
#elif _GAMMA_BLADE
    return;
#endif
}

// Initialize TRISX registers and set oscillator frequency
void init_pic()
{
    // Configure for 16MHz operation with internal oscillator
    OSCCON |= 0b01111010;
    
    // Set pin RB3 to output
    TRISB &= 0b11110111;
}
