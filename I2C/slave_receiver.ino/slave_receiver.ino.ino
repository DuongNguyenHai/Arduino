#include <Wire.h>

void setup() {
  Wire.begin(0x08);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while(Wire.available())    // slave may send less than requested
  { 
    byte c = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
  }
}
