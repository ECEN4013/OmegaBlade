/*====================================================================================
File:   function_stubs.c
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void init_ir()
{
    printf("Initialized IR send/receive code.\n\r");
	PSMC1CON = 0x00;
	PSMC1MDL = 0x80;
	PSMC1SYNC = 0x00;
	PSMC1CLK = 0x01;
	PSMC1POL = 0x00;
	PSMC1BLNK = 0x00;
	PSMC1REBS = 0x80;
	PSMC1FEBS = 0x80;
	PSMC1PHS = 0x01;
	PSMC1DCS = 0x01;
	PSMC1PRS = 0x01;
	PSMC1ASDC = 0x00;
	PSMC1ASDL = 0x10;
	PSMC1ASDS = 0x00;
	PSMC1PHH = 0x00;
	PSMC1PHL = 0x00;
	PSMC1DCH = 0x02;
	PSMC1DCL = 0x30;
	PSMC1PRH = 0x04;
	PSMC1PRL = 0x76;
	PSMC1DBR = 0x00;
	PSMC1DBF = 0x00;
	PSMC1FFA = 0x00;
	PSMC1BLKR = 0x00;
	PSMC1BLKF = 0x00;
	PSMC1STR0 = 0x00;
	PSMC1STR1 = 0x00;
	PSMC1INT = 0x00;
	PSMC1OEN = 0x00;
	PSMC1CON = 0x8A;
	PIE4 &= 0xEE;
	PIE4 |= 0x00;
}

void output_ir(char pkt_type, char amount)
{
	//printf("Sent %d ", amount);
	if(pkt_type == 0)
	{
		for(int i = 0;i < amount){		
			//printf("damage.\n\r");
			//Start Envelope
			P1MDLBIT = 1;
			__delay_us(178);
			P1MDLBIT = 0;
			__delay_us(2678-178);
			
			//2x Damage Envelope
			P1MDLBIT = 1;
			__delay_us(357);
			P1MDLBIT = 0;
			__delay_us(2678-357);
			P1MDLBIT = 1;
			__delay_us(357);
			P1MDLBIT = 0;
			__delay_us(2678-357);
			
			//Stop envelope
			P1MDLBIT = 1;
			__delay_us(2678);
			P1MDLBIT = 0;
		}
		
	}
	else if(pkt_type == 1)
	{
		for(int i = 0;i < amount){	
			//printf("health.\n\r");		
			//Start Envelope
			P1MDLBIT = 1;
			__delay_us(178);
			P1MDLBIT = 0;
			__delay_us(2678-178);
			
			//2x Healing Envelope
			P1MDLBIT = 1;
			__delay_us(535);
			P1MDLBIT = 0;
			__delay_us(2678-535);
			P1MDLBIT = 1;
			__delay_us(535);
			P1MDLBIT = 0;
			__delay_us(2678-535);
			
			//Stop envelope
			P1MDLBIT = 1;
			__delay_us(2678);
			P1MDLBIT = 0;
		}
	}
	else
	{
		for(int i = 0;i < amount){	
			//printf("stun.\n\r");		
			//Start Envelope
			P1MDLBIT = 1;
			__delay_us(178);
			P1MDLBIT = 0;
			__delay_us(2678-178);
			
			//2x Stun Envelope
			P1MDLBIT = 1;
			__delay_us(714);
			P1MDLBIT = 0;
			__delay_us(2678-714);
			P1MDLBIT = 1;
			__delay_us(714);
			P1MDLBIT = 0;
			__delay_us(2678-714);
			
			//Stop envelope
			P1MDLBIT = 1;
			__delay_us(2678);
			P1MDLBIT = 0;
		}
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
