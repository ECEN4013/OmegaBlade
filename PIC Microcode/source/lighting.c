#include "main_header.h"

void writespi( unsigned char data_out );

void init_leds()
{
    // Set pins RC4, RC5, and RC6 to output
    TRISC &= 0b10001111;
    
    // Set pins RB5 and RB7 to output
    TRISBbits.TRISB7 = 0;
	TRISBbits.TRISB5 = 0;
    
    // ===== RGB LED =====
    //RED
	PSMC2CON  = 0x00;
	PSMC2MDL  = 0x00;
	PSMC2SYNC = 0x00;
	PSMC2CLK  = 0x00;
	PSMC2POL  = 0x00;
	PSMC2BLNK = 0x00;
	PSMC2REBS = 0x00;
	PSMC2FEBS = 0x00;
	PSMC2PHS  = 0x01;
	PSMC2DCS  = 0x01;
	PSMC2PRS  = 0x01;
	PSMC2ASDC = 0x00;
	PSMC2ASDL = 0x01;
	PSMC2ASDS = 0x00;
	PSMC2PHH  = 0x00;
	PSMC2PHL  = 0x00;
	PSMC2DCH  = 0x01;
	PSMC2DCL  = 0xF4;
	PSMC2PRH  = 0x03;
	PSMC2PRL  = 0xE7;
	PSMC2DBR  = 0x00;
	PSMC2DBF  = 0x00;
	PSMC2FFA  = 0x00;
	PSMC2BLKR = 0x00;
	PSMC2BLKF = 0x00;
	PSMC2STR0 = 0x01;
	PSMC2STR1 = 0x00;
	PSMC2INT  = 0x00;
	PSMC2OEN  = 0x01;
	PSMC2CON  = 0x80;
	PIE4     &= 0xDD;
	PIE4     |= 0x00;
	
    //GREEN
	PSMC3CON  = 0x00;
	PSMC3MDL  = 0x00;
	PSMC3SYNC = 0x02;
	PSMC3CLK  = 0x00;
	PSMC3POL  = 0x00;
	PSMC3BLNK = 0x00;
	PSMC3REBS = 0x00;
	PSMC3FEBS = 0x00;
	PSMC3PHS  = 0x01;
	PSMC3DCS  = 0x01;
	PSMC3PRS  = 0x01;
	PSMC3ASDC = 0x00;
	PSMC3ASDL = 0x01;
	PSMC3ASDS = 0x00;
	PSMC3PHH  = 0x00;
	PSMC3PHL  = 0x00;
	PSMC3DCH  = 0x01;
	PSMC3DCL  = 0xF4;
	PSMC3PRH  = 0x03;
	PSMC3PRL  = 0xE7;
	PSMC3DBR  = 0x00;
	PSMC3DBF  = 0x00;
	PSMC3FFA  = 0x00;
	PSMC3BLKR = 0x00;
	PSMC3BLKF = 0x00;
	PSMC3STR0 = 0x01;
	PSMC3STR1 = 0x00;
	PSMC3INT  = 0x00;
	PSMC3OEN  = 0x01;
	PSMC3CON  = 0x80;
	PIE4     &= 0xBB;
	PIE4     |= 0x00;
    
    //BLUE
	PSMC4CON  = 0x00;
	PSMC4MDL  = 0x00;
	PSMC4SYNC = 0x02;
	PSMC4CLK  = 0x00;
	PSMC4POL  = 0x00;
	PSMC4BLNK = 0x00;
	PSMC4REBS = 0x00;
	PSMC4FEBS = 0x00;
	PSMC4PHS  = 0x01;
	PSMC4DCS  = 0x01;
	PSMC4PRS  = 0x01;
	PSMC4ASDC = 0x00;
	PSMC4ASDL = 0x02;
	PSMC4ASDS = 0x00;
	PSMC4PHH  = 0x00;
	PSMC4PHL  = 0x00;
	PSMC4DCH  = 0x01;
	PSMC4DCL  = 0xF4;
	PSMC4PRH  = 0x03;
	PSMC4PRL  = 0xE7;
	PSMC4DBR  = 0x00;
	PSMC4DBF  = 0x00;
	PSMC4FFA  = 0x00;
	PSMC4BLKR = 0x00;
	PSMC4BLKF = 0x00;
	PSMC4STR0 = 0x02;
	PSMC4STR1 = 0x00;
	PSMC4INT  = 0x00;
	PSMC4OEN  = 0x02;
	PSMC4CON  = 0x80;
	PIE4     &= 0x77;
	PIE4     |= 0x00;
    
    // ===== SPI LEDs =====
    //Clear SSP Enable to config SPI
    SSPEN = 0;
    SSPCON1 = 0b00100000;
    SCKSEL = 1; //Setting MSSP Serial Clock to RB7
    SDOSEL = 1; //Setting MSSP Seruil Data Out to RB5
    SDISEL = 1; //Setting MSSP Serial Data In to RB6 (not used though)
    //Set SSP to enable SPI
    SSPEN = 1;
}

void display_health()
{       
    // END TEST ================================================================
    if(health < 10)
    {
        //****************Turn full red
        //Changing Red DC to 100%
        PSMC2DCH  = 0x00;//PSMC2 Duty Cycle High-byte
        PSMC2DCL  = 0x00;//PSMC2 Duty Cycle Low-byte
        PSMC2LD = 1; //PSMC 2 Load		
        //Green to 0%
        PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
        PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
        PSMC3LD = 1; //PSMC 3 Load
        //Blue to 0%
        PSMC4DCH  = 0xFF;//PSMC4 Duty Cycle High-byte
        PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
        PSMC4LD = 1; //PSMC 4 Load		
        //Set Load Bit to load duty cycle values
        PSMC2LD = 1; //PSMC 2 Load
        PSMC3LD = 1; //PSMC 3 Load
        PSMC4LD = 1; //PSMC 4 Load
    }
    else if(10 < health && health < 35)
    {
        //****************Turn full blue
        //Changing Red DC to 100%
        PSMC2DCH  = 0xFF;
        PSMC2DCL  = 0xFF;
        PSMC2LD = 1;		
        //Green to 0%
        PSMC3DCH  = 0xFF;
        PSMC3DCL  = 0xFF;
        PSMC3LD = 1;		
        //Blue to 0%
        PSMC4DCH  = 0x00;
        PSMC4DCL  = 0x00;
        PSMC4LD = 1;		
        //Set Load Bit to load duty cycle values
        PSMC2LD = 1;
        PSMC3LD = 1;
        PSMC4LD = 1;
    }
    else
    {
        //****************Turn full green
        //Changing Red DC to 100%
        PSMC2DCH  = 0xFF;
        PSMC2DCL  = 0xFF;
        PSMC2LD = 1;		
        //Green to 0%
        PSMC3DCH  = 0x00;
        PSMC3DCL  = 0x00;
        PSMC3LD = 1;		
        //Blue to 0%
        PSMC4DCH  = 0xFF;
        PSMC4DCL  = 0xFF;
        PSMC4LD = 1;		
        //Set Load Bit to load duty cycle values
        PSMC2LD = 1;
        PSMC3LD = 1;
        PSMC4LD = 1;
    }
}

void display_blade_lights(char mode)
{
    if( (mode == _LIGHT_MODE_INDIVIDUAL_SWING)
         || (mode == _LIGHT_MODE_OMEGA_SWING)
         || (mode == _LIGHT_MODE_CONNECT) )
    {
        for(unsigned char r = 0;r < 255; r+=5)
        {
        //32-bit start frame
            for(int i = 0;i < 4; i++){
            writespi(0x00);
            }
        //LED 1
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red    
        //LED 2
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(255 - r);//Red    
        //LED 3
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red    
        //LED 4
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(255-r);//Red    
        //LED 5
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red     
        //32-bit end frame
            for(int i = 0;i < 4; i++){
            writespi(0xFF);
            }
            __delay_ms(20);
        }

        //__delay_ms(1000);

        for(unsigned char r = 255;r > 0; r-=5)
        {
        //32-bit start frame
            for(int i = 0;i < 4; i++){
            writespi(0x00);
            }
        //LED 1
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red    
        //LED 2
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(255 - r);//Red    
        //LED 3
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red    
        //LED 4
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(255-r);//Red    
        //LED 5
                writespi(0xFF);//Brightness
                writespi(0x00);//Blue
                writespi(0x00);//Green
                writespi(r);//Red     
        //32-bit end frame
            for(int i = 0;i < 4; i++){
            writespi(0xFF);
            }
            __delay_ms(20);
        }
    }
}

void writespi( unsigned char data_out )
{
  unsigned char TempVar;  
  TempVar = SSPBUF;           // Clears BF
  PIR1bits.SSP1IF = 0;         // Clear interrupt flag
  SSPCON1bits.WCOL = 0;			//Clear any previous write collision
  SSPBUF = data_out;           // write byte to SSPBUF register
  //if ( SSPCON1 & 0x80 )        // test if write collision occurred
   //return ( -1 );              // if WCOL bit is set return negative #
  //else
   //while( !SSPSTATbits.BF );  // wait until bus cycle complete 
   while( !PIR1bits.SSP1IF );  // wait until bus cycle complete  
  //return ( 0 );                // if WCOL bit is not set return non-negative#
}
