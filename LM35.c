/******************************************************************************
 * File Name   : LM35.c
 * Description : LM35 temperature sensor interface file
 *               Reads temperature using ADC and converts it
 *               into Celsius or Fahrenheit
 ******************************************************************************/

#include "types.h"           // User-defined data types (u8, u32, f32)
#include "adc.h"             // ADC function declarations
#include "adc_defines.h"     // ADC channel definitions

/******************************************************************************
 * Function Name : Read_LM35
 * Description   : Reads temperature from LM35 sensor
 * Arguments     : tType - 'C' for Celsius, 'F' for Fahrenheit
 * Return Value  : Temperature value as floating-point number
 ******************************************************************************/
f32 Read_LM35(u8 tType)
{
    u32 adcDVal;             // Variable to store raw ADC digital value
    f32 eAR, tdeg;           // eAR = equivalent analog reading (voltage)
                             // tdeg = calculated temperature value

    Read_ADC(CH1, &eAR, &adcDVal);
                             // Read ADC channel CH1
                             // eAR stores converted analog voltage
                             // adcDVal stores raw ADC data

    tdeg = eAR * 100;        // Convert voltage to temperature in Celsius
                             // LM35 gives 10mV per degree Celsius

    if (tType == 'C');       // If temperature type is Celsius
                             // Semicolon means no action is required
                             // Value is already in Celsius

    else if (tType == 'F')   // If temperature type is Fahrenheit
        tdeg = ((tdeg * (9 / 5.0)) + 32);
                             // Convert Celsius to Fahrenheit

    return tdeg;             // Return calculated temperature value
}
