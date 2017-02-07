// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
#include <Time.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// time setting : seconds/minutes/hours/day of week/day/month/(year-1970)
tmElements_t tm_set = {55,59,16,4,5,1,2017-1970};
#define INT_ALARM 5     // active low

void setup () {

   pinMode(INT_ALARM, INPUT);
   Serial.begin(115200);

   delay(3000); // wait for console opening

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
   }

   if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(makeTime(tm_set)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   }

   // rtc.setAlarm(1, DateTime(2017,1,1,17,01,10), 3);
   // rtc.setAlarm(2, DateTime(2017,1,1,17,01,10), 3);
   rtc.setAlarmHour(DS3231_ALARM_1, 17);
   rtc.setAlarmHour(DS3231_ALARM_2, 17);
   Serial.print("Read register control: "); Serial.println(rtc.readRegControl(), HEX);
   Serial.printf("Register[0x7]: 0x%x\n", rtc.readRegister(0x7));
   Serial.printf("Register[0x8]: 0x%x\n", rtc.readRegister(0x8));
   Serial.printf("Register[0x9]: 0x%x\n", rtc.readRegister(0x9));
   Serial.printf("Register[0xA]: 0x%x\n", rtc.readRegister(0xA));

   Serial.printf("Register[0xB]: 0x%x\n", rtc.readRegister(0xB));
   Serial.printf("Register[0xC]: 0x%x\n", rtc.readRegister(0xC));
   Serial.printf("Register[0xD]: 0x%x\n", rtc.readRegister(0xD));

}

void loop () {

   DateTime now = rtc.now();
   PrintDateTime(now);

   Serial.printf("status[0xF]: 0x%x\n", rtc.readRegStatus());

   if(rtc.isFlagSet(DS3231_ALARM_1)) {
      if(digitalRead(INT_ALARM))
         Serial.println("INT_ALARM is high");
      else
         Serial.println("INT_ALARM is low");
      Serial.println("Flag is set. Clear flag !");
      // rtc.clearFlag(DS3231_ALARM_1);
      rtc.setAlarmHour(DS3231_ALARM_1, 18);
      if(digitalRead(INT_ALARM))
         Serial.println("INT_ALARM is high");
      else
         Serial.println("INT_ALARM is low");
   }

   if(rtc.isFlagSet(DS3231_ALARM_2)) {
      if(digitalRead(INT_ALARM))
         Serial.println("INT_ALARM is high");
      else
         Serial.println("INT_ALARM is low");
      Serial.println("Flag is set. Clear flag !");
      // rtc.clearFlag(DS3231_ALARM_2);
      rtc.setAlarmHour(DS3231_ALARM_2, 18);
      if(digitalRead(INT_ALARM))
         Serial.println("INT_ALARM is high");
      else
         Serial.println("INT_ALARM is low");
   }
   delay(1000);

}

void PrintDateTime(DateTime tm) {
   Serial.printf("Time = %d:%d:%d, Date (D/M/Y) = %d/%d/%d \n", tm.hour(), tm.minute(), tm.second(), tm.day(), tm.month(), tm.year());
}
