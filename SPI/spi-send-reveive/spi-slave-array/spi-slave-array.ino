#include <SPI.h>

#define EN 2

volatile char EN_flag = 0;
volatile char old_flag = 0;

volatile int count = 0;
volatile int byte_num = 0;
char buff[5] = {0x06,0x07,0x08,0x09,0x10};

void setup (void)
{
	Serial.begin (9600);   // debugging

	// turn on SPI in slave mode
	SPCR |= bit (SPE);

	// have to send on master in, *slave out*
	pinMode(MISO, OUTPUT);

	// now turn on interrupts
	SPI.attachInterrupt();
	Serial.println("Receive via SPI: ");

	pinMode(EN, OUTPUT);
	digitalWrite(EN, HIGH);
}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect) {
	byte c = SPDR;  // grab byte from SPI Data Register
	if(EN_flag==1) {
		if(c==0) {
			SPDR = buff[count];
			Serial.print(count);Serial.print("->|0x");Serial.println(buff[count], HEX);
			count++;
			if(count==5) {
				EN_flag = 0;
				count = 0;
			}
		}
	}
	else {
		if(c!=0) {
			Serial.print("<-|0x");Serial.println(c, HEX);
			byte_num++;
			if(byte_num==5) {
				EN_flag = 1;
				byte_num = 0;
			}
		}
	}
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
	if(EN_flag==old_flag);
	else {
		old_flag = EN_flag;
		if(EN_flag==0){
			digitalWrite(EN, HIGH);
			Serial.println("Receiving from master :");
		}else {
			digitalWrite(EN, LOW);
			Serial.println("Sending to master :");
		}
	}
}  // end of loop
