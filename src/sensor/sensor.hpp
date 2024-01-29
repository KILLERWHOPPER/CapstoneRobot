#ifndef SENSOR_HPP
#define SENSOR_HPP

#define sensor_1 15
#define sensor_2 2
#define sensor_3 4
#define sensor_4 16
#define sensor_5 17
#define sensor_6 5

#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "motor/motor.hpp"

void sensors_init();
void read_sensors_th1();



#endif