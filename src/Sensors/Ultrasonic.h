#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>

#define ECHO_PIN            26
#define SENSOR_1_TRIG       22
#define SENSOR_2_TRIG       24
#define SENSOR_3_TRIG       26
#define SENSOR_4_TRIG       28
#define SENSOR_5_TRIG       32
#define SENSOR_6_TRIG       36
#define SENSOR_7_TRIG       38
#define SENSOR_8_TRIG       40

/// @brief Initializes pins for ultrasonic sensors
void UltrasonicInit();

/// @brief Sets up timer and starts sampling sensors
void BeginSampling();

/// @brief Samples the sensor value
/// @param sensorNum the number of the sensor to sample (1 - 8)
void SampleSensor(int sensorNum);
#endif