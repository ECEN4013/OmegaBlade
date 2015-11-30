#include "main_header.h"

/*
void init_accel()
{
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    ANSELAbits.ANSA2 = 1;
    ANSELAbits.ANSA3 = 1;
    ADCON1 = 0b11110000; //2?s complement, Frc clock
    ADCON2 = 0b00001111; //Vdd and Vss Vref 
}


char determine_sword_was_swung()
{
    if(RC7 == 1)
    {
        return 1;
    }
    
    //thresholds for swing
    int lowAdh;
    int lowAdl;
    int highAdh;
    int highAdl;
	//counters for the adc
	int x = 0;
	int y = 0;
	int count = 2;
	//value to return if the blade has been swung
	char swung = 0;
	
	//Sets the threshold depending on if it is in Omega mode.
	if(determine_omega_mode_active())
	{
		//For light swings
		lowAdh = 1;
		lowAdl = 80;
		highAdh = 1;
		highAdl = 170;
	}
	else
	{
#if _ALPHA_BLADE
    //for light flick
    lowAdh = 1;
    lowAdl = 80;
    highAdh = 1;
    highAdl = 170;
#elif _BETA_BLADE
    //for heavy swings
    lowAdh = 1;
    lowAdl = 73;
    highAdh = 1;
    highAdl = 177;
#elif _DELTA_BLADE || _GAMMA_BLADE
    //for moderate swings
    lowAdh = 1;
    lowAdl = 75;
    highAdh = 1;
    highAdl = 175;
#endif
		
	}
	  //Check yout
      ADCON0 = 0b10001111;   //Select Channel RA3 for yout.
                               
        
        for(int i = 0; i< 1000 && y < count ; i++)
        {    
	
            
            if(ADGO)
            {
				//still converting Analog voltage
			}
            else
             {
                //sets it to be ready to convert voltage
				ADGO = 1;
                
                //if the input voltages passes threshold, the y counter increments.
				//Having a counter prevents any non-swing movement from being counted.
				
                if((ADRESH >=  highAdh && ADRESL >= highAdl ) || (ADRESH <= lowAdh && ADRESL <= lowAdl))
                {
                    y = y + 1;
                }
                else
                {
					//resets counter for next cycle.
                    y = 0;
                }
            }
        }   
    
	 //check xout
      ADCON0 = 0b10001011;   //Select Channel RA2 to read xout voltage; pg 177
        for(int i = 0; i < 1000 && x < count; i++)
        {
			
            if(ADGO)
            {
				//still converting Analog voltage
			}
            else
            {
				//if the input voltages passes threshold, the x counter increments.
				//Having a counter prevents any non-swing movement from being counted.
                if((ADRESH >=  highAdh && ADRESL >= highAdl ) || (ADRESH <= lowAdh && ADRESL <= lowAdl))
                {
                    x = x+1;
                }
                else
                {
                    x = 0;
                }
				//sets it to be ready to convert Analog voltage.
                ADGO = 1;
            }
        }
	
		//If both counters are high enough, they send a high signal to main
		//indicating the sword has been swung.
	    if(x >= count && y >= count)
        {
            swung = 1;
            x = 0;
            y = 0;
        }
      
	return swung;
	
}
 */

void init_accel()
{
    ADCON0 = 0;
    ADCON1 = 0b10000000;
	ADCON2 = 0b00001111;
	
	// Set pins RA2, RA3, and RA5 to analog input
	TRISA |= 0b00101100;
	ANSELA |= 0b00101100;
    
    // Set pin RC7 to digital input (for manual swing input)
    TRISC |= 10000000;
}


char determine_sword_was_swung()
{
    
    if(RC7 == 1)
    {
        return 1;
    }
    
    unsigned char xh = 0;
    unsigned char yh = 0;
    unsigned char zh = 0;
    unsigned char xl = 0;
    unsigned char yl = 0;
    unsigned char zl = 0;
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
	int x_pos_thresh = 0;
    int x_neg_thresh = 0;
    int y_pos_thresh = 0;
    int y_neg_thresh = 0;
    int z_pos_thresh = 0;
    int z_neg_thresh = 0;
    const int midpoint = 4096;//0x0151;  // Represents 1.65 volts
    const int pos_shock_thresh = midpoint + 1000;
    const int neg_shock_thresh = midpoint - 1000;
	
#if _ALPHA_BLADE
	x_pos_thresh = midpoint + 2900;
    x_neg_thresh = midpoint - 2900;
    y_pos_thresh = midpoint + 2900;
    y_neg_thresh = midpoint - 2900;
    z_pos_thresh = midpoint + 2900;
    z_neg_thresh = midpoint - 2900;
#elif _BETA_BLADE
	x_pos_thresh = midpoint + 2900;//3500;
    x_neg_thresh = midpoint - 2900;//3500;
    y_pos_thresh = midpoint + 2900;//3500;
    y_neg_thresh = midpoint - 2900;//3500;
    z_pos_thresh = midpoint + 2900;//3500;
    z_neg_thresh = midpoint - 2900;//3500;
#elif _DELTA_BLADE
	x_pos_thresh = midpoint + 3200;
    x_neg_thresh = midpoint - 3200;
    y_pos_thresh = midpoint + 3200;
    y_neg_thresh = midpoint - 3200;
    z_pos_thresh = midpoint + 3200;
    z_neg_thresh = midpoint - 3200;
#elif _GAMMA_BLADE
	x_pos_thresh = midpoint + 3200;
    x_neg_thresh = midpoint - 3200;
    y_pos_thresh = midpoint + 3200;
    y_neg_thresh = midpoint - 3200;
    z_pos_thresh = midpoint + 3200;
    z_neg_thresh = midpoint - 3200;
#endif
	
	// Select channel AN2
    ADCON0 = 0b00001001;
	__delay_us(100);
	ADGO = 1;
	while(ADGO)
	{
		continue;
	}
    x = ADRES;
    
	
	// Select channel AN3
	ADCON0 = 0b00001101;
	__delay_us(100);
	ADGO = 1;
	while(ADGO)
	{
		continue;
	}
	y = ADRES;
	
	// Select channel AN4
	ADCON0 = 0b00010101;
	__delay_us(100);
	ADGO = 1;
	while(ADGO)
	{
		continue;
	}
	z = ADRES;
    
    /*if( ( y > y_neg_thresh ) && ( ( x > x_pos_thresh ) || ( x < x_neg_thresh ) || ( y > y_pos_thresh ) ) )*/
	if( (( x > x_pos_thresh ) || ( x < x_neg_thresh )
        || ( y > y_pos_thresh ) || ( y < y_neg_thresh ) 
        || ( z > z_pos_thresh ) || ( z < z_neg_thresh )) 
        /*&& ( x < pos_shock_thresh )
        && ( x > neg_shock_thresh )
        && ( y < pos_shock_thresh )
        && ( y > neg_shock_thresh )
        && ( z < pos_shock_thresh )
        && ( z > neg_shock_thresh )*/ )
	{
		return 1;
	}
	else
	{
		return 0;
	}
    
}
