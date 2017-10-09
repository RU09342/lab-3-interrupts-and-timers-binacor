#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // give power to channel
    P1DIR |= BIT0;                  // configure P1.0 as output
    P1REN |= BIT1;                  //give P1.1 a resistor
    P1OUT |= BIT1;                  //give P1.1 a pull up resistor
    P1IE |=  BIT1;                            // P1.1 interrupt enabled
    P1IES |= BIT1;                            // P1.1 falling edge trigger
    P1IFG &= ~BIT1;                           // P1.1 Interrupt Flag cleared

    __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= BIT0;                            // P1.0 = toggle
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared
}

