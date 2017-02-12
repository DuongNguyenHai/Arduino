#include <Arduino.h>
#include <EEPROM.h>

unsigned int eeAddress = 0;   //Location we want the data to be put.
unsigned int val;

void setup() {
   Serial.begin(9600);
}
void loop() {
   EEPROM.get(eeAddress, val);
   Serial.print("val");
   Serial.println(val);
   delay(1000);
}
