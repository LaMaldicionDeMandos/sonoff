#include "leds.h"

Leds::Leds() {
}

void Leds::on_red() {
  digitalWrite(STATE_OUTPUT_RED_PIN, LED_H);
}

void Leds::off_red() {
  digitalWrite(STATE_OUTPUT_RED_PIN, LED_L);
}

void Leds::on_green() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, LED_H);
}

void Leds::off_green() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, LED_L);
}

void Leds::on_blue() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, LED_H);
}

void Leds::off_blue() {
  digitalWrite(STATE_OUTPUT_BLUE_PIN, LED_L);
}

void Leds::nothing() {}

void Leds::reset() {
  Leds::off_red();
  Leds::off_green();
  Leds::off_blue();
}