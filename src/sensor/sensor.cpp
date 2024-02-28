#include "sensor/sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float sensity[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool directions[] = {false, false, false,
                     false};  // Forward, Backward, Left, Right
bool isClose = false;

void sensors_init() {
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(sensor_5, INPUT);
  pinMode(sensor_6, INPUT);
}

float cal_distance(float rawD) {
  // TODO: Calculate distance
  return rawD;
}

void read_sensors_th1(void *sensors_th1) {
  while (1) {
    isClose = false;
    sensity[0] = analogRead(sensor_1);
    sensity[1] = analogRead(sensor_2);
    sensity[2] = analogRead(sensor_3);
    sensity[3] = analogRead(sensor_4);
    sensity[4] = analogRead(sensor_5);
    sensity[5] = analogRead(sensor_6);

    int i = 0;
    for (float cur : sensity) {
      distances[i] = cal_distance(cur);
      i++;
    }

    for (int i = 0; i < 4; i++) {
      if (distances[i] < THRESHOLD_DISTANCE) {
        directions[i] = true;
        if(moving_dir == i+1) stop();
      } else {
        directions[i] = false;
      }
    }
    delay(100);
  }
}