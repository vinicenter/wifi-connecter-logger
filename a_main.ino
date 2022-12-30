#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define ONBOARD_LED  2

AsyncWebServer server(80);

char* ssid;
char* password;
char* wifiMode = "ap";

const char* ssidAP = "ESP32-Connect-Logger";
const char* apiurl = "http://10.1.0.60:3001/device/65944d48-c734-4b47-b380-32f076ff517a/save";

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);

  pinMode(ONBOARD_LED,OUTPUT);

  setWifiAp();
  // setWifiStation();

  startHttpServer();
}

void loop() {
  if(wifiMode == "ap") {
    delay(1000);
    digitalWrite(ONBOARD_LED, HIGH);
    delay(1000);
    digitalWrite(ONBOARD_LED, LOW);
  } else {
    digitalWrite(ONBOARD_LED, HIGH);
  }
}
