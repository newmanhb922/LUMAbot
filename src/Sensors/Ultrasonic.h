#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wiringPi.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
//#include "../MQTT_Comms/MQTTModule.h"

// these are the wiringPi pin definitions.
// see pinout.xyz/pinout/wiringpi for the corresponding rpi gpio pins
// echo pin can't be wired directly into raspberry pi
// have to use voltage divider circuit to generate 3.3 V from sensors 5 V output
#define ECHO_PIN            25
#define SENSOR_1_TRIG       6
#define SENSOR_2_TRIG       10
#define SENSOR_3_TRIG       11
#define SENSOR_4_TRIG       31
#define SENSOR_5_TRIG       26
#define SENSOR_6_TRIG       27
#define SENSOR_7_TRIG       28
#define SENSOR_8_TRIG       29
#define SPEED_OF_SOUND      343.8 // approximate speed of sound in 69.8 degree F air

int sensorCounter;

volatile float sensor1Val;
volatile float sensor2Val;
volatile float sensor3Val;
volatile float sensor4Val;
volatile float sensor5Val;
volatile float sensor6Val;
volatile float sensor7Val;
volatile float sensor8Val;

/// @brief Initializes pins for ultrasonic sensors
void UltrasonicInit();

/// @brief Sets up timer and starts sampling sensors
/// @param microSeconds interval in microseconds to trigger the timer
void StartSampling(int microSeconds);
#endif
