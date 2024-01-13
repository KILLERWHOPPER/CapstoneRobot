#ifndef MOTOR_HPP
#define MOTOR_HPP

#define motor_1 2
#define motor_2 3
#define motor_3 4
#define motor_4 5
#define motor_5 6
#define motor_6 7
#define motor_7 8
#define motor_8 9

#include <Arduino.h>

extern byte moving_state;

void motor_init();
void move_forward();
void move_backward();
void turn_left();
void turn_right();
void stop();

#endif