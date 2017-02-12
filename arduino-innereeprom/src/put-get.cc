#include <Arduino.h>
#include <EEPROM.h>

#define INDEX_OFFSET EEPROM.length() - 2

unsigned int eeAddress = 0;   //Location we want the data to be put.
unsigned int data;
unsigned int index_data;

void calcIndex(int inc);
unsigned int index();

void setup() {

   Serial.begin(9600);

   EEPROM.put(INDEX_OFFSET, 0);
   index_data = index();

   Serial.println("Written array data to eeprom!");
   for (int i = 0; i < 5; i++) {
      EEPROM.put(index_data, i);
      calcIndex(sizeof(unsigned int));
      index_data += sizeof(unsigned int);
      if (index_data == EEPROM.length()) {
         index_data = 0;
      }
   }


}
void loop() {

   Serial.print("index: ");
   Serial.println(index());

   unsigned int eead=0;
   for (size_t i = 0; i < 5; i++) {
      EEPROM.get(eead, data);
      eead += 2;
      Serial.print(data);
      Serial.print(", ");
   }
   Serial.println();

   delay(1000);
}

void calcIndex(int inc) {
   index_data += inc;
   EEPROM.put(INDEX_OFFSET, index_data);
}

unsigned int index() {
   unsigned int _index;
   EEPROM.get(INDEX_OFFSET, _index);
   return _index;
}
