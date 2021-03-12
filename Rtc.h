#ifndef Rtc_h
#define Rtc_h

#include "RTClib.h"


void RtcInit();
void RtcAdjust(char* Date, char* Time);
DateTime RtcNow();
char* RtcCurrent();
#endif
