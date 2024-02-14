#include <Arduino.h>

#include "motor/motor.hpp"
#include "network/network.hpp"
#include "sensors/sensor.hpp"
TaskHandle_t *th_p = (TaskHandle_t*)malloc(sizeof(TaskHandle_t) * 2);
void setup() {
  Serial.begin(9600);
  motor_init();
//   setup_network();
  sensors_init();
  xTaskCreatePinnedToCore(read_sensors_th1, "read_sensors_th", 4096, NULL, 1,
                          &th_p[1], 0);
}

void loop() {
//   loop_network();
  delay(20);
}