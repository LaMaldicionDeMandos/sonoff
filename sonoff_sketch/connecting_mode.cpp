#include "connecting_mode.h"

ESP8266WiFiMulti WiFiMulti;

void on_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

void wait_c() {}

String getSettingProperty(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readConfig();
  JsonDocument doc;
  deserializeJson(doc, networkSetting);
  return doc[propertyName];
}

ConnectingMode::ConnectingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

String ConnectingMode::getSSID() {
  return getSettingProperty(this->persistenceService, "ssid");
}

String ConnectingMode::getPassword() {
  return getSettingProperty(this->persistenceService, "password");
}

void ConnectingMode::handleRoot() {
}

void ConnectingMode::setup() {
  Serial.println("Setup Connecting Mode");
  const String ssid = this->getSSID();
  Serial.println("SSID: " + ssid);
  const String password = this->getPassword();
  Serial.println("Password: " + password);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.broadcastIP());

}

void ConnectingMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);

  AsyncTask* on500 = new AsyncTask(500, on_c);
  AsyncTask* off1000 = new AsyncTask(500, off_c);

  on500->concat(off1000);

  this->task = on500;
  this->task->start();  
}

void ConnectingMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
  if (WiFi.status() == WL_CONNECTED) {
  }
  //server.handleClient();
}
