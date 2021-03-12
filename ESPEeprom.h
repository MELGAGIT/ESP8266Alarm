#ifndef ESPEeprom_h
#define ESPEeprom_h

#include "alarm.h"
#include <EEPROM.h>

void EepromInit();
int EepromErase(int from, int to);
int EepromEraseAll();
int EepromRemoveAlarm(int numAlarm);
int EepromWrite(Alarm* a, int addr);
int EepromGetEmptyAddress(int from, int to);
int EepromAddAlarm(Alarm* a);
int EepromRead(Alarm *a, int addr);
int EepromLoadAlarm();

 
#endif
