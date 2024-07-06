#ifndef DISCOVERY_LEDS_SCENE_H
#define DISCOVERY_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class DiscoveryLedsScene : public LedsScene {

public:
  DiscoveryLedsScene();

private:
  void initLoop() override;
};
#endif //DISCOVERY_LEDS_SCENE_H