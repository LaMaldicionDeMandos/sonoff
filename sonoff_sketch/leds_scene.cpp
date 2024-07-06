#include "leds_scene.h"

void LedsScene::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}