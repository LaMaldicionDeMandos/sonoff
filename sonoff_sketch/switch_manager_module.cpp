#include "switch_manager_module.h"

SwitchManager::SwitchManager(PersistenceService persistenceService) {
  this->persistenceService = persistenceService;
  this->switchValue = L;
  this->buttonPressed = L;
  this->buttonState = MIN_BOUND;
}


void SwitchManager::setup() {
  this->switchValue = this->persistenceService.readSwitch();
  Serial.println("Switch Value: " + String(this->switchValue));
  digitalWrite(RELAY_STATE_PIN, this->switchValue);
}

void SwitchManager::loop() {
  this->updateButtonStatus();
  if (this->isPushed() && this->buttonPressed == L) {
    Serial.println("Button Pressed");
    this->toogle();
    this->buttonPressed = H;
  }
  if (this->isNotPushed() && this->buttonPressed == H) {
    Serial.println("Button Pulled");
    this->buttonPressed = L;
  }
}

void SwitchManager::toogle() {
  if (this->switchValue == L) this->switchValue = H;
  else this->switchValue = L;
  this->persistenceService.saveSwitch(this->switchValue);
  digitalWrite(RELAY_STATE_PIN, this->switchValue);
}

void SwitchManager::updateButtonStatus() {
  uint8_t buttonStatus = digitalRead(RELAY_SWITCH_PIN);
  if (buttonStatus == H && this->buttonState < MAX_BOUND) this->buttonState++;
  if (buttonStatus == L && this->buttonState > MIN_BOUND) this->buttonState--;
}

boolean SwitchManager::isPushed() {
  return this->buttonState == MAX_BOUND;
}

boolean SwitchManager::isNotPushed() {
  return this->buttonState == MIN_BOUND;
}
