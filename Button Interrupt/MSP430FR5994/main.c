#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // give power to channel
    P1DIR |= BIT0;                            // Set P1.0 to output direction
    P5IE |=  BIT5;                            // P5.5 interrupt enabled
    P5IES |= BIT5;                            // P5.5 falling edge trigger
    P5REN |= BIT5;                            // Enable resistor on SW2 (P5.5)
    P5OUT |= BIT5;                             //Pull up resistor on P5.5
    P5IFG &= ~BIT5;                           // P5.5 Interrupt Flag cleared
                                              //BIT5 on Port 1 can be used as Switch2

    __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
    //Low Power Mode 4 shuts off three clocks and the CPU, this would have to change
    //if a timer was used
  }

  // Port 1 interrupt service routine
  #pragma vector=PORT5_VECTOR
  __interrupt void Port_5(void)

  {
    P1OUT ^= BIT0;                            // P1.0 = toggle
    P5IFG &= ~BIT5;                           // P5.5 IFG cleared
}
