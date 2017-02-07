// Nguyen Hai Duong
// Jan 13 2017
// Display from 1 -> 9 and A,b,C,d,E,F on dual LED 7 segs, use 74HC595N
// Arduino -> 74HC595N -> dual LED 7segs
// References:
// https://www.arduino.cc/en/tutorial/ShiftOut
// https://en.wikipedia.org/wiki/Seven-segment_display
// http://www.ti.com/lit/ds/symlink/sn74hc595.pdf

// Pin connected to latch pin (ST_CP or RCLK (texas instrument)) of 74HC595
#define LATCH 8
// Pin connected to clock pin (SH_CP or SRCLK (texas instrument)) of 74HC595
#define CLK 12
// Pin connected to Data in (DS or SER (texas instrument)) of 74HC595
#define DATA 11

//This is the hex value of each number stored in an array by index num
// value display :   0     1     2     3     4     5     6     7     8     9     A  b     C    d    E    F
byte digit[16]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void setup(){
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop(){

  for(int i=0; i<16; i++) {
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLK, MSBFIRST, ~digit[i]); // digit on LED 1
      shiftOut(DATA, CLK, MSBFIRST, ~digit[i]); // digit on LED 2. if use wanna more LED, just add more shiftOut function.
      digitalWrite(LATCH, HIGH);
      delay(1000);
  }

}
