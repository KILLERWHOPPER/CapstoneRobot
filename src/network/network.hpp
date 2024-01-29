#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <WiFi.h>
#include "motor/motor.hpp"

extern char ssid[];          // your network SSID (name)
extern char pass[];          // your network password
extern char server[];         // IP address of the server you want to connect to
extern int port;              // port number
extern int robot_id;

extern int status;            // the WiFi connection status
extern const int bufferSize;  // Adjust the buffer size based on your message size
extern char message[];        // Buffer to store incoming messages
extern WiFiClient client;      // WiFi client for communication

void registration();
void setup_network();
void loop_network();
void decodeMessage(String jsonString);
void handleCommand(String command, float data);

#endif // NETWORK_H