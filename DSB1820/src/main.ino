// Nguyen Hai Duong
// Jan 5 2017

// Reading temperature from ds18b20 waterproof
// https://www.sparkfun.com/products/11050

#include <OneWire.h>

OneWire  ds(3);
byte addr[8];
#define NOT_REAL -100 // the value will not never exist
float CalculateTempt();

void setup() {
   Serial.begin(115200);
}

void loop() {
   float tempt = CalculateTempt();
   if(tempt!=NOT_REAL) {
      Serial.print("Tempt: ");
      Serial.println(tempt);
   }
   else {
      Serial.println("Reading sensor failed !");
   }
   delay(1000);
}

float CalculateTempt() {

   byte data[9];

   if ( !ds.search(addr) ) {
      // Serial.print("NO more device.\n");
   }

   // Serial.print("Addr: ");
   // for(byte i = 0; i < 8; i++) {
   //    Serial.print(addr[i], HEX);
   //    Serial.print(" ");
   // }

   if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n");
      return NOT_REAL;
   }

   ds.reset();
   ds.select(addr);
   ds.write(0x44,1);         // start conversion, with parasite power on at the end

   delay(1000);     // Temperature Conversion Time at 12 bit resolution is 750ms, so should delay more than that a little bit
   // we might do a ds.depower() here, but the reset will take care of it.

   ds.reset();
   ds.select(addr);
   ds.write(0xBE);                           // Read Scratchpad

   // Serial.println();
   // Serial.print("Read: ");

   for (byte i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
      // Serial.print(data[i], HEX);
      // Serial.print(" ");
   }

   // Serial.print(" CRC=");
   // Serial.print( OneWire::crc8( data, 8), HEX);
   // Serial.println();

   float celsius = (float)((data[1] << 8) | data[0]) / 16.0;
   return celsius;
}
