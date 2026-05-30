/******************************************************************************
 * File Name   : ADC_defines.h
 * Description : ADC hardware constants, pin and channel definitions
 ******************************************************************************/

#ifndef ADC_DEFINES_H
#define ADC_DEFINES_H

/* Clock Configuration */
#define FOSC            12000000UL   // Oscillator frequency
#define CCLK            (FOSC*5)     // CPU Clock
#define PCLK            (CCLK/4)     // Peripheral Clock
#define ADCLK           3750000UL    // ADC operating clock
#define CLKDIV          ((PCLK/ADCLK)-1) // ADC clock divider

/* ADC Control Register Bits */
#define CLK_DIV_BITS    8            // ADC clock divider bits (8-15)
#define PDN_BIT         21           // Power-down control bit
#define START_BIT       24           // Start conversion bit(s)

/* ADC Data Register Bits */
#define DIGITAL_DATA_BITS   6        // Digital data bits for ADC (6-15)
#define DONE_BIT            31       // Conversion done flag bit

/* ADC Pin Selection */
#define AIN0_PIN_0_27   0x00400000   // Pin P0.27 as AD0.0
#define AIN1_PIN_0_28   0x01400000   // Pin P0.28 as AD0.1
#define AIN2_PIN_0_29   0x05400000   // Pin P0.29 as AD0.2
#define AIN3_PIN_0_30   0x15400000   // Pin P0.30 as AD0.3

/* ADC Channel Numbers */
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

#endif /* ADC_DEFINES_H */
