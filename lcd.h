/******************************************************************************
 * File Name   : lcd.h
 * Description : LCD driver function prototypes for LPC21xx
 ******************************************************************************/

#ifndef LCD_H
#define LCD_H

#include "types.h"            // Include custom data types (u8, s32, f32, etc.)

/* LCD Initialization */
void init_LCD(void);            // Initialize LCD in 8-bit mode

/* LCD Data/Command Functions */
void cmdLCD(u8 cmd);            // Send a command byte to LCD
void displayLCD(u8 data);       // Send a raw byte to LCD data lines
void charLCD(u8 data);          // Display a single character on LCD
void stringLCD(char *p);        // Display a null-terminated string on LCD
void integerLCD(s32 data);      // Display a signed integer on LCD
void floatLCD(f32 data);        // Display a floating-point number on LCD

/* Custom Characters */
void custCharDegree(void);      // Create custom degree (°) character in LCD CGRAM

#endif /* LCD_H */
