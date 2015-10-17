/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void main_loop_individual();
void main_loop_omega();

int stun_counter = 0;

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
    char pkt_arr = {0, 0, 0};
    int i = 0;
    
#if _ALPHA_BLADE || _GAMMA_BLADE
    
    while(!determine_sword_was_swung()) {}
    
    if(!determine_omega_mode_active())
    {
        determine_packets_to_send(&pkt_arr);
        
        for(i = 0; i < 3; ++i)
        {
            if(pkt_arr[i] > 0)
            {
                output_ir(pkt_arr[i], i);
            }
        }
    }
    
    display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
    
    GIE = 0;
    if(stun_counter > 0)
    {
        GIE = 1;
        __delay_ms(100);
        GIE = 0;
        --stun_counter;
    }
    GIE = 1;
    
    return;
#elif _BETA_BLADE
    return;
#elif _DELTA_BLADE
    return;
#endif
}

// Single iteration of main loop for the omega blade
void main_loop_omega()
{
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
