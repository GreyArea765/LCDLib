
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
    RS_LAT = 0;
    
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
    RS_LAT = 0;
    
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
 
#ifndef DEBUG
	__delay_us(200);
#endif
}

void LCDChar(unsigned char *chr)
{
    RS_LAT = 1;
    
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
 
#ifndef DEBUG
	__delay_us(200);
#endif
}