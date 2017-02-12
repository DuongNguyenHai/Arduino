#include "realtime.h"

#define DEFAULT_TIME 1483228800           // 00:00:00 jan 1 2017

SystemTime::SystemTime() {
   pinMode(PIN_ALARM, INPUT);
   track_measure_ = 0;
   track_lamp_ = 0;
}

SystemTime::~SystemTime() {}

int SystemTime::set(time_t t) {
   adjust(DateTime(t));
   time_t t2 = getTime();
   if(t2<=t+TIME_DIFF)
      return RT_SUSS;
   else
      return RT_FAIL;
}

int SystemTime::setDefault() {
   return set(DEFAULT_TIME);
}

time_t SystemTime::get() {
   return now().unixtime();
}

time_t SystemTime::getTime() {
   if(lostPower())
      return 0;
   time_t tnow = get();
   if(tnow==RCT_WRONG)
      Log.errors("RTC device read error !");

   return tnow;
}

unsigned char SystemTime::getTimeHour() {
   return DateTime(getTime()).hour();
}

void SystemTime::print() {
   time_t tnow = get();
   if (tnow!=RCT_WRONG)
      printDateTime(DateTime(tnow));
   else
      Log.errors("RTC device read error !");
}

time_t SystemTime::convertToDateTime(String str) {

   tmElements_t tm;
   String dw("SunMonTueWedThuFriSat");
   String mt("JanFebMarAprMayJunJulAugSepOctNovDec");

   String sub = str.substring(0,3); // day of week
   tm.Wday = dw.indexOf(sub.c_str())/3;

   sub = str.substring(5,7);        // day
   tm.Day = sub.toInt();

   sub = str.substring(8,11);       // month (short string)
   tm.Month = mt.indexOf(sub.c_str())/3;

   sub = str.substring(12,16);      // year
   tm.Year = CalendarYrToTm(sub.toInt());

   sub = str.substring(17,19);      // hour
   tm.Hour = sub.toInt();

   sub = str.substring(20,22);      // minute
   tm.Minute = sub.toInt();

   sub = str.substring(23,25);      // second
   tm.Second = sub.toInt();

   // printDateTime(tm);                           // print UTC time

   return makeTime(tm) + GMT_VIETNAM*3600 + 1;  // return GMT time, plus 1 to compensate elapsed calculation time

}

void SystemTime::printDateTime(tmElements_t tm) {
   Log.printfs("Time = %d:%d:%d, Date (D/M/Y) = %d/%d/%d", tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tmYearToCalendar(tm.Year));
}

void SystemTime::printDateTime(DateTime tm) {
   Log.printfs("Time = %d:%d:%d, Date (D/M/Y) = %d/%d/%d", tm.hour(), tm.minute(), tm.second(), tm.day(), tm.month(), tm.year());
}

bool SystemTime::isAlarmOn() {
   if(! digitalRead(PIN_ALARM))
      return true;
   else
      return false;
}

bool SystemTime::whichAlarmOn(unsigned char alarm) {
   if(! digitalRead(PIN_ALARM)) {
      if(isFlagSet(alarm)) {
         clearFlag(alarm);
         return true;
      }
      return false;
   }
   return false;
}

bool SystemTime::initAlarm(unsigned char alarm) {

   // set first time for alarm 1
   if(alarm==ALARM_1) {
      for (unsigned char i = 0; i < SCHEDULE_MEASURE_MAX; i++) {
         if(schedule_measure[i]!=0) {
            if(schedule_measure[i]>getTimeHour()) {
               track_measure_ = i;
               break;
            }
         }
      }
      Log.verboses("Set time for alarm %d: %uh", alarm, schedule_measure[track_measure_]);
      return setAlarmHour(alarm, schedule_measure[track_measure_]);

   }
   // set first time for alarm 2
   else {
      for (unsigned char i = 0; i < SCHEDULE_LAMP_MAX; i++) {
         if(schedule_lamp[i]!=0) {
            if(schedule_lamp[i]>getTimeHour()) {
               track_lamp_ = i;
               break;
            }
         }
      }
      Log.verboses("Set time for alarm %d: %uh", alarm, schedule_lamp[track_lamp_]);
      return setAlarmHour(alarm, schedule_lamp[track_lamp_]);
   }

}

bool SystemTime::setNextSchedule(unsigned char alarm) {

   // set next time for alarm 1
   if(alarm==ALARM_1) {
      track_measure_ = (track_measure_ + 1) % SCHEDULE_MEASURE_MAX;
      Log.verboses("Set next time for alarm %d: %uh", alarm, schedule_measure[track_measure_]);
      return setAlarmHour(alarm, schedule_measure[track_measure_]);
   }
   // set next time for alarm 2
   else {
      track_lamp_ = (track_lamp_ + 1) % SCHEDULE_LAMP_MAX;
      Log.verboses("Set next time for alarm %d: %uh", alarm, schedule_lamp[track_lamp_]);
      return setAlarmHour(alarm, schedule_lamp[track_lamp_]);
   }

}

unsigned char SystemTime::trackCurrent(unsigned int track) {
   if(track==TRACK_LAMP)
      return track_lamp_;
   else
      return track_measure_;

}

// Create a global Time
SystemTime Time;
