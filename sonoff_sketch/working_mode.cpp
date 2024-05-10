#include "working_mode.h"
void on_w() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_w() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

void wait_w() {}

void WorkingMode::handleRoot() {
}

WorkingMode::WorkingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void WorkingMode::setup() {
  Serial.println("Setup Working Mode");
}

void WorkingMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);

  AsyncTask* on100 = new AsyncTask(100, on_w);
  AsyncTask* off600 = new AsyncTask(500, off_w);
  AsyncTask* on1100 = new AsyncTask(500, on_w);
  AsyncTask* off1600 = new AsyncTask(500, off_w);
  AsyncTask* on2100 = new AsyncTask(500, on_w);
  AsyncTask* off2600 = new AsyncTask(500, off_w);
  AsyncTask* wait3000 = new AsyncTask(400, wait_w);

  on100->concat(off600);
  off600->concat(on1100);
  on1100->concat(off1600);
  off1600->concat(on2100);
  on2100->concat(off2600);
  off2600->concat(wait3000);

  this->task = on100;
  this->task->start();  
}

void WorkingMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
  //server.handleClient();
}
