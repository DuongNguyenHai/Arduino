// Send array of bytes.
// SPI.transfer(buff, size) can send with array but its will rewrite buff if slave respond

#include <SPI.h>

#define SS 10

void setup() {
   pinMode(SS, OUTPUT);
   SPI.begin();
   SPI.setBitOrder(MSBFIRST);
   SPI.setClockDivider(SPI_CLOCK_DIV4);
   SPI.setDataMode(SPI_MODE0);
}

void loop() {

   char buff[5] = {0x01,0x02,0x03,0x04,0x05};

   digitalWrite(SS, LOW);
   for (size_t i = 0; i < 5; i++) {
      SPI.transfer(buff[i]);
      delay(1000);
   }
   digitalWrite(SS, HIGH);

   SPI.end();
   return 0;

}
