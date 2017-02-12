// All pin was defined here are pins of ESP8266 ver 7
// Note:
// the pin 4 and 5 in ESP ver 7 was exchanged in ESP ver 12
#ifndef CONFIG_H
#define CONFIG_H

// three types of return
#define RT_MISS -1
#define RT_SUSS 0
#define RT_FAIL 1

// extern char ssid[30];  // network name
// extern char password[30]; // password
// extern char host[30]; // ip of host.

// loge_level = 0 : show nothing
//              1 : show error
//              2 : show error and warning
//              3 : show error, warning and log
//              4 : show error, warning, log, verbose
extern char log_level;
extern bool log_serial;  // log via serial
extern bool log_network; // log via network

#define BAUD_RATE 115200

#define SCHEDULE_MEASURE_MAX 13        // max times of alarm per day. it use for alarm 1
#define SCHEDULE_LAMP_MAX 2            // max times of alarm per day. it use for alarm 2
#define BUFFER_SIZE 128

extern unsigned char schedule_measure[SCHEDULE_MEASURE_MAX];
extern unsigned char schedule_lamp[SCHEDULE_LAMP_MAX];

// map data in eeprom
#define TOTAL_OFFSET 0
#define DATA_OFFSET 2

// I2C pin

#define PIN_TEMPT_TANK 3  // pin connect to sensor to measure tempt of tempt tank. the pin 4 and 5 in ESP ver 7 was exchanged in ESP ver 12
#define PIN_ALARM 2     // pin connect to alarm pin (INTCN/SQW) of RTC. This pin actives low
// #define LATCH 5        // Pin connected to latch pin (ST_CP or RCLK (texas instrument)) of 74HC595
// #define CLK 4          // Pin connected to clock pin (SH_CP or SRCLK (texas instrument)) of 74HC595
// #define DATA 3          // Pin connected to Data in (DS or SER (texas instrument)) of 74HC595

const char relay[4] = {10,11,12,13};   // relay pin

#endif
