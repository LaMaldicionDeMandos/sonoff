#ifndef WORKIGN_MODE_H
#define WORKING_MODE_H

#include <arduino.h>
#include <stdint.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

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
  String clientId;
  String deviceId;
  String topicToSend;
  String topicToListen;

public:
  void setup() override;
  void loop() override;
  void end() override;

private:
  void configureMqtt(String config);
  String getSSID();
  String getPassword();
  String getNetSettingProperty(PersistenceService* persistenceService, String propertyName);
  String getMqttServerAddress(String config);
  uint32_t getMqttPort(String config);
  String getClientId(String config);
  String getDeviceId(String config);
  void reconnect();
  void mqttTopicsSetup();
};
#endif //WORKING_MODE_H