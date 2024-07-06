#include "error_leds_scene.h"

ErrorLedsScene::ErrorLedsScene() {}

void ErrorLedsScene::setup() {
  Leds::reset();
}

void ErrorLedsScene::initLoop() {  
  Leds::reset();

  AsyncTask* on500 = new AsyncTask(500, Leds::on_red);
  AsyncTask* off1000 = new AsyncTask(500, Leds::off_red);

  on500->concat(off1000);

  this->task = on500;
  this->task->start();  
}

void ErrorLedsScene::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}