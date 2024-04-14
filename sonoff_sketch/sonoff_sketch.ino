#include "board_constants.h"
#include "pairing_mode.h"
#include "persisten_service.h"

#define mode_t uint8_t

#define SPEED 115200

#define PAIRING_MODE 1

PersistenceService persistenceService;

mode_t mode = PAIRING_MODE;

PairingMode pairingMode;
SonoffMode* currentMode;

bool isValidMode(mode_t mode) {
  return mode == PAIRING_MODE;
}

SonoffMode* setupMode() {
  SonoffMode* modeSetup = &pairingMode;
  mode = persistenceService.readMode();
  if (!isValidMode(mode)) mode = PAIRING_MODE;
  persistenceService.saveMode(mode);
  return modeSetup;
}

void setupMemory() {
  persistenceService.setup();
}

void setupOutput() {
  pinMode(STATE_OUTPUT_RED_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_GREEN_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_BLUE_PIN, OUTPUT);
  
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

void setup() {
  delay(1000);
  Serial.begin(SPEED);
  setupOutput();
  currentMode = setupMode();
  currentMode->setup();
}

void loop() {
  if (currentMode != nullptr) {
    currentMode->loop();
  }
}
