#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NeoPixelBus.h>
#include <ESP8266HTTPClient.h>
#include <Streaming.h>


const char* ssid = "vladiHome";
const char* password = "0888414447";

ESP8266WebServer server(80);

const char* www_username = "vladiHome";
const char* apiKey = "Qw8rdb20aV";
//http://randomkeygen.com/
NeoPixelBus strip = NeoPixelBus(4, 1);
NeoPixelAnimator anim = NeoPixelAnimator(&strip);
#define colorSaturation 255
RgbColor red =    RgbColor(255, 0, 0);
RgbColor pink =   RgbColor(255, 0, 128);
RgbColor lila =   RgbColor(255, 0, 255);
RgbColor violet = RgbColor(128, 0, 255);
RgbColor blue =   RgbColor(0, 0, 255);
RgbColor mblue =  RgbColor(0, 128, 255);
RgbColor cyan =   RgbColor(0, 255, 255);
RgbColor green =  RgbColor(0, 255, 0);
RgbColor yellow = RgbColor(255, 255, 0);
RgbColor orange = RgbColor(255, 100, 0);
RgbColor white = RgbColor(colorSaturation);
RgbColor black = RgbColor(0);

void setShineColor(String color) {
  RgbColor c = yellow;
  if (color == "red") c = red;
  else if (color == "blue") c = blue;
  else if (color == "green") c = green;
  else if (color == "yellow") c = yellow;
  else if (color == "orange") c = orange;
  else if (color == "white") c = white;
  else if (color == "black") c = black;
  else if (color == "pink") c = pink;
  else if (color == "lila") c = lila;
  else if (color == "violet") c = violet;
  else if (color == "mblue") c = mblue;
  else if (color == "cyan") c = cyan;

  anim.FadeTo(1000, c);
  //for (int i=0; i<4; i++) strip.SetPixelColor(i, c);
  //strip.Show();    
}

void shine() {
  if (!server.hasArg("key") || server.arg("key") != apiKey) {
    server.send(401, "text/plain", "missing key");
    return;
  }

  if (server.hasArg("color")) {
    setShineColor(server.arg("color"));
  }
  
  server.send(200, "text/plain", "color set");
}

int sendPing() {
  HTTPClient http;
  http.begin("http://ping.eu/");
  http.sendRequest("HEAD", (uint8_t*)"", 0);

  //302 - no connection
  //200 - connection ok
}

String getTalkback(String tbID, String tbKey) {
  Serial << "getting Talkback" << endl;
  HTTPClient http;
  http.begin(String("http://api.thingspeak.com/talkbacks/") + tbID + "/commands/execute?api_key=" + tbKey);
  //int rc = http.GET();
  int rc = http.sendRequest("HEAD", (uint8_t*)"", 0);
  Serial << "response = " << rc << endl;
  if (rc >0) Serial << " >> " << http.getString();
  Serial << "1 " << ESP.getFreeHeap() << endl;
  Serial << "2 "<< ESP.getFreeHeap() << endl;
  Serial << "3 "<< ESP.getFreeHeap() << endl;
  Serial << "4 "<< ESP.getFreeHeap() << endl;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("\n\nWiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }

  server.on("/shine", shine); 
  server.begin();

  Serial.print("\n\nOpen http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
  strip.Begin();
//
  sendPing();
  Serial << ESP.getFreeHeap() << endl;
  delay(1000);
  sendPing();
  Serial << ESP.getFreeHeap() << endl;
  delay(1000);
  sendPing();
  Serial << ESP.getFreeHeap() << endl;
  delay(1000);
  sendPing();
  Serial << ESP.getFreeHeap() << endl;
  delay(1000);
  sendPing();
  Serial << ESP.getFreeHeap() << endl;
  delay(1000);
//  getTalkback("4527", "D7I11XXEVF2PSIAC");
//  Serial << ESP.getFreeHeap() << endl;
//  delay(1000);
//  getTalkback("4527", "D7I11XXEVF2PSIAC");
//  Serial << ESP.getFreeHeap() << endl;
//  delay(1000);
//  getTalkback("4527", "D7I11XXEVF2PSIAC");
//  Serial << ESP.getFreeHeap() << endl;
//  delay(1000);
//  getTalkback("4527", "D7I11XXEVF2PSIAC");
//  Serial << ESP.getFreeHeap() << endl;
//  delay(1000);
}

void loop() {
  server.handleClient();
  while (anim.IsAnimating())  {
        anim.UpdateAnimations();
        strip.Show();
        delay(31); // ~30hz change cycle
    }
  getTalkback("4527", "D7I11XXEVF2PSIAC");
  delay(5000);
}
