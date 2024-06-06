#include "board_constants.h"
#include "pairing_mode.h"
#include "discovering_mode.h"
#include "config_mode.h"
#include "persisten_service.h"
#include "switch_manager_module.h"

#define mode_t uint8_t

#define SPEED 115200

PersistenceService persistenceService;
SwitchManager switchManager = SwitchManager(&persistenceService);

mode_t mode = PAIRING_MODE;

PairingMode pairingMode = PairingMode(&persistenceService);
DiscoveringMode discoveringMode = DiscoveringMode(&persistenceService);
ConfigMode configMode = ConfigMode(&persistenceService);
SonoffMode* currentMode;
mode_t currentModeType;

bool isValidMode(mode_t mode) {
  return mode == PAIRING_MODE || mode == DISCOVERING_MODE || mode == CONFIG_MODE;
}

SonoffMode* selectMode(mode_t mode) {
  SonoffMode* modeSetup = nullptr;
  if (mode == PAIRING_MODE) modeSetup = &pairingMode;
  if (mode == DISCOVERING_MODE) modeSetup = &discoveringMode;
  if (mode == CONFIG_MODE) modeSetup = &configMode;
  return modeSetup;
}

SonoffMode* setupMode() {
  SonoffMode* modeSetup = &pairingMode;
  mode = persistenceService.readMode();
  Serial.println("Saved Mode: " + String(mode));
  if (!isValidMode(mode)) {
    mode = PAIRING_MODE;
    persistenceService.saveMode(mode);
  } else {
    modeSetup = selectMode(mode);
  }
  currentModeType = mode;
  return modeSetup;
}

void setupMemory() {
  persistenceService.setup();
}

void setupOutput() {
  pinMode(STATE_OUTPUT_RED_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_GREEN_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_BLUE_PIN, OUTPUT);

  pinMode(RELAY_STATE_PIN, OUTPUT);
  pinMode(RELAY_SWITCH_PIN, INPUT);
  
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

void setup() {
  delay(1000);
  Serial.begin(SPEED);
  setupOutput();
  setupMemory();
  currentMode = setupMode();
  currentMode->setup();
  switchManager.setup();
}

void loop() {
  mode_t modeType = persistenceService.readMode();
  if (currentModeType != modeType) {
    currentMode->end();
    delay(500);
    currentMode = setupMode();
    currentMode->setup();
  }
  if (currentMode != nullptr) {
    currentMode->loop();
  }
  switchManager.loop();
}
