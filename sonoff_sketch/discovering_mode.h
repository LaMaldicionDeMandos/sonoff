#ifndef DISCOVERING_MODE_H
#define DISCOVERING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

#include <ArduinoJson.h>

#include "asyncTask.h"
#include "sonoff_mode.h"
#include "board_constants.h"
#include "persisten_service.h"

using namespace std;

class DiscoveringMode : public SonoffMode {

public:
  DiscoveringMode(PersistenceService* persistenceService);
private:
  AsyncTask* task;
  AsyncTask* broadcastTask;
  PersistenceService* persistenceService;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void initLoop();
  void handleRoot();
  String getSSID();
  String getPassword();
  void broadcastLoop();
  void sendBroadcast();
  void listeningAck();
  bool isACK(String message);
};
#endif //DISCOVERING_MODE_H