#ifndef DISCOVERY_LEDS_SCENE_H
#define DISCOVERY_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class DiscoveryLedsScene : public LedsScene {

public:
  DiscoveryLedsScene();
private:
  AsyncTask* task;

public:
  void setup() override;
  void loop() override;

private:
  void initLoop();
};
#endif //DISCOVERY_LEDS_SCENE_H