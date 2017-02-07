// Nguyen Hai Duong
// jun 18 2017
// example of LiquidCrystal lib for LCD 16x2
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);      // select the pins used on the LCD panel

void setup() {
   lcd.begin(16, 2);               // start LCD library
   lcd.clear();
   lcd.print("Hello man !");
   lcd.setCursor(0, 1);
   lcd.print("number : ");
}

void loop() {
   for (size_t i = 0; i < 10; i++) {
      lcd.setCursor(9, 1);
      lcd.print(i);
      delay(1000);
   }
}
