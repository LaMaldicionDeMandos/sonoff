#include "discovering_mode.h"

void on_d() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_d() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

void sendBroadcast() {
  Serial.println("Send Broadcast message");
}

String getSettingProperty(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readConfig();
  JsonDocument doc;
  deserializeJson(doc, networkSetting);
  return doc[propertyName];
}

DiscoveringMode::DiscoveringMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

String DiscoveringMode::getSSID() {
  return getSettingProperty(this->persistenceService, "ssid");
}

String DiscoveringMode::getPassword() {
  return getSettingProperty(this->persistenceService, "password");
}

void DiscoveringMode::handleRoot() {
}

void DiscoveringMode::setup() {
  Serial.println("Setup Discovering Mode");
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

void DiscoveringMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);

  AsyncTask* on500 = new AsyncTask(500, on_d);
  AsyncTask* off1000 = new AsyncTask(500, off_d);

  on500->concat(off1000);

  this->task = on500;
  this->task->start();  
}

void DiscoveringMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
  this->broadcastLoop();
}

void DiscoveringMode::broadcastLoop() {
  if (WiFi.status() == WL_CONNECTED) {
    if(this->broadcastTask == nullptr) {
      Serial.println("Init Broadcast sending");
      this->broadcastTask = new AsyncTask(1000, sendBroadcast);
      this->broadcastTask->start();
    }  else {
      this->broadcastTask = this->broadcastTask->update();
    }
  }
}

void DiscoveringMode::end() {
  Serial.println("Ending discoverying mode");
  WiFi.disconnect();
}
