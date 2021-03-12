#include <Wire.h> // Library for I2C communication
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include "Rtc.h"

RTC_DS1307 RTC;     // Setup an instance of DS1307 naming it RTC


void RtcInit(){
    /*start RTC Init*/
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  //TODO MEHDI : TO REMOVE RTC.adjust
  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
}
void RtcAdjust(char* Date, char* Time) {
  RTC.adjust(DateTime(Date, Time));  // Time and date is expanded to date and time on your computer at compiletime
  Serial.print("Time and date adjusted");
}

DateTime RtcNow(){
  return RTC.now();
}

char* RtcCurrent(){
  DateTime dateTime = RTC.now();
  std::string res;
  const char* tpl = R"({"Day": %d,"Month": %d,"Year": %d,"Hours": %d,"Minutes": %d,"Second": %d }")";
  char s[250];
  
  sprintf(s, tpl, dateTime.day(),  dateTime.month(), dateTime.year(), dateTime.hour(), dateTime.minute(), dateTime.second());
  res += s;
  
  return s;
}
