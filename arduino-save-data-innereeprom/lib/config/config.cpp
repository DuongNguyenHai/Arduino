#include "config.h"


char log_level = 4;
bool log_serial = 1;       // log via serial
bool log_network = 0;       // log via network

// 2 shedule below is hour shedule. all value are hours.
unsigned char schedule_measure[SCHEDULE_MEASURE_MAX] = {6,7,8,9,10,11,12,13,14,15,16,17,18};
unsigned char schedule_lamp[SCHEDULE_LAMP_MAX] = {6,16};
