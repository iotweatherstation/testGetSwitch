// project: IoT Weather Station, EAFIT University, Systems Engineering, 20171
// Adaptation done by: Edwin Montoya Munera - emontoya@eafit.edu.co , David Velasquez - dvelas25@eafit.edu.co and Alexander Acosta Jimenez - aacosta8@eafit.edu.co
// github: https://github.com/iotweatherstation/iotws-testGetSwitch.git

// Description: This program test the connection to the server "iotweatherstation" in order to obtain the LED's status
// the connection is done throught Wifi network and HTTP Connection. It uses GET Method.

// Libraries

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

// Wifi module from Chipset
ESP8266WiFiMulti WiFiMulti;

//Constants
const unsigned long SEND_Timer = 5000;  //Delay between SEND variables, 5000 milliseconds - 5 seconds
const char* SSID = "wifi-name"; //WiFi SSID, change wifi-name by your own
const char* PASSWORD = "wifi-password"; //WiFi Pass, change wifi-password by your own
const char* HOST = "http://server";  // //REST Web Host, replace by real server url

String appName = "/weather";
String serviceGetStatus = "/service"; // replace by real server service
String idhome = "idhome"; //Replace by your own idhome
unsigned long lastConnectionTime = 0; //Last time you connected to the server, in milliseconds


String webGetSwitch() {
  // variables:
  HTTPClient http;
  String url;
  int httpCode;
  String payload;

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    url = appName;
    url += serviceGetStatus;
    url += "?idhome=";
    url += idhome;
    http.begin(HOST + url);
    Serial.print(HOST + url);
    httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        Serial.println(payload);
      }
    }
    http.end();
    return payload;
  }
}

void setup() {

  Serial.begin(9600);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP(SSID, PASSWORD);

}

void loop() {

  if (millis() - lastConnectionTime > SEND_Timer) {
    int statusLed = webGetSwitch().toInt(); 
    Serial.println(statusLed);
    lastConnectionTime = millis();
  }
}
