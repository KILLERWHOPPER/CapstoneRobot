#include <Arduino.h>

#include "motor/motor.hpp"
#include "network/network.hpp"
#include "sensor/sensor.hpp"

void setup() {
  Serial.begin(9600);
  motor_init();
  setup_network();
  sensors_init();
}

void loop() {
  loop_network();
  delay(500);
}