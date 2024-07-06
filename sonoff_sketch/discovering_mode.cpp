#include "discovering_mode.h"

WiFiUDP Udp;

char packetBuffer[255];

void broadcastWait() {
}

String getSettingProperty(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readNetConfig();
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
  uint8_t ttl = 40;
  while (WiFi.status() != WL_CONNECTED) {
    ttl--;
    Serial.print('.');
    delay(500);
    if (!ttl) {
      this->persistenceService->saveMode(ERROR_MODE);
      return;
    }
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.broadcastIP());
}

void DiscoveringMode::loop() {
  ledsScene.loop();
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
