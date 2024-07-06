#ifndef CONFIG_LEDS_SCENE_H
#define CONFIG_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class ConfigLedsScene : public LedsScene {

public:
  ConfigLedsScene();

private:
  void initLoop() override;
};
#endif //CONFIG_LEDS_SCENE_H