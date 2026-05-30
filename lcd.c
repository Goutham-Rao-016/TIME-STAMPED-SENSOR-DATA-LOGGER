/******************************************************************************
 * File Name   : lcd.c
 * Description : LCD driver functions for LPC21xx
 *               Provides initialization, command, character, string, integer,
 *               float display, and custom character routines.
 ******************************************************************************/

#include <LPC21xx.h>        // LPC21xx microcontroller register definitions
#include "delay.h"          // Delay routines (us, ms, s)
#include "lcd.h"            // LCD function prototypes
#include "defines.h"        // Project-wide defines
#include "lcd_defines.h"    // LCD-specific defines (data pins, control pins)
#include "types.h"          // Custom data types (u8, u32, f32, etc.)

/******************************************************************************
 * Function Name : init_LCD
 * Description   : Initialize LCD in 8-bit mode with default configuration
 ******************************************************************************/
void init_LCD() {
    IODIR0 |= ((LCD_DAT) | (1 << RS) | (1 << EN) | (1 << RW)); // Set LCD data and control pins as output
    delay_ms(20);                    // Wait for LCD to power up

    cmdLCD(0x30);                    // Function set: 8-bit mode
    delay_ms(10);                    

    cmdLCD(0x30);                    // Function set again (as per datasheet)
    delay_ms(1);

    cmdLCD(0x30);                    // Function set third time
    delay_ms(1);

    cmdLCD(0x38);                    // Function set: 2 lines, 5x8 font
    cmdLCD(0x010);                   // Set cursor
    cmdLCD(0x001);                   // Clear display
    cmdLCD(0x06);                    // Entry mode: increment cursor
    cmdLCD(0x0C);                    // Display ON, cursor OFF
}

/******************************************************************************
 * Function Name : displayLCD
 * Description   : Send a byte to LCD data lines
 ******************************************************************************/
void displayLCD(u8 data) {
    IOCLR0 = 1 << RW;                // Select write mode
    WRITEBYTE(IOPIN0, 8, data);      // Write data to LCD data pins
    IOSET0 = 1 << EN;                 // Enable pulse
    delay_ms(1);                      // Small delay
    IOCLR0 = 1 << EN;                 // Clear enable
    delay_ms(5);                      // Wait for LCD to process data
}

/******************************************************************************
 * Function Name : cmdLCD
 * Description   : Send command byte to LCD
 ******************************************************************************/
void cmdLCD(u8 cmd) {
    IOCLR0 = 1 << RS;                // Select command register
    displayLCD(cmd);                 // Send command
}

/******************************************************************************
 * Function Name : charLCD
 * Description   : Display a single character on LCD
 ******************************************************************************/
void charLCD(u8 data) {
    IOSET0 = 1 << RS;                // Select data register
    displayLCD(data);                // Send character
}

/******************************************************************************
 * Function Name : stringLCD
 * Description   : Display a null-terminated string on LCD
 ******************************************************************************/
void stringLCD(char *p) {
    while (*p)                        // Loop until null character
        charLCD(*p++);                // Display each character
}

/******************************************************************************
 * Function Name : integerLCD
 * Description   : Display a signed integer on LCD
 ******************************************************************************/
void integerLCD(s32 data) {
    u8 a[30];                         // Array to store digits
    s32 i = 0;

    if (data == 0) {                  // Handle zero
        charLCD('0');
        return;
    }

    if (data < 0) {                   // Handle negative numbers
        charLCD('-');
        data = -data;
    }

    while (data) {                     // Convert integer to character array
        a[i++] = data % 10 + 48;       // Get each digit and convert to ASCII
        data /= 10;
    }

    for (i = i - 1; i >= 0; i--)      // Display digits in correct order
        charLCD(a[i]);
}

/******************************************************************************
 * Function Name : floatLCD
 * Description   : Display a floating-point number on LCD
 ******************************************************************************/
void floatLCD(f32 f) {
    u32 num1 = f, num2, n = 0;        // Separate integer and fractional parts
    f = f - num1;

    while (n++ < 6)                    // Scale fractional part
        f *= 10;

    num2 = f;                          // Fractional part as integer
    integerLCD(num1);                  // Display integer part
    charLCD('.');                      // Display decimal point
    integerLCD(num2);                  // Display fractional part
}

/******************************************************************************
 * Function Name : custCharDegree
 * Description   : Create custom degree (°) character in LCD CGRAM
 ******************************************************************************/
void custCharDegree(void) {
    u8 i, LUT[] = {0x0E, 0x11, 0x11, 0x0E, 0x00, 0x00, 0x00, 0x00}; // Custom degree pattern
    cmdLCD(0x40);                     // Set CGRAM address
    for (i = 0; i < 8; i++)
        charLCD(LUT[i]);              // Write each byte to CGRAM
}
