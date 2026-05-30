/******************************************************************************
 * File Name   : uart.c
 * Description : UART driver implementation for LPC21xx microcontroller.
 *               Provides functions for UART initialization, transmitting and
 *               receiving characters, strings, numbers, floats, and RTC data.
 ******************************************************************************/

#include <LPC21xx.h>       // LPC21xx MCU hardware register definitions
#include "defines.h"       // Bit manipulation macros (SETBIT, CLRBIT, etc.)
#include "uart_defines.h"  // UART specific register and pin definitions
#include "types.h"         // Custom data types (u8, u32, f32, etc.)

/******************************************************************************
 * Function Name : init_Uart
 * Description   : Initializes UART0 peripheral for 9600 baud, 8-bit word length
 ******************************************************************************/
void init_Uart() {
    PINSEL0 = 0x00000001;        // Configure P0.0 as TXD0 (UART transmit)
    PINSEL0 = 0x00000005;        // Configure P0.1 as RXD0 (UART receive)
    
    U0LCR |= 3 << WORDLENGTH;    // Set word length to 8 bits
    U0LCR |= 1 << DLAB;          // Enable Divisor Latch Access Bit to set baud rate
    U0DLL = 97;                  // Set lower byte of baud rate divisor
    U0DLM = 0;                    // Set upper byte of baud rate divisor
    U0LCR &= ~(1 << DLAB);       // Disable DLAB after setting baud rate
}

/******************************************************************************
 * Function Name : uartRxChar
 * Description   : Receives a single character from UART
 ******************************************************************************/
u8 uartRxChar() {
    while (!READBIT(U0LSR, DATA_READY)); // Wait until UART has received data
    return (U0RBR);                      // Return the received character from RBR
}

/******************************************************************************
 * Function Name : uartTxChar
 * Description   : Transmits a single character via UART
 ******************************************************************************/
void uartTxChar(u8 ch) {
    U0THR = ch;                           // Load the character into Transmit Holding Register
    while (READBIT(U0LSR, TX_EMPTY));     // Wait until the transmit register is empty
}

/******************************************************************************
 * Function Name : uartTxStr
 * Description   : Transmits a null-terminated string via UART
 ******************************************************************************/
void uartTxStr(char *p) {
    while (*p)                            // Loop through each character until null terminator
        uartTxChar(*p++);                 // Transmit the character
}

/******************************************************************************
 * Function Name : uartTxU32
 * Description   : Transmits an unsigned 32-bit integer as ASCII characters
 ******************************************************************************/
void uartTxU32(u32 num) {
    u8 a[10];                             // Array to store individual digits
    s8 i = 0;                              // Index for digit array

    if (num == 0) {                        // Check for zero
        uartTxChar('0');                   // Send '0' as ASCII
    } else {
        while (num > 0) {                  // Extract digits from number
            a[i++] = num % 10 + 48;       // Convert digit to ASCII and store
            num /= 10;                     // Reduce number
        }
        for (--i; i >= 0; i--)            // Send digits in correct order
            uartTxChar(a[i]);             // Transmit each digit
    }
}

/******************************************************************************
 * Function Name : uartTxF32
 * Description   : Transmits a floating-point number with 6 decimal places
 ******************************************************************************/
void uartTxF32(f32 fnum) {
    u32 num, i;                             // Variables for integer and fractional parts

    if (fnum < 0) {                         // Check if number is negative
        uartTxChar('-');                     // Transmit negative sign
        fnum = -fnum;                        // Make number positive
    }

    num = fnum;                             // Extract integer part
    fnum = fnum - num;                       // Get fractional part
    uartTxU32(num);                          // Transmit integer part
    uartTxChar('.');                         // Transmit decimal point

    for (i = 0; i < 6; i++)                 // Scale fractional part for 6 decimal digits
        fnum *= 10;

    num = fnum;                              // Convert fractional part to integer
    uartTxU32(num);                          // Transmit fractional part
}

/******************************************************************************
 * Function Name : uartTxRTCTime
 * Description   : Transmits current RTC time in HH:MM:SS format
 ******************************************************************************/
void uartTxRTCTime() {
    uartTxChar(' ');                         // Transmit space before time

    if (HOUR < 10) {                         // Add leading zero if hour < 10
        uartTxChar('0');
        uartTxU32(HOUR);                     // Transmit hour
    } else
        uartTxU32(HOUR);

    uartTxChar(':');                          // Transmit colon separator

    if (MIN < 10) {                           // Add leading zero if minute < 10
        uartTxChar('0');
        uartTxU32(MIN);                       // Transmit minute
    } else
        uartTxU32(MIN);

    uartTxChar(':');                          // Transmit colon separator

    if (SEC < 10) {                           // Add leading zero if second < 10
        uartTxChar('0');
        uartTxU32(SEC);                       // Transmit second
    } else
        uartTxU32(SEC);

    uartTxChar(' ');                          // Transmit space after time
}

/******************************************************************************
 * Function Name : uartTxRTCDate
 * Description   : Transmits current RTC date in DD/MM/YYYY format
 ******************************************************************************/
void uartTxRTCDate() {
    uartTxChar(' ');                          // Space before date
    uartTxU32(DOM);                           // Transmit day
    uartTxChar('/');                           // Separator
    uartTxU32(MONTH);                          // Transmit month
    uartTxChar('/');                           // Separator
    uartTxU32(YEAR);                           // Transmit year
    uartTxChar(' ');                           // Space after date
}
