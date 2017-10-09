# TIMER A Blink
Russell Binaco:
Timer A Blink utilizes the Timer A (or B) modules to separately control the rate of two LEDs blinking on the boards.
All boards have successfully implemented Timer A Blink.

For this lab, continuous mode is used. This means the timer will count up to 65535 and then reset to zero.
CCR1 and CCR2 are used in compare mode. When the timer value reaches the values of CCR1 and CCR0, the Timer A interrupt vector sets flags in BIT1 and BIT2, respectively.
Timer0_A1_Vector is the ISR that handles the interrupts. By reading TAIV, the interrupt flags are cleared. 
The clock source is the 1Mhz SMCLK, which can be divided internally by up to 8, reduced to 125KHz. Divide this by the desired frequency to get the correct CCRX values, which have an upper limit of 65535.

### Extra Work
#### Low Power Timers
Low power modes disable certain components of the processor. The two most commonly used LMPs are 0 and 4. LPM4, however, disables the timers which are used for this lab. LPM0 only disables the CPU and is used in this lab to conserve power. This also halts the program counter, eliminating the need to have a while loop in the main function. 
All of the boards use LPM0 in this manner. 