/******************************************************************************
 * File Name   : main_functions.c
 * Description : Application-level functions for the project
 *               Handles system initialization, LCD display,
 *               and temperature monitoring with alert logging
 ******************************************************************************/

#include <LPC21xx.h>          // LPC21xx microcontroller register definitions

/* Driver Header Files */
#include "lcd.h"              // LCD driver functions
#include "RTC.h"              // RTC driver functions
#include "adc.h"              // ADC driver functions
#include "adc_defines.h"      // ADC pins, channels, and control register definitions
#include "kpdAndSw_defines.h" // Keypad and switch pin definitions
#include "keypadAndSwitch.h"  // Keypad and switch interface functions
#include "uart.h"             // UART communication functions
#include "LM35.h"             // LM35 temperature sensor functions

#include "main.h"             // Application-level function declarations

/* Global Variables */
u8  epoint = 27;              // Temperature threshold value in degree Celsius
u32 prev   = 0;               // Stores previous time value to control logging rate
u32 curr   = 0;               // Stores current time value for comparison
u32 sprev = 0;
u32 scurr = 0;
/******************************************************************************
 * Function Name : System_Init
 * Description   : Initializes all peripherals used in the project
 ******************************************************************************/
void System_Init(void)
{
    init_LCD();               // Initialize LCD hardware and configure display
    init_RTC();               // Initialize Real Time Clock module
    init_ADC(AIN1_PIN_0_28);  // Initialize ADC and select LM35 input pin
    init_BUZZER();            // Configure buzzer GPIO pin as output
    init_Uart();              // Initialize UART for serial communication
    custCharDegree();         // Load custom degree (°) symbol into LCD CGRAM
}

/******************************************************************************
 * Function Name : Display_Main_Screen
 * Description   : Displays time, temperature, date, and day on LCD
 ******************************************************************************/
void Display_Main_Screen(void)
{
    int temperature;          // Local variable to store temperature value

    /* Display RTC Time */
    display_RTC_Time_On_LCD(HOUR, MIN, SEC);
                              // Fetch and display hour, minute, and second

    /* Display Temperature Label */
    cmdLCD(0x8A);              // Move LCD cursor to temperature display position
    charLCD('T');              // Display character 'T'
    charLCD(':');              // Display colon symbol

    temperature = (int)Read_LM35('C');
                              // Read temperature from LM35 sensor in Celsius

    if (temperature < 10)      // Check if temperature is a single digit
        charLCD('0');          // Display leading zero for proper formatting

    integerLCD(temperature);   // Display numeric temperature value on LCD

    cmdLCD(0x8E);              // Move LCD cursor to degree symbol position
    charLCD(0);                // Display custom degree symbol from CGRAM
    charLCD('C');              // Display character 'C' indicating Celsius

    /* Display Date */
    display_RTC_Date_On_LCD(DOM, MONTH, YEAR);
                              // Display day, month, and year from RTC

    /* Display Day */
    display_RTC_Day_On_LCD(DOW);
                              // Display current day of the week
}

/******************************************************************************
 * Function Name : Monitor_Temperature
 * Description   : Monitors temperature, controls buzzer,
 *                 and logs system status over UART with timestamp
 ******************************************************************************/
void Monitor_Temperature(void)
{
    u32 temp = Read_LM35('C'); // Read current temperature from LM35 sensor

    /* Check for over-temperature condition */
    if (temp > epoint)         // Compare temperature with threshold
    {
      IOSET0 = 1 << BUZZER;   // Turn ON buzzer for alert indication

			scurr = SEC;            // Use seconds value to limit alert frequency

        if (scurr != sprev)      // Check if this second was already logged
        {

            uartTxStr("[ALERT] Temp: "); // Send alert message over UART
            uartTxU32(temp);            // Send temperature value
            uartTxChar('C');            // Send temperature unit
            uartTxChar(' ');            // Send space character
            uartTxChar('@');            // Send separator symbol
            uartTxRTCTime();            // Send current RTC time
            uartTxRTCDate();            // Send current RTC date
            uartTxStr(" - OVER TEMP!\r\n");
                                          // Send alert message termination

            sprev = scurr;                // Update previous time marker
        }
    }
    else                       // Normal temperature condition
    {
        IOCLR0 = 1 << BUZZER;   // Turn OFF buzzer

        curr = MIN;            // Use minute value to limit info logging rate

        if (curr != prev)      // Check if this minute was already logged
        {
            uartTxStr("[INFO] Temp: "); // Send info message over UART
            uartTxU32(temp);            // Send temperature value
            uartTxChar('C');            // Send temperature unit
            uartTxChar(' ');            // Send space character
            uartTxChar('@');            // Send separator symbol
            uartTxRTCTime();            // Send current RTC time
            uartTxRTCDate();            // Send current RTC date
            uartTxStr("\r\n");          // End UART message

            prev = curr;                // Update previous time marker
        }
    }
}
