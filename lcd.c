
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "lcd.h"

/*
 Order of operations for LCDInit()
 https://www.8051projects.net/lcd-interfacing/initialization.php
  
    Wait for abour 20mS
    Send the first init value (0x30 shifted right 4 bits)
    Wait for about 10mS
    Send second init value (0x30 bshifted right 4 bits)
    Wait for about 1mS
    Send third init value (0x30 shifted right 4 bits)
    Wait for 1mS
    Select bus width (0x30 - for 8-bit and 0x20 for 4-bit)
    Wait for 1mS
 */
void LCDInit(void)
{
     // Wait for about 20mS
#ifndef DEBUG
    __delay_ms(20);
#endif
       
    // Send the first init value (0x03.
    LCDCmd8Bit(0x03);
    
    // Wait for about 10ms
#ifndef DEBUG
    __delay_ms(10);
#endif
    
    // Send second init value (0x30 shifted right 4 bits)
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
    
    //	lcd_cmd(0x80);       // Address DDRAM with 0 offset 80h.
    
}

void LCDCmd8Bit(unsigned char cmd)
{
    RS_LAT = 0;
    
    // Push data to the latch.
    DATA_LAT = cmd;
    
    // Bring EN high.
    EN_LAT = 1;
    // Clock in the data.
#ifndef DEBUG
    __delay_us(5);
#endif
    // Bring EN low.
    EN_LAT = 0;
    
}

void LCDCmd (unsigned char cmd)
{ 
    RS_LAT = 0;
    
	DATA_LAT = ((cmd >> 4) & 0x0F)|EN_PORT;
	DATA_LAT = ((cmd >> 4) & 0x0F);
 
	DATA_LAT = (cmd & 0x0F)|EN_PORT;
	DATA_LAT = (cmd & 0x0F);
 
#ifndef DEBUG
	__delay_us(200);
	__delay_us(200);
#endif
}

void LCDChar(unsigned char *chr)
{
    RS_LAT = 1;
    
	DATA_LAT = ((*chr >> 4) & 0x0F)|EN_PORT;
	DATA_LAT = ((*chr >> 4) & 0x0F);
 
	DATA_LAT = (*chr & 0x0F)|EN_PORT;
	DATA_LAT = (*chr & 0x0F);
 
#ifndef DEBUG
	__delay_us(200);
	__delay_us(200);
#endif
}