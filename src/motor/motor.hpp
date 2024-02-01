#ifndef MOTOR_HPP
#define MOTOR_HPP

#define motor_1_A 13
#define motor_1_B 12
#define motor_1_PWM 14
#define motor_2_A 27
#define motor_2_B 26
#define motor_2_PWM 25

#define pwm_freq 2000
#define motor_speed 127 //out of 255

#include <Arduino.h>
#include <esp32-hal-timer.h>

extern byte moving_state;

void motor_init();
void move_forward();
void move_backward();
void turn_left();
void turn_right();
void stop();

#endif