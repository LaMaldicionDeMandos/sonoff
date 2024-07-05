#ifndef LEDS_H
#define LEDS_H

#include <arduino.h>
#include <stdint.h>

#include "asyncTask.h"
#include "board_constants.h"
#include "utils.h"

using namespace std;

class Leds {

public:
  Leds();
private:

public:
  static void reset();
  static void on_red();
  static void on_green();
  static void on_blue();
  static void off_red();
  static void off_green();
  static void off_blue();
  static void nothing();  

private:
};
#endif //LEDS_H