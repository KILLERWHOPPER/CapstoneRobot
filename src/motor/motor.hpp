#ifndef MOTOR_HPP
#define MOTOR_HPP

#define motor_1_A 27 
#define motor_1_B 14 
#define motor_1_PWM 12
#define motor_2_A 26 
#define motor_2_B 25 
#define motor_2_PWM 13 

#define pwm_freq 1000
#define motor_speed 127  // out of 255

#include <Arduino.h>
#include <Ticker.h>
#include <esp32-hal-timer.h>
#include "sensor/sensor.hpp"

void motor_init();
void move_forward();
void move_backward();
void turn_left();
void turn_right();
void stop();
void move_distance(float distance);
void turn_angle(float angle);

#endif