#include "connecting_mode.h"
void on_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

void wait_c() {}

void ConnectingMode::handleRoot() {
}

ConnectingMode::ConnectingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void ConnectingMode::setup() {
  Serial.println("Setup Connecting Mode");
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
  //server.handleClient();
}
