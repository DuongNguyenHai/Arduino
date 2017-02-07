// Nguyen Hai Duong
// Jan 9 2017
// Modify date : Feb 6
#ifndef EEPROM_AT24C256_H
#define EEPROM_AT24C256_H

// #include <Arduino.h>
#include <Wire.h>

#if (ARDUINO >= 100)
 #include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
 // Macro to deal with the difference in I2C write functions from old and new Arduino versions.
 #define _I2C_WRITE write
 #define _I2C_READ  read
#else
 #include <WProgram.h>
 #define _I2C_WRITE send
 #define _I2C_READ  receive
#endif

#define AT24C256_ADDR 0x50

#define CHAR 1
#define INT 2
#define LONG 4
#define FLOAT 4
#define DOUBLE 8

#if defined(ESP8266)
#define MAX_STR 128
#define ESP8266_SDA 2         // esp8266 ver7
#define ESP8266_SCL 14        // esp8266 ver7
#else
#define MAX_STR 64
#endif

#define EEPROM EPROM_AT24C256

class EPROM_AT24C256 {

public:
   EPROM_AT24C256();
   EPROM_AT24C256(int dv_addr);
   ~EPROM_AT24C256();
   bool begin();
   unsigned int write(unsigned int addr, char c);  // byte write. return the address written
   unsigned int write(unsigned int addr, const char *s, unsigned char length); // page write. data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes. return the last address written
   unsigned int print(unsigned int addr, const char *s); // print string. return the last address written
   unsigned int printSpecial(unsigned int add, const char *s, char tail); // print and add special char at last. return the last address written
   unsigned int printSpecial(unsigned int add, const char *s, char head, char tail); // print speical char at begin, print string and print speical char at last. return the last address written
   char read(unsigned int addr); // read a character
   unsigned int read(unsigned int addr, char *s, unsigned char length); // length maximum = 32. return the last address
   unsigned int readString(unsigned int addr, char *arr);                 // read string, add '\0' automatic. return the last address read
   unsigned int readString(unsigned int addr, char *arr, unsigned char length); // read string with fixed length. return the last address read
   unsigned int readStringUntil(unsigned int addr, char *s, char delim='\0'); // read string until meet delim. return the last address read
   unsigned int readStringBetween(unsigned int addr, char *s, char head, char tail);  // read string between two special char. return the last address read

   unsigned int writeNumber(unsigned int addr, char data);
   unsigned int writeNumber(unsigned int addr, unsigned char data);
   unsigned int writeNumber(unsigned int addr, int data);      // write number, return the last address written
   unsigned int writeNumber(unsigned int addr, unsigned int data);
   unsigned int writeNumber(unsigned int addr, long data);
   unsigned int writeNumber(unsigned int addr, unsigned long data);
   unsigned int writeNumber(unsigned int addr, float data);
   unsigned int writeNumber(unsigned int addr, double data);
   unsigned int readNumber(unsigned int addr, char &num);
   unsigned int readNumber(unsigned int addr, unsigned char &num);
   unsigned int readNumber(unsigned int addr, int &num);     // read int number, return the last address read
   unsigned int readNumber(unsigned int addr, unsigned int &num);
   unsigned int readNumber(unsigned int addr, long &num);
   unsigned int readNumber(unsigned int addr, unsigned long &num);
   unsigned int readNumber(unsigned int addr, float &num);
   unsigned int readNumber(unsigned int addr, double &num);

   unsigned int clear(unsigned int addr, unsigned int length); // clear bytes from addr to addr + length

private:
   int eep_addr;
   char readCurrentAddr(); // read current address of AT24C256 device. the address was increased automaticly by AT24C256 device
   unsigned int readBytes(unsigned int addr, char *s, unsigned char size);    // read size bytes and return the last address read
};

#endif
