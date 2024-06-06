#include "config_mode.h"

ESP8266WebServer server(CONFIG_SERVER_PORT);

void wait_config_mode() {}

void on_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, H);
}

void off_c() {
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
}

String getSettingPropertyConfigMode(PersistenceService* persistenceService, String propertyName) {
  const String networkSetting = persistenceService->readConfig();
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

void ConfigMode::handleRoot() {
  Serial.println("llegó acá?");
  server.send(200, "text/plain", "OK");
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
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
  server.on("/healt", HTTPMethod::HTTP_GET, std::bind(&ConfigMode::handleRoot, this));
  server.keepAlive(false);
  server.begin();
  Serial.println("HTTP server started");
}

void ConfigMode::initLoop() {
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);

  AsyncTask* on700 = new AsyncTask(700, on_c);
  AsyncTask* off1400 = new AsyncTask(700, off_c);

  on700->concat(off1400);

  this->task = on700;
  this->task->start();
}

void ConfigMode::loop() {
  if(this->task != nullptr) this->task = this->task->update(); 
  else this->initLoop();
  server.handleClient();
}

void ConfigMode::end() {
  Serial.println("Ending Config mode");
  server.close();
}
