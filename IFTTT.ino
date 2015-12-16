#include <ESP8266WebServer.h>

const char* apiKey = "Qw8rdb20aV";
//http://randomkeygen.com/

ESP8266WebServer server(80);

void handleWebServer() {
   server.handleClient();
}

void setupWebServer() {
  server.on("/shine", shine); 
  server.begin();

  Serial.print("\n\nOpen http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
}

void shine() {
  if (!server.hasArg("key") || server.arg("key") != apiKey) {
    server.send(401, "text/plain", "missing key");
    return;
  }

  if (server.hasArg("color")) {
    processCommand(server.arg("color"));
  }
  
  server.send(200, "text/plain", "color set");
}
