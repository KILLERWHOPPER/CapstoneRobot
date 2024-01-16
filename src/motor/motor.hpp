#ifndef MOTOR_HPP
#define MOTOR_HPP

#define motor_1 13
#define motor_2 12
#define motor_3 14
#define motor_4 27
#define motor_5 26
#define motor_6 25
#define motor_7 33
#define motor_8 32

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