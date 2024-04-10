
#include <EEPROM.h>

#define mode_t uint8_t

#define L 1
#define H 0

#define ROM_MEMORY_SIZE 512
#define MODE_ADDRESS 0x0

#define PAIRING_MODE 1

typedef void (*ModeFunction)();

mode_t mode = 1;

/* Util functions ********************/
uint8_t readValueFromEEPROM(int address) {
  return EEPROM.read(address);
}

void saveValueToEEPROM(int address, uint8_t value) {
  EEPROM.write(address, value);
  EEPROM.commit();
}

/* Setup Functions *****************/
bool isValidMode(mode_t mode) {
  return mode == PAIRING_MODE;
}

void setupMode() {
  mode = readValueFromEEPROM(MODE_ADDRESS);
  if (!isValidMode(mode)) mode = PAIRING_MODE;
  saveValueToEEPROM(MODE_ADDRESS, mode);
}

void printCurrentMode(mode_t mode) {
  if (PAIRING_MODE == mode) {
    Serial.println("PAIRING MODE...");
  }
}

/* Pairing mode Function ***************/
void pairingModeLoop() {
  digitalWrite(LED_BUILTIN, L);
  delay(2000);
  digitalWrite(LED_BUILTIN, H);
  delay(100);
  digitalWrite(LED_BUILTIN, L);
  delay(100);                      
  digitalWrite(LED_BUILTIN, H);
  delay(100);
  digitalWrite(LED_BUILTIN, L);
  delay(500);
  digitalWrite(LED_BUILTIN, H);  
  delay(500);                 
  digitalWrite(LED_BUILTIN, L);
  printCurrentMode(mode);
}

/* Main loop functions ****************/
ModeFunction selectMode(mode_t mode) {
  if (PAIRING_MODE == mode) {
    return &pairingModeLoop;
  }
  return 0;
}

void setup() {
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  EEPROM.begin(ROM_MEMORY_SIZE);
  Serial.begin(115200);
  Serial.println();
  setupMode();
  digitalWrite(LED_BUILTIN, L);
}

void loop() {
  ModeFunction modeLoop = selectMode(mode);
  modeLoop();
}
