#include <Arduino.h>

#include "motor/motor.hpp"
#include "web/test_wifi.hpp"

void setup() {
  Serial.begin(9600);
  motor_init();
  wifi_init();
}

void loop() {
  handleClient();
  delay(20);
}