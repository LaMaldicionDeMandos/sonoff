#include "pairing_mode.h"

ESP8266WebServer serverPairing(PAIRING_SERVER_PORT);

void on() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, H);
}

void off() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

void wait() {}

void PairingMode::handleRoot() {
  const HTTPMethod method = serverPairing.method();
  if (method == HTTPMethod::HTTP_POST) {
    const String body = serverPairing.arg("plain");
    this->persistenceService->saveConfig(body);
    const String config = this->persistenceService->readConfig();
    JsonDocument doc;
    deserializeJson(doc, config);
    const String response = "{\n  \"udp_broadcast_port\": " + String(UDP_BROADCAST_PORT) + "\n}"; 
    serverPairing.send(201, "application/json", response);
    this->persistenceService->saveMode(DISCOVERING_MODE);
  } else {
    serverPairing.send(400, "text/html", "<h1>Noooo, tenes que mandar un post</h1>");
  }

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
  serverPairing.on("/", std::bind(&PairingMode::handleRoot, this));
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
  serverPairing.handleClient();
}

void PairingMode::end() {
  Serial.println("Ending Pairing mode");
  serverPairing.close();
}
