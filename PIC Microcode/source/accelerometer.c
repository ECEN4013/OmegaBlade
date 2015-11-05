#include "main_header.h"

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
