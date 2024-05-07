#ifndef SWITCh_MANAGER_MODULE_H
#define SWITCh_MANAGER_MODULE_H

#include <arduino.h>
#include <stdint.h>

#include "board_constants.h"
#include "persisten_service.h"

#define MAX_BOUND 5
#define MIN_BOUND 0

using namespace std;

class SwitchManager {
public:
  SwitchManager(PersistenceService persistenceService);

private:
  PersistenceService persistenceService;
  uint8_t switchValue;
  uint8_t buttonPressed;
  uint8_t buttonState;

public:
  void setup();
  void loop();

private:
  void toogle();
  void updateButtonStatus();
  boolean isPushed();
  boolean isNotPushed();
};
#endif //SWITCh_MANAGER_MODULE_H