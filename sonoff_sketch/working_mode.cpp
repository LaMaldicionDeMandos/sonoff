#include "working_mode.h"

void WorkingMode::handleRoot() {
}

WorkingMode::WorkingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void WorkingMode::setup() {
  Serial.println("Setup Working Mode");
}

void WorkingMode::initLoop() {
}

void WorkingMode::loop() {

}
