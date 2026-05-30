/******************************************************************************
 * File Name   : main.h
 * Description : Function prototypes for main system control functions
 ******************************************************************************/

#ifndef MAIN_H
#define MAIN_H

void System_Init(void);           // Initialize all peripherals
void Display_Main_Screen(void);   // Display time, date, day, and temperature on LCD
void Monitor_Temperature(void);   // Monitor temperature and control buzzer

#endif /* MAIN_H */
