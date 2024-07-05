#include "pairing_mode.h"

AsyncWebServer serverPairing(PAIRING_SERVER_PORT);

void PairingMode::handleRoot(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  const String body = parsePostBody(data, len);
  Serial.println("Body: " + body);
  this->persistenceService->saveNetConfig(body);
  const String config = this->persistenceService->readNetConfig();
  JsonDocument doc;
  deserializeJson(doc, config);
  const String response = "{\n  \"udp_broadcast_port\": " + String(UDP_BROADCAST_PORT) + "\n}"; 
  request->send(201, "application/json", response);
  this->persistenceService->saveMode(DISCOVERING_MODE);
}

PairingMode::PairingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void PairingMode::setup() {
  Serial.println("Setup Pairing Mode");
  WiFi.softAP(APSSID, APPSK);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  serverPairing.on("/", HTTP_POST, 
    [](AsyncWebServerRequest *request){}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    this->handleRoot(request, data, len, index, total); 
  });
  serverPairing.begin();
  Serial.println("HTTP server started");
  this->ledsScene.setup();
}

void PairingMode::loop() {
  ledsScene.loop();
}

void PairingMode::end() {
  Serial.println("Ending Pairing mode");
  serverPairing.end();
}
