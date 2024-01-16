#include "diy_wifi.hpp"

WiFiMulti wifiMulti;
WebServer server(80);

void wifi_init() {
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to %s ...", WIFI_SSID);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.printf("IP address: %s", WiFi.localIP().toString().c_str());
  Serial.println("Starting server...");
  server.on("/test", HTTP_GET, handleTest);
  server.on("/forward", HTTP_GET, handleForward);
  server.on("/backward", HTTP_GET, handleBackward);
  server.on("/left", HTTP_GET, handleLeft);
  server.on("/right", HTTP_GET, handleRight);
  server.on("/stop", HTTP_GET, handleStop);
  server.begin();
  Serial.println("Server started");
}

void handleForward() {
  server.send(200, "text/html", "Forward");
  move_forward();
  Serial.println("Forward");
}

void handleBackward() {
  server.send(200, "text/html", "Backward");
  move_backward();
  Serial.println("Backward");
}

void handleLeft() {
  server.send(200, "text/html", "Left");
  turn_left();
  Serial.println("Left");
}

void handleRight() {
  server.send(200, "text/html", "Right");
  turn_right();
  Serial.println("Right");
}

void handleStop() {
  server.send(200, "text/html", "Stop");
  stop();
  Serial.println("Stop");
}

void handleTest() {
  server.send(200, "text/html", "Test");

  // TODO: Put control code here
  Serial.println("Test");
}

void handleAction1() {
  server.send(200, "text/html", "Action 1");
  // TODO: Put control code here
  Serial.println("Action 1");
}

void handleAction2() {
  server.send(200, "text/html", "Action 2");
  // TODO: Put control code here
  Serial.println("Action 2");
}

void handleAction3() {
  server.send(200, "text/html", "Action 3");
  // TODO: Put control code here
  Serial.println("Action 3");
}

void handleClient() {
  server.handleClient();
}