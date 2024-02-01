#ifndef DIY_WIFI_HPP
#define DIY_WIFI_HPP

#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "1029946339"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include "motor/motor.hpp"

extern WiFiMulti wifiMulti;
extern WebServer server;

void wifi_init();

void handleTest();

void handleForward();

void handleBackward();

void handleLeft();

void handleRight();

void handleStop();

void handleAction1();

void handleAction2();

void handleAction3();

void handleSetBit();

void handleClient();

#endif