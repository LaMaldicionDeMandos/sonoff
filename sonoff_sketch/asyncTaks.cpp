#include "asyncTask.h"

AsyncTask::AsyncTask(uint8_t delay, TaskFunction func) {
  this->delay = delay;
  this->func = func;
  this->active = true;
}

void AsyncTask::start() {
  this->startTime = millis();
}

void AsyncTask::update() {
  if (this-> active == false) return;
  uint8_t current = millis();
  if ((this->startTime - current) > this->delay) {
    this->func();
    this->active = false;
  }
}
bool AsyncTask::isFinished() {
  return !(this->active);
}