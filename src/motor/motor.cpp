#include "motor.hpp"

byte moving_state = 0;

void motor_init() {
  pinMode(motor_1_A, OUTPUT);
  pinMode(motor_1_B, OUTPUT);
  pinMode(motor_1_PWM, OUTPUT);
  pinMode(motor_2_A, OUTPUT);
  pinMode(motor_2_B, OUTPUT);
  pinMode(motor_2_PWM, OUTPUT);
  stop();
  ledcSetup(0, pwm_freq, 8);
  ledcAttachPin(motor_1_PWM, 0);
  ledcSetup(1, pwm_freq, 8);
  ledcAttachPin(motor_2_PWM, 1);
  ledcWrite(0, motor_speed);
  ledcWrite(1, motor_speed);
}

void move_forward() {
  digitalWrite(motor_1_A, LOW);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, LOW);
}

void move_backward() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, LOW);
  digitalWrite(motor_2_A, LOW);
  digitalWrite(motor_2_B, HIGH);
}

void turn_left() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, LOW);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, LOW);
}

void turn_right() {
  digitalWrite(motor_1_A, LOW);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, LOW);
  digitalWrite(motor_2_B, HIGH);
}

void stop() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, HIGH);
}