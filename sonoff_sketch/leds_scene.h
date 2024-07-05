#ifndef LEDS_SCENE_H
#define LEDS_SCENE_H

#include <arduino.h>
#include <stdint.h>

#include "asyncTask.h"
#include "board_constants.h"
#include "utils.h"
#include "leds.h"

using namespace std;

class LedsScene {
private:

public:
  virtual void setup() = 0;
  virtual void loop() = 0;

private:
};
#endif //LEDS_H