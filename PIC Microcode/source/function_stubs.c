/*====================================================================================
File:   function_stubs.c
Author: bjesper

Created on October 12, 2015, 11:56 AM
====================================================================================*/

#include "main_header.h"

#ifdef _BUILD_STUBS

void init_pic()
{
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111010;
    
    // Set pin RB3 to output
    TRISB &= 0b11110111;
}
void init_ir() { return; }
void output_ir(char pkt_type, char amount) { return; }
void play_sound(char sound_selection) { return; }
void init_accel() { return; }
char determine_sword_was_swung(char* buffer) { return 0; }
char determine_omega_mode_active()
{
    RB3 = 1;
    return 0;
}
void determine_packets_to_send(char* packets) { return; }
void display_health(char health) { return; }
void init_leds() { return; }
void display_blade_lights(char mode) { return; }
void init_isr() { return; }
void isr() { return; }

#endif