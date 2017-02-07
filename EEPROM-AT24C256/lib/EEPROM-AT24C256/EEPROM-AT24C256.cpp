#include "EEPROM-AT24C256.h"

EPROM_AT24C256::EPROM_AT24C256() {
   eep_addr = AT24C256_ADDR;
}

EPROM_AT24C256::EPROM_AT24C256(int dv_addr) {
   eep_addr = dv_addr;
}

bool EPROM_AT24C256::begin() {
   #if defined(ESP8266)
   Wire.begin(ESP8266_SDA, ESP8266_SCL);
   #else
   Wire.begin();
   #endif
   return true;
}

EPROM_AT24C256::~EPROM_AT24C256() {}

unsigned int EPROM_AT24C256::write(unsigned int addr, char data) {
   // int rdata = data;
   Wire.beginTransmission(eep_addr);
   Wire._I2C_WRITE((unsigned char)(addr >> 8)); // MSB
   Wire._I2C_WRITE((unsigned char)(addr & 0xFF)); // LSB
   Wire._I2C_WRITE(data);
   Wire.endTransmission();
   delay(20);   // delay is reall important.
   return addr;
}

unsigned int EPROM_AT24C256::write(unsigned int addr, const char *s, unsigned char length) {
   Wire.beginTransmission(eep_addr);
   Wire._I2C_WRITE((unsigned char)(addr >> 8)); // MSB
   Wire._I2C_WRITE((unsigned char)(addr & 0xFF)); // LSB
   unsigned char n = Wire._I2C_WRITE(s, length);
   Wire.endTransmission();
   delay(20);  // delay is reall important
   return addr + n - 1;
}

unsigned int EPROM_AT24C256::print(unsigned int addr, const char *s) {
   return write(addr, s, strlen(s));
}

unsigned int EPROM_AT24C256::printSpecial(unsigned int addr, const char *s, char tail) {
   unsigned int addr_af = print(addr, s);
   return write(addr_af+1, tail);
}

unsigned int EPROM_AT24C256::printSpecial(unsigned int addr, const char *s, char head, char tail) {
   unsigned int addr_af = write(addr, head);
   addr_af = print(addr_af+1, s);
   return write(addr_af+1, tail);
}

char EPROM_AT24C256::read(unsigned int addr) {
   Wire.beginTransmission(eep_addr);
   Wire._I2C_WRITE((unsigned char)(addr >> 8)); // MSB
   Wire._I2C_WRITE((unsigned char)(addr & 0xFF)); // LSB
   Wire.endTransmission();
   Wire.requestFrom(eep_addr, 1);
   return Wire._I2C_READ();
}

char EPROM_AT24C256::readCurrentAddr() {
   Wire.requestFrom(eep_addr, 1);
   return Wire._I2C_READ();
}

unsigned int EPROM_AT24C256::read(unsigned int addr, char *s, unsigned char length) {
   char *p = s;
   char c = read(addr);
   if (c==-1 || c==0) return 0;
   *s++ = c;
   Serial.print(c);
   for (unsigned char i = 1; i < length; i++) {
      c = readCurrentAddr();
      if (c==-1 || c==0) break;
      *s++ = c;
   }
   *s = '\0';
   return addr + (s-p) - 1;   // count from addr, so need to abstract 1
}

unsigned int EPROM_AT24C256::readString(unsigned int addr, char *s, unsigned char length) {
   if(length > MAX_STR) length = MAX_STR;
   unsigned int n = read(addr, s, length);
   s[n-addr+1] = '\0';
   return n;
}

unsigned int EPROM_AT24C256::readString(unsigned int addr, char *s) {
   return readString(addr, s, MAX_STR);
}

unsigned int EPROM_AT24C256::readStringUntil(unsigned int addr, char *s, char delim) {
   char *p = s;
   char c = read(addr);
   if (c==-1 || c==0) return 0;
   *s++ = c;
   for (unsigned char i = 1; i < MAX_STR; i++) {
      c = readCurrentAddr();
      if (c==-1 || c==0 || c==delim) break;
      *s++ = c;
   }
   *s = '\0';
   return addr + (s-p);
}

unsigned int EPROM_AT24C256::readStringBetween(unsigned int addr, char *s, char head, char tail) {
   unsigned int n = addr;
   bool head_flag = false;
   char c = read(addr);
   if (c==-1 || c==0) return addr;
   else if(c==head) head_flag = true;
   n++;
   for (unsigned char i = 1; i < MAX_STR; i++) {
      c = readCurrentAddr();
      if(c==-1 || c==0)						// not found any more character
			break;
		if(head_flag) {
			if(c==tail) break;
			*s++ = c;
		}
		if(c==head)
			head_flag = true;
      n++;
   }
   *s = '\0';
	return n;
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, char data) {
   return write(addr, data);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, unsigned char data) {
   return write(addr, data);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, int data) {
   return write(addr, (char *) &data, INT);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, unsigned int data) {
   return write(addr, (char *) &data, INT);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, long data) {
   return write(addr, (char *) &data, LONG);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, unsigned long data) {
   return write(addr, (char *) &data, LONG);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, float data) {
   return write(addr, (char *) &data, FLOAT);
}

unsigned int EPROM_AT24C256::writeNumber(unsigned int addr, double data) {
   return write(addr, (char *) &data, DOUBLE);
}

unsigned int EPROM_AT24C256::readBytes(unsigned int addr, char *s, unsigned char size) {
   char *p = s;
   Wire.beginTransmission(eep_addr);
   Wire._I2C_WRITE((unsigned char)(addr >> 8)); // MSB
   Wire._I2C_WRITE((unsigned char)(addr & 0xFF)); // LSB
   Wire.endTransmission();
   Wire.requestFrom(eep_addr, (int)size);
   char c;
   for (unsigned char i = 0; i < size; i++) {
      c = Wire._I2C_READ();
      if(c==-1) break;
      *s++ = c;
   }
   return addr+(s-p);
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, char &num) {
   unsigned int addr_af = readBytes(addr, &num, CHAR);
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, unsigned char &num) {
   char n;
   unsigned int addr_af = readBytes(addr, &n, CHAR);
   num = (unsigned char)n;
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, int &num) {
   char b[INT];
   unsigned int addr_af = readBytes(addr, b, INT);
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, unsigned int &num) {
   char b[INT];
   unsigned int addr_af = readBytes(addr, b, INT);
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, long &num) {
   char b[LONG];
   unsigned int addr_af = readBytes(addr, b, INT);
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, unsigned long &num) {
   char b[LONG];
   unsigned int addr_af = readBytes(addr, b, sizeof(b));
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, float &num) {
   char b[FLOAT];
   unsigned int addr_af = readBytes(addr, b, sizeof(b));
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::readNumber(unsigned int addr, double &num) {
   char b[DOUBLE];
   unsigned int addr_af = readBytes(addr, b, sizeof(b));
   memcpy(&num, b, sizeof(b));
   return addr_af;
}

unsigned int EPROM_AT24C256::clear(unsigned int addr, unsigned int length) {
   unsigned int n = 0;
   for (unsigned int i = 0; i < length; i++) {
      n += write(addr+i,0);
   }
   return n;
}
