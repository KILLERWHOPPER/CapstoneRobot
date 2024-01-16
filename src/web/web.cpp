#include "web.hpp"

const char *ssid = "phone_hotspot";
const char *password = "dummy_pwd";

WebServer _server(80);

void web_init() {
    WiFi.begin(ssid, password);
    Serial.printf("Connecting to WiFi... ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.printf(".");
    }
    Serial.printf("\n");
    Serial.printf("Connected to WiFi!\n");
    Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
    //TODO: Not finished
}