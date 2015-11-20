#include "main_header.h"

void play_sound(char sound_selection)
{
    if( sound_selection == _SOUND_TYPE_INDIVIDUAL )
    {
        RB3 = 0;
        __delay_ms(150);
        RB3 = 1;
    }
    else if( sound_selection == _SOUND_TYPE_OMEGA )
    {
        RB2 = 0;
        __delay_ms(150);
        RB2 = 1;
    }
}
