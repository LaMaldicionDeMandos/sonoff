#ifndef PERSISTEN_SERVICE_H
#define PERSISTEN_SERVICE_H
#include <arduino.h>

#include <EEPROM.h>

using namespace std;

#define ROM_MEMORY_SIZE 512
#define MODE_ADDRESS 0x0
#define SWITCH_ADDRESS 0x1
#define CONFIG_LENGTH_ADDRESS 0x2
#define CONFIG_LENGTH_MQTT CONFIG_LENGTH_ADDRESS + sizeof(uint32_t)
#define CONFIG_ADDRESS CONFIG_LENGTH_MQTT + sizeof(uint32_t)

class PersistenceService {
public:

private:
  uint8_t readByteFromEEPROM(int address);
  void saveByteToEEPROM(int address, uint8_t value);
  
  uint32_t readIntFromEEPROM(int address);
  void saveIntToEEPROM(int address, uint32_t value);

public:
  void setup();
  
  uint8_t readMode();
  void saveMode(uint8_t mode);
  
  uint8_t readSwitch();
  void saveSwitch(uint8_t value);

  String readNetConfig();
  void saveNetConfig(String config);

  String readMqttConfig();
  void saveMqttConfig(String config);
};

#endif //PERSISTEN_SERVICE_H