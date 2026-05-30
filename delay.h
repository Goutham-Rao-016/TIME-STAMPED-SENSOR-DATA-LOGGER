/******************************************************************************
 * File Name   : delay.h
 * Description : Function prototypes for delay routines
 ******************************************************************************/

#ifndef DELAY_H
#define DELAY_H

#include "types.h"            // Include custom data types (u8, u32, f32)

/* Delay Functions */
void delay_us(u32 us);        // Delay for specified microseconds
void delay_ms(u32 ms);        // Delay for specified milliseconds
void delay_s(u32 s);          // Delay for specified seconds

#endif /* DELAY_H */
