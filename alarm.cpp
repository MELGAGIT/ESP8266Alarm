#include "alarm.h"
#include <stdio.h>
#include <ESP8266WiFi.h>

#define DEBUG

using namespace json11;
using std::string;

std::map<int, Alarm> gv_Alarms;

const char* getAllAlarms(){

  std::string res;
  const char* tpl = R"({"Day": %c,"Month": %c,"Year": %c,"Hours": %c,"Minutes": %c,"Type": %c,"State": %c,"Order": %c }")";
  char s[250];
#ifdef DEBUG
  for(int i = 0; i < 6; i++){
    gv_Alarms[i].alarm.Day = i+1;
    gv_Alarms[i].alarm.Month = i+2;
    gv_Alarms[i].alarm.Year = i+3;
    gv_Alarms[i].alarm.Hours = i+4;
    gv_Alarms[i].alarm.Minutes = i+5;
    gv_Alarms[i].alarm.Type = i+6;
    gv_Alarms[i].alarm.State = i+7;
    gv_Alarms[i].alarm.Order = i+8;
  }
#endif
  
  res = "{";
  
  for(int i = 0; i < gv_Alarms.size(); i++){

    sprintf(s, tpl, gv_Alarms[i].rawAlarm[0], gv_Alarms[i].rawAlarm[1], gv_Alarms[i].rawAlarm[2], gv_Alarms[i].rawAlarm[3], gv_Alarms[i].rawAlarm[4], gv_Alarms[i].rawAlarm[5], gv_Alarms[i].rawAlarm[6], gv_Alarms[i].rawAlarm[7]);
    res += s;
    
    if(i < gv_Alarms.size() - 1) res += ",";
  }
  
  res += "}";
  
  return res.data();
}
int setAlarm(std::string input){

 int r = 1, alarmsSize = gv_Alarms.size();
 std::string err;
 json11::Json myArray = json11::Json(input);
 const auto js = json11::Json::parse(input, err);
  
  for(int i = 0; i < myArray.array_items().size(); i++){


    gv_Alarms[alarmsSize + i].alarm.Day = js.array_items()[i]["Day"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Day));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Month = js.array_items()[i]["Month"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Month));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Year = js.array_items()[i]["Year"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Year));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Hours = js.array_items()[i]["Hours"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Hours));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Minutes = js.array_items()[i]["Minutes"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Minutes));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Type = js.array_items()[i]["Type"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Type));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.State = js.array_items()[i]["State"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.State));Serial.print(",");
    gv_Alarms[alarmsSize + i].alarm.Order = js.array_items()[i]["Order"].char_value();Serial.print(int(gv_Alarms[alarmsSize + i].alarm.Order));Serial.print(",");
    
  }
    
  return r;
}

int clearAllAlarms(){
  int r = 1;
  gv_Alarms.clear();
  return r;
}
