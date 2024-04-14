#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "board_constants.h"
#include "pairing_mode.h"

#define mode_t uint8_t

#define SPEED 115200

#define ROM_MEMORY_SIZE 512
#define MODE_ADDRESS 0x0

#define PAIRING_MODE 1

/* PAIRING DEFINITIONS ************************/
#ifndef APSSID
#define APSSID "Argensonoff"
#define APPSK ""
#define PAIRING_SERVER_PORT 80
#endif

mode_t mode = 1;

PairingMode pairingMode;
SonoffMode* currentMode;

ESP8266WebServer server(PAIRING_SERVER_PORT);

/* Util functions ********************/
uint8_t readValueFromEEPROM(int address) {
  return EEPROM.read(address);
}

void saveValueToEEPROM(int address, uint8_t value) {
  EEPROM.write(address, value);
  EEPROM.commit();
}

/* Setup Functions *****************/
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}
void setupParingMode() {
  WiFi.softAP(APSSID, APPSK);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");  
}
bool isValidMode(mode_t mode) {
  return mode == PAIRING_MODE;
}

SonoffMode* setupMode() {
  SonoffMode* modeSetup = &pairingMode;
  mode = readValueFromEEPROM(MODE_ADDRESS);
  if (!isValidMode(mode)) mode = PAIRING_MODE;
  saveValueToEEPROM(MODE_ADDRESS, mode);
  return modeSetup;
}

void setupMemory() {
  EEPROM.begin(ROM_MEMORY_SIZE);
}

void setupOutput() {
  pinMode(STATE_OUTPUT_RED_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_GREEN_PIN, OUTPUT);
  pinMode(STATE_OUTPUT_BLUE_PIN, OUTPUT);
  
  digitalWrite(STATE_OUTPUT_RED_PIN, L);
  digitalWrite(STATE_OUTPUT_GREEN_PIN, L);
  digitalWrite(STATE_OUTPUT_BLUE_PIN, L);
}

/*
void pairingModeLoop() {
  stateOutputPairingMode();
  server.handleClient();
}
*/

/* Main loop functions ****************/
SonoffMode* selectMode(mode_t mode) {
  if (PAIRING_MODE == mode) {
    return &pairingMode;
  }
  return nullptr;
}

void setup() {
  delay(1000);
  Serial.begin(SPEED);
  setupOutput();
  currentMode = setupMode();
  currentMode->setup();
}

void loop() {
  if (currentMode != nullptr) {
    currentMode->loop();
  }
}
