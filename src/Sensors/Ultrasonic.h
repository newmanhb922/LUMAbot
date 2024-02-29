#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>
#include <signal.h>

#define ECHO_PIN            26
#define SENSOR_1_TRIG       22
#define SENSOR_2_TRIG       24
#define SENSOR_3_TRIG       26
#define SENSOR_4_TRIG       28
#define SENSOR_5_TRIG       32
#define SENSOR_6_TRIG       36
#define SENSOR_7_TRIG       38
#define SENSOR_8_TRIG       40

int sensorCounter = 0;

unsigned int sensor1Val = 0;
unsigned int sensor2Val = 0;
unsigned int sensor3Val = 0;
unsigned int sensor4Val = 0;
unsigned int sensor5Val = 0;
unsigned int sensor6Val = 0;
unsigned int sensor7Val = 0;
unsigned int sensor8Val = 0;

/// @brief Initializes pins for ultrasonic sensors
void UltrasonicInit();

/// @brief Sets up timer and starts sampling sensors
/// @param microSeconds interval in microseconds to trigger the timer
void StartSampling(int microSeconds);
#endif