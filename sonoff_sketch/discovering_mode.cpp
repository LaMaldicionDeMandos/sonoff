#include "discovering_mode.h"

WiFiUDP Udp;

char packetBuffer[255];

void on_d() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_d() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

void broadcastWait() {
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
        this->sendBroadcast();
    }  else {
        this->listeningAck();
    }
  }
}

void DiscoveringMode::sendBroadcast() {
  this->broadcastTask = new AsyncTask(2000, broadcastWait);
  this->broadcastTask->start();
  Serial.println("Send Broadcast message");
  Udp.beginPacket(WiFi.broadcastIP(), UDP_BROADCAST_PORT);
  Udp.write(BROADCAST_MESSAGE);
  Udp.endPacket();
  Udp.begin(Udp.localPort());
}

void DiscoveringMode::listeningAck() {
  this->broadcastTask = this->broadcastTask->update();
  if (Udp.parsePacket()) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
      this->processAck(packetBuffer);
    }
  }
}

void DiscoveringMode::processAck(String message) {
  Serial.println(message);
  if (isACK(packetBuffer)) {
    this->persistenceService->saveMode(CONFIG_MODE);
  }
}

bool DiscoveringMode::isACK(String message) {
  return String(ACK_MESSAGE).equals(message);
}

void DiscoveringMode::end() {
  Serial.println("Ending discoverying mode");
  WiFi.disconnect();
}
