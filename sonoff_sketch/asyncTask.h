#ifndef ASYNC_TASK_H
#define ASYNC_TASK_H

#include <arduino.h>
#include <stdint.h>

using namespace std;

typedef void (*TaskFunction)();

class AsyncTask {
public:
  AsyncTask(uint64_t delay, TaskFunction func);

private:
  uint64_t delay;
  uint64_t startTime;
  TaskFunction func;
  AsyncTask* next;

protected:
  void start(uint64_t currentTime);

public:
  void start();
  AsyncTask* update();
  AsyncTask* concat(AsyncTask* task);
};

#endif //ASYNC_TASK_H