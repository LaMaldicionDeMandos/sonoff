#ifndef SWITCh_MANAGER_MODULE_H
#define SWITCh_MANAGER_MODULE_H

#include <arduino.h>
#include <stdint.h>

#include "board_constants.h"
#include "persisten_service.h"

using namespace std;

class SwitchManager {
public:
  SwitchManager(PersistenceService persistenceService);

private:
  PersistenceService persistenceService;
  uint8_t switchValue;
  uint8_t buttonPressed;

public:
  void setup();
  void loop();
};
#endif //SWITCh_MANAGER_MODULE_H