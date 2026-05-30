/******************************************************************************
 * File Name   : RTC.h
 * Description : RTC (Real Time Clock) driver function prototypes for LPC21xx
 ******************************************************************************/

#ifndef RTC_H
#define RTC_H

#include "types.h"        // Include custom data types (u8, u32, etc.)

/* RTC Initialization and Configuration */
void init_RTC(void);                     // Initialize the RTC peripheral

/* RTC Time Functions */
void set_RTC_Time(u8 hour, u8 min, u8 sec);           // Set RTC time (HH:MM:SS)
void get_RTC_Time(int *hour, int *min, int *sec);    // Get RTC time from registers

/* RTC Date Functions */
void set_RTC_Date(u8 dom, u8 month, u32 year);       // Set RTC date (DD/MM/YYYY)
void get_RTC_Date(int *dom, int *month, int *year);  // Get RTC date from registers

/* RTC Day Functions */
void set_RTC_Day(u8 day);                             // Set day of the week (0 = Sunday)
void get_RTC_Day(int *day);                           // Get day of the week from RTC

/* RTC Display Functions on LCD */
void display_RTC_Time_On_LCD(u8 hour, u8 min, u8 sec);  // Display time on LCD in HH:MM:SS format
void display_RTC_Date_On_LCD(u8 dom, u8 month, u32 year); // Display date on LCD in DD/MM/YYYY format
void display_RTC_Day_On_LCD(u8 day);                   // Display weekday on LCD

#endif /* RTC_H */
