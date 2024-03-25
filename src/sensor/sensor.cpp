#include "sensor/sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float sensity[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
bool directions[] = {false, false};  // Forward, Backward
const char* sensorLabels[] = {"sensor_1 (forward)", "sensor_2 (forward)", "sensor_3 (forward)", "sensor_4 (backward)", "sensor_5 (backward)", "sensor_6 (backward)"};
bool isClose = false;
float para[5] = {0.01, 1.2, 5, 0.1, 0.0};  // q, r, x, p, k

void sensors_init() {
  Serial.begin(9600);
  // pinMode(sensor_1, INPUT);
  // pinMode(sensor_2, INPUT);
  // pinMode(sensor_3, INPUT);
  pinMode(sensor_4, INPUT);
  pinMode(sensor_5, INPUT);
  pinMode(sensor_6, INPUT);
}

float kalman_c(float* para, float measurement) {
  // q, r, x, p, k
  // 0, 1, 2, 3, 4
  float q = para[0];
  float r = para[1];
  float x = para[2];
  float p = para[3];
  float k = para[4];

  p += q;
  k = p / (p + r);
  x += k * (measurement - x);
  p = (1 - k) * p;

  if (fpclassify(q) != FP_NORMAL) return -1.0;
  if (fpclassify(r) != FP_NORMAL) return -1.0;
  if (fpclassify(x) != FP_NORMAL) return -1.0;
  if (fpclassify(p) != FP_NORMAL) return -1.0;
  if (fpclassify(k) != FP_NORMAL) return -1.0;

  para[0] = q;
  para[1] = r;
  para[2] = x;
  para[3] = p;
  para[4] = k;
  return x;
}

//TODO: apply karman filter


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
  float raw_k = 0;
  float distance;

  while (1) {
    raw=analogRead(sensor_6);
    raw_k = kalman_c(para,raw );
    distance = raw * MAX_RANG  / ADC_SOLUTION;
    // Print the average sensor reading
    // printf("%s detects: %f, %f \n", sensorLabels[5],raw, raw_k);
    Serial.print(">raw:");
    Serial.println(raw);
    Serial.print(">kalman:");
    Serial.println(raw_k);
    Serial.print(">distance:");
    Serial.println(distance);
    delay(1000);
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


void can_move_forward_test() {
  float values_sensor_1[10];
  float values_sensor_2[10];
  float values_sensor_3[10];
  float sensor_averages[3];

  while (1) {

    for (int i = 0; i<10; i ++) {
      values_sensor_1[i] = analogRead(sensor_1); // backward
      delay(25);
      values_sensor_2[i] = analogRead(sensor_2); // backward
      delay(25);
      values_sensor_3[i] = analogRead(sensor_3); // backward
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
      delay(10);
    }

    if (distances[0] < 1 || distances[1] < 1 || distances[2] < 1)
      printf("obstacle detected \n");
    else 
      printf("no obstacle \n");

    delay(1000);
  }
}

void can_move_backward_test() {
  //float raw_k[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  float values_sensor_4[10];
  float values_sensor_5[10];
  float values_sensor_6[10];
  float sensor_averages[3];

  while (1) {

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
      delay(10);
    }

    if (distances[0] < 1 || distances[1] < 1 || distances[2] < 1)
      printf("obstacle detected \n");
    else 
      printf("no obstacle \n");

    delay(1000);
  }
}