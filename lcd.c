
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "lcd.h"

/*
 Order of operations for LCDInit()
 https://www.8051projects.net/lcd-interfacing/initialization.php
  
    Wait for abour 20mS
    Send the first init value (shifted right 4 bits)
    Wait for about 10mS
    Send second init value (shifted right 4 bits)
    Wait for about 1mS
    Send third init value (shifted right 4 bits)
    Wait for 1mS
    Select bus width (0x30 - for 8-bit and 0x20 for 4-bit)
    Wait for 1mS
 */
void LCDInit(void)
{
     // Wait for about 20mS
#ifndef DEBUG
    __delay_ms(1000);
#endif
       
    // Send the first init value (0x03.
    LCDCmd8Bit(0x03);
    
    // Wait for about 10ms
#ifndef DEBUG
    __delay_ms(10);
#endif
    
    // Send second init value
    LCDCmd8Bit(0x03);
    
    // Wait for about 1ms
#ifndef DEBUG
    __delay_ms(1);
#endif
    
    // Send third init value (0x30 shifted right 4 bits)
    LCDCmd8Bit(0x03);
    
    // Wait for about 1ms
#ifndef DEBUG
    __delay_ms(1);
#endif
    
    // Select bus width (0x30 - for 8-bit and 0x20 for 4-bit)
    LCDCmd8Bit(0x02);
    
    // Wait for about 1ms
#ifndef DEBUG
    __delay_ms(1);
#endif
    
    // We are now in 4-b9t mode.
    
    LCDCmd(0x28);       // 4-bit mode - 2 line - 5x7 font. 
    
    LCDCmd(0x0C);       // Display no cursor - no blink.
    
    LCDCmd(0x06);       // Automatic Increment - No Display shift.
    
    LCDCmd(0x80);       // Address DDRAM with 0 offset 80h.
    
}

void LCDCmd8Bit(unsigned char cmd)
{
    RW_LAT = 0;                         // 0 is Write.
    RS_LAT = 0;                         // 0 Select instruction register
    
    // Push data to the latch.
    DATA_LAT = cmd;
  
    // Clock in the data.
    // Bring EN high.
    EN_LAT = 1;
#ifndef DEBUG
    // Wait
    //__delay_us(1);
    __delay_ms(1);
#endif
    // Bring EN low.
    EN_LAT = 0;
    
}

void LCDCmd (unsigned char cmd)
{ 
    RW_LAT = 0;                         // 0 is Write.
    RS_LAT = 0;                         // 0 Select instruction register
    
    // Set upper nibble.
	DATA_LAT = ((cmd >> 4) & 0x0F);
    EN_LAT = 1;
#ifndef DEBUG
    // Wait
    __delay_us(5);
#endif
    EN_LAT = 0;
 
    // Send lower nibble.
	DATA_LAT = (cmd & 0x0F);
    EN_LAT = 1;
#ifndef DEBUG
    // Wait
    __delay_us(5);
#endif
    EN_LAT = 0;
 
// Waiting for a while to ensure busy flag clears.
#ifndef DEBUG
	__delay_ms(5);
#endif
}

void LCDChar(unsigned char *chr)
{
    RW_LAT = 0;                         // 0 is Write.
    RS_LAT = 1;                         // 0 Select data register.
    
    // Set upper nibble.
	DATA_LAT = ((*chr >> 4) & 0x0F);
    EN_LAT = 1;
#ifndef DEBUG
    // Wait
    __delay_us(5);
#endif
    EN_LAT = 0;
 
    // Send lower nibble.
	DATA_LAT = (*chr & 0x0F);
    EN_LAT = 1;
#ifndef DEBUG
    // Wait
    __delay_us(5);
#endif
    EN_LAT = 0;

    // Waiting for a while to ensure busy flag clears.
#ifndef DEBUG
	__delay_ms(5);
#endif
}

// Expects a null terminated string.
void LCDSendString(char *str)
{
    while (*str != '\0')
    {
        LCDChar(str);
        str++;
    }
}

void LCDClear(void)
{
    LCDCmd(0x01);
}

// Set the cursor at X,Y coordinates.
void LCDGotoXY(unsigned int x, unsigned int y)
{
    if(x>=20) return;
    
    // In a 2-line display mode the DDRAM address for line 1 is:
    // 0x00 - 0x27 and for line two it's 0x40 - 0x67
    switch(y)
    {
            case 0:
                break;
            case 1:
                x+=0x40;      // The second line starts at address => 0x40
    }
    
    // The command for set DDRAM address is 0b10000000 so OR it with data.
    x|=0b10000000;
    LCDCmd(x);
}

void LCDHome(void)
{
    LCDCmd(0x02);
}

// LCDScrollLeft uses the display shift function described here:
//
// DB4 DB3 DB2 DB1 DB0
//  1  S/C R/L  -   -
//
// S/C R/L Description
//  L  L   Shift cursor to the left
//  L  H   Shift cursor to the right/
//  H  L   Shift display to the left, cursor follows the display shift.
//  H  H   Shift display to the right, cursor follows the display shift.
//
void LCDScrollLeft(void)
{
    // 0b11000 = 0x18
    LCDCmd(0x18);
}

// See description for LCDScrollLeft
void LCDScrollRight(void)
{
    // 0b1110 = 0x1C
    LCDCmd(0x1C);
}