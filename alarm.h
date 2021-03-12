#ifndef alarm_h
#define alarm_h

#include <map>
#include "json11.h"

#ifdef __cplusplus
extern "C" {
#endif
  
typedef enum alarmType {
  ON = 1,
  OFF = 2,
  DAYLY = 3, 
  WEEKLY = 4,
  INVALID = 0xFF
} alarmType;

typedef struct S_Alarm {
  char Day;
  char Month;
  char Year;
  char Hours;
  char Minutes;
  char Type;
  char State;
  char Order;
  
} S_Alarm;

typedef union Alarm {
  S_Alarm alarm;
  char rawAlarm[8];
} Alarm;


extern std::map<int, Alarm> gv_Alarms;

const char* getAllAlarms();
int setAlarm(std::string input);
int clearAllAlarms();

#ifdef __cplusplus
}
#endif

#endif
