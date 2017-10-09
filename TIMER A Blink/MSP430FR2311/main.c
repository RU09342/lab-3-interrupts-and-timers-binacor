#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TB0CCTL2 = CCIE;                             // CCR2 interrupt enabled
    TB0CCTL1 = CCIE;
    TB0CTL = TBSSEL_2 + MC_2 + ID_3;           // SMCLK, contmode, clk/8
    TB0CCR2 =  40000;                           // 3.125 Hz -- 1Mhz/8/40000
    TB0CCR1 = 10000;                               //6.25 Hz

    P1DIR |= BIT0;       // P1.0 pin output
    P2DIR |= BIT0;         //P2.0 output


    __bis_SR_register(CPUOFF + GIE);  //clocks are needed so LPM0 with just CPUOFF is used
}

//Timer A interrupt routine
#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer_B (void)
{
    switch( TB0IV){
    case 2:
    {
        P2OUT ^= BIT0;                      // Toggle P2.0
        TB0CCR1 += 10000;                      //Inc CCR1 to trigger again
    }
    break;
    case 4:
        {
           P1OUT ^= BIT0;                          // Toggle P1.0, IFG gets cleared automatically
           TB0CCR2 += 40000;
        }
        break;
    case 10:
    {
    }
    break;
    }
}
