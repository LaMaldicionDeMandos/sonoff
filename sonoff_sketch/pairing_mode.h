#ifndef PAIRING_MODE_H
#define PAIRING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>

#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"
#include "utils.h"
#include "pairing_leds_scene.h"

using namespace std;

#define APSSID "IoTProject"
#define APPSK ""
#define PAIRING_SERVER_PORT 80

class PairingMode : public SonoffMode {

public:
  PairingMode(PersistenceService* persistenceService);
private:
  PersistenceService* persistenceService;
  PairingLedsScene ledsScene;  

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void handleRoot(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
};
#endif //PAIRING_MODE_H