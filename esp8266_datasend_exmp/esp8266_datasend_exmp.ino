/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
String serverName = "http://192.168.0.6:8000/name/";
String AGE = "/age/";
int age=0;
int namexmp=0;
char link;


void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("123456", "ppap1542xd");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

   
   
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      age=random(1, 100);
      namexmp=random(1, 100);
      delay(100);
      String serverPath = serverName + namexmp + AGE + age;
      if (http.begin(client, serverPath.c_str())) {  // HTTP


        Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
        int httpCode = http.GET();

      // httpCode will be negative on error
        if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.println(serverPath.c_str());
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println(serverPath.c_str());
      Serial.printf("[HTTP} Unable to connect\n");
    }
    
    

    
    
  }

  delay(100);
}
