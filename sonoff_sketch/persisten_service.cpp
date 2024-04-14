#include "persisten_service.h"

uint8_t PersistenceService::readByteFromEEPROM(int address) {
  return EEPROM.read(address);
}

void PersistenceService::saveByteToEEPROM(int address, uint8_t value) {
  EEPROM.write(address, value);
  EEPROM.commit();
}

void PersistenceService::setup() {
    EEPROM.begin(ROM_MEMORY_SIZE);
}

uint8_t PersistenceService::readMode() {
  return readByteFromEEPROM(MODE_ADDRESS);
}

void PersistenceService::saveMode(uint8_t mode) {
  saveByteToEEPROM(MODE_ADDRESS, mode);
}