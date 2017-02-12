

#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include <stdarg.h>
#include "config.h"
#include "RTClib.h"
#define printf_mode 0
#define error_mode 1
#define warning_mode 2
#define log_mode 3
#define verbose_mode 4



class LOG : public RTC {

public :
   LOG();
   ~LOG();
   void log(unsigned char mode, const char *fmt, ... );                 // print information
   #ifdef F // check to see if F() macro is available
   void log(unsigned char mode, const __FlashStringHelper *fmt, ... ); // print information
   #endif

private:
   void write(const char *fmt, va_list args, unsigned char mode);       // write information to serial, tcp/ip ...
   #ifdef F // check to see if F() macro is available
   void write(const __FlashStringHelper *fmt, va_list args, unsigned char mode); // write information to serial, tcp/ip ...
   #endif

};

#define printfs(fmt,...) log(printf_mode, fmt, ##__VA_ARGS__ )       // print every things
#define errors(fmt, ... ) log(error_mode, fmt,  ##__VA_ARGS__ )      // print error
#define warnings(fmt, ... ) log(warning_mode, fmt,  ##__VA_ARGS__ )  // print error
#define logs(fmt, ... ) log(log_mode, fmt, ##__VA_ARGS__ )           // print log
#define verboses(fmt, ... ) log(verbose_mode, fmt, ##__VA_ARGS__ )   // print verbose

#define float2str(num) String(num).c_str()

extern LOG Log;

#endif
