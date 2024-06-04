#ifndef PAIRING_MODE_H
#define PAIRING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

#include "asyncTask.h"
#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"

using namespace std;

#define APSSID "IoTProject"
#define APPSK ""
#define PAIRING_SERVER_PORT 80

class PairingMode : public SonoffMode {

public:
  PairingMode(PersistenceService* persistenceService);
private:
  AsyncTask* task;
  PersistenceService* persistenceService;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void initLoop();
  void handleRoot();
};
#endif //PAIRING_MODE_H