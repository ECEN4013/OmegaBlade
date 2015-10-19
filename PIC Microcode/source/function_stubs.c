/*====================================================================================
File:   function_stubs.c
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void init_ir()
{
    printf("Initialized IR send/receive code.\n\r");
}

void output_ir(char pkt_type, char amount)
{
    printf("Sent %d ", amount);
    if(pkt_type == 0)
    {
        printf("damage.\n\r");
    }
    else if(pkt_type == 1)
    {
        printf("health.\n\r");
    }
    else
    {
        printf("stun.\n\r");
    }
}

void play_sound(char sound_selection)
{
    if(sound_selection == 0)
    {
        printf("Played Beta blade swing sound.\n\r");
    }
    else if(sound_selection == 1)
    {
        printf("Played Omega blade swing sound.\n\r");
    }
}

void init_accel()
{
    printf("Initialized accelerometer.\n\r");
}

char determine_sword_was_swung()
{
    char input = getch();
    if( input == 's' )
    {
        return 1;
    }
    else
    {
        return input;
    }
}

char determine_omega_mode_active()
{
    return omega_mode;
}

void determine_packets_to_send(char* packets)
{
    packets[0] = 5;
    packets[1] = 10;
    packets[2] = 15;
}

void display_health(char health) { return; }

void init_leds()
{
    printf("Initialized LEDs.\n\r");
}

void display_blade_lights(char mode)
{
    if(mode == _LIGHT_MODE_INDIVIDUAL_SWING)
    {
        printf("Displayed individual sword swing light show.\n\r");
    }
    else if(mode == _LIGHT_MODE_OMEGA_SWING)
    {
        printf("Displayed Omega blade swing light show.\n\r");
    }
}

void init_isr()
{
    printf("Initialized ISR.\n\r");
}
void isr() { return; }
