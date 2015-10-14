/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015, 11:56 AM
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
        // select omega mode loop or individual blade loop
        if(determine_omega_mode_active() <= 0)
        {
            main_loop_individual();
        }
        else
        {
            main_loop_omega();
        }
    }
}

// Single iteration of main loop for an individual blade
void main_loop_individual()
{
#ifdef _ALPHA_BLADE
    return;
#endif
#ifdef _BETA_BLADE
    return;
#endif
#ifdef _DELTA_BLADE
    return;
#endif
#ifdef _GAMMA_BLADE
    return;
#endif
}

// Single iteration of main loop for the omega blade
void main_loop_omega()
{
#ifdef _ALPHA_BLADE
    return;
#endif
#ifdef _BETA_BLADE
    return;
#endif
#ifdef _DELTA_BLADE
    return;
#endif
#ifdef _GAMMA_BLADE
    return;
#endif
}

#ifndef _BUILD_STUBS

// Initialize TRISX registers and set oscillator frequency
void init_pic()
{
    
}

#endif