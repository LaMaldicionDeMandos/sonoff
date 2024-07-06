#include "config_mode.h"

AsyncWebServer server(CONFIG_SERVER_PORT);

String getSettingPropertyConfigMode(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readNetConfig();
  JsonDocument doc;
  deserializeJson(doc, networkSetting);
  return doc[propertyName];
}

String ConfigMode::getSSID() {
  return getSettingPropertyConfigMode(this->persistenceService, "ssid");
}

String ConfigMode::getPassword() {
  return getSettingPropertyConfigMode(this->persistenceService, "password");
}

void ConfigMode::handleHttpHealth(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "OK");
}

void ConfigMode::handlePost(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  Serial.println("Ejecuto el post");
  const String body = parsePostBody(data, len);
  Serial.println("Body: " + body);
  this->persistenceService->saveMqttConfig(body);
  const String config = this->persistenceService->readMqttConfig();
  const String response = config; 
  request->send(201, "application/json", response);
  this->persistenceService->saveMode(WORKING_MODE);
}

ConfigMode::ConfigMode(PersistenceService* persistenceService) {
  this->persistenceService = persistenceService;
}

void ConfigMode::setup() {
  Serial.println("Setup Config Mode");
  const String ssid = this->getSSID();
  const String password = this->getPassword();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  uint8_t ttl = 40;
  while (WiFi.status() != WL_CONNECTED) {
    ttl--;
    Serial.print('.');
    delay(500);
    if (!ttl) {
      this->persistenceService->saveMode(ERROR_MODE);
      return;
    }
  }
  Serial.println(WiFi.localIP());
  server.on("/health", WebRequestMethod::HTTP_GET, [this](AsyncWebServerRequest *request) {
    this->handleHttpHealth(request); 
  });
  server.on("/", HTTP_POST, 
    [](AsyncWebServerRequest *request){}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    this->handlePost(request, data, len, index, total); 
  });
  server.begin();
  Serial.println("HTTP server started");
}

void ConfigMode::loop() {
  ledsScene.loop();
}

void ConfigMode::end() {
  Serial.println("Ending Config mode");
  server.end();
}
