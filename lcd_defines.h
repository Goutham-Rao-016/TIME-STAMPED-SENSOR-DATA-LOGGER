/******************************************************************************
 * File Name   : lcd_defines.h
 * Description : LCD pin definitions and data port for LPC21xx
 ******************************************************************************/

#ifndef LCD_DEFINES_H
#define LCD_DEFINES_H

#define LCD_DAT  (0xFF << 8)   // LCD data pins (P0.8 to P0.15)
#define RS       5             // Register Select pin number
#define RW       7             // Read/Write pin number
#define EN       6             // Enable pin number

#endif /* LCD_DEFINES_H */
