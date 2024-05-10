#include "persisten_service.h"

uint8_t PersistenceService::readByteFromEEPROM(int address) {
  return EEPROM.read(address);
}

void PersistenceService::saveByteToEEPROM(int address, uint8_t value) {
  EEPROM.write(address, value);
  EEPROM.commit();
}

uint32_t PersistenceService::readIntFromEEPROM(int address) {
  uint32_t value = (uint32_t)EEPROM.read(address) |
               ((uint32_t)EEPROM.read(address + 1) << 8) |
               ((uint32_t)EEPROM.read(address + 2) << 16) |
               ((uint32_t)EEPROM.read(address + 3) << 24);
  return value;
}

void PersistenceService::saveIntToEEPROM(int address, uint32_t value) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, (value >> 8) & 0xFF);
  EEPROM.write(address + 2, (value >> 16) & 0xFF);
  EEPROM.write(address + 3, (value >> 24) & 0xFF);
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

uint8_t PersistenceService::readSwitch() {
  return readByteFromEEPROM(SWITCH_ADDRESS);
}

void PersistenceService::saveSwitch(uint8_t value) {
  saveByteToEEPROM(SWITCH_ADDRESS, value);
}

String PersistenceService::readConfig() {
  uint32_t size = readIntFromEEPROM(CONFIG_LENGTH_ADDRESS);
  Serial.println("Config size: " + String(size));
  String text = String();
  for(uint32_t i = 0; i < size; i++) {
    text+= (char)readByteFromEEPROM(CONFIG_ADDRESS + i);
  }
  Serial.println("Config: " + text);
  return text;
}
void PersistenceService::saveConfig(String config) {
  uint32_t size = config.length();
  saveIntToEEPROM(CONFIG_LENGTH_ADDRESS, size);
  for (uint32_t i = 0; i < size; i++) {
    saveByteToEEPROM(CONFIG_ADDRESS + i, config.charAt(i));
  }
}