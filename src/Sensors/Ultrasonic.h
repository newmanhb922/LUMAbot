#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>

#define ECHO_PIN            26
#define SENSOR_1_TRIG       22
#define SENSOR_2_TRIG       24
#define SENSOR_3_TRIG       26
#define SENSOR_4_TRIG       28
#define SENSOR_5_TRIG       32
#define SENSOR_6_TRIG       36
#define SENSOR_7_TRIG       38
#define SENSOR_8_TRIG       40

int sensorCounter;

float sensor1Val;
float sensor2Val;
float sensor3Val;
float sensor4Val;
float sensor5Val;
float sensor6Val;
float sensor7Val;
float sensor8Val;

/// @brief Initializes pins for ultrasonic sensors
void UltrasonicInit();

/// @brief Sets up timer and starts sampling sensors
/// @param microSeconds interval in microseconds to trigger the timer
void StartSampling(int microSeconds);
#endif
