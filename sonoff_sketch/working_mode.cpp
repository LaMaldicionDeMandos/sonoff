#include "working_mode.h"

WorkingMode::WorkingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void WorkingMode::setup() {
  Serial.println("Setup Working Mode"); 
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
  Serial.println(WiFi.localIP());
}

void WorkingMode::loop() {

}

void WorkingMode::end() {
  Serial.println("Ending Working mode");
  WiFi.disconnect();
}
