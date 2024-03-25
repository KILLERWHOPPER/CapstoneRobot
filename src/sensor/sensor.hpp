#ifndef SENSOR_HPP
#define SENSOR_HPP

#define sensor_1 14
#define sensor_2 27
#define sensor_3 26
#define sensor_4 32 // backward 
#define sensor_5 33 // backward
#define sensor_6 25 // backward

#define THRESHOLD_DISTANCE (15)  // Distance threshold in cm
#define MAX_RANG (520)
#define ADC_SOLUTION (4095) // 12-bit resolution

#define NUM_READINGS 20 // Number of readings to average

#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "motor/motor.hpp"

extern bool directions[];  // Forward, Backward, Left, Right
extern bool isClose;

void sensors_init();
void read_sensors_th1();
void simple_read_sensors();
bool can_move_forward();
bool can_move_backward();
void can_move_backward_test();
void can_move_forward_test();

#endif