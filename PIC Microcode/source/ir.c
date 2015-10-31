#include "main_header.h"

void init_ir()
{   
    TRISC &= 0b11110111;
    
    PSMC1CON  = 0x00;
	PSMC1MDL  = 0x80;
	PSMC1SYNC = 0x00;
	PSMC1CLK  = 0x00;
	PSMC1POL  = 0x00;
	PSMC1BLNK = 0x00;
	PSMC1REBS = 0x00;
	PSMC1FEBS = 0x00;
	PSMC1PHS  = 0x01;
	PSMC1DCS  = 0x01;
	PSMC1PRS  = 0x01;
	PSMC1ASDC = 0x00;
	PSMC1ASDL = 0x08;
	PSMC1ASDS = 0x00;
	PSMC1PHH  = 0x00;
	PSMC1PHL  = 0x00;
	PSMC1DCH  = 0x01;
	PSMC1DCL  = 0x6A;
	PSMC1PRH  = 0x02;
	PSMC1PRL  = 0x3A;
	PSMC1DBR  = 0x00;
	PSMC1DBF  = 0x00;
	PSMC1FFA  = 0x00;
	PSMC1BLKR = 0x00;
	PSMC1BLKF = 0x00;
	PSMC1STR0 = 0x08;
	PSMC1STR1 = 0x00;
	PSMC1INT  = 0x00;
	PSMC1OEN  = 0x08;
	PSMC1CON  = 0x80;
	PIE4     &= 0xEE;
	PIE4     |= 0x00;
}

void output_ir(char pkt_type, char amount)
{
	if(pkt_type == 0)
	{
		for(int i = 0;i < amount;i++){
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
		for(int i = 0;i < amount;i++){		
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
		for(int i = 0;i < amount;i++){
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


