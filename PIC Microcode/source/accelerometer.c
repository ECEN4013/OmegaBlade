#include "main_header.h"

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
	
    if(determine_omega_mode_active())
    {
        x_pos_thresh = midpoint + 2900;
        x_neg_thresh = midpoint - 2900;
        y_pos_thresh = midpoint + 2900;
        y_neg_thresh = midpoint - 2900;
        z_pos_thresh = midpoint + 2900;
        z_neg_thresh = midpoint - 2900;
    }
    else
    {
#if _ALPHA_BLADE
        x_pos_thresh = midpoint + 2900;
        x_neg_thresh = midpoint - 2900;
        y_pos_thresh = midpoint + 2900;
        y_neg_thresh = midpoint - 2900;
        z_pos_thresh = midpoint + 2900;
        z_neg_thresh = midpoint - 2900;
#elif _BETA_BLADE
        x_pos_thresh = midpoint + 3000;
        x_neg_thresh = midpoint - 3000;
        y_pos_thresh = midpoint + 3000;
        y_neg_thresh = midpoint - 3000;
        z_pos_thresh = midpoint + 3000;
        z_neg_thresh = midpoint - 3000;
#elif _DELTA_BLADE
        x_pos_thresh = midpoint + 3050;
        x_neg_thresh = midpoint - 3050;
        y_pos_thresh = midpoint + 3050;
        y_neg_thresh = midpoint - 3050;
        z_pos_thresh = midpoint + 3050;
        z_neg_thresh = midpoint - 3050;
#elif _GAMMA_BLADE
        x_pos_thresh = midpoint + 3050;
        x_neg_thresh = midpoint - 3050;
        y_pos_thresh = midpoint + 3050;
        y_neg_thresh = midpoint - 3050;
        z_pos_thresh = midpoint + 3050;
        z_neg_thresh = midpoint - 3050;
#endif
    }
	
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
