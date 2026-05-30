/******************************************************************************
 * File Name   : defines.h
 * Description : Useful bit manipulation macros for LPC21xx
 ******************************************************************************/

#ifndef DEFINES_H
#define DEFINES_H

/* Bit Manipulation Macros */
#define SETBIT(WORD, BP)      ((WORD) |= (1 << (BP)))               // Set bit BP in WORD
#define CLRBIT(WORD, BP)      ((WORD) &= ~(1 << (BP)))              // Clear bit BP in WORD
#define CPLBIT(WORD, BP)      ((WORD) ^= (1 << (BP)))               // Toggle bit BP in WORD
#define WRITEBIT(WORD, BP, BIT) ((WORD) = ((WORD & ~(1 << (BP))) | ((BIT) << (BP)))) // Write BIT value to bit BP in WORD
#define WRITENIBBLE(WORD, SBP, NIBBLE) ((WORD) = ((WORD & ~(0xF << (SBP))) | ((NIBBLE) << (SBP)))) // Write 4-bit NIBBLE to WORD starting at SBP
#define WRITEBYTE(WORD, SBP, BYTE) ((WORD) = ((WORD & ~(0xFF << (SBP))) | ((BYTE) << (SBP)))) // Write 8-bit BYTE to WORD starting at SBP
#define WRITEHWORD(WORD, SBP, HWORD) ((WORD) = ((WORD & ~(0xFFFF << (SBP))) | ((HWORD) << (SBP)))) // Write 16-bit HWORD to WORD starting at SBP
#define READBIT(WORD, BP)     (((WORD >> (BP)) & 1) == 0)           // Read bit BP from WORD (returns 1 if bit is 0)

#endif /* DEFINES_H */
