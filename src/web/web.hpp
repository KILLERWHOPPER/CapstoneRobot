#ifndef WEB_HPP
#define WEB_HPP

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>

extern const char *ssid;
extern const char *password;
extern WebServer _server;

void web_init();

#endif