#include "sensor/sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float sensity[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool directions[] = {false, false};  // Forward, Backward
const char* sensorLabels[] = {"sensor_1 (forward)", "sensor_2 (forward)", "sensor_3 (forward)", "sensor_4 (backward)", "sensor_5 (backward)", "sensor_6 (backward)"};
bool isClose = false;

void sensors_init() {
  Serial.begin(9600);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(sensor_5, INPUT);
  pinMode(sensor_6, INPUT);
}

float cal_distance(float rawD) {
  float distanceCm = ((rawD * MAX_RANG) / (ADC_SOLUTION));
  return distanceCm;
}

// TODO : fix infinite loop 
void read_sensors_th1() {
  isClose = false;
  while (isClose == false) {

    // Get the analog raw data
    sensity[0] = analogRead(sensor_1); // forward
    sensity[1] = analogRead(sensor_2); // forward
    sensity[2] = analogRead(sensor_3); // forward
    sensity[3] = analogRead(sensor_4); // backward
    sensity[4] = analogRead(sensor_5); // backward
    sensity[5] = analogRead(sensor_6); // backward

    // Convert in cm
    for (int i = 0; i < 6; i ++) {
      distances[i] = cal_distance(sensity[i]);
      printf("distance of sensor %d is %f \n", i, distances[i]);
    }

    // Handle motors accordingly
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

void simple_read_sensors() {
  float raw = 0;
  float distance;

  while (1) {
    raw = analogRead(sensor_5);
    distance = raw * MAX_RANG  / ADC_SOLUTION;
    // Print the average sensor reading
    printf("%s detects: %f \n", sensorLabels[5], raw);
    delay (10);
  }
}

bool can_move_forward() {
    // Get the analog raw data
    sensity[0] = analogRead(sensor_1); // forward
    sensity[1] = analogRead(sensor_2); // forward
    sensity[2] = analogRead(sensor_3); // forward

    // Convert in cm
    distances[0] = cal_distance(sensity[0]);
    distances[1] = cal_distance(sensity[1]);
    distances[2] = cal_distance(sensity[2]);

    printf("%s detects: %f \n", sensorLabels[0], distances[0]);
    printf("%s detects: %f \n", sensorLabels[1], distances[1]);
    printf("%s detects: %f \n", sensorLabels[2], distances[2]);

    if (distances[0] < THRESHOLD_DISTANCE || distances[1] < THRESHOLD_DISTANCE || distances[2] < THRESHOLD_DISTANCE)
      return false;
    else 
      return true;
}

bool can_move_backward() {
    // Get the analog raw data
    sensity[3] = analogRead(sensor_4); // backward
    sensity[4] = analogRead(sensor_5); // backward
    sensity[5] = analogRead(sensor_6); // backward

    // Convert in cm
    for (int i = 3; i < 6; i ++) {
      distances[i] = cal_distance(sensity[i]);
      printf("distance of sensor %d is %f \n", i, distances[i]);
    }

    if (distances[3] < THRESHOLD_DISTANCE || distances[4] < THRESHOLD_DISTANCE || distances[5] < THRESHOLD_DISTANCE)
      return false;
    else 
      return true;
}