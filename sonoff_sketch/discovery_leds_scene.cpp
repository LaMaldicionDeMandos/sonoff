#include "discovery_leds_scene.h"

DiscoveryLedsScene::DiscoveryLedsScene() {}

void DiscoveryLedsScene::initLoop() {  
  Leds::reset();

  AsyncTask* on500 = new AsyncTask(500, Leds::on_green);
  AsyncTask* off1000 = new AsyncTask(500, Leds::off_green);

  on500->concat(off1000);

  this->task = on500;
  this->task->start();
}
