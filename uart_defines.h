/******************************************************************************
 * File Name   : uart_defines.h
 * Description : UART register bit definitions for LPC21xx microcontroller
 *               - DLAB and word length bits in U0LCR
 *               - Data Ready and TX Empty bits in U0LSR
 ******************************************************************************/
#define DLAB        7   // Divisor Latch Access Bit position in U0LCR register
#define WORDLENGTH  0   // Word length select bits start position in U0LCR register

#define DATA_READY  0   // Data Ready bit position in U0LSR register (RX data available)
#define TX_EMPTY    6   // Transmit Holding Register Empty bit position in U0LSR register
