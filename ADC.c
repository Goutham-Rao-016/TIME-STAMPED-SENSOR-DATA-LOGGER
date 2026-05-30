/******************************************************************************
 * File Name   : adc.c
 * Description : ADC driver functions for LPC21xx
 *               - Initialize ADC channel
 *               - Read ADC value and convert to voltage
 ******************************************************************************/

#include <LPC21xx.h>       // LPC21xx microcontroller register definitions
#include "ADC.h"           // ADC function declarations
#include "types.h"         // Custom data types (u8, u32, f32)
#include "delay.h"         // Delay functions for timing
#include "ADC_defines.h"   // ADC channel/pin definitions and constants

/******************************************************************************
 * Function Name : init_ADC
 * Description   : Initializes the specified ADC channel
 * Arguments     : chNo - ADC channel number/pin bitmask
 ******************************************************************************/
void init_ADC(u32 chNo)
{
    PINSEL1 &= ~(chNo);        // Clear the pin function bits for selected channel
    PINSEL1 |= (chNo);         // Set pin function bits to enable ADC mode

    /* Configure ADC Control Register:
       - Set PDN_BIT to power up ADC
       - Set CLKDIV to divide PCLK and set ADC clock
    */
    ADCR |= (1 << PDN_BIT) | (CLKDIV << CLK_DIV_BITS);
}

/******************************************************************************
 * Function Name : Read_ADC
 * Description   : Reads ADC value from the specified channel
 *                 Converts it into analog voltage
 * Arguments     : 
 *    chNo     - ADC channel number
 *    eAR      - Pointer to store equivalent analog voltage (float)
 *    adcDVal  - Pointer to store raw ADC digital value (0-1023)
 ******************************************************************************/
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal)
{
    ADCR &= 0xFFFFFF00;              // Clear old channel selection and start bits

    /* Start ADC conversion:
       - Set START_BIT to start conversion
       - Enable selected channel by setting bit corresponding to chNo
    */
    ADCR |= (1 << START_BIT) | (1 << chNo);

    delay_us(3);                      // Short delay for ADC acquisition time

    /* Wait until conversion is done:
       - Check DONE_BIT in ADC data register
    */
    while (((ADDR >> DONE_BIT) & 1) == 0);

    ADCR &= ~(1 << START_BIT);        // Clear START_BIT to stop conversion

    /* Extract 10-bit digital value from ADC result register */
    *adcDVal = ((ADDR >> DIGITAL_DATA_BITS) & 1023);

    /* Convert digital value to voltage:
       ADC voltage = ADC_value * (Vref / 1023)
       Assuming Vref = 3.3V
    */
    *eAR = *adcDVal * (3.3 / 1023);
}
