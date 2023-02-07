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

    P2REN |= BIT3;               //Enable resistor on P2.3
    P2OUT |= BIT3;               //Configure resistor on P2.3 to be Pullup



    unsigned int totaltime=0;
    while(1)                                //Loops toggling of LEDs
    {
        if (((P4IN & BIT1)==0X002) & (totaltime<0x14))// If the left button is not pressed and total count is less than 10 seconds
              {
                  P1OUT &= ~BIT0;            // Turns off red led
                  P6OUT ^= BIT6;             // Makes the Green LED Blink
                  _delay_cycles(3000000);     // 3 secound delay
                  totaltime=0;                //resets timer to 0
              }




          if (((P4IN & BIT1)==0X00) & (totaltime<0x14)) // If the Left Button is pressed and timer is less then 10 secounds
          {

              P6OUT &= ~BIT6;          // Turns off green led
              P1OUT ^= BIT0;           // Makes the RED LED Blink
             _delay_cycles(500000);    // 5ms delay
             totaltime= totaltime+ 1;  // counts up the timer until it hits 10 seconds (20 cycles *5ms= 10sec)
          }


          if (totaltime==0X14)         // if timer = 10 secounds

           {
               P1OUT ^= BIT0;          // Makes the RED LED solid
           }

          if((((P2IN & BIT3)==0X00))) //If the right button is pressed
                    {
                       totaltime=0;   // resets the timer
                    }

        // if (!(P4IN & BIT1))        // If S1 (P4.1) is pressed (inverted)
        //{
          //  totaltime= totaltime+ 1;
            // if (totaltime==0X14)
           //{
             //P1OUT &= ~BIT0;
             //P1OUT |= BIT0; //add code to leave red led on
           //}
           //  else if (totaltime!= 0X14)
            // {
           //P1OUT ^= BIT0;
           //P6OUT &= ~BIT6;
            // }
       // __delay_cycles(500000);          //5ms delay to signify warning state

       // }
        //else {                              // if 4.1 is not pressed
        //P6OUT ^= BIT6;                      // Toggle P6.6 using exclusive-OR
        //P1OUT &= ~BIT0;
       // __delay_cycles(3000000);             // creates a 3s delay for armed status
       // totaltime=0;
        }
    }




