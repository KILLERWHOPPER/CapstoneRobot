#ifndef WEB_HPP
#define WEB_HPP

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>

const char *ssid = "phone_hotspot";
const char *password = "dummy_pwd";
extern WebServer server;

void web_init();

#endif