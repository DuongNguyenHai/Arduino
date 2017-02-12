// Nguyen Hai Duong

#include "log.h"

#define PRINTF_BUF 128 // define the tmp buffer size (change if desired)

LOG::LOG() {}
LOG::~LOG() {}

void LOG::log( unsigned char mode, const char *fmt, ... ) {
   if(mode<=log_level) {
      va_list args;
      va_start (args, fmt );
      write(fmt, args, mode);
      va_end (args);
   }
}

#ifdef F // check to see if F() macro is available
void LOG::log(unsigned char mode, const __FlashStringHelper *fmt, ... ) {
   if(mode<=log_level) {
      va_list args;
      va_start (args, fmt );
      write(fmt, args, mode);
      va_end (args);
   }
}
#endif

void LOG::write(const char *fmt, va_list args, unsigned char mode) {
   if(log_serial || log_network) {
      char buf[PRINTF_BUF];
      if(mode==printf_mode) {
         vsnprintf(buf, PRINTF_BUF, fmt, args);
      }
      else {
         char ss[strlen(fmt)+32];      // add time and string mode
         if(mode==error_mode) {
            strcpy(ss,"ERROR ");
            char tm[22];
            if(getTimeString(tm)) {
               strcat(ss, tm);
            }
            strcat(ss,": ");
         }
         else if(mode==warning_mode)
            strcpy(ss,"WARNING : ");
         else if(mode==log_mode)
            strcpy(ss,"LOG : ");
         else if(mode==verbose_mode)
            strcpy(ss,"VERBOSE : ");
         strcat(ss, fmt);
         vsnprintf(buf, PRINTF_BUF, ss, args);
      }

      if(log_serial) {
         strcat(buf,"\n");
         Serial.print(buf);
      }
   }
}

#ifdef F // check to see if F() macro is available
void LOG::write(const __FlashStringHelper *fmt, va_list args, unsigned char mode) {
   if(log_serial || log_network) {
      char buf[PRINTF_BUF];
      if(mode==printf_mode) {
         #ifdef __AVR__
         vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
         #else
         vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
         #endif
      }
      else {
         char ss[strlen((const char *)fmt)+32];      // add time and string mode
         if(mode==error_mode) {
            strcpy(ss,"ERROR ");
            char tm[22];
            if(getTimeString(tm)) {
               strcat(ss, tm);
            }
            strcat(ss,": ");
         }
         else if(mode==warning_mode)
            strcpy(ss,"WARNING : ");
         else if(mode==log_mode)
            strcpy(ss,"LOG : ");
         else if(mode==verbose_mode)
            strcpy(ss,"VERBOSE : ");
         strcat(ss, (const char *)fmt);
         #ifdef __AVR__
         vsnprintf_P(buf, sizeof(buf), ss, args); // progmem for AVR
         #else
         vsnprintf(buf, sizeof(buf), ss, args); // for the rest of the world
         #endif
      }

      if(log_serial) {
         Serial.print(buf);
         Serial.println();
      }
   }
}
#endif

// define a global Log for every file can use it.
LOG Log;
