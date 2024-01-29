#include "motor.hpp"

byte moving_state = 0;

Ticker timer;

void motor_init() {
  // pinMode(motor_1, OUTPUT);
  // pinMode(motor_2, OUTPUT);
  // pinMode(motor_3, OUTPUT);
  // pinMode(motor_4, OUTPUT);
  // pinMode(motor_5, OUTPUT);
  // pinMode(motor_6, OUTPUT);
  // pinMode(motor_7, OUTPUT);
  // pinMode(motor_8, OUTPUT);
  ledcSetup(0, 800, 8);
  ledcAttachPin(motor_1, 0);
  ledcSetup(1, 800, 8);
  ledcAttachPin(motor_2, 1);
  ledcSetup(2, 800, 8);
  ledcAttachPin(motor_3, 2);
  ledcSetup(3, 800, 8);
  ledcAttachPin(motor_4, 3);
  ledcSetup(4, 800, 8);
  ledcAttachPin(motor_5, 4);
  ledcSetup(5, 800, 8);
  ledcAttachPin(motor_6, 5);
  ledcSetup(6, 800, 8);
  ledcAttachPin(motor_7, 6);
  ledcSetup(7, 800, 8);
  ledcAttachPin(motor_8, 7);
}

void move_forward() {
  //   analogWrite(motor_1, 100);
  //   analogWrite(motor_2, 100);
  //   analogWrite(motor_3, 100);
  //   analogWrite(motor_4, 0);
  //   analogWrite(motor_5, 100);
  //   analogWrite(motor_6, 100);
  //   analogWrite(motor_7, 100);
  //   analogWrite(motor_8, 100);
  ledcWrite(0, 100);
  ledcWrite(1, 100);
  ledcWrite(2, 100);
  ledcWrite(3, 0);
  ledcWrite(4, 100);
  ledcWrite(5, 100);
  ledcWrite(6, 100);
  ledcWrite(7, 100);
  moving_state = 1;
}

void move_forward_distance(float distance) {
  // we know from testing that robot speed is 36 cm/s
  move_forward();
  int delayTime = 1000 * distance / 36;
  Serial.printf("delayTime: %d ms\n", delayTime);
  timer.attach_ms(delayTime, stop);
}

void move_backward() {
  //   analogWrite(motor_1, 100);
  //   analogWrite(motor_2, 0);
  //   analogWrite(motor_3, 100);
  //   analogWrite(motor_4, 100);
  //   analogWrite(motor_5, 100);
  //   analogWrite(motor_6, 100);
  //   analogWrite(motor_7, 100);
  //   analogWrite(motor_8, 100);
  ledcWrite(0, 100);
  ledcWrite(1, 0);
  ledcWrite(2, 100);
  ledcWrite(3, 100);
  ledcWrite(4, 100);
  ledcWrite(5, 100);
  ledcWrite(6, 100);
  ledcWrite(7, 100);
  moving_state = 2;
}

void turn_left() {
  //   analogWrite(motor_1, 100);
  //   analogWrite(motor_2, 0);
  //   analogWrite(motor_3, 100);
  //   analogWrite(motor_4, 0);
  //   analogWrite(motor_5, 0);
  //   analogWrite(motor_6, 0);
  //   analogWrite(motor_7, 0);
  //   analogWrite(motor_8, 0);
  ledcWrite(0, 100);
  ledcWrite(1, 0);
  ledcWrite(2, 100);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  ledcWrite(5, 0);
  ledcWrite(6, 0);
  ledcWrite(7, 0);
  moving_state = 3;
}

void turn_right() {
  //   analogWrite(motor_1, 100);
  //   analogWrite(motor_2, 100);
  //   analogWrite(motor_3, 100);
  //   analogWrite(motor_4, 100);
  //   analogWrite(motor_5, 100);
  //   analogWrite(motor_6, 100);
  //   analogWrite(motor_7, 100);
  //   analogWrite(motor_8, 100);
  ledcWrite(0, 100);
  ledcWrite(1, 100);
  ledcWrite(2, 100);
  ledcWrite(3, 100);
  ledcWrite(4, 100);
  ledcWrite(5, 100);
  ledcWrite(6, 100);
  ledcWrite(7, 100);
  moving_state = 4;
}

void stop() {
  //   analogWrite(motor_1, 0);
  //   analogWrite(motor_2, 0);
  //   analogWrite(motor_3, 0);
  //   analogWrite(motor_4, 0);
  //   analogWrite(motor_5, 0);
  //   analogWrite(motor_6, 0);
  //   analogWrite(motor_7, 0);
  //   analogWrite(motor_8, 0);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
  ledcWrite(5, 0);
  ledcWrite(6, 0);
  ledcWrite(7, 0);
  moving_state = 0;
}