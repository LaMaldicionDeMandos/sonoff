#include "pairing_mode.h"

ESP8266WebServer server(PAIRING_SERVER_PORT);

void on() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, H);
}

void off() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

void wait() {}

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

PairingMode::PairingMode() {}

void PairingMode::setup() {
  Serial.println("Setup Pairing Mode");
  WiFi.softAP(APSSID, APPSK);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
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
  AsyncTask* on500 = new AsyncTask(100, on);
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
  server.handleClient();
}
