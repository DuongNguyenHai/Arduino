// set up date time and print on terminal
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// time setting : seconds/minutes/hours/day of week/day/month/(year-1970)

char tm[22];

void setup () {
   Serial.begin(115200);
   delay(1000); // wait for console opening

   if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
   }

   if (rtc.lostPower()) {     // check RTC time has set or not.
      Serial.println("RTC lost power, lets set the time!");
      // following line sets the RTC to the date & time.
      //  adjust(DateTime(year,month,day,hour,minute,second))
      rtc.adjust(DateTime(2017, 01, 1, 00, 00, 00));
   }
}

void loop () {
   rtc.getDateTimeString(tm);
   Serial.print("Date time: ");
   Serial.println(tm);
   delay(1000);
}
