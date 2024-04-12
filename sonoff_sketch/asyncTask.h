#ifndef ASYNC_TASK_H
#define ASYNC_TASK_H

#include <arduino.h>
#include <stdint.h>

using namespace std;

typedef void (*TaskFunction)();

class AsyncTask {
public:
  AsyncTask(uint8_t delay, TaskFunction func);

private:
  uint8_t delay;
  uint8_t startTime;
  TaskFunction func;
  bool active;

public:
  void start();
  void update();
  bool isFinished();
};

#endif //ASYNC_TASK_H