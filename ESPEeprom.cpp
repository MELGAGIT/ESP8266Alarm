#include "ESPEeprom.h"


#define EEPROM_SIZE 1024 //1KB
#define NBR_ALARM (EEPROM_SIZE / 8)   // 8 is sizeof(union Alarm)

void EepromInit(){
  /*start EEPROM Init*/
  EEPROM.begin(EEPROM_SIZE);
}
int EepromErase(int from, int to) {
  int r = 1;
  for (int i = from; i < to; i++)
  {
    EEPROM.write(i, 0);
  }
  
  if (EEPROM.commit()) {
    //Serial.println("Data successfully committed");
    r = 1;
  } else {
    //Serial.println("ERROR! Data commit failed");
    r = 0;
  }
  return r;
}

int EepromEraseAll() {
  return EepromErase(0, EEPROM_SIZE);
}

int EepromRemoveAlarm(int numAlarm) {
  int addr = numAlarm * sizeof(Alarm);
  return EepromErase(addr, sizeof(Alarm));
}

int EepromWrite(Alarm* a, int addr) {
  int r = 1;
  for (int i = 0; i < sizeof(Alarm); i++)
  {
    EEPROM.write(addr + i, a->rawAlarm[i]);
    //Serial.print("write = ");
    //Serial.println(int(a->rawAlarm[i]));
  }
  
  if (EEPROM.commit()) {
    //Serial.println("Data successfully committed");
    r = 1;
  } else {
    //Serial.println("ERROR! Data commit failed");
    r = 0;
  }
  return r;
}

int EepromGetEmptyAddress(int from, int to) {

  int IsWrongArea = 0;

  if(from >= EEPROM_SIZE - sizeof(Alarm)) return -1;
  if(to > EEPROM_SIZE - 1) return -1;
  
  for(int i = from; i < to; i++){
    if(EEPROM.read(i) != 0){
      IsWrongArea = 1;
      continue;
    }
  }

  if(IsWrongArea) return EepromGetEmptyAddress(to+1, to+1+sizeof(Alarm));
  
  return from;
}

int EepromAddAlarm(Alarm* a) {   
  int addr = EepromGetEmptyAddress(0, sizeof(Alarm));//TODO MEHDI : REPLACE 0 BY CST
  
  if(addr == -1) 
    return -1;
  else if((addr + sizeof(Alarm)) <= EEPROM_SIZE){
    //Add Alarm To Map
    gv_Alarms[a->alarm.Order] = *a;
    return EepromWrite(a, addr);
  }
    
  return -1;
}


int EepromRead(Alarm *a, int addr) {
  int r = 1;
  
  for (int i = 0; i < sizeof(Alarm); i++)
  {
    a->rawAlarm[i] = EEPROM.read(addr + i);
    //Serial.print("read = ");
    //Serial.println(int(a->rawAlarm[i]));
  }
  
  return r;
}

int EepromLoadAlarm() { 

  Alarm a;
  int r = 1;
  
  for(int i = 0; i < NBR_ALARM; i+= sizeof(Alarm)){
    EepromRead(&a, i);
    gv_Alarms[a.alarm.Order] = a;
  }

  return r;
}

 
