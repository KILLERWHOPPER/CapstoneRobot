#include "motor.hpp"

byte moving_state = 0;

void motor_init() {
    pinMode(motor_1, OUTPUT);
    pinMode(motor_2, OUTPUT);
    pinMode(motor_3, OUTPUT);
    pinMode(motor_4, OUTPUT);
    pinMode(motor_5, OUTPUT);
    pinMode(motor_6, OUTPUT);
    pinMode(motor_7, OUTPUT);
    pinMode(motor_8, OUTPUT);
}

void move_forward() {
  analogWrite(motor_1, 100);
  analogWrite(motor_2, 100);
  analogWrite(motor_3, 100);
  analogWrite(motor_4, 0);
  analogWrite(motor_5, 100);
  analogWrite(motor_6, 100);
  analogWrite(motor_7, 100);
  analogWrite(motor_8, 100);
  moving_state = 1;
}

void move_backward() {
  analogWrite(motor_1, 100);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 100);
  analogWrite(motor_4, 100);
  analogWrite(motor_5, 100);
  analogWrite(motor_6, 100);
  analogWrite(motor_7, 100);
  analogWrite(motor_8, 100);
  moving_state = 2;
}

void turn_left() {
  analogWrite(motor_1, 100);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 100);
  analogWrite(motor_4, 0);
  analogWrite(motor_5, 0);
  analogWrite(motor_6, 0);
  analogWrite(motor_7, 0);
  analogWrite(motor_8, 0);
  moving_state = 3;
}

void turn_right() {
  analogWrite(motor_1, 100);
  analogWrite(motor_2, 100);
  analogWrite(motor_3, 100);
  analogWrite(motor_4, 100);
  analogWrite(motor_5, 100);
  analogWrite(motor_6, 100);
  analogWrite(motor_7, 100);
  analogWrite(motor_8, 100);
  moving_state = 4;
}

void stop() {
  analogWrite(motor_1, 0);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, 0);
  analogWrite(motor_5, 0);
  analogWrite(motor_6, 0);
  analogWrite(motor_7, 0);
  analogWrite(motor_8, 0);
  moving_state = 0;
}