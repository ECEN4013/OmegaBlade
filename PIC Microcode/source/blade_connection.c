#include "main_header.h"

void init_conn()
{
    // Configure RA1 (sword RX) as input
    TRISA |= 0b00000010;
}

char determine_omega_mode_active()
{
    return RA1;
}

void determine_packets_to_send(char* packets)
{
    if(determine_omega_mode_active())
    {
        
#if _ALPHA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 0;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 0;
#elif _BETA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 0;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 0;
#elif _DELTA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 22;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 15;
#elif _GAMMA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 0;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 0;
#endif
        
    }
    else
    {
        
#if _ALPHA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 2;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 0;
#elif _BETA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 0;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 10;
#elif _DELTA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 5;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 5;
#elif _GAMMA_BLADE
        packets[_PKT_TYPE_DAMAGE] = 15;
        packets[_PKT_TYPE_HEALTH] = 0;
        packets[_PKT_TYPE_STUN]   = 0;
#endif
        
    }
    
    return;
}

