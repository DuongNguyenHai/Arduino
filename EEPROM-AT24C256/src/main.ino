#include <Arduino.h>
#include <EEPROM-AT24C256.h>

EPROM_AT24C256 eeprom;

void setup()
{
   unsigned int addr = 0;
   char name[] = "name"; // data to write
   char dt1[] = "mona lisa";

   Serial.begin(115200);
	// Wire.begin();
   eeprom.begin(); // initialise the connection
   eeprom.clear(0, 100);
   addr = eeprom.print(addr, "data");
   addr = eeprom.printSpecial(addr+1, name,'#',':');
   addr = eeprom.print(addr+1, dt1);
   // addr = eeprom.writeNumber(addr+1, 49);
   // Serial.print("addr of num: ");
   // Serial.println(addr);
   delay(10); //add a small delay

   Serial.println("Memory read");
}

void loop()
{
   char s[32];
   char s1[25];
   char s2[20];
   char s3[20];
   int ad = eeprom.read(0, s, 32);
   Serial.print("last s: "); Serial.println(ad);
   // must be sure about size of storage
   ad = eeprom.readString(0, s1, 25);
   Serial.print("last s1: "); Serial.println(ad);
   ad = eeprom.readStringUntil(0, s2, ':');
   Serial.print("last s2: "); Serial.println(ad);
   ad = eeprom.readStringBetween(0, s3,'#',':');
   Serial.print("last s3: "); Serial.println(ad);
	// int num;
   // ad = eeprom.readNumber(19, num);
   Serial.print("s: ");Serial.println(s);
   Serial.print("s1: ");Serial.println(s1);
   Serial.print("s2: ");Serial.println(s2);
   Serial.print("s3: ");Serial.println(s3);
   // Serial.print("number: ");Serial.println(num);

   delay(5000);

}
