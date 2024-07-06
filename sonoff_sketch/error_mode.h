#ifndef ERROR_MODE_H
#define ERROR_MODE_H

#include <arduino.h>
#include <stdint.h>

#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"
#include "utils.h"
#include "error_leds_scene.h"

using namespace std;

class ErrorMode : public SonoffMode {

public:
  ErrorMode(PersistenceService* persistenceService);
private:
  PersistenceService* persistenceService;
  ErrorLedsScene ledsScene;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void initLoop();
};
#endif //ERROR_MODE_H