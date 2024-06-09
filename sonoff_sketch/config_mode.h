#ifndef CONFIG_MODE_H
#define GONFIG_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>

#include "asyncTask.h"
#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"
#include "utils.h"

using namespace std;

#define CONFIG_SERVER_PORT 80

class ConfigMode : public SonoffMode {

public:
  ConfigMode(PersistenceService* persistenceService);
private:
  AsyncTask* task;
  PersistenceService* persistenceService;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void initLoop();
  void handleHttpHealth(AsyncWebServerRequest *request);
  void handlePost(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
  String getSSID();
  String getPassword();
};
#endif //CONFIG_MODE_H