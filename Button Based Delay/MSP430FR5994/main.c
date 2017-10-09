#include <msp430.h> 

unsigned long hz;
int reset = 0;
unsigned int start = 0;
unsigned int end =0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // give power to channel

    TA0CCTL0 |= CCIE;                              //enable interrupt
    TA0CCTL0 &= ~TAIFG;                            //clear flag
    TA0CTL = TASSEL_1 + MC_2 + ID_3;           // ACLK, contmode, clk/8
    TA0CCR0 = 205;                               //20 Hz (10Hz for LED) (visually correct, ACLK seems to be too slow)
    hz = 205;                                    //increment value for CCR0


    P5IE |=  BIT5;                            // P5.5 interrupt enabled
    P5IES |= BIT5;                            //falling edge
    P5REN |= BIT5;                            // Enable resistor on SW2 (P5.5)
    P5OUT |= BIT5;                             //Pull up resistor on P5.5
    P5IFG &= ~BIT5;                           // P5.5 Interrupt Flag cleared

    P1DIR |= BIT0;       // P1.0 pin output

    __bis_SR_register(GIE);  //not low power mode
    while(1){
        if(reset)
        {
            reset = 0;
            if(end <= start){                       //account for overflow (will work for button press up to 16 seconds)
                TA0CCR0 = 65535-start+end+TA0R;     //account for current timer value to start immediately
                hz=65535-start+end;                 //update increment value
            }else{
                TA0CCR0=end-start+TA0R;
                hz=end-start;
            }
        }

    }
}


//Timer A interrupt routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
        P1OUT ^= BIT0;
        TA0CCR0 += hz;                          //increment CCR0
}



#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)

{

    if(P5IES & BIT5){
    start = TA0R;                       //time button was pressed
    }else{
        end = TA0R;                     //time button was released
        reset = 1;                      //flag to recalculate CCR1
    }

    P5IES ^= BIT5;  //flip edge
    P5IFG &= ~BIT5;  //clear flag

}
