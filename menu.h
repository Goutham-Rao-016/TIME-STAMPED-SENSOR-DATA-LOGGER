/******************************************************************************
 * File Name   : menu.h
 * Description : Header file for menu-related functions in the project.
 *               Provides function prototypes to handle RTC settings,
 *               temperature threshold, and menu display on LCD.
 ******************************************************************************/

void implementMenu(void);        // Main menu loop to select options
void setRtcTime(void);           // Sub-menu to set RTC time, date, and day
void setEPoint(void);            // Set the temperature e-point (threshold)
void displaySetRtcMenu(void);    // Display RTC setting options on LCD
void setHour(void);              // Set RTC hour
void setMinute(void);            // Set RTC minute
void setSecond(void);            // Set RTC second
void setDate(void);              // Set RTC date (day of month)
void setMonth(void);             // Set RTC month
void setYear(void);              // Set RTC year
void setDay(void);               // Set RTC day of the week
void checkTemp(void);            // Monitor temperature and take action (e.g., buzzer)
void displayEPoint(void);        // Display the current e-point value on LCD
