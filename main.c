/******************************************************************************
 * File Name   : main.c
 * Description : Main application file
 *               - LCD display
 *               - RTC date & time
 *               - Temperature monitoring (LM35)
 *               - UART communication
 *               - Menu handling (Keypad + Switch)
 ******************************************************************************/

#include <LPC21xx.h>          // LPC21xx microcontroller register definitions

/* Driver Headers */
#include "lcd.h"              // LCD driver functions
#include "RTC.h"              // RTC driver functions
#include "keypadAndSwitch.h"  // Keypad and switch interface
#include "kpdAndSw_defines.h" // Keypad and switch pin definitions
#include "menu.h"             // Menu handling functions
#include "uart.h"             // UART communication functions

#include "main.h"             // Application-level declarations

/******************************************************************************
 * Function Name : main
 * Description   : Entry point of the application
 ******************************************************************************/
int main(void)
{
    System_Init();             // Initialize all system peripherals
    /* Set default RTC values */
    set_RTC_Time(23, 48, 00);   // Set time: HH:MM:SS
    set_RTC_Date(28, 12, 2025); // Set date: DD:MM:YYYY
    set_RTC_Day(0);             // Set day of week (0 = Sunday)
    while (1)                  // Infinite loop
    {
        Display_Main_Screen(); // Display time, date and temperature
        /* Check menu switch press (active low) */
				if (((IOPIN0 >> SW) & 1) == 0)
        {
            while (((IOPIN0 >> SW) & 1) == 0); // Wait for switch release
            uartTxStr("*** Time Editing Mode Activated *** \r\n");//Send Message over Uart
            displayMenu();     // Show menu on LCD
            init_keyPad();     // Initialize keypad
            implementMenu();   // Handle menu operations
            cmdLCD(0x01);      // Clear LCD after exiting menu
        }
        Monitor_Temperature(); // Monitor temperature & trigger alert if needed
    }
}
