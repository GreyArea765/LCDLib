# LIBLcd

My attempt at getting the PIC16F18877 to initialize a Hitachi compatible
1602A 16 character, 2 line LCD display.

o Make sure your XTAL_FREQ is #defined somewhere and #include lcd.h
o Call LCDInit()
o Call LCDChar() to write a single characters.
o Call LCDSendString() to write a string.

## To-do:

o Add function to wait for BUSY flag to be cleared.
