/******************************************************************************
 * File Name   : kpdAndSw_defines.h
 * Description : Pin definitions for keypad, switch, and buzzer on LPC21xx
 ******************************************************************************/

#ifndef KPDANDSW_DEFINES_H
#define KPDANDSW_DEFINES_H

#include "types.h"      // Include custom data types (u8, u32, etc.)

/* Switch Pin */
#define SW      4        // Input pin connected to external switch (active low)

/* Buzzer Pin */
#define BUZZER  23       // Output pin connected to buzzer

/* Keypad Row Pins */
#define R0      16       // Row 0 of keypad
#define R1      17       // Row 1 of keypad
#define R2      18       // Row 2 of keypad
#define R3      19       // Row 3 of keypad

/* Keypad Column Pins */
#define C0      20       // Column 0 of keypad
#define C1      21       // Column 1 of keypad
#define C2      22       // Column 2 of keypad
#define C3      23       // Column 3 of keypad

#endif /* KPDANDSW_DEFINES_H */
