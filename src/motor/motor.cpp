#include "motor.hpp"
Ticker timer;
byte moving_dir =
    0;  // 0: stop, 1: forward, 2: backward, 3: turn left, 4: turn right

void motor_init() {
  pinMode(motor_1_A, OUTPUT);
  pinMode(motor_1_B, OUTPUT);
  pinMode(motor_1_PWM, OUTPUT);
  pinMode(motor_2_A, OUTPUT);
  pinMode(motor_2_B, OUTPUT);
  pinMode(motor_2_PWM, OUTPUT);
  stop();
  analogWrite(motor_1_PWM, motor_speed - 5);
  analogWrite(motor_2_PWM, motor_speed);
}

int cal_move_delay(float distance) {
    int delay = 1000 * distance / 36;
    return delay;
}

int cal_turn_delay(float angle) {
    int delay = angle * 600 / 90; 
    return delay;
}

void move_distance(float distance) {
  bool distanceCompleted = false; 
  while ((isClose == false) && (distanceCompleted == false)) {
    if (distance > 0) {
      if (can_move_forward() == true)
        move_forward();
      else 
        isClose = true;
    }
    if (distance < 0) {
      distance = 0 - distance;
      if (can_move_backward()) {
         move_backward();
      }
      else 
        isClose = true;
    }
    int delayTime = cal_move_delay(distance);
    timer.attach_ms(delayTime, stop);
    distanceCompleted = true;
  }
  stop();
}

void turn_angle(float angle) {
  if (angle > 0) {
    Serial.printf("The robot is turn right");
    turn_right();
  }
  // we know from testing that robot speed is 36 cm/s
  if (angle < 0) {
    Serial.printf("The robot is turn left");
    angle = 0 - angle;
    turn_left();
  }
  int delayTime = cal_turn_delay(angle);
    //   angle * 600 /
    //   90;  // we know from testing that a 90deg spin takes about 700ms
  Serial.printf("delayTime: %d ms\n", delayTime);
  timer.attach_ms(delayTime, stop);
  // delay(5000);
  // stop();
}

void move_forward() {
  digitalWrite(motor_1_A, LOW);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, LOW);
  moving_dir = 1;
}

void move_backward() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, LOW);
  digitalWrite(motor_2_A, LOW);
  digitalWrite(motor_2_B, HIGH);
  moving_dir = 2;
}

void turn_left() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, LOW);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, LOW);
  moving_dir = 3;
}

void turn_right() {
  digitalWrite(motor_1_A, LOW);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, LOW);
  digitalWrite(motor_2_B, HIGH);
  moving_dir = 4;
}

void stop() {
  digitalWrite(motor_1_A, HIGH);
  digitalWrite(motor_1_B, HIGH);
  digitalWrite(motor_2_A, HIGH);
  digitalWrite(motor_2_B, HIGH);
  moving_dir = 0;
}