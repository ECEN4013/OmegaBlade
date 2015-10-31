/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/

#include "main_header.h"

void main_loop_individual();
void main_loop_omega();

char stun_counter = 0;
char health = 5;

int main()
{
    char pkt_arr[] = {0, 0, 0}; // {damage, health, stun}
    char i = 0;
    
    // Initialize PIC and UART
    init_pic();
    //init_uart();
    
    // Wait a tenth of a second for clock to stabilize
    __delay_ms(100);
    
    // Initialize teammates' code
    init_ir();
    //init_accel();
    init_leds();
    init_isr();
    
    // main loop
    while(1)
    {
#if _ALPHA_BLADE
        while( 1 )
        {
            display_health();
            output_ir(_PKT_TYPE_DAMAGE, 5);
            /*
            if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
            {

                if(!determine_omega_mode_active())
                {
                    determine_packets_to_send(&pkt_arr);

                    for(i = 2; i >= 0; --i)
                    {
                        if(pkt_arr[i] > 0)
                        {
                            output_ir(i, pkt_arr[i]);
                        }
                    }
                    display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                }
                else
                {
                    display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
                }

                break;
            }
             */
        }
/*
        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            __delay_ms(100);
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;
*/    
#elif _BETA_BLADE
        while( 1 )
        {
            display_health();
            if( determine_sword_was_swung() )
            {
                if(!determine_omega_mode_active())
                {
                    determine_packets_to_send(&pkt_arr);

                    for(i = 2; i >= 0; --i)
                    {
                        if(pkt_arr[i] > 0)
                        {
                            output_ir(i, pkt_arr[i]);
                        }
                    }

                    play_sound(0);
                    display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                }
                else
                {
                    play_sound(1);
                    display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
                }

                break;
            }
        }
    
#elif _DELTA_BLADE
        while( 1 )
        {
            display_health();
            if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
            {
                determine_packets_to_send(&pkt_arr);

                for(i = 2; i >= 0; --i)
                {
                    if(pkt_arr[i] > 0)
                    {
                        output_ir(i, pkt_arr[i]);
                    }
                }

                if(!determine_omega_mode_active())
                {
                    display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                }
                else
                {
                    display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
                }

                break;
            }
        }

        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            __delay_ms(100);
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;

#elif _GAMMA_BLADE
        while( 1 )
        {
            display_health();
            if( determine_sword_was_swung() && ( ( health > 0) || determine_omega_mode_active() ) )
            {
                if(!determine_omega_mode_active())
                {
                    determine_packets_to_send(&pkt_arr);

                    for(i = 2; i >= 0; --i)
                    {
                        if(pkt_arr[i] > 0)
                        {
                            output_ir(i, pkt_arr[i]);
                        }
                    }
                    display_blade_lights(_LIGHT_MODE_INDIVIDUAL_SWING);
                }
                else
                {
                    display_blade_lights(_LIGHT_MODE_OMEGA_SWING);
                }

                break;
            }
        }

        GIE = 0;
        while( ( stun_counter > 0 ) && !determine_omega_mode_active() )
        {
            GIE = 1;
            __delay_ms(100);
            GIE = 0;
            --stun_counter;
        }
        GIE = 1;
        
        //main_loop_individual();
        /*
        // select omega mode loop or individual blade loop
        if(determine_omega_mode_active() <= 0)
        {
            main_loop_individual();
        }
        else
        {
            main_loop_omega();
        }
        */
        
#endif
        
    }
}

// Initialize TRISX registers and set oscillator frequency
void init_pic()
{
    ANSELA = 0;
    ANSELB = 0;
    
    // Configure RB2 and RB3 (audio triggers) as outputs
    TRISB = 0b11110011;
    
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111000;
    
    // Enable global interrupts
    GIE = 1;
}
