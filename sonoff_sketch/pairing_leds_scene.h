#ifndef PAIRING_LEDS_SCENE_H
#define PAIRING_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class PairingLedsScene : public LedsScene {

public:
  PairingLedsScene();
private:
  AsyncTask* task;

public:
  void setup() override;
  void loop() override;

private:
  void initLoop();
};
#endif //PAIRING_LEDS_SCENE_H