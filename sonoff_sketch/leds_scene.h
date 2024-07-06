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
protected:
  AsyncTask* task;

public:
  void loop();

protected:
  virtual void initLoop() = 0;

private:
};
#endif //LEDS_H