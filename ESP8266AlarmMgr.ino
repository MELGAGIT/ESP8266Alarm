#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ESPEeprom.h"
#include "Rtc.h"
#include <FS.h>
#include <map>

#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

#define LED_BUILTIN 2

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif


/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

AsyncWebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

void handleRoot() {
  //server.send(200, "text/html", "<h1>You are connected</h1>");
}


// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "ALL_ALARMS"){
    return String(getAllAlarms());
  }
  else if (var == "RESET_ALL_ALARMS"){
    clearAllAlarms();
    EepromEraseAll();
    return String(R"({"Response" : "OK"})");
  }
  else if (var == "CURRENT_TIME"){
    return String(RtcCurrent());
  }
  
  /*if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }*/

}

void setup() {
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(115200);

  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  //server.on("/", handleRoot);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("AAAAAAAAAA");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("BBBBBBBBBB");
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    //digitalWrite(ledPin, HIGH);    
    Serial.println("CCCCCCCCCCCC");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.begin();
  Serial.println("HTTP server started");


  RtcInit();
  Serial.print("Time and date set");
  //delay(3000);

  //EepromInit();
  //EepromLoadAlarm();
  //std::string s = getAllAlarms();
  //clearAllAlarms();
  //Serial.println(s.c_str());
  //setAlarm(s);
  //delay(3000);
}

void loop() {  
  DateTime now = RtcNow();
 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  
}

 
 
