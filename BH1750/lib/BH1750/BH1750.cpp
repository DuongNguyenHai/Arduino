/*

   This is a library for the BH1750FVI Digital Light Sensor
   breakout board.

   The board uses I2C for communication. 2 pins are required to
   interface to the device.

   Written by Christopher Laws, March, 2013.
   Modifier : Nguyen Hai Duong, Feb 7 2017.

*/

#include "BH1750.h"

// Define milliseconds delay for ESP8266 platform
#if defined(ESP8266)

  #include <pgmspace.h>
  #define delay_ms_(ms) delayMicroseconds((ms) * 1000)

// Use delay_ms_ from utils for AVR-based platforms
#elif defined(__avr__)
  #include <util/delay.h>

// Use Wiring's delay for compability with another platforms
#else
  #define delay_ms_(ms) delay(ms)
#endif


// Legacy Wire.write() function fix
#if (ARDUINO >= 100)
  #define write_(d) Wire.write(d)
#else
  #define write_(d) Wire.send(d)
#endif


// Legacy Wire.read() function fix
#if (ARDUINO >= 100)
  #define read_() Wire.read()
#else
  #define read_() Wire.receive()
#endif


/**
 * Constructor
 * @params addr Sensor address (0x76 or 0x72, see datasheet)
 *
 * On most sensor boards, it was 0x76
 */
BH1750::BH1750(unsigned char addr) {

  BH1750_I2CADDR = addr;

}


/**
 * Begin I2C and configure sensor
 * @param mode Measurment mode
 */
void BH1750::begin(uint8_t mode) {

   // Initialize I2C
   #if defined(ESP8266)
   Wire.begin(ESP8266_SDA, ESP8266_SCL);
   #else
   Wire.begin();
   #endif

   // Configure sensor in specified mode
   configure(mode);

}

/**
 * Configurate BH1750 with specified working mode
 * @param mode Measurment mode
 */
void BH1750::configure(uint8_t mode) {

   // Check, is measurment mode exist
   switch (mode) {

      case BH1750_CONTINUOUS_HIGH_RES_MODE: {
      // Send mode to sensor
      Wire.beginTransmission(BH1750_I2CADDR);
      Wire.write((uint8_t)mode);
      Wire.endTransmission();

      // Wait few moments for waking up
      delay_ms_(100);
      } break;
      case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
      case BH1750_CONTINUOUS_LOW_RES_MODE:
      case BH1750_ONE_TIME_HIGH_RES_MODE:
      case BH1750_ONE_TIME_HIGH_RES_MODE_2:
      case BH1750_ONE_TIME_LOW_RES_MODE:
      default: // Invalid measurement mode
         break;

   }

}


/**
 * Read light level from sensor
 * @return  Lightness in lux (0 ~ 65535)
 */
uint16_t BH1750::readLightLevel(void) {

   // Measurment result will be stored here
   uint16_t level;

   // Read two bytes from sensor
   Wire.requestFrom(BH1750_I2CADDR, 2);

   // Read two bytes, which are low and high parts of sensor value
   level = read_();
   level <<= 8;
   level |= read_();

   // Convert raw value to lux
   level /= 1.2;

   return level;

}
