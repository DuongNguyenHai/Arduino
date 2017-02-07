// Send array of bytes.
// SPI.transfer(buff, size) can send with array but its will rewrite buff if slave respond

#include <SPI.h>

#define SS 10
#define EN 2

char buff[5] = {0x01,0x02,0x03,0x04,0x05};

void setup() {
   pinMode(SS, OUTPUT);
   pinMode(EN, INPUT);
   digitalWrite(SS, HIGH);

   Serial.begin(9600);

   SPI.begin();
   SPI.setBitOrder(MSBFIRST);
   SPI.setClockDivider(SPI_CLOCK_DIV4);
   SPI.setDataMode(SPI_MODE0);
}

void loop() {

   if(digitalRead(EN)==HIGH) {
      Serial.println("Sending to slave");
      digitalWrite(SS, LOW);
      for (size_t i = 0; i < 5; i++) {
         SPI.transfer(buff[i]);
         Serial.print(i);Serial.print("->|0x");Serial.println(buff[i], HEX);
         delay(500);
      }
      digitalWrite(SS, HIGH);
   }
   else {
      Serial.println("Receive from slave :");
      digitalWrite(SS, LOW);
      int byte_num = 0;
      SPI.transfer(0);  // first request will receive nothing
      delay(500);
      for (size_t i = 0; i < 10; i++) {
         byte c = SPI.transfer(0);
         delay(500);
         Serial.print(i);Serial.print("<-|0x");Serial.println(c, HEX);
         if(c!=0) {
            byte_num++;
         }
         if(byte_num==5) {
            break;
         }
      }
      digitalWrite(SS, HIGH);
      delay(500);
      SPI.end();
      while(1) {
         delay(10);
      }
   }

}
