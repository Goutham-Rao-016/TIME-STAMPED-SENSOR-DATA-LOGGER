/******************************************************************************
 * File Name   : RTC_defines.h
 * Description : RTC register and clock configuration defines for LPC21xx
 ******************************************************************************/

#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H

/* Clock Definitions */
#define FOSC          12000000               // External oscillator frequency (Hz)
#define CCLK          (FOSC * 5)             // CPU Clock = 5 * FOSC
#define PCLK          (CCLK / 4)             // Peripheral Clock = CCLK / 4

/* RTC Prescaler Values */
#define PREINT_VAL    ((int)(PCLK / 32768) - 1)  // RTC prescaler integer part
#define PREFRAC_VAL   (PCLK - ((PREINT_VAL + 1) * 32768)) // RTC prescaler fractional part

/* RTC Control Register Bits */
#define RTC_ENABLE    (1 << 0)               // Enable RTC
#define RTC_RESET     (1 << 1)               // Reset RTC
#define CLK_SRC       (1 << 4)               // RTC clock source select

#endif /* RTC_DEFINES_H */
