#include "asyncTask.h"

AsyncTask::AsyncTask(uint64_t delay, TaskFunction func) {
  this->delay = delay;
  this->func = func;
  this->next = nullptr;
}

void AsyncTask::start(uint64_t currentTime) {
  this->startTime = currentTime;
}

void AsyncTask::start() {
  this->start(millis());
}

AsyncTask* AsyncTask::update() {
  uint64_t current = millis();
  if ((current - this->startTime) >= this->delay) {
    this->func();
    if (next) {
      this->next->start(this->startTime + this->delay);
      AsyncTask* n = this->next;
      delete this;
      return n;
    } else {
      return nullptr;
    }
  }
  return this;
}

AsyncTask* AsyncTask::concat(AsyncTask* task) {
  this->next = task;
  return this;
}