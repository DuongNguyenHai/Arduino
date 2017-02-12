#include <Arduino.h>
#include <EEPROM.h>

#define INDEX_OFFSET EEPROM.length() - 2

unsigned int eeAddress = 0;   //Location we want the data to be put.
unsigned int data;
unsigned int index_data;
void calcIndex(int inc);
unsigned int index();
void clear(unsigned int addr, unsigned int length);

void setup() {

   Serial.begin(9600);
   delay(3000);
   EEPROM.put(INDEX_OFFSET, 0);
   index_data = index();

   //One simple call, with the address first and the object second.
   // EEPROM.put(eeAddress, val);
   // calcIndex(sizeof(unsigned int));
   Serial.println("Written unsigned int type!");
   for (int i = 0; i < 5; i++) {
      EEPROM.put(index_data, i);
      calcIndex(sizeof(unsigned int));
      eeAddress += sizeof(unsigned int);
      if (eeAddress == EEPROM.length()) {
         eeAddress = 0;
      }
   }

   // clear(0,30);

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

void clear(unsigned int addr, unsigned int length) {
   for (unsigned int i = 0; i < length; i++) {
      EEPROM.write(addr+i, 0);
   }
}
