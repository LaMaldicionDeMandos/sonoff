#include "utils.h"

String parsePostBody(uint8_t *data, size_t len) {
  char _data[len + 1];
  for(size_t i=0; i<len; i++){
    _data[i] = data[i];
  }
  _data[len] = 0;
  return String(_data);
}