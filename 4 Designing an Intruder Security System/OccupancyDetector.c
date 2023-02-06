/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: David Myers
 */
#include <msp430.h>

int main(void)
{


    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    P6OUT &= ~BIT6;                         // Clear P6.6 output latch for a defined power-on state
    P6DIR |= BIT6;                          // Set P6.6 to output direction
    PM5CTL0 &= ~LOCKLPM5;

    P4REN |= BIT1;               // Enable Resistor on P4.1
    P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup

    P6OUT^=BIT6;                            // Toggle P6.6 using exclusive-OR


    while(1)                                //Loops toggling of LEDs
    {
        if (!(P4IN & BIT1))         // If S1 (P4.1) is pressed
        {
           P1OUT ^= BIT0;          // Toggle P1.0
           P6OUT &= ~BIT6;
           __delay_cycles(500000);          //5ms delay to signify warning state
        }
        else {
        P6OUT ^= BIT6;                      // Toggle P6.6 using exclusive-OR
        P1OUT &= ~BIT0;
        __delay_cycles(3000000);             // creates a 3s delay for armed status
        }
    }
}



