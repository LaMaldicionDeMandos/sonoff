#include "pairing_mode.h"

AsyncWebServer serverPairing(PAIRING_SERVER_PORT);

void on() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, H);
}

void off() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

void wait() {}

void PairingMode::handleRoot(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  char _data[len + 1];
  for(size_t i=0; i<len; i++){
    _data[i] = data[i];
  }
  _data[len] = 0;
  const String body = String(_data);
  Serial.println("Body: " + body);
  this->persistenceService->saveConfig(body);
  const String config = this->persistenceService->readConfig();
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
}

void PairingMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);

  AsyncTask* on100 = new AsyncTask(100, on);
  AsyncTask* off200 = new AsyncTask(100, off);
  AsyncTask* on300 = new AsyncTask(100, on);
  AsyncTask* off400 = new AsyncTask(100, off);
  AsyncTask* on500 = new AsyncTask(200, on);
  AsyncTask* off1000 = new AsyncTask(500, off);
  AsyncTask* wait1400 = new AsyncTask(400, wait);

  on100->concat(off200);
  off200->concat(on300);
  on300->concat(off400);
  off400->concat(on500);
  on500->concat(off1000);
  off1000->concat(wait1400);

  this->task = on100;
  this->task->start();  
}

void PairingMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}

void PairingMode::end() {
  Serial.println("Ending Pairing mode");
  serverPairing.end();
}
