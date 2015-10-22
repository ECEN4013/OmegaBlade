/*====================================================================================
File:   main_header.h
Author: bjesper

Created on October 12, 2015
====================================================================================*/
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include "stdio.h"
#include "xc.h"
#include "uart_header.h"

#define F_OSC 32000000
#define _XTAL_FREQ 32000000

// Uncomment the appropriate line for the blade you wish to compile the program for
#define _ALPHA_BLADE 1
#define _BETA_BLADE 0
#define _DELTA_BLADE 0
#define _GAMMA_BLADE 0

// Define values of IR packet types
#define _PKT_TYPE_DAMAGE 0
#define _PKT_TYPE_HEALTH 1
#define _PKT_TYPE_STUN   2

// Define values of blade lighting modes
#define _LIGHT_MODE_INDIVIDUAL_SWING 0
#define _LIGHT_MODE_OMEGA_SWING      1
#define _LIGHT_MODE_CONNECT          2

// Global variables
extern char stun_counter;
extern char health;
extern char omega_mode;
extern char blade; // A=1, B=2, D=3, G=4

/*------------------------------------------------------------------------------------
Name: init_pic
Inputs: void
Return: void
Purpose: Initialize TRISX registers to set up basic I/O directions and set up
         oscillator frequency.
Developer: Ben Jespersen
------------------------------------------------------------------------------------*/
void init_pic();

/*------------------------------------------------------------------------------------
Name: init_ir
Inputs: void
Return: void
Purpose: Initialize any registers, peripherals, etc. needed by the IR communication
         functions.
Developer: Brandon Hogue
------------------------------------------------------------------------------------*/
void init_ir();

/*------------------------------------------------------------------------------------
Name: output_ir
Inputs: pkt_type - determines whether to send damage or stun packets
        amount - determines amount of damage or stun to send
Return: void
Purpose: This function is responsible for sending IR signals to other MAGE devices.
         The main function passes the type of signal and amount to send, and the
         function returns after completing its transmission. This will frequently
         require multiple packets to be sent within this function. Note that the IR
         input interrupt may trigger while this function is running; therefore the
         function should periodically check the sword's health or stun status and
         stop transmission if necessary.
         If possible, it would be preferable to use this function to set up one or
         more timer or CCP interrupts rather than waiting while IR is sent. This is
         because, when the sword is swung, we would like to be able to play sounds
         and flash lights at the same time as the IR packets are being sent. This
         may not be critical, however, if the packets are sent fast enough. We'll
         have to experiment with it some.
Developer: Brandon Hogue
------------------------------------------------------------------------------------*/
void output_ir(char pkt_type, char amount);

/*------------------------------------------------------------------------------------
Name: play_sound
Inputs: sound_selection - indicates which sound the function should play
Return: void
Purpose: This function should play a selected sound based on the input variable.
Developer: Brandon Hogue
------------------------------------------------------------------------------------*/
void play_sound(char sound_selection);

/*------------------------------------------------------------------------------------
Name: init_accel
Inputs: void
Return: void
Purpose: Initialize any registers, peripherals, etc. needed for the accelerometer
         functions.
Developer: Derrian Glynn
------------------------------------------------------------------------------------*/
void init_accel();

/*------------------------------------------------------------------------------------
Name: determine_sword_was_swung
Inputs: buffer - circular buffer in the form of a char array, containing data from
                 accelerometer reads
Return: This function should return an appropriate value indicating a weak swing,
        medium swing, heavy swing, or no swing.
Purpose: This function is responsible for reading the accelerometer once, updating
         the buffer with the new reading, and determining whether the sword has
         just been swung. If the sword has been swung, the function must determine
         what type of swing it was.
Developer: Derrian Glynn
------------------------------------------------------------------------------------*/
char determine_sword_was_swung();

/*------------------------------------------------------------------------------------
Name: determine_omega_mode_active
Inputs: void
Return: This function should return 1 if omega mode is active or 0 if it is not.
Purpose: This function is responsible for checking the inter-blade connection inputs
         to determine if the sword is in omega mode. The function may not behave
         exactly the same on every sword, but every sword must implement it in some
         way. The function should simply output 1 if omega mode is active and 0 if it
         is not.
Developer: Derrian Glynn
------------------------------------------------------------------------------------*/
char determine_omega_mode_active();

/*------------------------------------------------------------------------------------
Name: determine_packet_to_send
Inputs: pointer to array of 3 char variables corresponding to health, damage, and
        stun
Return: void
Purpose: This function should edit the input array to contain the number of health,
         damage, and stun packets that should be sent. This may include setting one
         or more of the array elements to zero if no packets of that type should be
         sent. No value will be returned because the original array will be directly
         edited through the pointer.
Developer: Derrian Glynn
------------------------------------------------------------------------------------*/
void determine_packets_to_send(char* packets);

/*------------------------------------------------------------------------------------
Name: display_health
Inputs: void
Return: void
Purpose: This function updates the PWM outputs to the RGB health LED. This includes
         calculating the correct values for the PWM registers based on the global
         health variable.
Developer: Austin Allen
------------------------------------------------------------------------------------*/
void display_health();

/*------------------------------------------------------------------------------------
Name: init_leds
Inputs: void
Return: void
Purpose: Initialize any registers, peripherals, etc. needed for the blade LEDs and
         health LEDs functions.
Developer: Austin Allen
------------------------------------------------------------------------------------*/
void init_leds();

/*------------------------------------------------------------------------------------
Name: display_blade_lights
Inputs: mode - determines which lighting mode to use
Return: void
Purpose: This function displays a particular lighting mode on the sword's blade
         LEDs. Different modes may have different colors, flashing patterns, etc.
         This will involve SPI communication to the RGB LED strip on the blade.
Developer: Austin Allen
------------------------------------------------------------------------------------*/
void display_blade_lights(char mode);

/*------------------------------------------------------------------------------------
Name: init_isr
Inputs: void
Return: void
Purpose: Initialize any registers, peripherals, etc. needed for the ISR.
Developer: Christian Coffield
------------------------------------------------------------------------------------*/
void init_isr();

/*------------------------------------------------------------------------------------
Name: isr (to be changed once the correct name for the compiler is known)
Inputs: void
Return: void
Purpose: This function will be responsible for interrupting the main program when an
         IR packet is received. It will then process the IR packet and alter the
         health or stun time counter as necessary. It cannot receive input from or
         send output to the main program, so it will need to interact with one or
         more shared variables in the main program.
Developer: Christian Coffield
------------------------------------------------------------------------------------*/
void isr();

