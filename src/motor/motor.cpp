#include "motor.hpp"
Ticker timer;

void motor_init() {
  pinMode(motor_1_A, OUTPUT);
  pinMode(motor_1_B, OUTPUT);
  pinMode(motor_1_PWM, OUTPUT);
  pinMode(motor_2_A, OUTPUT);
  pinMode(motor_2_B, OUTPUT);
  pinMode(motor_2_PWM, OUTPUT);
  stop();
  analogWrite(motor_1_PWM, motor_speed - 3);
  analogWrite(motor_2_PWM, motor_speed);
}

int cal_move_delay(float distance) {
  // we know from testing that robot speed is 36 cm/s
  int delay = 1000 * distance / 36;
  return delay;
}

int cal_turn_delay(float angle) {
  int delay = angle * 600 / 90; 
  return delay;
}

void move_distance(float distance) {
  if (distance > 0) {
      move_forward();
  }

  else if (distance < 0) {
    distance = 0 - distance;
    move_backward();
  }

  // compute time to move for required 
  int delayTime = cal_move_delay(distance);
  timer.attach_ms(delayTime, stop);
}

void turn_angle(float angle) {
  if (angle > 0) {
    Serial.printf("The robot is turn right");
    turn_right();
  }
  
  if (angle < 0) {
    Serial.printf("The robot is turn left");
    angle = 0 - angle;
    turn_left();
  }

  // compute angle
  int delayTime = cal_turn_delay(angle);
  timer.attach_ms(delayTime, stop);
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