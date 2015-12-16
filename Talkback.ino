unsigned long lastTickCheck = 0;

boolean timePassed(unsigned long *since, unsigned long interval) {
  bool resp = (unsigned long)(millis() - *since) > interval;
  if (resp) *since = millis();
  return resp;
}

void checkTalkback() {
  if (timePassed(&lastTickCheck, 15000)) {
    String tb = getTalkback("4527", "D7I11XXEVF2PSIAC");
    tb.trim();
    if (tb.length() > 0) processCommand(tb);
  }
}

String getTalkback(String tbID, String tbKey) {  
  HTTPClient http;
  http.begin(String("http://api.thingspeak.com/talkbacks/") + tbID + "/commands/execute?api_key=" + tbKey);
  int rc = http.GET();
  if (rc == 200) return handleChunks(http.getString());
  else {
    Serial << rc << " " << http.getString() << endl; ;
    return "";
  }
}

String handleChunks(String data) {
  int s = data.indexOf('\n');
  int e = data.indexOf('\n', s+1);
  return data.substring(s+1, e-1);
}

