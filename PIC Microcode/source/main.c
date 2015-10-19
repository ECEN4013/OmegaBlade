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
char omega_mode = 0;
char blade = 0;

int main()
{
    char pkt_arr[] = {0, 0, 0}; // {damage, health, stun}
    char userInput = ' ';
    char i = 0;
    
    // Initialize team members' blocks
    init_pic();
    init_uart();
    
    // Wait a tenth of a second for clock to stabilize, then turn on status LED
    __delay_ms(100);
    RB3 = 1;
    
    printf("\n\r=========================================================\n\r");
    
    // Initialize teammates' code
    init_ir();
    init_accel();
    init_leds();
    init_isr();
    
    // Ask user to select test conditions
    printf("\n\rWhich blade would you like to test? Enter a for Alpha, b for\n\r");
    printf("Beta, d for Delta, or g for Gamma.\n\r");
    while(1)
    {
        userInput = waitch();
        if(userInput == 'a') 
        {
            printf("1\n\r");
            blade = 1;
            break;
        }
        else if( userInput == 'b' )
        {
            printf("2\n\r");
            blade = 2;
            break;
        }
        else if( userInput == 'd' )
        {
            printf("3\n\r");
            blade = 3;
            break;
        }
        else if( userInput == 'g' )
        {
            printf("4\n\r");
            blade = 4;
            break;
        }
        printf("Invalid input. Try again.\n\r");
    }
    
    printf("Are the blades in omega mode? (y/n)\n\r");
    while(1)
    {
        userInput = waitch();
        if(userInput == 'y') 
        {
            printf("y\n\r");
            omega_mode = 1;
            break;
        }
        else if( userInput == 'n' )
        {
            printf("n\n\r");
            omega_mode = 0;
            break;
        }
        printf("Invalid input. Try again.\n\r");
    }
    
    printf("Press \'s\' to swing the sword and see what happens!\n\r");
    printf("Press 'd', 'h', or 't' to send damage, health, or stun packets.\n\r");
    printf("Press 'o' to toggle Omega mode.\n\r\n\r");
    
    // main loop
    while(1)
    {
        // -----Alpha blade--------------------
        if( blade == 1 )
        {
            while( 1 )
            {
                userInput = determine_sword_was_swung();
                if(userInput == 1)
                {
                    printf("Sword was swung\n\r");

                    if(!determine_omega_mode_active())
                    {
                        determine_packets_to_send(&pkt_arr);

                        for(i = 0; i < 3; ++i)
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
                if(userInput == 'd' && !determine_omega_mode_active())
                {
                    if(health > 0)
                    {
                        health -= 10;
                    }
                    printf("The blade has been damaged. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 'h' && !determine_omega_mode_active())
                {
                    if(health < 50)
                    {
                        health += 10;
                    }
                    printf("The blade has been healed. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 't' && !determine_omega_mode_active())
                {
                    stun_counter += 10;
                    printf("The blade has been stunned.\n\r");
                    
                    break;
                }
                else if(userInput == 'o')
                {
                    if(!determine_omega_mode_active())
                    {
                        omega_mode = 1;
                        printf("Omega mode enabled.\n\r");
                    }
                    else
                    {
                        omega_mode = 0;
                        printf("Omega mode disabled.\n\r");
                    }
                    break;
                }
                
                userInput = ' ';
            }

            GIE = 0;
            while(stun_counter > 0)
            {
                GIE = 1;
                __delay_ms(100);
                GIE = 0;
                --stun_counter;
            }
            GIE = 1;
        }
        // -----Beta blade--------------------
        if( blade == 2 )
        {
            while( 1 )
            {
                userInput = determine_sword_was_swung();
                if(userInput == 1)
                {
                    printf("Sword was swung\n\r");

                    if(!determine_omega_mode_active())
                    {
                        determine_packets_to_send(&pkt_arr);

                        for(i = 0; i < 3; ++i)
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
                else if(userInput == 'o')
                {
                    if(!determine_omega_mode_active())
                    {
                        omega_mode = 1;
                        printf("Omega mode enabled.\n\r");
                    }
                    else
                    {
                        omega_mode = 0;
                        printf("Omega mode disabled.\n\r");
                    }
                    break;
                }
                
                userInput = ' ';
            }
        }
        // -----Delta blade--------------------
        if( blade == 3 )
        {
            while( 1 )
            {
                userInput = determine_sword_was_swung();
                if(userInput == 1)
                {
                    printf("Sword was swung\n\r");

                    determine_packets_to_send(&pkt_arr);

                    for(i = 0; i < 3; ++i)
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
                if(userInput == 'd' && !determine_omega_mode_active())
                {
                    if(health > 0)
                    {
                        health -= 10;
                    }
                    printf("The blade has been damaged. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 'h' && !determine_omega_mode_active())
                {
                    if(health < 50)
                    {
                        health += 10;
                    }
                    printf("The blade has been healed. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 't' && !determine_omega_mode_active())
                {
                    stun_counter += 10;
                    printf("The blade has been stunned.\n\r");
                    
                    break;
                }
                else if(userInput == 'o')
                {
                    if(!determine_omega_mode_active())
                    {
                        omega_mode = 1;
                        printf("Omega mode enabled.\n\r");
                    }
                    else
                    {
                        omega_mode = 0;
                        printf("Omega mode disabled.\n\r");
                    }
                    break;
                }
                
                userInput = ' ';
            }

            GIE = 0;
            while(stun_counter > 0)
            {
                GIE = 1;
                __delay_ms(100);
                GIE = 0;
                --stun_counter;
            }
            GIE = 1;
        }
        // -----Gamma blade--------------------
        if( blade == 4 )
        {
            while( 1 )
            {
                userInput = determine_sword_was_swung();
                if(userInput == 1)
                {
                    printf("Sword was swung\n\r");

                    if(!determine_omega_mode_active())
                    {
                        determine_packets_to_send(&pkt_arr);

                        for(i = 0; i < 3; ++i)
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
                if(userInput == 'd' && !determine_omega_mode_active())
                {
                    if(health > 0)
                    {
                        health -= 10;
                    }
                    printf("The blade has been damaged. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 'h' && !determine_omega_mode_active())
                {
                    if(health < 50)
                    {
                        health += 10;
                    }
                    printf("The blade has been healed. Health = %d.\n\r",
                            health);
                    
                    break;
                }
                else if(userInput == 't' && !determine_omega_mode_active())
                {
                    stun_counter += 10;
                    printf("The blade has been stunned.\n\r");
                    
                    break;
                }
                else if(userInput == 'o')
                {
                    if(!determine_omega_mode_active())
                    {
                        omega_mode = 1;
                        printf("Omega mode enabled.\n\r");
                    }
                    else
                    {
                        omega_mode = 0;
                        printf("Omega mode disabled.\n\r");
                    }
                    break;
                }
                
                userInput = ' ';
            }

            GIE = 0;
            while(stun_counter > 0)
            {
                GIE = 1;
                __delay_ms(100);
                GIE = 0;
                --stun_counter;
            }
            GIE = 1;
        }
        
        
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
        
        printf("\n\r");
    }
}

// Single iteration of main loop for an individual blade
void main_loop_individual()
{   
#if _ALPHA_BLADE || _GAMMA_BLADE
    return;
#elif _BETA_BLADE
    return;
#elif _DELTA_BLADE
    return;
#endif
}

// Single iteration of main loop for the omega blade
void main_loop_omega()
{
#if _ALPHA_BLADE
    return;
#elif _BETA_BLADE
    return;
#elif _DELTA_BLADE
    return;
#elif _GAMMA_BLADE
    return;
#endif
}

// Initialize TRISX registers and set oscillator frequency
void init_pic()
{
    // Configure for 32MHz operation with internal oscillator
    OSCCON |= 0b11111000;
    
    // Set pin RB3 to output
    TRISB &= 0b11110111;
    
    // Enable interrupts
    GIE = 1;
}
