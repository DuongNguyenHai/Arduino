// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
// #include <Time.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char tm[22];

void setup () {
   Serial.begin(115200);
   delay(1000); // wait for console opening

   if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
   }

   // time setting : year, month, day, hour, minute, second
   rtc.adjust(DateTime(2017, 02, 19, 18, 11, 55));

   // rtc.setAlarm(2, alarm_t tm, optional uint8_t mode)
   rtc.setAlarmRepeat(ALARM_1);
   rtc.setAlarmRepeat(ALARM_2);

}

void loop () {
   rtc.getDateTimeString(tm);
   Serial.print("Date time: ");
   Serial.println(tm);
   if(rtc.isAlarmRinging(ALARM_1)) {
      Serial.println("alarm 1 is ringing !");
      rtc.clearAlarm(ALARM_1);
   }
   if(rtc.isAlarmRinging(ALARM_2)) {
      Serial.println("alarm 2 is ringing !");
      rtc.clearAlarm(ALARM_2);
   }
   delay(1000);
}
