#ifndef CONNECTING_MODE_H
#define CONNECTING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

#include <ArduinoJson.h>

#include "asyncTask.h"
#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"

#define BROADCAST_PORT

using namespace std;

class ConnectingMode : public SonoffMode {

public:
  ConnectingMode(PersistenceService* persistenceService);
private:
  AsyncTask* task;
  PersistenceService* persistenceService;

public:
  void setup() override;
  void loop() override;

private:
  void initLoop();
  void handleRoot();
  String getSSID();
  String getPassword();
};
#endif //CONNECTING_MODE_H