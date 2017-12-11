/* 
 * File:   lcd.h
 * Author: mattb
 *
 * Created on December 10, 2017, 9:33 PM
 */

#ifndef LCD_H
#define	LCD_H

#include <xc.h>

// Set up  pin definitions for LCD signals.
#define RS_LAT LATDbits.LATD5
#define RW_LAT LATDbits.LATD6
#define EN_LAT LATDbits.LATD7

#define RS_PORT PORTDbits.RD5
#define RW_PORT PORTDbits.RD6
#define EN_PORT PORTDbits.RD7

#define DATA_LAT LATB
#define DATA_PORT PORTB

void LCDInit(void);
//void LCDSendChar(char *a);

// Used during initialisation;
void LCDCmd8Bit(unsigned char);
// Used once in 4 bit mode.
void LCDCmd(unsigned char);

void LCDChar(unsigned char *);


#endif	/* LCD_H */

