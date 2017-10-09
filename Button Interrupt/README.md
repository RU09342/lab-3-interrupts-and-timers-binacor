# Button Interrupt
Russell Binaco:
Button Interrupt utilizes interrupts to improve over the "polling" concept of a while loop. 
All boards have successfully implemented button interrupt.
Note: some boards use different ports for the button (i.e. P1.3 or P5.5). There is a different interrupt service routine (ISR) for each port, so the correct one must be implemented.

## Extra Work 
### Multiple Buttons
The MSP430FR6989 simply has two different buttons control two different LEDs.