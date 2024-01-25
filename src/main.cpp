#include <Arduino.h>

#include "motor/motor.hpp"
#include "network/network.hpp"

void setup() {
  Serial.begin(9600);
  motor_init();
  setup_network();
}

void loop() {
  loop_network();
  delay(20);
}