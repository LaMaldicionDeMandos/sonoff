#include "switch_manager_module.h"

SwitchManager::SwitchManager(PersistenceService persistenceService) {
  this->persistenceService = persistenceService;
  this->switchValue = L;
  this->buttonPressed = L;
}


void SwitchManager::setup() {
  this->switchValue = this->persistenceService.readSwitch();
  digitalWrite(RELAY_STATE_PIN, this->switchValue);
}

void SwitchManager::loop() {
  uint8_t buttonStatus = digitalRead(RELAY_SWITCH_PIN);
  if(buttonStatus == H && this->buttonPressed == L) {
    this->buttonPressed = H;
    Serial.println("Button Pressed");
    //TODO Meter la logica de persistir el estado
  }
  if (buttonStatus == L) {
    this->buttonPressed = L;
  }
}
