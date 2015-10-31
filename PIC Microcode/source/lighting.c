#include "main_header.h"

void init_leds()
{
    TRISC &= 0b10001111;
}

void display_health()
{
    if(health <= 0)
    {
        RC4 = 1;
    }
    else
    {
        RC4 = 0;
    }
}

void display_blade_lights(char mode)
{
    
}
