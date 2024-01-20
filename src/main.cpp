#include <Arduino.h>

#include "motor/motor.hpp"
// #include "web/diy_wifi.hpp"
#include "network/network.hpp"

void setup() {
  Serial.begin(9600);
  motor_init();
  // wifi_init();
  setup();
}

void loop() {
  loop();
  delay(20);
}