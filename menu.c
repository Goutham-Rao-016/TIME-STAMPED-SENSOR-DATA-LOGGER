/******************************************************************************
 * File Name   : menu.c
 * Description : Menu handling for RTC settings and e-point adjustment
 *               - Time (HH:MM:SS)
 *               - Date (DD/MM/YYYY)
 *               - Day of Week
 *               - Temperature e-point
 ******************************************************************************/
 #include <LPC21xx.h>             // LPC21xx MCU register definitions
#include "types.h"                // Custom typedefs (u8, u32, etc.)
#include "lcd.h"                  // LCD driver function prototypes
#include "menu.h"                 // Menu function prototypes
#include "kpdAndSw_defines.h"     // Keypad, switch, buzzer pin definitions
#include "keypadAndSwitch.h"      // Keypad input and buzzer functions
#include "delay.h"                // Delay functions (us, ms, s)
#include "ADC_defines.h"          // ADC channel/pin definitions
#include "uart.h"                 // UART communication functions

u32 point;                        // Temporary storage for numeric input
extern u8  epoint;              // Temperature threshold value in degree Celsius
/****************************************************************************** 
 * Function Name: implementMenu
 * Description  : Main menu loop for time, date, day, and e-point
 ******************************************************************************/
void implementMenu() {
    u8 ch;                        // Variable to store pressed key
    while (1) {                    // Infinite loop for menu
        while (colStat());         // Wait until any key is pressed
        ch = keyVal();             // Get the key value
        switch (ch) {              // Check which menu option was pressed
            case 1:                // Option 1: Edit RTC Time
                setRtcTime();      // Call sub-menu for time setting
                displayMenu();     // Redisplay main menu after completion
                break;
            case 2:                // Option 2: Edit e-point
                setEPoint();       // Set temperature threshold
                displayMenu();     // Redisplay main menu
                break;
            case 3:                // Option 3: Display current e-point
                displayEPoint();  // Show e-point value on LCD
                displayMenu();     // Redisplay main menu
                break;
            case 4:                // Option 4: Exit menu
                return;            // Exit menu function
        }
    }
}

/****************************************************************************** 
 * Function Name: setRtcTime
 * Description  : Handles RTC sub-menu for setting time, date, and day
 ******************************************************************************/
void setRtcTime(void) {
    u8 ch = 0;                     // Variable to store submenu key
    displaySetRtcMenu();           // Display RTC editing options
    while (1) {                    // Infinite loop for RTC sub-menu
        while (colStat());         // Wait until key pressed
        ch = keyVal();             // Get key value
        switch (ch) {              // Check which sub-option was selected
            case 1: setHour(); displaySetRtcMenu(); break;     // Set hour
            case 2: setMinute(); displaySetRtcMenu(); break;   // Set minute
            case 3: setSecond(); displaySetRtcMenu(); break;   // Set second
            case 4: setDate(); displaySetRtcMenu(); break;     // Set date
            case 5: setMonth(); displaySetRtcMenu(); break;    // Set month
            case 6: setYear(); displaySetRtcMenu(); break;     // Set year
            case 7: setDay(); displaySetRtcMenu(); break;      // Set day of week
            case 8: return;                                    // Exit sub-menu
        }
    }
}

/****************************************************************************** 
 * Function Name: displaySetRtcMenu
 * Description  : Shows the RTC setting options on LCD
 ******************************************************************************/
void displaySetRtcMenu() {
    cmdLCD(0x01);                  // Clear LCD display
    cmdLCD(0x80);                  // Move cursor to first line
    stringLCD("1.H 2.M 3.S 4.D"); // Show options for time and date
    cmdLCD(0xC0);                  // Move cursor to second line
    stringLCD("5.M 6.Y 7.DY 8.E");// Show month, year, day, and exit options
}

/****************************************************************************** 
 * RTC Sub-functions: Set individual fields of time and date
 ******************************************************************************/
void setHour() {
    u32 ch;                        // Variable to store numeric input
    cmdLCD(0x01);                  // Clear LCD
    stringLCD("HOUR:");               // Prompt for hour
    while(!colStat());             // Wait until key pressed
    ch = readNum();                // Read numeric value from keypad
    if(ch > 23) {                  // Validate hour (0-23)
        cmdLCD(0x01); stringLCD("INVALID HOURS"); // Show error
        delay_ms(500);             // Delay to let user read error
        return;                    // Exit function
    }else
			HOUR = ch;                     // Update RTC hour
}

void setMinute() {
    u32 ch;
    cmdLCD(0x01); stringLCD("MINUTE:"); // Prompt for minutes
    while(!colStat());
    ch = readNum();                // Read numeric value
    if(ch > 59) {                  // Validate minute
        cmdLCD(0x01); stringLCD("INVALID MINUTES");
        delay_ms(500);
    }else
			MIN = ch;                      // Update RTC minute
}

void setSecond() {
    u32 ch;
    cmdLCD(0x01); stringLCD("SECOND:"); // Prompt for seconds
    while(!colStat());
    ch = readNum();
    if(ch > 59) {                  // Validate seconds
        cmdLCD(0x01); stringLCD("INVALID SECONDS");
        delay_ms(500);
    }else
			SEC = ch;                      // Update RTC second
}

void setDate() {
    u32 ch;
    cmdLCD(0x01); stringLCD("DATE:"); // Prompt for date
    while(!colStat());
    ch = readNum();                // Read date input
    
    // Validate date based on month and leap year
    if(MONTH % 2 && MONTH < 8) { if(ch > 31) goto invalidDate; }
    else if(MONTH == 2 && YEAR % 4 == 0) { if(ch > 29) goto invalidDate; }
    else if(MONTH == 2) { if(ch > 28) goto invalidDate; }
    else if(MONTH % 2 == 0 && MONTH < 8) { if(ch > 30) goto invalidDate; }
    else if(MONTH % 2 == 0 && MONTH >= 8) { if(ch > 31) goto invalidDate; }
    else { if(ch > 30) goto invalidDate; }

    if(ch != 0) DOM = ch;          // Update day of month if valid
    return;

invalidDate:                     // Label for invalid date
    cmdLCD(0x01); stringLCD("INVALID DATE"); // Show error
    delay_ms(500);                 // Delay for user to read
}

void setMonth() {
    u32 ch;
    cmdLCD(0x01); stringLCD("MONTH:"); // Prompt for month
    while(!colStat());
    ch = readNum();                // Read numeric input
    if(ch > 12) { cmdLCD(0x01); stringLCD("INVALID MONTH"); delay_ms(500); }
    else if(ch == 0) return;
		else MONTH = ch;   // Update month if valid
}

void setYear() {
    cmdLCD(0x01); stringLCD("YEAR:"); // Prompt for year
    while(!colStat());
    if((point = readNum()) != 0 && point < 10000) YEAR = point; // Update year
}

void setDay() {
    u32 ch;
    cmdLCD(0x01); stringLCD("DAY:"); // Prompt for day of week
    while(!colStat());
    ch = readNum();                // Read numeric input
    if(ch > 6) { cmdLCD(0x01); stringLCD("INVALID DAY"); delay_ms(500); }
    else DOW = ch;                 // Update day of week (0=Sunday)
}

/****************************************************************************** 
 * Temperature e-point functions
 ******************************************************************************/
void setEPoint() {
		//u32 epoint = 27;
    cmdLCD(0x01); stringLCD("E.POINT:"); // Prompt for e-point
    while(!colStat());
    point = readNum();                     // Read numeric input
    if(point < 156 && point != 0) epoint = point; // Update e-point if valid
    else { cmdLCD(0x01); stringLCD("INVALID E.POINT"); delay_ms(500); }
}

void displayEPoint() {
    cmdLCD(0x01); stringLCD("E.POINT:");  // Show e-point label
    integerLCD(epoint);                    // Display value
    delay_s(1);                            // Wait 1 second to show value
}
