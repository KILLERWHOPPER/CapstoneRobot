#ifndef MOTOR_HPP
#define MOTOR_HPP

#define motor_1_A 27 // new board
#define motor_1_B 14 // new board
#define motor_1_PWM 12 // new board
#define motor_2_A 26 // new board
#define motor_2_B 25 // new board
#define motor_2_PWM 13 // new board

#define pwm_freq 1000
#define motor_speed 127  // out of 255

#include <Arduino.h>
#include <Ticker.h>
#include <esp32-hal-timer.h>
#include "sensor/sensor.hpp"

extern byte moving_dir;

void motor_init();
void move_forward();
void move_backward();
void turn_left();
void turn_right();
void stop();
void move_distance(float distance);
void turn_angle(float angle);

#endif