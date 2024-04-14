#ifndef PERSISTEN_SERVICE_H
#define PERSISTEN_SERVICE_H

#include <EEPROM.h>

using namespace std;

#define ROM_MEMORY_SIZE 512
#define MODE_ADDRESS 0x0

class PersistenceService {
public:

private:
  uint8_t readByteFromEEPROM(int address);
  void saveByteToEEPROM(int address, uint8_t value);

public:
  uint8_t readMode();
  void saveMode(uint8_t mode);
  void setup();
};

#endif //PERSISTEN_SERVICE_H