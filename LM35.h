/******************************************************************************
 * File Name   : LM35.h
 * Description : LM35 temperature sensor interface
 ******************************************************************************/

#ifndef LM35_H
#define LM35_H

#include "types.h"                 // Include custom data types

f32 Read_LM35(u8 tType);          // Read temperature in 'C' or 'F'

#endif /* LM35_H */
