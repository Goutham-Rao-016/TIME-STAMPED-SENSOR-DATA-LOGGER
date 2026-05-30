/******************************************************************************
 * File Name   : uart.h
 * Description : Header file for UART communication functions.
 *               Provides function prototypes to initialize UART, send and
 *               receive data, and transmit formatted time, date, and numbers.
 ******************************************************************************/

#ifndef UART_H    // Check if UART_H is not defined
#define UART_H    // Define UART_H

#include "types.h"               // Include custom data type definitions (u8, u32, f32, etc.)

void init_Uart(void);           // Initialize UART peripheral
u8 uartRxChar(void);            // Receive a single character from UART
void uartTxChar(u8);            // Transmit a single character via UART
void uartTxStr(char *);         // Transmit a string via UART
void uartTxU32(u32);            // Transmit an unsigned 32-bit integer via UART
void uartTxF32(f32);            // Transmit a float (32-bit) value via UART
void uartTxRTCTime(void);       // Transmit current RTC time via UART
void uartTxRTCDate(void);       // Transmit current RTC date via UART

#endif  // UART_H  // End of include guard
