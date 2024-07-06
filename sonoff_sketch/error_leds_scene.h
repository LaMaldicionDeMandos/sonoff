#ifndef ERROR_LEDS_SCENE_H
#define ERROR_LEDS_SCENE_H

#include "leds_scene.h"

using namespace std;

class ErrorLedsScene : public LedsScene {

public:
  ErrorLedsScene();

private:
  void initLoop() override;
};
#endif //ERROR_LEDS_SCENE_H