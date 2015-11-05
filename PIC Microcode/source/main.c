/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void main_loop_individual();
void main_loop_omega();

char stun_counter = 0;
char health = 50;
char damage_received = 0;

int main()
{
    char pkt_arr[] = {0, 0, 0}; // {damage, health, stun}
    unsigned char i = 0;
    
    // Initialize PIC and UART
    init_pic();
    //init_uart();
    
    // Wait a tenth of a second for clock to stabilize
    __delay_ms(100);
    
    // Initialize teammates' code
    init_ir();
    init_accel();
    init_leds();
    init_isr();
    init_conn();
    
    /*
    RC4 = 1;
    __delay_ms(250);
    RC4 = 0;
    __delay_ms(250);
    RC4 = 1;
    __delay_ms(250);
    RC4 = 0;
    __delay_ms(250);
    RC4 = 1;
    __delay_ms(250);
    RC4 = 0;
    */
    
    // main loop
    while(1)
    {
#if _ALPHA_BLADE
        display_health();
        if(damage_received)
        {
            display_blade_lights(_LIGHT_MODE_DAMAGE_RECEIVED);
            damage_received = 0;
        }
        
        if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
        {

            if(!determine_omega_mode_active())
            {
                display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                
                determine_packets_to_send(&pkt_arr);
                
                for(i = 3; i > 0; --i)
                {
                    if(pkt_arr[i-1] > 0)
                    {
                        GIE = 0;
                        output_ir(i-1, pkt_arr[i-1]);
                        GIE = 1;
                    }
                }
            }
            else
            {
                display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
            }
        }

        
        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            
            //****************Turn full blue
            //Green to 0%
            PSMC2DCH  = 0x00;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0x00;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 100%
            PSMC4DCH  = 0x00;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);

            //****************Turn off
            //Green to 0%
            PSMC2DCH  = 0xFF;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0xFF;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 0%
            PSMC4DCH  = 0xFF;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);
            
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;
    
#elif _BETA_BLADE
        display_health();
        if( determine_sword_was_swung() )
        {
            if(!determine_omega_mode_active())
            {
                play_sound(_SOUND_TYPE_INDIVIDUAL);
                display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                
                determine_packets_to_send(&pkt_arr);

                for(i = 3; i > 0; --i)
                {
                    if(pkt_arr[i-1] > 0)
                    {
                        GIE = 0;
                        output_ir(i-1, pkt_arr[i-1]);
                        GIE = 1;
                    }
                }
            }
            else
            {
                play_sound(_SOUND_TYPE_OMEGA);
                display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
            }

            break;
        }
    
#elif _DELTA_BLADE
        display_health();
        if(damage_received)
        {
            display_blade_lights(_LIGHT_MODE_DAMAGE_RECEIVED);
            damage_received = 0;
        }
        
        if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
        {
            if(!determine_omega_mode_active())
            {
                display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
            }
            else
            {
                display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
            }
            
            determine_packets_to_send(&pkt_arr);

            for(i = 3; i > 0; --i)
            {
                if(pkt_arr[i-1] > 0)
                {
                    GIE = 0;
                    output_ir(i-1, pkt_arr[i-1]);
                    GIE = 1;
                }
            }

            break;
        }

        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            
            //****************Turn full blue
            //Green to 0%
            PSMC2DCH  = 0x00;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0x00;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 100%
            PSMC4DCH  = 0x00;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);

            //****************Turn off
            //Green to 0%
            PSMC2DCH  = 0xFF;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0xFF;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 0%
            PSMC4DCH  = 0xFF;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);
            
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;

#elif _GAMMA_BLADE
        display_health();
        if(damage_received)
        {
            display_blade_lights(_LIGHT_MODE_DAMAGE_RECEIVED);
            damage_received = 0;
        }
        
        if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
        {
            if(!determine_omega_mode_active())
            {
                display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                
                determine_packets_to_send(&pkt_arr);

                for(i = 3; i > 0; --i)
                {
                    if(pkt_arr[i-1] > 0)
                    {
                        GIE = 0;
                        output_ir(i-1, pkt_arr[i-1]);
                        GIE = 1;
                    }
                }
            }
            else
            {
                display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
            }

            break;
        }

        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            
            //****************Turn full blue
            //Green to 0%
            PSMC2DCH  = 0x00;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0x00;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 100%
            PSMC4DCH  = 0x00;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);

            //****************Turn off
            //Green to 0%
            PSMC2DCH  = 0xFF;//PSMC2 Duty Cycle High-byte
            PSMC2DCL  = 0xFF;//PSMC2 Duty Cycle Low-byte
            PSMC2LD = 1; //PSMC 2 Load		
            //Blue to 0%
            PSMC3DCH  = 0xFF;//PSMC3 Duty Cycle High-byte
            PSMC3DCL  = 0xFF;//PSMC3 Duty Cycle Low-byte
            PSMC3LD = 1; //PSMC 3 Load
            //Red to 0%
            PSMC4DCH  = 0xFF;//PSMC4 Duty Cycle High-byte
            PSMC4DCL  = 0xFF;//PSMC4 Duty Cycle Low-byte
            PSMC4LD = 1; //PSMC 4 Load		
            //Set Load Bit to load duty cycle values
            PSMC2LD = 1; //PSMC 2 Load
            PSMC3LD = 1; //PSMC 3 Load
            PSMC4LD = 1; //PSMC 4 Load

            __delay_ms(50);
            
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;
        
#endif
        
    }
}

// Initialize TRISX registers and set oscillator frequency
void init_pic()
{
    ANSELA = 0;
    ANSELB = 0;
    
    // Configure RB2 and RB3 (audio triggers) as outputs
    TRISB &= 0b11110011;
    RB2 = 1;
    RB3 = 1;
    
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111000;
    
    // Enable global interrupts
    GIE = 1;
}
