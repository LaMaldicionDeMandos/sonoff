#ifndef PAIRING_MODE_H
#define PAIRING_MODE_H

#include <arduino.h>
#include <stdint.h>
#include "asyncTask.h"
#include "sonoff_mode.h"
#include "board_constants.h"

using namespace std;

class PairingMode : public SonoffMode {

public:
  PairingMode();
private:
  AsyncTask* task;

public:
  void setup() override;
  void loop() override;

private:
  void initLoop();
};
#endif //PAIRING_MODE_H