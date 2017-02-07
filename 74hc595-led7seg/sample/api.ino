// Nguyen Hai Duong
// Jan 13 2017
// Display from 1 -> 99 on dual LED 7 segs, use 74HC595N
// Display character : A,b,C,d,E,F
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

  for(int i=0; i<100; i++) {
      DisplayDual(i);
      delay(1000);
  }
  // DisplayCharacter(2,'c');
  // DisplayDualCharacter("ef");
}

bool Display(unsigned char led, unsigned char n) {
   if(n<0 || n>15)
      return false;
   digitalWrite(LATCH, LOW);
   if(led==1) {
      shiftOut(DATA, CLK, MSBFIRST, ~digit[0]);
      shiftOut(DATA, CLK, MSBFIRST, ~digit[n]); // digit on LED 1
   } else
   if(led==2) {
      shiftOut(DATA, CLK, MSBFIRST, ~digit[n]);
      shiftOut(DATA, CLK, MSBFIRST, ~digit[0]); // digit on LED 1
   }
   digitalWrite(LATCH, HIGH);

   return true;
}


bool DisplayDual(int n) {
   if(n<0 || n>99)
      return false;
   unsigned char tens = n/10;
   unsigned char units = n%10;
   digitalWrite(LATCH, LOW);
   shiftOut(DATA, CLK, MSBFIRST, ~digit[units]); // digit on LED 2. if use wanna more LED, just add more shiftOut function.
   shiftOut(DATA, CLK, MSBFIRST, ~digit[tens]); // digit on LED 1
   digitalWrite(LATCH, HIGH);
   return true;
}

bool DisplayCharacter(unsigned char led, char c) {
   if(c>90)
      c = c -32;

   Display(led, c - 55);
   return true;
}

bool DisplayDualCharacter(const char *s) {
   char c1 = s[0];
   char c2 = s[1];

   if(s[0]>90)
      c1 = c1 - 32;
   if(c2>90)
      c2 = c2 - 32;

   digitalWrite(LATCH, LOW);
   shiftOut(DATA, CLK, MSBFIRST, ~digit[c2-55]); // digit on LED 2. if use wanna more LED, just add more shiftOut function.
   shiftOut(DATA, CLK, MSBFIRST, ~digit[c1-55]); // digit on LED 1
   digitalWrite(LATCH, HIGH);
   return true;

}
