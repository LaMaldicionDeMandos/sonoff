#include "pairing_leds_scene.h"

PairingLedsScene::PairingLedsScene() {}

void PairingLedsScene::setup() {
  Leds::reset();
}

void PairingLedsScene::initLoop() {
  Leds::reset();

  AsyncTask* on100 = new AsyncTask(100, Leds::on_blue);
  AsyncTask* off200 = new AsyncTask(100, Leds::off_blue);
  AsyncTask* on300 = new AsyncTask(100, Leds::on_blue);
  AsyncTask* off400 = new AsyncTask(100, Leds::off_blue);
  AsyncTask* on500 = new AsyncTask(200, Leds::on_blue);
  AsyncTask* off1000 = new AsyncTask(500, Leds::off_blue);
  AsyncTask* wait1400 = new AsyncTask(400, Leds::nothing);

  on100->concat(off200);
  off200->concat(on300);
  on300->concat(off400);
  off400->concat(on500);
  on500->concat(off1000);
  off1000->concat(wait1400);

  this->task = on100;
  this->task->start();  
}

void PairingLedsScene::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
}