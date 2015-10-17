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
    return;    
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
