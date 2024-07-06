#ifndef PAIRING_LEDS_SCENE_H
#define PAIRING_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class PairingLedsScene : public LedsScene {

public:
  PairingLedsScene();

private:
  void initLoop() override;
};
#endif //PAIRING_LEDS_SCENE_H