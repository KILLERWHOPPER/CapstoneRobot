#include <Arduino.h>

#include "motor/motor.hpp"
#include "network/network.hpp"
#include "sensor/sensor.hpp"

// TaskHandle_t th_p[0];  // Task handle list (for now only 1 thread)

void setup() {
  Serial.begin(9600);
  // motor_init();
  // setup_network();
  sensors_init();
  // Create thread for the sensors
  // xTaskCreatePinnedToCore(read_sensors_th1, "Sensor Thread", 4096, NULL, 1, &th_p[0], 0);
}

void loop() {
  can_move_forward_test();
  // can_move_backward_test();
  // loop_network();
  delay(20);
}