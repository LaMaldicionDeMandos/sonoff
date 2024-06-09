#ifndef SONOFF_UTILS_H
#define SONOFF_UTILS_H

#include <arduino.h>

using namespace std;

String parsePostBody(uint8_t *data, size_t len);

#endif //SONOFF_UTILS_H