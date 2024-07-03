#ifndef BOARD_CONSTANTS_H
#define BOARD_CONSTANTS_H

using namespace std;

#define L 0x0
#define H 0x1

#define LED_L 0x1
#define LED_H 0x0

#define PAIRING_MODE 1
#define DISCOVERING_MODE 2
#define CONFIG_MODE 3
#define WORKING_MODE 4
#define ERROR_MODE 5

#define STATE_OUTPUT_RED_PIN 5 //D1
#define STATE_OUTPUT_GREEN_PIN 4 //D2
#define STATE_OUTPUT_BLUE_PIN 14 //D5

#define RELAY_STATE_PIN 13 //D7
#define RELAY_SWITCH_PIN 12 //D6

#define UDP_BROADCAST_PORT 12357
#define BROADCAST_MESSAGE "IotProject:sonoff"
#define ACK_MESSAGE "ACK"

#define STATE_ON "on"
#define STATE_OFF "off"

#endif //BOARD_CONSTANTS_H