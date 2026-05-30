/******************************************************************************
 * File Name   : ADC.h
 * Description : ADC driver function prototypes
 ******************************************************************************/

#ifndef ADC_H
#define ADC_H

#include "types.h"                 // Include custom data types

void init_ADC(u32 chNo);           // Initialize the specified ADC channel
void Read_ADC(u32 chNo, f32 *eAR, u32 *adcDVal); // Read ADC and get digital & analog values

#endif /* ADC_H */
