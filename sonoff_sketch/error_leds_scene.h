#ifndef ERROR_LEDS_SCENE_H
#define ERROR_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class ErrorLedsScene : public LedsScene {

public:
  ErrorLedsScene();
private:
  AsyncTask* task;

public:
  void setup() override;
  void loop() override;

private:
  void initLoop();
};
#endif //ERROR_LEDS_SCENE_H