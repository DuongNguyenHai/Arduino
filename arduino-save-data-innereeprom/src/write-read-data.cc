#include <Arduino.h>
#include <EEPROM.h>

#define TOTAL_OFFSET_EP EEPROM.length() - 2
#define INDEX_OFFSET_EP EEPROM.length() - 4

unsigned int eeAddress = 0;   //Location we want the data to be put.
// unsigned int data;
unsigned int index_addr;
unsigned int total_dt;
void calcIndex(int inc);
void calcTotal(int inc);
unsigned int index();
unsigned int total();
void saveData(char hh, unsigned int light);
void clear(unsigned int addr, unsigned int length);

void setup() {

   Serial.begin(115200);
   delay(1000);
   EEPROM.put(INDEX_OFFSET_EP, 0);
   EEPROM.put(TOTAL_OFFSET_EP, 0);
   EEPROM.get(INDEX_OFFSET_EP, index_addr);
   EEPROM.get(TOTAL_OFFSET_EP, total_dt);
   Serial.print("index: ");
   Serial.println(index());
   Serial.print("total: ");
   Serial.println(total());
   //One simple call, with the address first and the object second.
   // EEPROM.put(eeAddress, val);
   // calcIndex(sizeof(unsigned int));
   Serial.println("Written unsigned int type!");
   for (int i = 0; i < 5; i++) {
      saveData(1,i+15000);
   }
   // Serial.print("index: ");
   // Serial.println(index_addr);
   // EEPROM.write(index_addr, 1);
   // clear(0,30);

}
void loop() {

   Serial.print("index: ");
   Serial.println(index());
   Serial.print("total: ");
   Serial.println(total());

   unsigned int eead=0;
   for (size_t i = 0; i < 5; i++) {
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

void saveData(char hh, unsigned int light) {
   Serial.print("index: ");
   Serial.println(index_addr);
   EEPROM.write(index_addr, hh);
   calcTotal(1);
   Serial.print("index: ");
   Serial.println(index_addr);
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
