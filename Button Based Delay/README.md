# Button Based Delay
Russell Binaco:
Button based delay allows the frequency of a button blinking to be set to the length of a button press. 
All of the boards have successfully implemented button based delay.

This code is implemented in continuous mode. The LED blinks at 10Hz. WHen the button is pressed, PXIES ^= BITX switches to detect the other edge of the button and the time in TA0R is saved. The same thing happens when the button is released, and the difference of these values is stored in CCR1 to change the frequency. 
The input clock is ACLK, divided internally by 8, which allows the timer to run for 16 seconds before overflowing. This means that, in 16 seconds from the button being pressed down or less, the timer will overflow at a maximum of one time. Logic is used to correct for this single overflow by checking if the release time is less than the start time, and calculations are changed accordingly.

### Extra Work
## Reset Button
The MSP430FR6989 uses a second button to set the frequency back to 10Hz. The PORT1 ISR checks which button interrupt was flagged in order to handle multiple interrupts in the ISR.

# Implementation Note
Between the boards, the main differences are the ports that are used for buttons and LEDs, and the FR-series requiring the extra line "PM5CTL0 &= ~LOCKLPM5;" since the default startup does not provide power to the ports.
The only other significant difference is that Timer_A does not exist in the FR2311, but Timer_B can be used using exactly the same code, replacing 'A' with 'B' for register names and bit names that use it, such as TBSSEL instead of TASSEL.