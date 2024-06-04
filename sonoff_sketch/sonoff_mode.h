#ifndef SONOFF_MODE_H
#define SONOFF_MODE_H

using namespace std;

class SonoffMode {
public:
  SonoffMode() {}

public:
  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual void end() = 0;
};

#endif //SONOFF_MODE_H