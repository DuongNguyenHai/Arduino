#include <Arduino.h>
#include <EEPROM.h>

#define TOTAL_OFFSET_EP EEPROM.length() - 2
#define INDEX_OFFSET_EP EEPROM.length() - 4

unsigned int eeAddress = 0;   //Location we want the data to be put.
unsigned int index_addr;
unsigned int total_dt;
unsigned int index();
unsigned int total();

void setup() {

   Serial.begin(115200);
   delay(1000);

   EEPROM.get(INDEX_OFFSET_EP, index_addr);
   EEPROM.get(TOTAL_OFFSET_EP, total_dt);
   Serial.print("index: ");
   Serial.println(index_addr);
   Serial.print("total: ");
   Serial.println(total_dt);

}
void loop() {

   unsigned int eead=0;
   for (size_t i = 0; i < total_dt/3; i++) {
      char hh = EEPROM.read(eead);
      Serial.print(hh,DEC);
      Serial.print(", ");
      eead += 1;
      unsigned int val;
      EEPROM.get(eead, val);
      Serial.print(val);
      Serial.print(", ");
      eead += 2;
   }
   Serial.println();

   delay(1000);
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
