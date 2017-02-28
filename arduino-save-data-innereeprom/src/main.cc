#include <Arduino.h>
#include "log.h"
#include "config.h"
#include "realtime.h"
#include "BH1750.h"
#include <EEPROM.h>

#define ON 1
#define OFF 0
#define TOTAL_OFFSET_EP EEPROM.length() - 2
#define INDEX_OFFSET_EP EEPROM.length() - 4
BH1750 lightMeter;

bool state_flag = OFF;      // flag for relay
char tm[22];
char hourCurrent;
// address of eeprom. Arduino uno has 512 bytes eeprom
unsigned int index_addr;
unsigned int total_dt;
void calcIndex(int inc);
void calcTotal(int inc);
unsigned int index();
unsigned int total();
void saveData(char hh, unsigned int light);
void clear(unsigned int addr, unsigned int length);

void setup()
{
   Serial.begin(115200);
   // Wire.begin();                 // enable I2C
   lightMeter.begin();
   // EEPROM.put(INDEX_OFFSET_EP, 0);
   // EEPROM.put(TOTAL_OFFSET_EP, 0);
   EEPROM.get(INDEX_OFFSET_EP, index_addr);
   EEPROM.get(TOTAL_OFFSET_EP, total_dt);

   // Time.set(DateTime(2017, 02, 12, 07, 22, 20).unixtime());
   if (Time.getTime()==0) {
      Serial.println("RTC lost power, lets set the time!");
      // set up time for realtime and alarm
      //                 yy   mm  dd  hh  mm  ss
      Time.set(DateTime(2017, 01, 18, 06, 00, 00).unixtime());
   }

   Time.getDateTimeString(tm);
   Log.logs("System has took %lu ms for start up, %s", millis(), tm);
   delay(2000);

   Time.initAlarm(ALARM_DATA);
   hourCurrent = Time.getTimeHour();
   uint16_t light = lightMeter.readLightLevel();
   Serial.print("Light: ");
   Serial.print(light);
   Serial.println(" lx");
   // saveData(hourCurrent, light);

}

void loop()
{
   hourCurrent = Time.getTimeHour();
   if(hourCurrent >= schedule_measure[Time.trackCurrent(TRACK_MEASURE)]) {
      Time.getTimeString(tm);
      Log.logs("Alarm measure is on %s", tm);
      Time.setNextSchedule(ALARM_DATA);
      uint16_t light = lightMeter.readLightLevel();
      Serial.print("Light: ");
      Serial.print(light);
      Serial.println(" lx");
      saveData(hourCurrent, light);
   }
   // Time.print();
   delay (1000); // Wait one second before repeating :)
}

void saveData(char hh, unsigned int light) {
   EEPROM.write(index_addr, hh);
   calcTotal(1);
   EEPROM.put(index_addr, light);
   calcTotal(2);
}

void calcIndex(int inc) {
   index_addr += inc;
   if (index_addr == EEPROM.length()) {
      index_addr = 0;
   }
   EEPROM.put(INDEX_OFFSET_EP, index_addr);
}

void calcTotal(int inc) {
   calcIndex(inc);
   total_dt += inc;
   EEPROM.put(TOTAL_OFFSET_EP, total_dt);
}

unsigned int index() {
   unsigned int _index;
   EEPROM.get(INDEX_OFFSET_EP, _index);
   return _index;
}

unsigned int total() {
   unsigned int _total;
   EEPROM.get(TOTAL_OFFSET_EP, _total);
   return _total;
}
