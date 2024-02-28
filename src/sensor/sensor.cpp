#include "sensor/sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float sensity[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool directions[] = {false, false};  // Forward, Backward, Left, Right
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
  float distanceCm = rawD * SOUND_SPEED/2;
  return distanceCm;
}

// TODO : fix infinite loop 
void read_sensors_th1() {
  isClose = false;
  while (isClose == false) {
    sensity[0] = analogRead(sensor_1); // forward
    sensity[1] = analogRead(sensor_2); // forward
    sensity[2] = analogRead(sensor_3); // forward
    sensity[3] = analogRead(sensor_4); // backward
    sensity[4] = analogRead(sensor_5); // backward
    sensity[5] = analogRead(sensor_6); // backward

    int i = 0;
    for (float cur : sensity) {
      distances[i] = cal_distance(cur);
      printf("%f \n", distances[i]);
      i++;
    }

    // If currently moving forward
    if(moving_dir == 1) {
      if (distances[0] < THRESHOLD_DISTANCE || distances[1] < THRESHOLD_DISTANCE || distances[2] < THRESHOLD_DISTANCE) {
        directions[0] = false;
        isClose = true;
        stop();
      }
      else directions[0] = true;
    }

    // If currently moving backward
    if(moving_dir == 2) {
      if (distances[3] < THRESHOLD_DISTANCE || distances[4] < THRESHOLD_DISTANCE || distances[5] < THRESHOLD_DISTANCE) {        
        directions[1] = false;
        isClose = true;
        stop();
      }
      else directions[1] = true;
    }
    delay(100);
  }
}