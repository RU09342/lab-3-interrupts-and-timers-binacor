#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // give power to channel
    P1DIR |= BIT0;                            // Set P1.0 to output direction
    P9DIR |= BIT7;                              //LED2


    P1IE |=  BIT1;                            // P1.1 interrupt enabled
    P1IES |= BIT1;                            // P1.1 falling edge trigger
    P1REN |= BIT1;                            // Enable resistor on SW1 (P1.1)
    P1OUT |= BIT1;                             //Pull up resistor on P1.1
    P1IFG &= ~BIT1;                           // P1.1 Interrupt Flag cleared
                                              //BIT1 on Port 1 can be used as Switch1

    P1IE |=  BIT2;                            // P1.2 interrupt enabled
    P1IES |= BIT2;                            // P1.2 falling edge trigger
    P1REN |= BIT2;                            // Enable resistor on SW2 (P1.2)
    P1OUT |= BIT2;                             //Pull up resistor on P1.2
    P1IFG &= ~BIT2;                           // P1.2 Interrupt Flag cleared
                                              //BIT1 on Port 1 can be used as Switch2

    __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
    //Low Power Mode 4 shuts off three clocks and the CPU, this would have to change
    //if a timer was used
  }

  // Port 1 interrupt service routine
  #pragma vector=PORT1_VECTOR
  __interrupt void Port_1(void)

  {
      if(P1IFG & BIT1){                         //S1
          P1OUT ^= BIT0;                            // P1.0 = toggle
          P1IFG &= ~BIT1;                           // P1.1 IFG cleared
      }
      if(P1IFG & BIT2){                         //S2
          P9OUT ^= BIT7;                            // P9.7 = toggle
          P1IFG &= ~BIT2;                           // P1.2 IFG cleared
      }
}
