#ifndef SENSOR_HPP
#define SENSOR_HPP

#define sensor_1 15
#define sensor_2 2
#define sensor_3 4
#define sensor_4 33
#define sensor_5 32
#define sensor_6 35

#define THRESHOLD_DISTANCE (15)  // Distance threshold in cm
#define SOUND_SPEED 0.034

#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "motor/motor.hpp"

extern bool directions[];  // Forward, Backward, Left, Right

void sensors_init();
void read_sensors_th1();

#endif