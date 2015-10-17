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
    init_uart();
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
    char userInput = 0;
    
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
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111000;
    
    // Set pin RB3 to output
    TRISB &= 0b11110111;
    
    // Enable interrupts
    GIE = 1;
}
