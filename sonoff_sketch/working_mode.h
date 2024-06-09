#ifndef WORKIGN_MODE_H
#define WORKING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <ArduinoJson.h>

#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"

using namespace std;

class WorkingMode : public SonoffMode {

public:
  WorkingMode(PersistenceService* persistenceService);
private:
  PersistenceService* persistenceService;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
};
#endif //WORKING_MODE_H