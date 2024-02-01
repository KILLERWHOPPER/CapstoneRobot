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
  server.on("/set_bit", HTTP_POST, handleSetBit);
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

void handleSetBit() {
  server.send(200, "text/html", "Set bit");
    // String patharg = server.pathArg(0);
    // Serial.printf("Path: %s\n", patharg.c_str());
    String rawData = server.arg("plain");
    Serial.printf("Raw data: %s\n", rawData.c_str());

  for (int i = 0; i < 8; i++) {
    int curBit = rawData.charAt(i)-48;
    ledcWrite(i, curBit*100);
  }
  // TODO: Put control code here
  //Serial.printf("Bits: %s\n", bits);
  //Serial.printf("Set bit: %d, %d, %d, %d, %d, %d, %d, %d\n", bits[0], bits[1], bits[2], bits[3], bits[4], bits[5], bits[6], bits[7]);
}

void handleClient() {
  server.handleClient();
}