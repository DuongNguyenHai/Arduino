// Author : Nguyen Hai Duong
// Jan 5 2017

#ifndef REALTIME_H
#define REALTIME_H

#include <Time.h>
#include <RTClib.h>
#include "config.h"
#include "log.h"
// #include "../../src/main.h"

#define TIME_DIFF 30
#define GMT_VIETNAM 7
#define ALARM_DATA ALARM_1    // ALARM_1 was defined in another file
#define ALARM_LAMP ALARM_2    // ALARM_2 was defined in another file
#define TRACK_LAMP 1
#define TRACK_MEASURE 2

class SystemTime : public RTC {

public:
   SystemTime();
   ~SystemTime();

   int set(time_t t);               // set time to RTC
   int setDefault();                // set default time 00:00:00 jan 1 2017
   time_t getTime();                // check lost power and get time from RTC
   unsigned char getTimeHour();     // get hour of RTC time. Use for set schedule time
   void print();                    // get time and print it
   bool isAlarmOn();                // check alarm on ? by alarm pin (INTCN). When alarm 1/2 on, RTC will active low INTCN
   bool whichAlarmOn(unsigned char alarm);  // whats alarm is ringing ?
   bool initAlarm(unsigned char alarm);       // initial time for alarm
   bool setNextSchedule(unsigned char alarm); // set next time in schedule for alarm
   unsigned char trackCurrent(unsigned track);  // return the index of tracking
private:
   time_t get();                             // get time from RTC. return unix time
   time_t convertToDateTime(String str);     // convert time (string) to UNIX time
   void printDateTime(tmElements_t tm);      // print time & date
   void printDateTime(DateTime tm);          // print time & date
   unsigned char track_measure_;              // use for tracking time in measure schedule
   unsigned char track_lamp_;                 // use for tracking time in lamp measure
   unsigned char alarm_pin;
};

// Other functions can be used directly from RCT library

extern SystemTime Time;

#endif // REALTIME_H
