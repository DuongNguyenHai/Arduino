#include <Arduino.h>
#include <EEPROM.h>

void clear(unsigned int addr, unsigned int length) ;

void setup() {

   Serial.begin(115200);
   clear(0, EEPROM.length());

}
void loop() {
   delay(1000);
}

void clear(unsigned int addr, unsigned int length) {
   for (unsigned int i = 0; i < length; i++) {
      EEPROM.write(addr+i, 0);
   }
}
