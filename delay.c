/******************************************************************************
 * File Name   : delay.c
 * Description : Delay routines for microsecond, millisecond, and second delays
 ******************************************************************************/

#include "delay.h"            // Include delay function prototypes
#include "types.h"            // Include custom data types (u32, etc.)

/******************************************************************************
 * Function Name : delay_us
 * Description   : Generates a delay in microseconds
 * Arguments     : tdly - number of microseconds to delay
 ******************************************************************************/
void delay_us(u32 tdly)
{
    tdly *= 12;               // Scale delay according to CPU clock (~1 us per loop iteration)
    while(tdly--);            // Busy-wait loop
}

/******************************************************************************
 * Function Name : delay_ms
 * Description   : Generates a delay in milliseconds
 * Arguments     : tdly - number of milliseconds to delay
 ******************************************************************************/
void delay_ms(u32 tdly)
{
    tdly *= 12000;            // Scale delay for milliseconds (~12,000 iterations per ms)
    while(tdly--);            // Busy-wait loop
}

/******************************************************************************
 * Function Name : delay_s
 * Description   : Generates a delay in seconds
 * Arguments     : tdly - number of seconds to delay
 ******************************************************************************/
void delay_s(u32 tdly)
{
    tdly *= 12000000;         // Scale delay for seconds (~12,000,000 iterations per second)
    while(tdly--);            // Busy-wait loop
}
