#include <ESP8266WiFi.h>
#include <Streaming.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "vladiHome";
const char* password = "0888414447";
const char* sap_user = "vladiHome";
const char* sap_pass = "0888414447";

void setup() {
  Serial.begin(115200);
  initWifi();
  setupWebServer();
  initLight();

    processCommand(String("red"));
    delay(5000);
    processCommand(String("blue"));
}

void loop() {
  handleWebServer();
  handleAnimation();
  checkTalkback();
}
