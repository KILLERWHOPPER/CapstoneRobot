#define MAX_RANG (520)
#define ADC_SOLUTION (1023.0)
#define THRESHOLD_DISTANCE (15) // Distance threshold in cm

#include "sensor.hpp"

// initialize variables
float distances[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float sensity[] = {0.0,0.0,0.0,0.0,0.0,0.0};
bool isClose = false;

void sensors_init() {
    pinMode(sensor_1, INPUT);
    pinMode(sensor_2, INPUT);
    pinMode(sensor_3, INPUT);
    pinMode(sensor_4, INPUT);
    pinMode(sensor_5, INPUT);
    pinMode(sensor_6, INPUT);    
}

void read_sensors_th1() {
    while(1){
        sensity[0] = analogRead(sensor_1);
        sensity[1] = analogRead(sensor_2);
        sensity[2] = analogRead(sensor_3);
        sensity[3] = analogRead(sensor_4);
        sensity[4] = analogRead(sensor_5);
        sensity[5] = analogRead(sensor_6);

        if(!isClose){
            for(int i = 0; i<6; i++){
            distances[i] = sensity[i]* MAX_RANG / ADC_SOLUTION;
            if (distances[i] <= THRESHOLD_DISTANCE){
                //Trigger sth
                stop();
                isClose = true;
                Serial.printf("Warning sensor: %d\n Distance = %d\n", i, distances[i]);
                break;
            }
        }
        }else{
            for(int i = 0; i<6; i++){
            distances[i] = sensity[i]* MAX_RANG / ADC_SOLUTION;
            if (distances[i] > THRESHOLD_DISTANCE){
                //Trigger sth
                isClose = true;
                //Serial.printf("Warning sensor: %d\n Distance = %d\n", i, distances[i]);
                continue;
                isClose = false;
            }
        }

        delay(1); // Small delay to maintain responsiveness
        }
    }
}