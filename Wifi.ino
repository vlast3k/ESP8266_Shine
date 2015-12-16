#include <vSAP_Auth.h>

void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("\n\nWiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  vSAP_Auth(sap_user, sap_pass);
}
