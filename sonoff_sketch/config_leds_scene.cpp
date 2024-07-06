#include "config_leds_scene.h"

ConfigLedsScene::ConfigLedsScene() {}

void ConfigLedsScene::setup() {
  Leds::reset();
}

void ConfigLedsScene::initLoop() {  
  Leds::reset();

  AsyncTask* on700 = new AsyncTask(700, Leds::on_green);
  AsyncTask* off1400 = new AsyncTask(700, Leds::off_green);

  on700->concat(off1400);

  this->task = on700;
  this->task->start();  
}

void ConfigLedsScene::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}