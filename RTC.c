/******************************************************************************
 * File Name   : RTC.c
 * Description : Real Time Clock (RTC) driver functions for LPC21xx
 *               Provides initialization, time/date setting, and LCD display
 ******************************************************************************/

#include <LPC21xx.h>        // LPC21xx microcontroller register definitions
#include "RTC_defines.h"    // RTC register addresses and constants
#include "types.h"          // Custom data types (u8, u32)
#include "lcd.h"            // LCD driver functions

/* Weekday lookup table for display on LCD */
char week[][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

/******************************************************************************
 * Function Name : init_RTC
 * Description   : Initialize RTC peripheral
 ******************************************************************************/
void init_RTC() {
    CCR = RTC_RESET;                      // Reset RTC

#ifdef LPC2148
    CCR = RTC_ENABLE | RTC_CLKSRC;        // Enable RTC with clock source for LPC2148
#else
    PREINT = PREINT_VAL;                  // Set RTC prescaler integer part
    PREFRAC = PREFRAC_VAL;                // Set RTC prescaler fractional part
    CCR = RTC_ENABLE;                     // Enable RTC
#endif
}

/******************************************************************************
 * Function Name : set_RTC_Time
 * Description   : Set RTC time (hour, minute, second)
 ******************************************************************************/
void set_RTC_Time(u8 hour, u8 min, u8 sec) {
    HOUR = hour;                           // Set hour
    MIN = min;                             // Set minute
    SEC = sec;                             // Set second
}

/******************************************************************************
 * Function Name : set_RTC_Date
 * Description   : Set RTC date (day, month, year)
 ******************************************************************************/
void set_RTC_Date(u8 dom, u8 month, u32 year) {
    DOM = dom;                             // Set day of month
    MONTH = month;                         // Set month
    YEAR = year;                           // Set year
}

/******************************************************************************
 * Function Name : set_RTC_Day
 * Description   : Set day of the week (0 = Sunday)
 ******************************************************************************/
void set_RTC_Day(u8 day) {
    DOW = day;                             // Set day of week
}

/******************************************************************************
 * Function Name : display_RTC_Time_On_LCD
 * Description   : Display time on LCD in HH:MM:SS format
 ******************************************************************************/
void display_RTC_Time_On_LCD(u8 hour, u8 min, u8 sec) {
    cmdLCD(0x80);                          // Set LCD cursor to first line

    charLCD((hour / 10) + 48);             // Display tens digit of hour
    charLCD((hour % 10) + 48);             // Display units digit of hour
    charLCD(':');                           // Display separator

    charLCD((min / 10) + 48);              // Display tens digit of minutes
    charLCD((min % 10) + 48);              // Display units digit of minutes
    charLCD(':');                           // Display separator

    charLCD((sec / 10) + 48);              // Display tens digit of seconds
    charLCD((sec % 10) + 48);              // Display units digit of seconds
}

/******************************************************************************
 * Function Name : display_RTC_Date_On_LCD
 * Description   : Display date on LCD in DD/MM/YYYY format
 ******************************************************************************/
void display_RTC_Date_On_LCD(u8 dom, u8 month, u32 year) {
    cmdLCD(0xC0);                          // Set LCD cursor to second line

    charLCD((dom / 10) + 48);              // Display tens digit of day
    charLCD((dom % 10) + 48);              // Display units digit of day
    charLCD('/');                           // Display separator

    charLCD((month / 10) + 48);            // Display tens digit of month
    charLCD((month % 10) + 48);            // Display units digit of month
    charLCD('/');                           // Display separator

    integerLCD(year);                       // Display full year
}

/******************************************************************************
 * Function Name : display_RTC_Day_On_LCD
 * Description   : Display day of the week on LCD
 ******************************************************************************/
void display_RTC_Day_On_LCD(u32 day) {
    cmdLCD(0xCC);                           // Set LCD cursor to specific position
    stringLCD(week[day]);                   // Display weekday string
}
