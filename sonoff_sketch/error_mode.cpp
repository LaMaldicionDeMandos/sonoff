#include "error_mode.h"

void wait_error_mode() {}

void on_e() {
  digitalWrite(STATE_OUTPUT_RED_PIN, LED_H);
}

void off_e() {
  digitalWrite(STATE_OUTPUT_RED_PIN, LED_L);
}

ErrorMode::ErrorMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void ErrorMode::setup() {
  Serial.println("Setup Error Mode");
}

void ErrorMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, LED_L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, LED_L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, LED_L);

  AsyncTask* on500 = new AsyncTask(500, on_e);
  AsyncTask* off1000 = new AsyncTask(500, off_e);

  on500->concat(off1000);

  this->task = on500;
  this->task->start();
}

void ErrorMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}

void ErrorMode::end() {
}
