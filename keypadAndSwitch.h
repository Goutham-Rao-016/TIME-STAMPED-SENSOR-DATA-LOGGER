/******************************************************************************
 * File Name   : keypadAndSwitch.h
 * Description : Keypad and switch driver function prototypes for LPC21xx
 ******************************************************************************/

#ifndef KEYPADANDSWTICH_H
#define KEYPADANDSWTICH_H

#include "types.h"        // Include custom data types (u8, u32, etc.)

/* Menu Functions */
void displayMenu(void);    // Display main menu on LCD

/* Keypad Initialization */
void init_keyPad(void);    // Initialize keypad row pins as output and clear them

/* Keypad Status Functions */
u8 colStat(void);          // Returns 1 if no key pressed, 0 if any key is pressed
u8 keyVal(void);           // Returns the value of the key currently pressed

/* Keypad Input Functions */
u32 readNum(void);         // Reads multi-digit numeric input from keypad until '=' is pressed

/* Buzzer Functions */
void init_BUZZER(void);    // Initialize buzzer pin as output

#endif /* KEYPADANDSWTICH_H */
