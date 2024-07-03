#include "WiFiClient.h"
#include "working_mode.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void WorkingMode::onChange(char* topic, uint8_t* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (length == 2 && (char)payload[0] == 'o' && (char)payload[1] == 'n') {
    Serial.println("SET ON");
    this->persistenceService->saveSwitch(H);
  } else if (length == 3 && (char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {
    Serial.println("SET OFF");
    this->persistenceService->saveSwitch(L);
  } else {
    Serial.println("SET ERROR");
  }
}

WorkingMode::WorkingMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

String WorkingMode::getNetSettingProperty(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readNetConfig();
  JsonDocument doc;
  deserializeJson(doc, networkSetting);
  return doc[propertyName];
}

String WorkingMode::getSSID() {
  return this->getNetSettingProperty(this->persistenceService, "ssid");
}

String WorkingMode::getPassword() {
  return this->getNetSettingProperty(this->persistenceService, "password");
}

String WorkingMode::getMqttServerAddress(String config) {
  JsonDocument doc;
  deserializeJson(doc, config);
  return doc["mqtt_broker"];
}

uint32_t WorkingMode::getMqttPort(String config) {
  JsonDocument doc;
  deserializeJson(doc, config);
  return doc["mqtt_port"];
}

String WorkingMode::getClientId(String config) {
  JsonDocument doc;
  deserializeJson(doc, config);
  return doc["mqtt_client_id"];
}

String WorkingMode::getDeviceId(String config) {
  JsonDocument doc;
  deserializeJson(doc, config);
  return doc["device_id"];
}

void WorkingMode::configureMqtt(String config) {
  Serial.println(config);
  String mqttServerAddress = this->getMqttServerAddress(config);
  Serial.println("MQTT Server Address: " + mqttServerAddress);

  uint32_t mqttServerPort = this->getMqttPort(config);
  Serial.println("MQTT Server Port: " + String(mqttServerPort));

  this->clientId = this->getClientId(config);
  Serial.println("ClientId: " + this->clientId);

  this->deviceId = this->getDeviceId(config);
  Serial.println("DeviceId: " + this->deviceId);

  client.setServer(mqttServerAddress.c_str(), (uint16_t)mqttServerPort);
  client.setCallback([this](char* topic, uint8_t* payload, unsigned int length) {
    this->onChange(topic, payload, length);
  });
}

void WorkingMode::sendCurrentStatus() {
  if (client.connected()) {
    String state = this->currentStatus ? STATE_ON : STATE_OFF;
    client.publish(this->topicToSend.c_str(), state.c_str());
  }
}

void WorkingMode::mqttTopicsSetup() {
  this->currentStatus = this->persistenceService->readSwitch();  
  this->topicToSend = "/iotProject/" + this->clientId + "/device/" + this->deviceId + "/state";
  this->topicToListen = "/iotProject/" + this->clientId + "/device/" + this->deviceId + "/set";
  client.subscribe(this->topicToListen.c_str());
  this->sendCurrentStatus();
}

void WorkingMode::reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(this->clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      this->mqttTopicsSetup();
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void WorkingMode::setup() {
  Serial.println("Setup Working Mode"); 
  digitalWrite(STATE_OUTPUT_GREEN_PIN, LED_H);

  const String ssid = this->getSSID();
  Serial.println("SSID: " + ssid);
  const String password = this->getPassword();
  Serial.println("Password: " + password);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.broadcastIP());

  const String config = this->persistenceService->readMqttConfig();
  this->configureMqtt(config);
}

void WorkingMode::manageChange() {
  uint8_t newState = this->persistenceService->readSwitch();
  if (newState != this->currentStatus) {
    Serial.println("Send state " + String(newState));
    this->currentStatus = newState;
    this->sendCurrentStatus();
  } 
}

void WorkingMode::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  this->manageChange();
}

void WorkingMode::end() {
  Serial.println("Ending Working mode");
  WiFi.disconnect();
}
