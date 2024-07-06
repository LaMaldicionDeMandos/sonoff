#include "error_mode.h"

ErrorMode::ErrorMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void ErrorMode::setup() {
  Serial.println("Setup Error Mode");
}

void ErrorMode::loop() {
  ledsScene.loop();
}

void ErrorMode::end() {
}
