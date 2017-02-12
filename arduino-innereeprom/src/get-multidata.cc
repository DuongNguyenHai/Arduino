#include <Arduino.h>
#include <EEPROM.h>

#define INDEX_OFFSET EEPROM.length() - 2

unsigned int data;
unsigned int index();
void printGetArray(unsigned int addr, unsigned int length, char type=1);

void setup() {

   Serial.begin(9600);

}
void loop() {

   Serial.print("address: ");
   Serial.println(index());

   printGetArray(0, 5, 2);
   Serial.println();

   delay(1000);
}

unsigned int index() {
   unsigned int _index;
   EEPROM.get(INDEX_OFFSET, _index);
   return _index;
}

void printGetArray(unsigned int addr, unsigned int length, char type) {
   for (unsigned int i = 0; i < length; i++) {
      EEPROM.get(addr, data);
      addr += type;
      Serial.print(data);
      Serial.print(", ");
   }
}
