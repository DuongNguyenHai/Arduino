#include <SPI.h>

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
	
}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect){
	byte c = SPDR;
	if(c != NULL){
		byte C = c -32;
		SPDR = C;

		Serial.print("\nReceive:");
		Serial.write(c);
		Serial.print(",Respond:");
		Serial.write(C);
	}
} 

// main loop - wait for flag set in interrupt routine
void loop (void)
{
	delay(10);  
}