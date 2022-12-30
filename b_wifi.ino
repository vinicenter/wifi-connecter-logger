void setWifiAp() {
  WiFi.disconnect();
  WiFi.softAP(ssidAP, "");

  wifiMode = "ap";

  digitalWrite(ONBOARD_LED, LOW);

  Serial.print('wifi is in ap mode');
}

void setWifiStation() {
  WiFi.disconnect();

  Serial.println("Connecting to WiFi network: ");
  Serial.println(ssid);
  Serial.println(password);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(100);
    digitalWrite(ONBOARD_LED, HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED, LOW);
  }

  if(WiFi.status() == WL_CONNECTED) {
    wifiMode = "station";
    Serial.println("wifi is in station mode");
    WiFi.softAPdisconnect(true);
  }
}
