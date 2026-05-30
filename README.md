# Time-Stamped Sensor Data Logger using LPC2148

## Objective

The objective of this project is to develop a real-time temperature monitoring and logging system using the LPC2148 microcontroller. The system records temperature readings along with accurate timestamps, provides over-temperature alerts, and allows users to modify RTC settings and temperature setpoints through a keypad-based interface.

## Overview

The **Time-Stamped Sensor Data Logger** is an embedded system designed using the **LPC2148 ARM7 Microcontroller** to continuously monitor temperature, maintain accurate real-time timestamps, and log sensor data for future analysis. The system utilizes the on-chip **Real-Time Clock (RTC)** for date and time management and an **LM35 temperature sensor** for environmental monitoring.

The project periodically records temperature readings along with date and time information and transmits the logged data to a serial terminal through UART communication. It also provides a user-friendly interface for editing RTC information and temperature setpoints using a keypad and LCD display.

---

## Features

### Real-Time Temperature Monitoring

* Reads temperature continuously using the LM35 sensor.
* Displays temperature on a 16x2 LCD.
* Updates temperature every second.

### RTC-Based Time Stamping

* Uses LPC2148's internal RTC module.
* Maintains current date, time, and day information.
* Associates each sensor reading with a timestamp.

### Periodic Data Logging

* Sends temperature data to Serial Terminal via UART.
* Logs data at predefined intervals (e.g., every 1 minute).

### Over-Temperature Detection

* User-configurable temperature setpoint.
* Generates alerts when temperature exceeds the configured threshold.
* Activates LED indication during fault conditions.

### RTC Editing Mode

* Allows modification of:

  * Hour
  * Minute
  * Second
  * Day
  * Month
  * Year
  * Weekday

### Setpoint Editing

* Allows user to update temperature threshold using keypad.

### User Interface

* 16x2 LCD display.
* Matrix keypad for navigation and data entry.
* Push button to enter editing mode.

---

## Hardware Requirements

| Component     | Description                  |
| ------------- | ---------------------------- |
| LPC2148       | ARM7TDMI-S Microcontroller   |
| LM35          | Analog Temperature Sensor    |
| 16x2 LCD      | Data Display                 |
| Matrix Keypad | User Input                   |
| Push Button   | Enter Edit Mode              |
| LED           | Fault Indication             |
| MAX232        | UART Communication Interface |

---

## Software Requirements

* Embedded C
* Keil uVision IDE
* Flash Magic
* Hyper Terminal 

---

## LCD Display Format

### Normal Mode

13:45:20  TUE
13/05/25 T:32°C

### Edit Menu

1.EDIT RTC INFO
2.E.SETPOINT 3.EXIT

### RTC Edit Menu

1.H 2.M 3.S 4.D
5.MON 6.Y 7.DAY 8.E

---

## UART Output Format

### Normal Operation

[INFO] Temp: 32.5°C @ 13:45:20 13/05/2025

### Over-Temperature Alert

[ALERT] Temp: 47.3°C @ 14:10:55 13/05/2025 - OVER TEMP!

### RTC Editing Mode

*** Time Editing Mode Activated ***

---

## Project Workflow

### System Initialization

Upon startup:

1. UART Initialization
2. RTC Initialization
3. ADC Initialization
4. LCD Initialization
5. Keypad Initialization
6. GPIO Initialization (LED & Switch)

---

### Normal Operation

The system continuously:

1. Reads temperature from LM35.
2. Retrieves current RTC information.
3. Displays temperature and time on LCD.
4. Sends timestamped data to UART.
5. Checks temperature threshold.
6. Activates LED if temperature exceeds setpoint.

---

### Edit Mode

When the push button is pressed:

1. Edit flag is enabled.
2. LCD displays menu options.
3. User selects:
   * RTC Information Edit
   * Temperature Setpoint Edit
   * Temperature Setpoint Display
   * Exit
4. New values are entered through keypad.
5. Values are validated.
6. RTC registers are updated.
7. System resumes normal operation.

---

## Temperature Conversion

The LM35 outputs:

10mV per °C

Example:

25°C = 250mV

For LPC2148 (10-bit ADC):

Temperature (°C) = ((ADC_Value * 3.3) / 1023) * 100

---

## Future Improvements

* EEPROM/SD Card based data storage
* Cloud-based logging (IoT)
* GSM alert notifications
* Humidity and smoke sensor integration
* Multiple sensor support
* Graphical data visualization

---

## Applications

* Industrial Temperature Monitoring
* Environmental Data Logging
* Laboratory Experiments
* Process Automation
* Equipment Health Monitoring
* Embedded Systems Learning

---

## Author

Goutham Rao

Embedded Systems | ARM7 | Embedded C 

---
