#ifndef SENSOR_HPP
#define SENSOR_HPP

#define sensor_1 33 // forward (right)
#define sensor_2 32 // forward (middle)
#define sensor_3 35 // forward (left)
#define sensor_4 36 // backward (right)
#define sensor_5 39 // backward (middle)
#define sensor_6 34 // backward (left)

#define MAX_RANG (520)
#define ADC_SOLUTION (4095) // 12-bit resolution

#include <Arduino.h>
#include "motor/motor.hpp"

extern bool noObstacle;

void sensors_init();
void can_move_forward();
void can_move_backward();

#endif