#include "sensor/sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0};
float sensor_averages[] = {0.0, 0.0, 0.0};

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

void can_move_forward() {
  // printf(">>>>>>Entering sensor reading function \n");

  float values_sensor_1[10];
  float values_sensor_2[10];
  float values_sensor_3[10];

  for (int i = 0; i<10; i ++) {
    values_sensor_1[i] = analogRead(sensor_1); // forward
    delay(25);
    values_sensor_2[i] = analogRead(sensor_2); // forward
    delay(25);
    values_sensor_3[i] = analogRead(sensor_3); // forward
    delay(25);
  }

  // Compute average values for each sensor
  float sum_sensor_1 = 0.0;
  float sum_sensor_2 = 0.0;
  float sum_sensor_3 = 0.0;

  for (int i = 0; i < 10; i++) {
    sum_sensor_1 += values_sensor_1[i];
    sum_sensor_2 += values_sensor_2[i];
    sum_sensor_3 += values_sensor_3[i];
  }

  float average_sensor_1 = sum_sensor_1 / 10.0;
  float average_sensor_2 = sum_sensor_2 / 10.0;
  float average_sensor_3 = sum_sensor_3 / 10.0;

  // Array to store average values for each sensor
  sensor_averages[0] = average_sensor_1;
  sensor_averages[1] = average_sensor_2;
  sensor_averages[2] = average_sensor_3;

  for (int i = 0; i < 3; i ++) {
    distances[i] = cal_distance(sensor_averages[i]);
    printf("distance of sensor %d is %f \n", i+1, distances[i]);
    // delay(10);
  }

  if (distances[0] < 0 || distances[1] < 0 || distances[2] < 0) {
    noObstacle = false;
    printf("obstacle detected \n");
    // return false;
  }
  else {
    noObstacle = true;
    printf("no obstacle \n");
    // return true;
  }
}

bool can_move_backward() {
  // printf(" >>>>>>  Entering sensor reading function \n");

  float values_sensor_4[10];
  float values_sensor_5[10];
  float values_sensor_6[10];

  for (int i = 0; i<10; i ++) {
    values_sensor_4[i] = analogRead(sensor_4); // backward
    delay(25);
    values_sensor_5[i] = analogRead(sensor_5); // backward
    delay(25);
    values_sensor_6[i] = analogRead(sensor_6); // backward
    delay(25);
  }

  // Compute average values for each sensor
  float sum_sensor_4 = 0.0;
  float sum_sensor_5 = 0.0;
  float sum_sensor_6 = 0.0;

  for (int i = 0; i < 10; i++) {
    sum_sensor_4 += values_sensor_4[i];
    sum_sensor_5 += values_sensor_5[i];
    sum_sensor_6 += values_sensor_6[i];
  }

  float average_sensor_4 = sum_sensor_4 / 10.0;
  float average_sensor_5 = sum_sensor_5 / 10.0;
  float average_sensor_6 = sum_sensor_6 / 10.0;

  // Array to store average values for each sensor
  sensor_averages[0] = average_sensor_4;
  sensor_averages[1] = average_sensor_5;
  sensor_averages[2] = average_sensor_6;

  for (int i = 0; i < 3; i ++) {
    distances[i] = cal_distance(sensor_averages[i]);
    printf("distance of sensor %d is %f \n", i+4, distances[i]);
    // delay(10);
  }

  if (distances[0] < 1 || distances[1] < 1 || distances[2] < 1) {
    printf("obstacle detected \n");
    return false;
  }
  else {
    printf("no obstacle \n");
    return true;
  }
}