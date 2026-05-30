/******************************************************************************
 * File Name   : keypad.c
 * Description : Keypad and buzzer driver functions for LPC21xx
 ******************************************************************************/

#include <LPC21xx.h>            // LPC21xx microcontroller register definitions
#include "lcd.h"                // LCD driver functions
#include "lcd_defines.h"        // LCD pin definitions
#include "keypadAndSwitch.h"    // Keypad and switch function prototypes
#include "kpdAndSw_defines.h"   // Keypad and switch pin definitions
#include "types.h"              // Custom data types (u8, u32, etc.)
#include "delay.h"              // Delay functions

/* Keypad Lookup Table: maps rows and columns to key values */
u8 LUT1[4][3] = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
    {'C', 0, '='}
};

/******************************************************************************
 * Function Name : displayMenu
 * Description   : Displays the main menu on LCD
 ******************************************************************************/
void displayMenu() {
    cmdLCD(0x01);                    // Clear LCD
    cmdLCD(0x80);                    // Set cursor to first line
    stringLCD("1.E.R.I  3.E.VAL");   // Display first line menu options
    cmdLCD(0xC0);                    // Set cursor to second line
    stringLCD("2.E.SET   4.EXIT");   // Display second line menu options
}

/******************************************************************************
 * Function Name : init_keyPad
 * Description   : Initialize keypad row pins as output and clear them
 ******************************************************************************/
void init_keyPad() {
    IODIR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3)); // Set row pins as output
    IOCLR1 = (1 << R0) | (1 << R1) | (1 << R2) | (1 << R3);   // Clear all row outputs
}

/******************************************************************************
 * Function Name : colStat
 * Description   : Returns 1 if no key pressed, 0 if any key is pressed
 ******************************************************************************/
u8 colStat() {
    if (((IOPIN1 >> C0) & 0x0F) == 0x0F)  // Read column pins
        return 1;                         // No key pressed
    else
        return 0;                         // Key pressed
}

/******************************************************************************
 * Function Name : keyVal
 * Description   : Returns the key value pressed on the keypad
 ******************************************************************************/
u8 keyVal(void) {
    u8 row_val = 0, col_val = 0;

    /* Check each row by setting one row low at a time */
    IOCLR1 = (1 << R0);                  // Clear R0
    IOSET1 = ((1 << R1) | (1 << R2) | (1 << R3)); // Set other rows high
    if ((((IOPIN1 >> 20) & 0x0F) != 0x0F)) {
        row_val = 0;                     // Key pressed in row 0
        goto colcheck;
    }

    IOCLR1 = (1 << R1);                  // Clear R1
    IOSET1 = ((1 << R0) | (1 << R2) | (1 << R3)); // Set other rows high
    if ((((IOPIN1 >> 20) & 0x0F) != 0x0F)) {
        row_val = 1;                     // Key pressed in row 1
        goto colcheck;
    }

    IOCLR1 = (1 << R2);                  // Clear R2
    IOSET1 = ((1 << R0) | (1 << R1) | (1 << R3)); // Set other rows high
    if ((((IOPIN1 >> 20) & 0x0F) != 0x0F)) {
        row_val = 2;                     // Key pressed in row 2
        goto colcheck;
    }

    IOCLR1 = (1 << R3);                  // Clear R3
    IOSET1 = ((1 << R0) | (1 << R1) | (1 << R2)); // Set other rows high
    if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
        row_val = 3;                     // Key pressed in row 3

colcheck:
    /* Check columns to determine exact key */
    if (((IOPIN1 >> C0) & 1) == 0)
        col_val = 0;
    else if (((IOPIN1 >> C1) & 1) == 0)
        col_val = 1;
    else if (((IOPIN1 >> C2) & 1) == 0)
        col_val = 2;
    else
        col_val = 3;

    IOCLR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3)); // Clear all rows
    return LUT1[row_val][col_val];       // Return corresponding key value
}

/******************************************************************************
 * Function Name : readNum
 * Description   : Reads a multi-digit number input from keypad until '=' is pressed
 ******************************************************************************/
u32 readNum() {
    u32 ch = 0, key;
    while (1) {
        while (colStat());                // Wait for key press
        key = keyVal();                   // Get key value
        while (!colStat());               // Wait for key release

        if (key == '=')                   // '=' indicates end of input
            break;
        else if (key == 'C') {            // Clear last digit
            if (ch > 0) {
                ch /= 10;                 // Remove last digit
                cmdLCD(0x10);             // Move cursor left
                charLCD(' ');             // Erase character on LCD
                cmdLCD(0x10);             // Move cursor left again
            }
        } else {                           // For numeric key press
            integerLCD(key);               // Display digit on LCD
            ch = (ch * 10) + key;         // Append digit
            delay_ms(10);                  // Small debounce delay
        }
    }
    return ch;                             // Return final number
}

/******************************************************************************
 * Function Name : init_BUZZER
 * Description   : Initialize buzzer pin as output
 ******************************************************************************/
void init_BUZZER() {
    IODIR0 |= 1 << BUZZER;                 // Set buzzer pin as output
}
